#include "../../includes/lang_headers/dfa.hh"
#include <string>
#include <iostream>

namespace fsm
{
    dfa::dfa()
    {
        this->q0 = "";
    }

    bool dfa::insert_state(std::string state)
    {
        if (this->Q.find(state) != this->Q.end())
            return false;
        this->Q.insert(state);
        is_valid = false;
        return true;
    }

    bool dfa::remove_state(std::string state)
    {
        if (this->Q.find(state) == this->Q.end())
            return false;
        this->Q.erase(state);
        if (this->q0 == state)
        {
            this->q0 = "";
        }
        if (this->F.find(state) != this->F.end())
        {
            this->F.erase(state);
        }
        for (auto d : this->delta)
        {
            if (d.first == state)
            {
                delta.erase(d.first);
                continue;
            }
            for (auto a : d.second)
            {
                if (a.second == state)
                {
                    d.second.erase(a.first);
                }
            }
        }
        checkValidity();
        return true;
    }

    bool dfa::insert_alphabet(std::string alphabet, std::string val)
    {
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
            this->S[alphabet] = val;
            is_valid = false;
            return true;
        }
        catch (std::exception &e)
        {
            std::cerr << "Runtime Error: " << e.what() << '\n';
            return false;
        }
    } // namespace fsm

    // removing alphabet will remove all transitions with that alphabet
    bool dfa::remove_alphabet(std::string alphabet)
    {
        auto it = this->S.find(alphabet);
        bool temp = !(this->S.end() == this->S.erase(it));

        if (!temp)
            return false;

        for (auto d : this->delta)
        {
            if (d.second.find(alphabet) != d.second.end())
                d.second.erase(alphabet);
        }
        checkValidity();
        return temp;
    }

    bool dfa::insert_final(std::string state)
    {
        if (this->F.find(state) != this->F.end())
            return false;
        this->F.insert(state);
        return true;
    }

    bool dfa::remove_final(std::string state)
    {
        if (this->F.find(state) == this->F.end())
            return false;
        this->F.erase(state);
        return true;
    }

    bool dfa::add_transition(std::string state, std::string alphabet, std::string next_state)
    {
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
        if (this->delta.find(state) == this->delta.end())
        {
            return false;
        }
        else
        {
            if (this->delta[state].find(alphabet) == this->delta[state].end())
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
        if (this->Q.find(state) == this->Q.end())
            return false;
        this->q0 = state;
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
                if (a.second.compare(0, val.length(), val) == 0)
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
        if (this->Q.empty() || this->S.empty() || this->F.empty() || this->q0.empty() || this->delta.size() == this->Q.size())
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
}