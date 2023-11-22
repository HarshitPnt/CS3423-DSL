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
        bool add_transition(std::string, std::string, std::string);
        bool remove_transition(std::string, std::string, std::string);
        bool change_start(std::string);
        bool simulate(std::string);
        void out();
        ~dfa();
        dfa();

    private:
        bool is_valid = false;
        void checkValidity();
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> delta;
        std::string q0;
        std::unordered_set<std::string> F;
        std::unordered_map<std::string, std::string> S;
        std::set<std::string> Q;
        bool findState(std::string state);
        bool findAlphabet(std::string alphabet);
    };

} // namespace fsm

#endif