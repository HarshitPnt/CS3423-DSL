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
            Q.insert(state);
            q0 = state;
            
        }

        void change_accept_state(std::string state) {
            string temp = q0;
            Q.erase(temp);
            Q.insert(state);
            q0 = state;
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
        }
        void delete_state(std::string state) {
            if (Q.find(state) == false) {
                return;
            }
            if(F.find(state)==true){
                F.erase(state);
            }
            if (q0 == state) {
                error_t("Cannot delete start state");
            }
            Q.erase(state);

        }

        void delete_transition(std::string state, char input, char stack_top) {
            if (delta.find(state) == delta.end()) {
                return;
            }
            if (delta[state].find(input) == delta[state].end()) {
                return;
            }
            if (delta[state][input].find(stack_top) == delta[state][input].end()) {
                return;
            }
            delta[state][input].erase(stack_top);

        }


        bool is_valid() {
            if (Q.empty() || Sigma.empty() || Gamma.empty() || delta.empty() || q0.empty() || F.empty()) {
                return false;
            }

            if (Q.find(q0) == Q.end()) {
                return false;
            }

            for (auto state : F) {
                if (Q.find(state) == Q.end()) {
                    return false;
                }
            }

            for (auto state : Q) {
                for (auto input : Sigma) {
                    if (delta[state].find(input) == delta[state].end()) {
                        return false;
                    }
                }
            }

            for (auto state : Q) {
                for (auto input : Sigma) {
                    for (auto stack_top : Gamma) {
                        if (delta[state][input].find(stack_top) == delta[state][input].end()) {
                            return false;
                        }
                    }
                }

            }
        }

        void change_start_state(std::string state) {
            Q.insert(state);
            string temp = q0;
            Q.erase(temp);
            q0 = state;

        }

       void add_accept_state(std::string state) {
            Q.insert(state);
            F.insert(state);
        }

       void remove_accept_state(std::string state) {
          
           if(Q.find(state)==true){

            if (F.find(state) == true) {
                F.erase(state);
                Q.erase(state);
            }
            
           }
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


      void delete_pda() {
        
            Q.clear();
            Sigma.clear();
            Gamma.clear();
            delta.clear();
            q0.clear();
            F.clear();


        }

            return F.find(curr_state) != F.end();
        }
    };
}