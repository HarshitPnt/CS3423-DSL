#include "lang_headers/nfa.hh"
#include "lang_headers/pda.hh"
#include "lang_headers/dfa.hh"
#include "lang_headers/cfg.hh"
#include "lang_headers/reg.hh"
#include "lang_headers/set.hh"

// Some useful functions

namespace fsm
{
    dfa *reg_to_dfa(regex);
    nfa *reg_to_nfa(regex, int);
    dfa *nfa_to_dfa(nfa);
    pda cfg_to_pda(cfg);

    // Add 2 dfa's
    dfa *concat_dfa(dfa &, dfa &);
    // Concatenate 2 dfa's
    dfa *union_dfa(dfa &, dfa &);
    // Kleene star of a dfa
    dfa *kleene_dfa(dfa &);
    // Intersection of 2 dfa's
    dfa *intersect_dfa(dfa &, dfa &);

    // Add 2 nfa's
    nfa *concat_nfa(nfa &, nfa &);
    // Concatenate 2 nfa's
    nfa *union_nfa(nfa &, nfa &);
    // Kleene star of a nfa
    nfa *kleene_nfa(nfa &);
    // Intersection of 2 nfa's
    nfa *intersect_nfa(nfa &, nfa &);

    
} // namespace fsm