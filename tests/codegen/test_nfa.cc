#include "../../includes/fsm.hh"

using namespace std;

int main(){
    fsm::nfa n;
    n.insert_state("q0");
    n.insert_state("q1");
    n.insert_state("q2");
    n.insert_state("q3");
    n.insert_state("q4");

    n.insert_alphabet("a", "0");
    n.insert_alphabet("b", "1");
    n.insert_alphabet("c", "2");

    n.insert_final("q3");

    n.add_transition("q0", "a", "q1");
    n.add_transition("q0", "b", "q0");
    n.add_transition("q1", "a", "q2");
    n.add_transition("q1", "b", "q1");
    n.add_transition("q2", "b", "q2");
    n.add_transition("q2", "c", "q3");
    n.add_transition("q3", "a", "q1");
    n.add_transition("q3", "c", "q4");
    n.add_transition("q4", "a", "q4");
    n.add_transition("q4", "b", "q4");

    n.change_start("q0");

    n.out();

    n.remove_state("q4");

    n.out();

    fsm::dfa d = fsm::nfa_to_dfa(n);

    d.out();
}