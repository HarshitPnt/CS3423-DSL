#ifndef __pda_hh__
#define __pda_hh__
#include <string>
#include <stack>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace fsm
{
    class pda
    {
    private:
        // start state
        std::string q0;

        // states
        std::unordered_set<std::string> Q;

        // accept states
        std::unordered_set<std::string> F;

        // input alphabet
        std::unordered_map<std::string, std::string> S;

        // stack alphabet
        std::unordered_map<std::string, std::string> T;

        // Transition function : Q-input x S-input x S-stack --> Q-output x S-stack
        std::unordered_map<std::string, std::unordered_multimap<std::pair<std::string, std::string>, std::pair<std::string, std::string>>> delta;

    public:
        pda();
        ~pda();
        bool insert_state(std::string);
        bool remove_state(std::string);
        bool insert_alphabet(std::string, std::string);
        bool remove_alphabet(std::string);
        bool insert_stack(std::string, std::string);
        bool remove_stack(std::string);
        bool insert_final(std::string);
        bool remove_final(std::string);
        bool insert_alphabetransition(std::string, std::string, std::string, std::string, std::string);
        bool remove_transition(std::string, std::string, std::string, std::string, std::string);
        bool change_start(std::string);
        bool simulate(std::string);
        bool simulate_helper(std::vector<std::string>, int, std::string, std::stack<std::string>, std::unordered_multimap<int, std::string>);
        void out();
    };
}
#endif