#include "../../includes/fsm.hh"
#include <queue>
#include <map>
#include <bitset>
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
        }
        return n;
    }
    // Convert a NFA to a DFA
    dfa nfa_to_dfa(nfa n)
    {
        dfa d;
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

    // Concat 2 dfa's
    dfa concat_dfa(dfa &d1, dfa &d2)
    {
        if (d1.S.size() != d2.S.size())
            throw std::runtime_error("Ambiguous alphabets");
        for (auto a : d1.S)
        {
            if (d2.S.find(a.first) == d2.S.end())
                throw std::runtime_error("Ambiguous alphabets");
            if (d1.S[a.first] != d2.S[a.first])
                throw std::runtime_error("Ambiguous alphabets");
        }

        nfa n;
        std::string q0 = d1.q0;
        std::string q1 = d2.q0;
        for (auto q : d1.Q)
        {
            n.insert_state("1@" + q);
        }
        for (auto q : d2.Q)
        {
            n.insert_state("2@" + q);
        }
        for (auto q : d2.F)
        {
            n.insert_final("2@" + q);
        }

        n.change_start("1@" + q0);

        n.S = d1.S;

        for (auto q : d1.Q)
        {
            for (auto a : d1.S)
            {
                if (d1.delta[q].find(a.first) != d1.delta[q].end())
                {
                    n.add_transition("1@" + q, a.first, "1@" + d1.delta[q][a.first]);
                }
            }
        }

        for (auto q : d2.Q)
        {
            for (auto a : d2.S)
            {
                if (d2.delta[q].find(a.first) != d2.delta[q].end())
                {
                    n.add_transition("2@" + q, a.first, "2@" + d2.delta[q][a.first]);
                }
            }
        }

        for (auto q : d1.F)
        {
            n.add_transition("1@" + q, "\\e", "2@" + d2.q0);
        }
        return nfa_to_dfa(n);
    }

    // Union of 2 dfa's
    dfa union_dfa(dfa &d1, dfa &d2)
    {
        if (d1.S.size() != d2.S.size())
            throw std::runtime_error("Ambiguous alphabets");
        for (auto a : d1.S)
        {
            if (d2.S.find(a.first) == d2.S.end())
                throw std::runtime_error("Ambiguous alphabets");
            if (d1.S[a.first] != d2.S[a.first])
                throw std::runtime_error("Ambiguous alphabets");
        }

        nfa n;
        for (auto q : d1.Q)
        {
            n.insert_state("1@" + q);
        }
        for (auto q : d2.Q)
        {
            n.insert_state("2@" + q);
        }
        for (auto q : d1.F)
        {
            n.insert_final("1@" + q);
        }
        for (auto q : d2.F)
        {
            n.insert_final("2@" + q);
        }
        n.S = d1.S;

        n.insert_state("q0");
        n.change_start("q0");
        n.add_transition("q0", "\\e", "1@" + d1.q0);
        n.add_transition("q0", "\\e", "2@" + d2.q0);

        for (auto q : d1.Q)
        {
            for (auto a : d1.S)
            {
                if (d1.delta[q].find(a.first) != d1.delta[q].end())
                {
                    n.add_transition("1@" + q, a.first, "1@" + d1.delta[q][a.first]);
                }
            }
        }

        for (auto q : d2.Q)
        {
            for (auto a : d2.S)
            {
                if (d2.delta[q].find(a.first) != d2.delta[q].end())
                {
                    n.add_transition("2@" + q, a.first, "2@" + d2.delta[q][a.first]);
                }
            }
        }

        return nfa_to_dfa(n);
    }

    // Kleene closure of a dfa
    dfa kleene_dfa(dfa &d1)
    {
        nfa n;
        for (auto q : d1.Q)
        {
            n.insert_state(q);
        }
        for (auto q : d1.F)
        {
            n.insert_final(q);
        }
        n.S = d1.S;
        n.insert_state("@q0");
        n.change_start("@q0");
        n.insert_final("@q0");
        n.add_transition("@q0", "\\e", d1.q0);
        for (auto q : d1.Q)
        {
            for (auto a : d1.S)
            {
                if (d1.delta[q].find(a.first) != d1.delta[q].end())
                {
                    n.add_transition(q, a.first, d1.delta[q][a.first]);
                }
            }
        }
        for (auto q : d1.F)
        {
            n.add_transition(q, "\\e", d1.q0);
        }
        return nfa_to_dfa(n);
    }

    // Concat 2 nfa's
    nfa concat_nfa(nfa &n1, nfa &n2)
    {
        if (n1.S.size() != n2.S.size())
            throw std::runtime_error("Ambiguous alphabets");
        for (auto a : n1.S)
        {
            if (n2.S.find(a.first) == n2.S.end())
                throw std::runtime_error("Ambiguous alphabets");
            if (n1.S[a.first] != n2.S[a.first])
                throw std::runtime_error("Ambiguous alphabets");
        }

        nfa n;
        for (auto q : n1.Q)
        {
            n.insert_state("1@" + q);
        }
        for (auto q : n2.Q)
        {
            n.insert_state("2@" + q);
        }
        for (auto q : n2.F)
        {
            n.insert_final("2@" + q);
        }

        n.change_start("1@" + n1.q0);

        n.S = n1.S;

        for (auto q : n1.Q)
        {
            for (auto a : n1.S)
            {
                auto it = n1.delta[q].equal_range(a.first);
                for (auto i = it.first; i != it.second; i++)
                {
                    n.add_transition("1@" + q, a.first, "1@" + i->second);
                }
            }
        }

        for (auto q : n2.Q)
        {
            for (auto a : n2.S)
            {
                auto it = n2.delta[q].equal_range(a.first);
                for (auto i = it.first; i != it.second; i++)
                {
                    n.add_transition("2@" + q, a.first, "2@" + i->second);
                }
            }
        }

        for (auto q : n1.F)
        {
            n.add_transition("1@" + q, "\\e", "2@" + n2.q0);
        }

        return n;
    }

    // Union of 2 nfa's
    nfa union_nfa(nfa &n1, nfa &n2)
    {
        if (n1.S.size() != n2.S.size())
            throw std::runtime_error("Ambiguous alphabets");
        for (auto a : n1.S)
        {
            if (n2.S.find(a.first) == n2.S.end())
                throw std::runtime_error("Ambiguous alphabets");
            if (n1.S[a.first] != n2.S[a.first])
                throw std::runtime_error("Ambiguous alphabets");
        }

        nfa n;
        for (auto q : n1.Q)
        {
            n.insert_state("1@" + q);
        }
        for (auto q : n2.Q)
        {
            n.insert_state("2@" + q);
        }
        for (auto q : n1.F)
        {
            n.insert_final("1@" + q);
        }
        for (auto q : n2.F)
        {
            n.insert_final("2@" + q);
        }
        n.S = n1.S;

        n.insert_state("q0");
        n.change_start("q0");
        n.add_transition("q0", "\\e", "1@" + n1.q0);
        n.add_transition("q0", "\\e", "2@" + n2.q0);

        for (auto q : n1.Q)
        {
            for (auto a : n1.S)
            {
                auto it = n1.delta[q].equal_range(a.first);
                for (auto i = it.first; i != it.second; i++)
                {
                    n.add_transition("1@" + q, a.first, "1@" + i->second);
                }
            }
        }

        for (auto q : n2.Q)
        {
            for (auto a : n2.S)
            {
                auto it = n2.delta[q].equal_range(a.first);
                for (auto i = it.first; i != it.second; i++)
                {
                    n.add_transition("2@" + q, a.first, "2@" + i->second);
                }
            }
        }

        return n;
    }

    // Kleene closure of a nfa
    nfa kleene_nfa(nfa &n1)
    {
        nfa n;
        for (auto q : n1.Q)
        {
            n.insert_state(q);
        }
        for (auto q : n1.F)
        {
            n.insert_final(q);
        }
        n.S = n1.S;
        n.insert_state("@q0");
        n.change_start("@q0");
        n.insert_final("@q0");
        n.add_transition("@q0", "\\e", n1.q0);
        for (auto q : n1.Q)
        {
            for (auto a : n1.S)
            {
                auto it = n1.delta[q].equal_range(a.first);
                for (auto i = it.first; i != it.second; i++)
                {
                    n.add_transition(q, a.first, i->second);
                }
            }
        }
        for (auto q : n1.F)
        {
            n.add_transition(q, "\\e", n1.q0);
        }
        return n;
    }
} // namespace fsm