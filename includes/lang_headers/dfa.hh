// should define a dfa class
// header guards
#ifndef __dfa_hh__
#define __dfa_hh__
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>

namespace fsm
{
    class dfa
    {
    public:
        void insert_state(std::string);
        void remove_state(std::string);
        void insert_alphabet(std::string, std::string);
        void remove_alphabet(std::string);
        void insert_final(std::string);
        void remove_final(std::string);
        void add_transition(std::string, std::string, std::string);
        void remove_transition(std::string, std::string, std::string);
        void change_start(std::string);
        bool simulate(std::string);
        void out();
        ~dfa();
        dfa();

    private:
        bool is_valid = false;
        bool checkValidity();
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> delta;
        std::string q0;
        std::unordered_set<std::string> F;
        std::unordered_map<std::string, std::string> S;
        std::set<std::string> Q;
        bool findState(std::string state);
        bool findAlphabet(std::string alphabet);
    };

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

} // namespace fsm

#endif