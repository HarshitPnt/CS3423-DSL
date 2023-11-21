#include <regex.h>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <map>
#include <iostream>

namespace fsm
{

    template <typename T>
    class o_set
    {
    public:
        std::set<T> set;
        int size();
        bool find(T);
        void insert(T);
        void remove(T);
        bool empty();
        void del();
        void out();
        ~o_set();
        o_set();
    };

    template <typename T>
    class u_set
    {
    public:
        std::unordered_set<T> set;
        int size();
        bool find(T);
        void insert(T);
        void remove(T);
        bool empty();
        void del();
        void out();
        ~u_set();
        u_set();
    };

    class dfa
    {
        std::set<std::string> Q;
        std::unordered_map<std::string, std::string> S;
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> delta;
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
        ~dfa();
        dfa();
    };

    class regex
    {
        regex_t reg;
        std::string str;
        bool simulate(std::string);
        ~regex();
        regex();
    };

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