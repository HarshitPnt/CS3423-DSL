#include "../../includes/lang_headers/cfg.hh"

#include <iostream>

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
            this->T[alias] = val;
            this->T_vals.insert(val);
            // check for prefixes/suffixes (to be done)
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
            // check if production exists
            if (this->isProduction(initial_state, rhs))
                throw std::runtime_error("Production already exists");
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
                for (auto rhs = production.second.begin(); rhs != production.second.end(); ++rhs)
                {
                    if ((*rhs).find("T_" + alias) != std::string::npos)
                        production.second.erase(rhs);
                }
            }
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
            // need to remove this non-terminal from map
            this->N.remove(nterm);
            // remove all productions which have this non-terminal
            this->P.erase(nterm);
            for (auto &production : this->P)
            {
                for (auto rhs = production.second.begin(); rhs != production.second.end(); ++rhs)
                {
                    if ((*rhs).find("NT_" + nterm) != std::string::npos)
                        production.second.erase(rhs);
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
                if (production_right[0] != '%') // non_terminal
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

    bool cfg::is_terminal(std::string terminal)
    {
        if (this->T.find(terminal) != this->T.end())
            return true;
        return false;
    }

    int cfg::is_terminal(std::string terminal, std::string val)
    {
        if (this->T_vals.find(terminal))
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
}
