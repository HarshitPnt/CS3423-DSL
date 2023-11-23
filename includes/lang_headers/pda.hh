#ifndef __pda_hh__
#define __pda_hh__
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace fsm
{
    class pda
    {
    private:
        // is the pda valid
        bool is_valid = false;

        // check if the pda is valid
        void checkValidity();

        // start state
        std::string q0;

        // states
        std::unordered_set<std::string> Q;

        // accept states
        std::unordered_set<std::string> F;

        // input alphabet
        std::unordered_set<std::string> S;

        // Transition function : Q-input x S-input x S-stack --> Q-output x S-stack
        std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>>> delta;

    public:
        pda();
        ~pda();
        bool insert_state(std::string);
        bool remove_state(std::string);
        bool insert_alphabet(std::string, std::string);
        bool remove_alphabet(std::string);
        bool insert_final(std::string);
        bool remove_final(std::string);
        bool add_transition(std::string, std::string, std::string, std::string, std::string);
        bool remove_transition(std::string, std::string, std::string, std::string, std::string);
        bool change_start(std::string);
        bool simulate(std::string);
        void out();
    };
}
#endif