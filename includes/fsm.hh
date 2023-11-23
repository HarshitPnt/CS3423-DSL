#include "lang_headers/dfa.hh"
#include "lang_headers/nfa.hh"
#include "lang_headers/pda.hh"
#include "lang_headers/dfa.hh"
#include "lang_headers/cfg.hh"
#include "lang_headers/reg.hh"
#include "lang_headers/set.hh"

// Some useful functions

namespace fsm
{
    dfa reg_to_dfa(const regex &r);
    nfa reg_to_nfa(const regex &r);
    dfa nfa_to_dfa(const nfa &n);
    pda cfg_to_pda(const cfg &c);
} // namespace fsm