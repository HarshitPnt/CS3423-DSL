#include "../../includes/lang_headers/nfa.hh"
#include <iostream>

namespace fsm
{
    std::string epsilon = "\\e";
    nfa::nfa()
    {
        this->q0 = "";
    }

    bool nfa::insert_state(std::string state)
    {
        if (this->Q.find(state) != this->Q.end())
            return false;
        this->Q.insert(state);
        return true;
    }

    bool nfa::remove_state(std::string state)
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
        return true;
    }

    bool nfa::insert_alphabet(std::string alphabet, std::string val)
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
                    throw std::runtime_error("Ambiguous alphabet");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Runtime error: " << e.what() << "\n";
            throw e;
        }
        this->S[alphabet] = val;
        return true;
    }

    bool nfa::remove_alphabet(std::string alphabet)
    {
        if (alphabet.length() == 0)
            return false;
        auto it = this->S.find(alphabet);
        if (it == this->S.end())
            return false;

        this->S.erase(it);
        for (auto &d : this->delta)
        {
            for (auto a : d.second)
            {
                if (a.first == alphabet)
                {
                    d.second.erase(a.first);
                }
            }
        }
        return true;
    }

    bool nfa::insert_final(std::string state)
    {
        if (this->Q.find(state) == this->Q.end())
            return false;
        if (this->F.find(state) != this->F.end())
            return false;
        this->F.insert(state);
        return true;
    }

    bool nfa::remove_final(std::string state)
    {
        if (this->F.find(state) == this->F.end())
            return false;
        this->F.erase(state);
        return true;
    }

    bool nfa::add_transition(std::string state, std::string alphabet, std::string next_state)
    {
        if (this->Q.find(state) == this->Q.end())
            return false;
        if (this->Q.find(next_state) == this->Q.end())
            return false;
        if (alphabet != epsilon && this->S.find(alphabet) == this->S.end())
            return false;
        if (this->delta.find(state) == this->delta.end())
        {
            std::unordered_multimap<std::string, std::string> temp;
            temp.insert({alphabet, next_state});
            this->delta[state] = temp;
        }
        else
        {
            auto it = this->delta[state].equal_range(alphabet);
            for (auto i = it.first; i != it.second; i++)
            {
                if (i->second == next_state)
                    return false;
            }
            this->delta[state].insert({alphabet, next_state});
        }
        return true;
    }

    bool nfa::remove_transition(std::string state, std::string alphabet, std::string next_state)
    {
        if (this->Q.find(state) == this->Q.end())
            return false;
        if (this->Q.find(next_state) == this->Q.end())
            return false;
        if (alphabet != epsilon && this->S.find(alphabet) == this->S.end())
            return false;
        if (this->delta.find(state) == this->delta.end())
            return false;
        auto it = this->delta[state].equal_range(alphabet);
        for (auto i = it.first; i != it.second; i++)
        {
            if (i->second == next_state)
            {
                this->delta[state].erase(i);
                return true;
            }
        }
        return false;
    }

    bool nfa::change_start(std::string state)
    {
        if(state.length()==0)
            return false;
        if (this->Q.find(state) == this->Q.end())
            return false;
        this->q0 = state;
        return true;
    }

    nfa::~nfa()
    {
        this->Q.clear();
        this->S.clear();
        this->delta.clear();
        this->F.clear();
    }

    bool nfa::simulate(std::string input)
    {
        if (this->q0.length() == 0)
            return false;
        std::unordered_set<std::string> current_states;
        std::unordered_set<std::string> next_states;
        current_states.insert(this->q0);
        for (auto i : input)
        {
            for (auto state : current_states)
            {
                auto it = this->delta[state].equal_range(std::string(1, i));
                for (auto j = it.first; j != it.second; j++)
                {
                    next_states.insert(j->second);
                }
            }
            current_states = next_states;
            next_states.clear();
        }
        for (auto i : current_states)
        {
            if (this->F.find(i) != this->F.end())
                return true;
        }
        return false;
    }
} // namespace fsm