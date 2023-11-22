// defines a class for non-deterministic finite automata
// header guard
#ifndef __nfa_hh__
#define __nfa_hh__
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>

namespace fsm
{

    class nfa
    {
        std::set<std::string> Q;
        std::unordered_map<std::string, std::string> S;
        std::unordered_map<std::string, std::unordered_multimap<std::string, std::string>> delta;
        std::string q0;
        std::unordered_set<std::string> F;
        void insert_state(std::string);
        void remove_state(std::string);
        void insert_alphabet(std::string, std::string);
        void remove_alphabet(std::string, std::string);
        void insert_final(std::string);
        void remove_final(std::string);
        void add_transition(std::string, std::string, std::string);
        void remove_transition(std::string, std::string, std::string);
        void change_start(std::string);
        bool simulate(std::string);
        void out();
        ~nfa();
        nfa();
    };

} // namespace fsm

#endif