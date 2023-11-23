#include "../../includes/fsm.hh"

namespace fsm
{
    // Convert a regular expression to a DFA

    nfa reg_to_nfa(regex reg)
    {
        if (reg.is_valid() == false)
            throw std::runtime_error("Invalid regex");
        std::string str = reg.str;
        int state = 0;
        nfa n;
        n.insert_state(std::to_string(state));
        while (str.length() != 0)
        {
            // if(str[0] == '('){
            //     int i = 1;
            //     int count = 1;
            //     while(count != 0){
            //         if(str[i] == '(')
            //             count++;
            //         else if(str[i] == ')')
            //             count--;
            //         i++;
            //     }
            //     std::string temp = str.substr(1, i-2);
            //     str = str.substr(i);
            //     nfa temp_nfa = reg_to_nfa(regex(temp));
            //     n.insert_nfa(temp_nfa, std::to_string(state));
            //     state += temp_nfa.Q.size();
            //     n.insert_state(std::to_string(state));
            //     n.add_transition(std::to_string(state-1), "epsilon", std::to_string(state));
            //     state++;
            // }
            // else if(str[0] == '*'){
            //     n.add_transition(std::to_string(state-1), "epsilon", std::to_string(state));
            //     n.add_transition(std::to_string(state), "epsilon", std::to_string(state-1));
            //     str = str.substr(1);
            // }
            // else if(str[0] == '|'){
            //     n.insert_state(std::to_string(state));
            //     n.add_transition(std::to_string(state-1), "epsilon", std::to_string(state));
            //     state++;
            //     str = str.substr(1);
            // }
            // else if(str[0] == '+'){
            //     n.add_transition(std::to_string(state-1), "epsilon", std::to_string(state));
            //     str = str.substr(1);
            // }
            // else if(str[0] == '?'){
            //     n.add_transition(std::to_string(state-1), "epsilon", std::to_string(state));
            //     n.add_transition(std::to_string(state-1), "epsilon", std::to_string(state));
            //     str = str.substr(1);
            // }
            // else{
            //     n.insert_state(std::to_string(state));
            //     n.insert_alphabet(std::string(1, str[0]), std::string(1, str[0]));
            //     n.add_transition(std::to_string(state-1), std::string(1, str[0]), std::to_string(state));
            //     state++;
            //     str = str.substr(1);
            // }
        }
        return n;
    }

    dfa nfa_to_dfa(nfa n)
    {
    }

    dfa reg_to_dfa(regex reg)
    {
        std::string str = reg.str;
        // nfa n = reg_to_nfa(reg);
        // return nfa_to_dfa(n);
    }

    pda cfg_to_pda(cfg c)
    {
    }
} // namespace fsm