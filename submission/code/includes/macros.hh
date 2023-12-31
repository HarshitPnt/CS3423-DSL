#include "fsm.hh"

#ifndef __macros_hh__
#define __macros_hh__
#define o_size(S) S.size()
#define u_size(S) S.size()
#define o_insert(S, x) S.insert(x)
#define u_insert(S, x) S.insert(x)
#define o_find(S, x) S.find(x)
#define u_find(S, x) S.find(x)
#define o_remove(S, x) S.remove(x)
#define u_remove(S, x) S.remove(x)
#define o_output(S) S.out()
#define u_output(S) S.out()
#define dfa_insert_state(D, x) D.insert_state(x)
#define dfa_remove_state(D, x) D.remove_state(x)
#define dfa_insert_alphabet(D, x, y) D.insert_alphabet(x, y)
#define dfa_remove_alphabet(D, x) D.remove_alphabet(x)
#define dfa_insert_transition(D, x, y, z) D.insert_transition(x, y, z)
#define dfa_remove_transition(D, x, y, z) D.remove_transition(x, y, z)
#define dfa_change_start(D, x) D.change_start(x)
#define dfa_insert_accept(D, x) D.insert_final(x)
#define dfa_remove_accept(D, x) D.remove_final(x)
#define dfa_simulate(D, x) D.simulate(x)
#define dfa_output(D) D.out()
#define nfa_insert_state(N, x) N.insert_state(x)
#define nfa_remove_state(N, x) N.remove_state(x)
#define nfa_insert_alphabet(N, x, y) N.insert_alphabet(x, y)
#define nfa_remove_alphabet(N, x) N.remove_alphabet(x)
#define nfa_insert_transition(N, x, y, z) N.insert_transition(x, y, z)
#define nfa_remove_transition(N, x, y, z) N.remove_transition(x, y, z)
#define nfa_change_start(N, x) N.change_start(x)
#define nfa_insert_accept(N, x) N.insert_final(x)
#define nfa_remove_accept(N, x) N.remove_final(x)
#define nfa_simulate(N, x) N.simulate(x)
#define nfa_output(N) N.out()
#define nfa_to_dfa(N) (*nfa_to_dfa(N))
#define cfg_add_T(C, x, y) C.insert_alphabet(x, y)
#define cfg_add_N(C, x) C.insert_state(x)
#define cfg_add_P(C, x) C.add_P(x)
#define cfg_add_S(C, x) C.change_start(x)
#define cfg_remove_T(C, x) C.remove_T(x)
#define cfg_remove_N(C, x) C.remove_N(x)
#define cfg_remove_P(C, x) C.remove_P(x)
#define cfg_output(C) C.out()
#define pda_insert_state(P, x) P.insert_state(x)
#define pda_remove_state(P, x) P.remove_state(x)
#define pda_insert_input_alphabet(P, x, y) P.insert_alphabet(x, y)
#define pda_remove_input_alphabet(P, x) P.remove_alphabet(x)
#define pda_insert_stack_alphabet(P, x, y) P.insert_stack_symbol(x, y)
#define pda_remove_stack_alphabet(P, x) P.remove_stack_symbol(x)
#define pda_insert_transition(P, x, y, z, w, v) P.insert_transition(x, y, z, w, v)
#define pda_remove_transition(P, x, y, z, w, v) P.remove_transition(x, y, z, w, v)
#define pda_change_start(P, x) P.change_start(x)
#define pda_insert_accept(P, x) P.insert_final(x)
#define pda_remove_accept(P, x) P.remove_final(x)
#define pda_simulate(P, x) P.simulate(x)
#define pda_output(P) P.out()
#define pda_to_cfg(P) P.to_cfg()
#endif