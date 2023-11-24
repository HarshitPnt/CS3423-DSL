#include "../../includes/fsm.hh"
int main()
{
    fsm::nfa n;
    n.insert_state("q1");
    n.insert_state("q3");
    n.insert_state("q2");
    n.insert_alphabet("a", "a");
    n.insert_alphabet("b", "b");
    n.change_start("q1");
    n.insert_final("q3");
    n.insert_transitions("q1", "\\e", "q2");
    n.insert_transitions("q2", "a", "q1");
    n.insert_transitions("q2", "b", "q3");
    n.insert_transitions("q3", "\\e", "q1");
    fsm::dfa *d = fsm::nfa_to_dfa(n);
}