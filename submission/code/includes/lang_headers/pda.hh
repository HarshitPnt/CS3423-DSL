#ifndef __pda_hh__
#define __pda_hh__

#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>

namespace fsm
{
    class pda
    {
    public:
        std::string q0;
        std::unordered_set<std::string> Q;
        std::unordered_map<std::string, std::string> S;
        std::unordered_set<std::string> F;
        std::unordered_map<std::string, std::string> T;
        std::unordered_map<std::string, std::set<std::vector<std::string>>> delta;

        pda();
        ~pda();
        bool insert_state(std::string); //
        bool remove_state(std::string);
        bool insert_alphabet(std::string, std::string); //
        bool remove_alphabet(std::string);
        bool insert_final(std::string); //
        bool remove_final(std::string);
        bool insert_stack_symbol(std::string, std::string); //
        bool remove_stack_symbol(std::string);
        bool change_start(std::string);
        bool simulate(std::string);
        bool simulate_helper(std::string, int, std::set<std::pair<int, std::string>> &, std::stack<std::string> &, std::vector<std::string> &); //
        bool insert_transition(std::string, std::string, std::string, std::string, std::string);                                                //
        void out();
    };
} // namespace fsm
#endif