#include "../../includes/lang_headers/dfa.hh"
#include <iostream>

namespace fsm
{
    dfa::dfa()
    {
        this->q0 = "";
    }

    bool dfa::insert_state(std::string state)
    {
        if (state.length() == 0)
            return false;
        if (this->Q.find(state) != this->Q.end())
            return false;
        this->Q.insert(state);
        is_valid = false;
        return true;
    }

    bool dfa::remove_state(std::string state)
    {
        if (state.length() == 0)
            return false;
        if (this->Q.find(state) == this->Q.end())
            return false;
        if (this->q0 == state)
        {
            this->q0 = "";
        }
        if (this->F.find(state) != this->F.end())
        {
            this->F.erase(state);
        }
        for (auto it = this->delta.begin(); it != this->delta.end();)
        {
            if (it->first == state)
            {
                it = this->delta.erase(it);
                continue;
            }
            for (auto a = it->second.begin(); a != it->second.end();)
            {
                if (a->second == state)
                {
                    a = it->second.erase(a);
                }
                else
                {
                    a++;
                }
            }
            it++;
        }
        this->Q.erase(state);
        checkValidity();
        return true;
    }

    bool dfa::insert_alphabet(std::string alphabet, std::string val)
    {
        if (alphabet.length() == 0 || val.length() == 0)
            return false;
        if (this->S.find(alphabet) != this->S.end())
            return false;
        try
        {
            for (auto d : this->S)
            {
                if (val.compare(0, d.second.length(), d.second) == 0 || d.second.compare(0, val.length(), val) == 0)
                {
                    throw std::runtime_error("Ambiguous alphabet");
                }
            }
        }
        catch (std::exception &e)
        {
            std::cerr << "Runtime Error: " << e.what() << '\n';
            throw e;
        }
        this->S[alphabet] = val;
        is_valid = false;
        return true;
    }

    bool dfa::remove_alphabet(std::string alphabet)
    {
        if (alphabet.length() == 0)
            return false;
        if (this->S.find(alphabet) == this->S.end())
            return false;

        for (auto &d : this->delta)
        {
            if (d.second.find(alphabet) != d.second.end())
            {
                d.second.erase(alphabet);
            }
        }
        checkValidity();
        return true;
    }

    bool dfa::insert_final(std::string state)
    {
        if (state.length() == 0)
            return false;
        if (this->Q.find(state) == this->Q.end())
            return false;
        else if (this->F.find(state) != this->F.end())
            return false;
        this->F.insert(state);
        return true;
    }

    bool dfa::remove_final(std::string state)
    {
        if (state.length() == 0)
            return false;
        if (this->F.find(state) == this->F.end())
            return false;
        this->F.erase(state);
        return true;
    }

    bool dfa::add_transition(std::string state, std::string alphabet, std::string next_state)
    {
        if (state.length() == 0 || alphabet.length() == 0 || next_state.length() == 0)
            return false;
        if ((this->Q.find(state) == this->Q.end()) || (this->Q.find(next_state) == this->Q.end()) || (this->S.find(alphabet) == this->S.end()))
            return false;
        if (this->delta.find(state) == this->delta.end())
        {
            this->delta[state] = std::unordered_map<std::string, std::string>();
            this->delta[state][alphabet] = next_state;
            checkValidity();
        }
        else
        {
            if (this->delta[state].find(alphabet) != this->delta[state].end())
                return false;
            this->delta[state][alphabet] = next_state;
            checkValidity();
        }
        return true;
    }

    bool dfa::remove_transition(std::string state, std::string alphabet, std::string next_state)
    {
        if (state.length() == 0 || alphabet.length() == 0 || next_state.length() == 0 || this->Q.find(state) == this->Q.end() || this->Q.find(next_state) == this->Q.end() || this->S.find(alphabet) == this->S.end())
            return false;
        else
        {
            if (this->delta[state].find(alphabet) == this->delta[state].end())
                return false;
            else if (this->delta[state][alphabet] != next_state)
                return false;
            if (this->delta[state].size() == 1)
                this->delta.erase(state);
            else
                this->delta[state].erase(alphabet);
            checkValidity();
            return true;
        }
    }

    bool dfa::change_start(std::string state)
    {
        if (state.length() == 0)
            return false;
        if (this->Q.find(state) == this->Q.end())
            return false;
        this->q0 = state;
        checkValidity();
        return true;
    }

    bool dfa::simulate(std::string input)
    {
        if (!this->is_valid)
            return false;
        std::string curr_state = this->q0;
        std::string val = "";
        std::string alphabet = "";
        for (auto c : input)
        {
            val += c;
            for (auto a : this->S)
            {
                if (a.second == val)
                {
                    alphabet = a.first;
                    break;
                }
            }
            if (!alphabet.empty())
            {
                curr_state = this->delta[curr_state][alphabet];
                val = "";
                alphabet = "";
            }
        }
        if (!val.empty())
            return false;

        if (this->F.find(curr_state) == this->F.end())
            return false;
        return true;
    }

    void dfa::checkValidity()
    {
        if (this->Q.empty() || this->S.empty() || this->F.empty() || this->q0.empty() || this->delta.size() != this->Q.size())
        {
            this->is_valid = false;
            return;
        }
        for (auto d : this->delta)
        {
            if (d.second.size() != this->S.size())
            {
                this->is_valid = false;
                return;
            }
        }
        this->is_valid = true;
        return;
    }

    dfa::~dfa()
    {
        this->delta.clear();
        this->F.clear();
        this->Q.clear();
        this->S.clear();
    }

    void dfa::out()
    {
        std::cout << "\n---DFA Details---\n";

        if (!this->is_valid)
            std::cout << "\nDFA is not valid\n";
        else
            std::cout << "\nDFA is valid\n";
        std::cout << "\nStates: \n";
        for (auto q : this->Q)
        {
            std::cout << q << " ";
        }
        std::cout << "\n";
        std::cout << "\ninput ( Token : Sigma ): \n";
        for (auto s : this->S)
        {
            std::cout << s.first << " : " << s.second << std::endl;
        }
        std::cout << "\n";
        std::cout << "Accept States: \n";
        for (auto f : this->F)
        {
            std::cout << f << " ";
        }
        std::cout << "\n";
        std::cout << "\nq0: " << this->q0 << "\n";
        std::cout << "\nTransition Function ( state -> nextState on token) : \n";
        for (auto d : this->delta)
        {
            for (auto a : d.second)
                std::cout << d.first << " -> " << a.second << " on " << a.first << "\n";
        }
        std::cout << "\n";
        std::cout << "-----------------\n";
    }

    dfa dfa::operator!()
    {
        dfa d;
        d.Q = this->Q;
        d.S = this->S;
        d.q0 = this->q0;
        d.F = this->Q;
        for (auto f : this->F)
        {
            d.F.erase(f);
        }
        d.delta = this->delta;
        return d;
    }

    dfa dfa::operator+(dfa &other)
    {
        dfa d;
        for (auto q : this->Q)
        {
            insert_state("1@" + q);
            for (auto q : other.Q)
            {
                insert_state("2@" + q);
            }
            for (auto s : this->S)
            {
            }
        }
    }
}