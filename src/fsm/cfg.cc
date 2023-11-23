#include "../../includes/lang_headers/cfg.hh"

#include <iostream>
#include <regex>

std::string &trim(std::string &s, const char *t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

namespace fsm
{
    cfg::cfg()
    {
        this->start = "";
        this->T = std::unordered_map<std::string, std::string>();
        this->N = o_set<std::string>();
        this->P = std::unordered_map<std::string, std::vector<std::string>>();
        this->T_vals = o_set<std::string>();
    }

    cfg::~cfg()
    {
        this->T.clear();
        this->N.~o_set();
        this->P.clear();
        this->T_vals.~o_set();
    }

    bool cfg::add_T(std::string alias, std::string val)
    {
        int x = this->is_terminal(alias, val);
        if (x) // 0 if not 1 if terminal with same name and 2 if with same value
        {
            if (x == 1)
                std::cerr << "Terminal " << alias << "  already exists\n ";
            else
                std::cerr << "Terminal " << val << "  already exists\n ";
            return false;
        }
        else
        {
            // check if this val is a prefix of any other val
            for (auto it = this->T_vals.set.begin(); it != this->T_vals.set.end(); ++it)
            {
                if ((*it).find(val) == 0)
                {
                    std::cerr << "Terminal " << val << " is a prefix of " << (*it) << '\n';
                    return false;
                }
                if (val.find((*it)) != std::string::npos)
                {
                    std::cerr << "Terminal " << val << " contains " << (*it) << '\n';
                    return false;
                }
            }
            this->T[alias] = val;
            this->T_vals.insert(val);
            return true;
        }
    }

    bool cfg::add_N(std::string nt)
    {
        if (this->is_non_terminal(nt))
        {
            std::cerr << "Non-terminal " << nt << "  already exists\n ";
            return false;
        }
        else
        {
            this->N.insert(nt);
            return true;
        }
    }

    bool cfg::add_P(std::string production)
    {
        // parse this production
        std::string initial_state, production_right;
        try
        {
            production = trim(production);
            if (production.find("->") == std::string::npos || production.find("->") == 0 || production.find("->") == production.size() - 1)
                throw std::runtime_error("Invalid production");
            initial_state = production.substr(0, production.find("->"));
            production_right = production.substr(production.find("->") + 2);
            initial_state = trim(initial_state);
            if (!this->is_non_terminal(initial_state))
                throw std::runtime_error("Invalid production: " + initial_state + " is not a non-terminal");
            // now parse the right string
            // rhs is a string of ${id}, id, \e
            production_right = trim(production_right);
            std::string rhs = parseProduction(production_right);
            rhs = trim(rhs);
            if (rhs == "")
                return false;
            // check if production exists
            if (this->isProduction(initial_state, rhs))
                throw std::runtime_error("Production already exists");
            std::cout << "HERE adding " << rhs << std::endl;
            this->P[initial_state].push_back(rhs);
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    bool cfg::change_start(std::string start)
    {
        if (this->is_non_terminal(start))
        {
            this->start = start;
            return true;
        }
        else
            std::cerr << "Invalid start state\n";
        return false;
    }

    bool cfg::remove_T(std::string alias)
    {
        if (this->is_terminal(alias))
        {
            // need to remove this terminal from map
            std::string val = this->T[alias];
            this->T.erase(alias);
            // remove all productions which have this terminal
            for (auto &production : this->P)
            {
                std::cout << production.first << std::endl;
                std::cout << production.second.size() << std::endl;
                for (int i = 0; i < production.second.size(); i++)
                {
                    std::cout << production.second[i] << std::endl;
                    if (production.second[i].find("T_" + alias) != std::string::npos)
                        production.second.erase(production.second.begin() + i);
                }
            }
            std::cout << "Removed " << alias << " " << val << std::endl;
            this->T_vals.remove(val);
            return true;
        }
        else
        {
            std::cerr << "Terminal " << alias << " does not exist\n";
            return false;
        }
    }

    bool cfg::remove_N(std::string nterm)
    {
        if (this->is_non_terminal(nterm))
        {
            if (nterm == this->start)
            {
                std::cerr << "Cannot remove start state\n";
                return false;
            }
            // need to remove this non-terminal from map
            this->N.remove(nterm);
            // remove all productions which have this non-terminal
            this->P.erase(nterm);
            for (auto &production : this->P)
            {
                for (auto i = 0; i < production.second.size(); ++i)
                {
                    if (production.second[i].find("NT_" + nterm) != std::string::npos)
                        production.second.erase(production.second.begin() + i);
                }
            }
            return true;
        }
        else
        {
            std::cerr << "Non-terminal " << nterm << " does not exist\n";
            return false;
        }
    }

    bool cfg::remove_P(std::string production)
    {
        // parse this production
        std::string initial_state, production_right;
        try
        {
            production = trim(production);
            if (production.find("->") == std::string::npos || production.find("->") == 0 || production.find("->") == production.size() - 1)
                throw std::runtime_error("Invalid production");
            initial_state = production.substr(0, production.find("->"));
            production_right = production.substr(production.find("->") + 2);
            initial_state = trim(initial_state);
            if (!this->is_non_terminal(initial_state))
                throw std::runtime_error("Invalid production: " + initial_state + " is not a non-terminal");
            // now parse the right string
            // rhs is a string of ${id}, id, \e
            production_right = trim(production_right);
            std::string rhs = parseProduction(production_right);
            if (!this->isProduction(initial_state, rhs))
                throw std::runtime_error("Production does not exist");
            // find the production
            for (auto it = this->P[initial_state].begin(); it != this->P[initial_state].end(); ++it)
            {
                if ((*it) == rhs)
                {
                    this->P[initial_state].erase(it);
                    break;
                }
            }
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    std::string cfg::parseProduction(std::string production_right)
    {
        try
        {
            if (production_right == "\\e") // epsilon transition
            {
                // here we need to remove the epsilon transition
                std::string rhs = "T_\\e";
                return rhs;
            }
            else
            {
                std::string rhs = "";
                while (production_right.length())
                {
                    if (production_right[0] == '%') // non_terminal
                    {
                        // extract the non terminal
                        size_t end = production_right.find_first_of("}");
                        std::string non_terminal = production_right.substr(2, end - 2);
                        if (!this->is_non_terminal(non_terminal))
                            throw std::runtime_error("Invalid production: " + non_terminal + " is not a non-terminal");
                        rhs += "NT_" + non_terminal + " ";
                        production_right = production_right.substr(end + 1);
                    }
                    else
                    {
                        size_t end = production_right.find_first_of("}");
                        std::string terminal = production_right.substr(2, end - 2);
                        if (!this->is_terminal(terminal))
                            throw std::runtime_error("Invalid production: " + terminal + " is not a terminal");
                        rhs += "T_" + terminal + " ";
                        production_right = production_right.substr(end + 1);
                    }
                }
                return trim(rhs);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return "";
        }
    }

    bool cfg::is_terminal(std::string terminal)
    {
        if (this->T.find(terminal) != this->T.end())
            return true;
        return false;
    }

    int cfg::is_terminal(std::string terminal, std::string val)
    {
        if (this->T.find(terminal) != this->T.end())
            return 1;
        if (this->T_vals.find(val))
            return 2;
        return 0;
    }

    bool cfg::is_non_terminal(std::string nterm)
    {
        if (this->N.find(nterm))
            return true;
        return false;
    }

    bool cfg::isProduction(std::string initial_state, std::string rhs)
    {
        // check if production exists
        for (auto production : this->P[initial_state])
        {
            if (production == rhs)
                return true;
        }
        return false;
    }

    std::string replaceText(std::string str, std::string pattern, std::string replacement)
    {
        std::regex regexPattern(pattern);
        return std::regex_replace(str, regexPattern, replacement);
    }

    cfg cfg::_CNF()
    {
        // fetch all the productions and add non-terminals for terminals
        CNF = new cfg();
        CNF->add_N("@start");
        CNF->change_start("@start");
        // add all non-terminals
        for (auto &nterm : this->N.set)
        {
            CNF->N.insert(nterm);
        }
        // fetch terminals
        for (auto &term : this->T)
        {
            CNF->add_N(term.first);
        }
        // add start production
        CNF->add_P(CNF->start + " -> " + "NT_" + this->start);
        CNF->out();
        // for all terminals add productions
        for (auto &term : this->T)
        {
            CNF->add_P(term.first + " -> " + term.second);
        }
        // add all productions
        std::unordered_map<std::string, std::string> new_nterm;
        long long int new_count = 0;
        for (auto &production : this->P)
        {
            for (auto &rhs : production.second)
            {
                // before change all terminals to non-terminals
                for (auto &term : this->T)
                {
                    rhs = replaceText(rhs, std::string("T_"), std::string("NT_"));
                }
                // check if rhs is two non-terminals or less
                size_t first = rhs.find("NT_");
                size_t second = rhs.find("NT_", first + 1);
                if (second == std::string::npos)
                {
                    // only one non-terminal
                    CNF->add_P(production.first + " -> " + rhs);
                    continue;
                }
                size_t third = rhs.find("NT_", second + 1);
                if (third == std::string::npos)
                {
                    // only two non-terminals
                    CNF->add_P(production.first + " -> " + rhs);
                    continue;
                }
                // extract last two non-terminals
                while (true)
                {
                    size_t end = rhs.find_last_of("NT_");
                    size_t second_last = rhs.find_last_of("NT_", end - 1);
                    if (second_last == std::string::npos)
                    {
                        // only two non-terminals
                        break;
                    }
                    std::string last_2 = rhs.substr(second_last, end - second_last + 3);
                    last_2 = trim(last_2);
                    // check if this non terminal exists
                    if (new_nterm.find(last_2) == new_nterm.end())
                    {
                        // add this non-terminal
                        new_nterm[last_2] = "NT_" + std::string("@") + std::to_string(new_count);
                        new_count++;
                        std::string new_char = new_nterm[last_2];
                        rhs = replaceText(rhs, last_2, new_char);
                    }
                    else
                    {
                        // this non-terminal already exists
                        std::string new_char = new_nterm[last_2];
                        rhs = replaceText(rhs, last_2, new_char);
                    }
                }
                rhs = trim(rhs);
                CNF->add_P(production.first + " -> " + rhs);
            }
        }
        // eliminate empty transitions
        while (true)
        {
            bool flag = false;
            for (auto &production : CNF->P)
            {
                for (auto &rhs : production.second)
                {
                    if (rhs == "T_\\e")
                    {
                        // empty transition
                        CNF->remove_P(production.first + " -> " + rhs);
                        if (CNF->P[production.first].size() == 0)
                        {
                            // remove this non-terminal
                            CNF->remove_N(production.first);
                        }
                        // find all productions which have this non-terminal in rhs
                        for (auto &production2 : CNF->P)
                        {
                            for (auto &rhs2 : production2.second)
                            {
                                if (rhs2.find(std::string("NT_") + production.first) != std::string::npos)
                                {
                                    // this production has this non-terminal
                                    // check if only one non-terminal
                                    size_t first = rhs2.find_last_of("NT_");
                                    if (first == 0)
                                    {
                                        // only one non-terminal
                                        CNF->add_P(production2.first + " -> T_\\e");
                                        if (CNF->P[production.first].size() == 0)
                                        {
                                            // remove this non-terminal
                                            CNF->remove_P(production2.first + " -> " + rhs2);
                                        }
                                        flag = true;
                                    }
                                    else
                                    {
                                        // more than one non-terminal
                                        size_t first = rhs2.find("NT_" + production.first);
                                        size_t second = rhs2.find("NT_" + production.first, first + 1);
                                        if (second == std::string::npos)
                                        {
                                            // only one non-terminal
                                            std::string rhs_new = replaceText(rhs2, "NT_" + production.first, "");
                                            rhs_new = trim(rhs_new);
                                            CNF->add_P(production2.first + " -> " + rhs_new);
                                        }
                                        else
                                        {
                                            if (is_non_terminal(production.first))
                                            {
                                                // more than one non-terminal
                                                std::string rhs_new = rhs2.substr(0, second - 1);
                                                rhs_new = trim(rhs_new);
                                                CNF->add_P(production2.first + " -> " + rhs_new);
                                                rhs_new = rhs2.substr(second);
                                                rhs_new = trim(rhs_new);
                                                CNF->add_P(production2.first + " -> " + rhs_new);
                                                // epsilon transition
                                                CNF->add_P(production2.first + " -> T_\\e");
                                                flag = true;
                                            }
                                            else
                                            {
                                                CNF->add_P(production2.first + " -> " + "T_\\e");
                                                CNF->remove_P(production2.first + " -> " + rhs2);
                                                flag = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (!flag)
                    break;
            }
        }
        // eliminate unit transitions
        // check all productions
        for (auto &production : CNF->P)
        {
            for (auto &rhs : production.second)
            {
                if (rhs.find_last_of("NT_") == 0)
                {
                    // unit transition
                    CNF->remove_P(production.first + " -> " + rhs);
                    // find all productions with rhs NT
                    for (auto &rhs2 : CNF->P[rhs.substr(3)])
                    {
                        CNF->add_P(production.first + " -> " + rhs2);
                    }
                }
            }
        }
        return *CNF;
    }

    void cfg::out()
    {
        // displaying information about CFG
        std::cout << "CFG:\n";
        std::cout << "Number of non-terminals: " << this->N.set.size() << "\n";
        std::cout << "Number of terminals: " << this->T.size() << "\n";
        std::cout << "Start state: " << this->start << "\n";
        std::cout << "Number of productions: ";
        int productions = 0;
        for (auto &production : this->P)
        {
            productions += production.second.size();
        }
        std::cout << productions << "\n";
        std::cout << "Non-terminals: ";
        for (auto &nterm : this->N.set)
        {
            std::cout << nterm << " ";
        }
        std::cout << "\n";
        std::cout << "Terminals: ";
        for (auto &term : this->T)
        {
            std::cout << term.first << ":" << term.second << " ";
        }
        std::cout << "\n";
        std::cout << "Productions:\n";
        for (auto &production : this->P)
        {
            for (auto &rhs : production.second)
            {
                std::cout << production.first << " -> " << rhs << "\n";
            }
        }
        std::cout << "T_vals: ";
        for (auto &term : this->T_vals.set)
        {
            std::cout << term << " ";
        }
        std::cout << "\n";
    }

}
