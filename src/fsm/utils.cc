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
        // if(n.get_start() == "")
        //     throw std::runtime_error("NFA has no start state");
        // dfa dfa;
        // std::map<std::set<std::string>, std::string> stateNames;
        // std::queue<std::set<std::string>> statesQueue;

        // std::set<std::string> startState = {n.get_start()};
        // statesQueue.push(startState);
        // stateNames[startState] = "q0";
        // dfa.insert_state("q0");
        // dfa.change_start("q0");

        // while (!statesQueue.empty())
        // {
        //     std::set<std::string> currentState = statesQueue.front();
        //     statesQueue.pop();

        //     for (auto &symbol : n.get_alphabet())
        //     {
        //         std::set<std::string> newState;
        //         for (auto &state : currentState)
        //         {
        //             std::set<std::string> reachable = n.get_reachable(state, symbol);
        //             newState.insert(reachable.begin(), reachable.end());
        //         }

        //         if (!newState.empty() && stateNames.find(newState) == stateNames.end())
        //         {
        //             std::string newStateName = "q" + std::to_string(stateNames.size());
        //             stateNames[newState] = newStateName;
        //             dfa.insert_state(newStateName);
        //             statesQueue.push(newState);

        //             if (n.is_final(*newState.begin()))
        //             {
        //                 dfa.insert_final(newStateName);
        //             }
        //         }

        //         if (!newState.empty())
        //         {
        //             dfa.add_transition(stateNames[currentState], symbol, stateNames[newState]);
        //         }
        //     }
        // }

        // return dfa;
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