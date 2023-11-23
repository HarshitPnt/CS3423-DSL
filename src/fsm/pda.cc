#include "../../includes/lang_headers/pda.hh"

#include <iostream>
#include <stack>
#include <map>
#include <set>

namespace fsm {
    class pda {
        std::set<std::string> Q; 
        std::set<char> Sigma; 
        std::set<char> Gamma; 
        std::map<std::string, std::map<char, std::map<char, std::pair<std::string, std::string>>>> delta; // transition function
        std::string q0; 
        char Z0; 
        std::set<std::string> F; 

    public:
        pda() : Z0('$') {} 

        void add_state(std::string state) {
            Q.insert(state);
        }

        void set_start_state(std::string state) {
            q0 = state;
        }

        void add_accept_state(std::string state) {
            F.insert(state);
        }

        void add_transition(std::string state, char input, char stack_top, std::string next_state, std::string stack_op) {
            Sigma.insert(input);
            Gamma.insert(stack_top);
            delta[state][input][stack_top] = {next_state, stack_op};
        }

        bool simulate(std::string input) {
            std::string curr_state = q0;
            std::stack<char> st;
            st.push(Z0);

            for (char c : input) {
                if (delta[curr_state][c].empty()) {
                    return false;
                }

                char stack_top = st.top();
                if (delta[curr_state][c].find(stack_top) == delta[curr_state][c].end()) {
                    return false;
                }

                std::pair<std::string, std::string> transition = delta[curr_state][c][stack_top];
                curr_state = transition.first;
                std::string stack_op = transition.second;

                
                if (!stack_op.empty()) {
                    if (stack_op[0] == 'P') { 
                        st.push(stack_op[1]);
                    } else if (stack_op[0] == 'R') { 
                        st.pop();
                        st.push(stack_op[1]);
                    } else if (stack_op == "POP") { 
                        st.pop();
                    }
                }
            }

            
            return F.find(curr_state) != F.end();
        }
    };
}