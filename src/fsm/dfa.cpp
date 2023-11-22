#include "../../includes/fsm.hh"

namespace fsm
{
    dfa::dfa()
    {
        this->q0 = "";
    }

    void dfa::insert_state(std::string state)
    {
        this->Q.insert(state);
    }

    void dfa::remove_state(std::string state)
    {
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
    }

    void dfa::insert_alphabet(std::string alphabet, std::string val)
    {
        this->S[alphabet] = val;
    }

    void dfa::remove_alphabet(std::string alphabet)
    {
        this->S.erase(alphabet);
        for (auto d : this->delta)
        {
            if (d.second.find(alphabet) != d.second.end())
            {
                d.second.erase(alphabet);
            }
        }
    }

    void dfa::insert_final(std::string state)
    {
        this->F.insert(state);
    }

    void dfa::remove_final(std::string state)
    {
        this->F.erase(state);
    }

    void dfa::add_transition(std::string state, std::string alphabet, std::string next_state)
    {
        if (this->Q.find(state) == this->Q.end())
        {
            this->insert_state(state);
        }
        if (this->Q.find(next_state) == this->Q.end())
        {
            this->insert_state(next_state);
        }
        this->delta[state][alphabet] = next_state;
    }
}