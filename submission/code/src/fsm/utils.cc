#include "../../includes/fsm.hh"
#include <queue>
#include <map>
#include <bitset>
namespace fsm
{

    std::string &trim(std::string &s, const char *t = " \t\n\r\f\v")
    {
        s.erase(0, s.find_first_not_of(t));
        s.erase(s.find_last_not_of(t) + 1);
        return s;
    }
    // Convert a regular expression to a DFA

    nfa *reg_to_nfa(regex reg, int state = 0)
    {
        if (reg.is_valid() == false)
            throw std::runtime_error("Invalid regex");
        nfa *n = new nfa;
        // std::string str = reg.str;
        // for (auto c : str)
        //     n->insert_alphabet(std::string(1, c), std::string(1, c));
        // std::stack<nfa *> st;

        // // First find the alphabet
        // for (auto c : str)
        // {
        //     if (c != '*' && c != '|' && c != '(' && c != ')')
        //         n->insert_alphabet(std::string(1, c), std::string(1, c));
        // }

        // for (auto c : str)
        // {
        //     if (c == '*')
        //     {
        //         nfa *n1 = st.top();
        //         st.pop();
        //         nfa *n2 = kleene_nfa(*n1);
        //         delete n1;
        //         st.push(n2);
        //     }
        //     else if (c == '|')
        //     {
        //         nfa *n1 = st.top();
        //         st.pop();
        //         nfa *n2 = st.top();
        //         st.pop();
        //         nfa *n3 = union_nfa(*n1, *n2);
        //         delete n1;
        //         delete n2;
        //         st.push(n3);
        //     }
        //     else if (c == '(')
        //     {
        //     }
        //     else if (c == ')')
        //     {
        //     }
        //     else
        //     {
        //     }
        // }
        // while(st.size() != 1){
        //     nfa *n1 = st.top();
        //     st.pop();
        //     nfa *n2 = st.top();
        //     st.pop();
        //     nfa *n3 = concat_nfa(*n1, *n2);
        //     delete n1;
        //     delete n2;
        //     st.push(n3);
        // }
        // n = st.top();
        return n;
    }

    // Convert a NFA to a DFA
    std::string concatState(std::set<std::string> &s)
    {
        std::string ans("");
        // std::cout << "Printing" << std::endl;
        for (auto &i : s)
        {
            // std::cout << i << std::endl;
            ans += std::string("#") + i;
        }
        // std::cout << trim(ans) << std::endl;
        return trim(ans);
    }
    long long int power(int a, int b)
    {
        long long int ans = 1;
        for (int i = 0; i < b; i++)
            ans *= a;
        return ans;
    }
    dfa *nfa_to_dfa(nfa n)
    {
        dfa *d = new dfa();
        int len = n.Q.size();
        // calculated epsilon closure
        auto Eclosure = n.eClosure();
        // get all states of dfa
        std::vector<std::string> states;
        std::vector<std::set<std::string>> state_set;
        // std::cout << len << std::endl;
        for (int i = 0; i < power(2, len); ++i)
        {
            std::string state("");
            std::set<std::string> temp;
            int j = 0;
            for (auto &s : n.Q)
            {
                if ((i / (power(2, j))) % 2 == 1)
                {
                    temp.insert(s);
                }
                j++;
            }
            state = concatState(temp);
            states.push_back(trim(state));
            state_set.push_back(temp);
        }
        // for (auto &s : states)
        // {
        //     std::cout << s << std::endl;
        // }
        // inserting states to dfa
        for (auto &s : states)
        {
            d->insert_state(s);
        }
        // inserting alphabet to dfa
        for (auto &a : n.S)
        {
            d->insert_alphabet(a.first, a.second);
        }
        // inserting initial state to dfa
        // initial state is e-closure of nfa-initial state
        // std::cout << "Printing new start state" << concatState(Eclosure[n.q0]) << std::endl;
        d->change_start(concatState(Eclosure[n.q0]));
        // inserting final states to dfa
        for (auto &s : states)
        {
            for (auto &f : n.F)
            {
                if (s.find(f) != std::string::npos)
                {
                    d->insert_final(s);
                    break;
                }
            }
        }
        // inserting transitions to dfa
        for (auto &s : state_set)
        {
            for (auto &alpha : n.S)
            {
                std::set<std::string> next_state;
                for (auto &i : s)
                {
                    std::set<std::string> eps = Eclosure[i];
                    // for all elements in epsilon closure of i add j to next_state such that i , a-> j exists
                    for (auto &ep : eps)
                    {
                        auto it = n.delta[ep].equal_range(alpha.first);
                        for (auto itr = it.first; itr != it.second; ++itr)
                        {
                            next_state.insert(itr->second);
                        }
                    }
                }
                // now check where you can reach using epsilon transitions from j
                for (auto &i : next_state)
                {
                    std::set<std::string> eps = Eclosure[i];
                    for (auto &ep : eps)
                    {
                        next_state.insert(ep);
                    }
                }
                if (next_state.size() == 0)
                    continue;
                std::string next = concatState(next_state);
                d->insert_transition(concatState(s), alpha.first, next);
            }
        }
        // d->out();
        return d;
    }

    dfa *reg_to_dfa(regex reg)
    {
        nfa *n = reg_to_nfa(reg);
        dfa *d = nfa_to_dfa(*n);
        delete n;
        return d;
    }

