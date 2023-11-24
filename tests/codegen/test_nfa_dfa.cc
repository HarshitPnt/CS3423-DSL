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
    n.insert_transition("q1", "\\e", "q2");
    n.insert_transition("q2", "a", "q1");
    n.insert_transition("q2", "b", "q3");
    n.insert_transition("q3", "\\e", "q1");
    fsm::dfa *d = fsm::nfa_to_dfa(n);
}