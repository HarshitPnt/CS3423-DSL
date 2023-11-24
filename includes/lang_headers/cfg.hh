#ifndef __cfg_hh__
#define __cfg_hh__
#include "set.hh"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
namespace fsm
{
    class cfg
    {
    public:
        // non-terminals, terminals, start, productions
        bool insert_alphabet(std::string, std::string);
        bool insert_state(std::string);
        bool add_P(std::string);
        bool change_start(std::string);
        bool remove_T(std::string);
        bool remove_N(std::string);
        bool remove_P(std::string);
        bool test_string(std::string);
        void print_reduction_CYK(std::string);
        void out();
        ~cfg();
        cfg();
        cfg _CNF();

    private:
        cfg *CNF;
        std::unordered_map<std::string, std::string> T;
        o_set<std::string> T_vals;
        o_set<std::string> N;
        std::string start;
        std::unordered_map<std::string, std::vector<std::string>> P; // "NT_nterm T_term"
        bool is_terminal(std::string);
        int is_terminal(std::string, std::string);
        bool is_non_terminal(std::string);
        std::string parseProduction(std::string);
        bool isProduction(std::string, std::string);
        bool _add_P(std::string);
    };
} // namespace fsm
#endif