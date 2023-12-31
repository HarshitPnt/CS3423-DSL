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
    public:
        bool insert_state(std::string);
        bool remove_state(std::string);
        bool insert_alphabet(std::string, std::string);
        std::unordered_map<std::string, std::string> get_alphabet();
        bool remove_alphabet(std::string);
        bool insert_final(std::string);
        bool is_final(std::string);
        bool remove_final(std::string);
        bool insert_transition(std::string, std::string, std::string);
        bool remove_transition(std::string, std::string, std::string);
        bool change_start(std::string);
        std::string get_start();
        std::unordered_map<std::string, std::set<std::string>> eClosure();
        std::unordered_set<std::string> get_reachable(std::string, std::string);
        bool simulate(std::string);
        nfa *operator!();
        friend std::ostream &operator<<(std::ostream &os, const nfa &a)
        {
            a.out();
            return os;
        }
        void out() const;
        ~nfa();
        nfa();

        // private:
        std::set<std::string> Q;
        std::unordered_map<std::string, std::string> S;
        std::unordered_map<std::string, std::unordered_multimap<std::string, std::string>> delta;
        std::string q0;
        std::unordered_set<std::string> F;
    };

} // namespace fsm

#endif