    // Concat 2 dfa's
    dfa *concat_dfa(dfa &d1, dfa &d2)
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
                    n.insert_transition("1@" + q, a.first, "1@" + d1.delta[q][a.first]);
                }
            }
        }

        for (auto q : d2.Q)
        {
            for (auto a : d2.S)
            {
                if (d2.delta[q].find(a.first) != d2.delta[q].end())
                {
                    n.insert_transition("2@" + q, a.first, "2@" + d2.delta[q][a.first]);
                }
            }
        }

        for (auto q : d1.F)
        {
            n.insert_transition("1@" + q, "\\e", "2@" + d2.q0);
        }
        return nfa_to_dfa(n);
    }

    // Union of 2 dfa's
    dfa *union_dfa(dfa &d1, dfa &d2)
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
        n.insert_transition("q0", "\\e", "1@" + d1.q0);
        n.insert_transition("q0", "\\e", "2@" + d2.q0);

        for (auto q : d1.Q)
        {
            for (auto a : d1.S)
            {
                if (d1.delta[q].find(a.first) != d1.delta[q].end())
                {
                    n.insert_transition("1@" + q, a.first, "1@" + d1.delta[q][a.first]);
                }
            }
        }

        for (auto q : d2.Q)
        {
            for (auto a : d2.S)
            {
                if (d2.delta[q].find(a.first) != d2.delta[q].end())
                {
                    n.insert_transition("2@" + q, a.first, "2@" + d2.delta[q][a.first]);
                }
            }
        }

        return nfa_to_dfa(n);
    }

    // Kleene closure of a dfa
    dfa *kleene_dfa(dfa &d1)
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
        n.insert_transition("@q0", "\\e", d1.q0);
        for (auto q : d1.Q)
        {
            for (auto a : d1.S)
            {
                if (d1.delta[q].find(a.first) != d1.delta[q].end())
                {
                    n.insert_transition(q, a.first, d1.delta[q][a.first]);
                }
            }
        }
        for (auto q : d1.F)
        {
            n.insert_transition(q, "\\e", d1.q0);
        }
        return nfa_to_dfa(n);
    }

    // Intersection of 2 dfa's
    dfa *intersect_dfa(dfa &d1, dfa &d2)
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

        dfa *d1c = !d1;
        dfa *d2c = !d2;

        dfa *dc = union_dfa(*d1c, *d2c);
        dfa *d = !*dc;
        delete d1c;
        delete d2c;
        delete dc;
        return d;
    }

    // Concat 2 nfa's
    nfa *concat_nfa(nfa &n1, nfa &n2)
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

        nfa *n = new nfa();
        for (auto q : n1.Q)
        {
            n->insert_state("1@" + q);
        }
        for (auto q : n2.Q)
        {
            n->insert_state("2@" + q);
        }
        for (auto q : n2.F)
        {
            n->insert_final("2@" + q);
        }

        n->change_start("1@" + n1.q0);

        n->S = n1.S;

        for (auto q : n1.Q)
        {
            for (auto a : n1.S)
            {
                auto it = n1.delta[q].equal_range(a.first);
                for (auto i = it.first; i != it.second; i++)
                {
                    n->insert_transition("1@" + q, a.first, "1@" + i->second);
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
                    n->insert_transition("2@" + q, a.first, "2@" + i->second);
                }
            }
        }

        for (auto q : n1.F)
        {
            n->insert_transition("1@" + q, "\\e", "2@" + n2.q0);
        }

        return n;
    }

    // Union of 2 nfa's
    nfa *union_nfa(nfa &n1, nfa &n2)
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

        nfa *n = new nfa();
        for (auto q : n1.Q)
        {
            n->insert_state("1@" + q);
        }
        for (auto q : n2.Q)
        {
            n->insert_state("2@" + q);
        }
        for (auto q : n1.F)
        {
            n->insert_final("1@" + q);
        }
        for (auto q : n2.F)
        {
            n->insert_final("2@" + q);
        }
        n->S = n1.S;

        n->insert_state("q0");
        n->change_start("q0");
        n->insert_transition("q0", "\\e", "1@" + n1.q0);
        n->insert_transition("q0", "\\e", "2@" + n2.q0);

        for (auto q : n1.Q)
        {
            for (auto a : n1.S)
            {
                auto it = n1.delta[q].equal_range(a.first);
                for (auto i = it.first; i != it.second; i++)
                {
                    n->insert_transition("1@" + q, a.first, "1@" + i->second);
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
                    n->insert_transition("2@" + q, a.first, "2@" + i->second);
                }
            }
        }

        return n;
    }

    // Kleene closure of a nfa
    nfa *kleene_nfa(nfa &n1)
    {
        nfa *n = new nfa();
        for (auto q : n1.Q)
        {
            n->insert_state(q);
        }
        for (auto q : n1.F)
        {
            n->insert_final(q);
        }
        n->S = n1.S;
        n->insert_state("@q0");
        n->change_start("@q0");
        n->insert_final("@q0");
        n->insert_transition("@q0", "\\e", n1.q0);
        for (auto q : n1.Q)
        {
            for (auto a : n1.S)
            {
                auto it = n1.delta[q].equal_range(a.first);
                for (auto i = it.first; i != it.second; i++)
                {
                    n->insert_transition(q, a.first, i->second);
                }
            }
        }
        for (auto q : n1.F)
        {
            n->insert_transition(q, "\\e", n1.q0);
        }
        return n;
    }

    // Intersection of 2 nfa's
    nfa *intersect_nfa(nfa &n1, nfa &n2)
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

        nfa *n1c = !n1;
        nfa *n2c = !n2;

        nfa *nc = union_nfa(*n1c, *n2c);
        nfa *n = !*nc;
        delete n1c;
        delete n2c;
        delete nc;
        return n;
    }

    bool nfa::simulate(std::string s)
    {
        dfa *d = nfa_to_dfa(*this);
        int ans = d->simulate(s);
        delete d;
        return ans;
    }
} // namespace fsm