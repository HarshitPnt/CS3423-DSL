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
        bool insert_state(std::string);
        bool remove_state(std::string);
        bool insert_alphabet(std::string, std::string);
        bool remove_alphabet(std::string);
        bool insert_final(std::string);
        bool remove_final(std::string);
        bool insert_transitions(std::string, std::string, std::string);
        bool remove_transition(std::string, std::string, std::string);
        bool change_start(std::string);
        bool simulate(std::string);
        bool __simulate(std::string);
        void out();
        dfa *operator!();
        ~dfa();
        dfa();

        // private:
        // is the dfa valid
        bool is_valid = false;

        // check if the dfa is valid
        void checkValidity();

        // Transition function : Q-input x S-input -> Q-output
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> delta;

        // Q0 : initial state
        std::string q0;

        // F : final states
        std::unordered_set<std::string> F;

        // S : alphabet
        std::unordered_map<std::string, std::string> S;

        // Q : set of states
        std::unordered_set<std::string> Q;

        // bool findState(std::string state);
        // bool findAlphabet(std::string alphabet);
    };

} // namespace fsm

#endif