#include "../../includes/fsm.hh"
#include <queue>
#include <map>

namespace fsm
{
    // Convert a regular expression to a DFA

    nfa reg_to_nfa(regex reg, int state = 0)
    {
        if (reg.is_valid() == false)
            throw std::runtime_error("Invalid regex");
        std::string str = reg.str;
        nfa n;
        n.insert_state(std::to_string(state));
        while (str.length() != 0)
        {
            // if (str[0] == '(')
            // {
            //     int i = 1;
            //     int count = 1;
            //     while (count != 0)
            //     {
            //         if (str[i] == '(')
            //             count++;
            //         else if (str[i] == ')')
            //             count--;
            //         i++;
            //     }
            //     std::string temp = str.substr(1, i - 2);
            //     str = str.substr(i);
            //     nfa temp_nfa = reg_to_nfa(regex(temp), state + 1);
            // }
        }
        return n;
    }
    // Convert a NFA to a DFA
    dfa nfa_to_dfa(nfa n)
    {
        dfa d;
        int len = n.Q.size();
        
        auto Eclosure = n.eClosure();
        
    }

    dfa reg_to_dfa(regex reg)
    {
        nfa n = reg_to_nfa(reg);
        return nfa_to_dfa(n);
    }

    pda cfg_to_pda(cfg c)
    {
    }
} // namespace fsm