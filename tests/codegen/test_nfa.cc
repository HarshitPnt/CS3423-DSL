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

    n.insert_transition("q0", "a", "q1");
    n.insert_transition("q0", "b", "q0");
    n.insert_transition("q1", "a", "q2");
    n.insert_transition("q1", "b", "q1");
    n.insert_transition("q2", "b", "q2");
    n.insert_transition("q2", "c", "q3");
    n.insert_transition("q3", "a", "q1");
    n.insert_transition("q3", "c", "q4");
    n.insert_transition("q4", "a", "q4");
    n.insert_transition("q4", "b", "q4");

    n.change_start("q0");

    n.out();

    n.remove_state("q4");

    n.out();

    fsm::dfa d1;
    d1.insert_state("q0");
    d1.insert_state("q1");
    d1.insert_state("q2");

    d1.insert_alphabet("a", "0");
    d1.insert_alphabet("b", "1");

    d1.insert_final("q2");
    d1.insert_final("q1");

    d1.insert_transition("q0", "a", "q1");
    d1.insert_transition("q0", "b", "q0");
    d1.insert_transition("q1", "a", "q2");
    d1.insert_transition("q1", "b", "q1");
    d1.insert_transition("q2", "b", "q2");
    d1.insert_transition("q2", "a", "q1");

    d1.change_start("q0");

    d1.out();

    fsm::dfa d2;
    d2.insert_state("x0");
    d2.insert_state("x1");
    d2.insert_state("x2");

    d2.insert_alphabet("a", "0");
    d2.insert_alphabet("b", "1");

    d2.insert_final("x2");

    d2.insert_transition("x0", "a", "x1");
    d2.insert_transition("x0", "b", "x0");
    d2.insert_transition("x1", "a", "x2");
    d2.insert_transition("x1", "b", "x1");
    d2.insert_transition("x2", "b", "x2");
    d2.insert_transition("x2", "a", "x1");

    d2.change_start("x0");

    d2.out();

    fsm::dfa *n1 = fsm::concat_dfa(d1, d2);

    n1->out();

    fsm::dfa *n2 = fsm::union_dfa(d1, d2);

    n2->out();

    fsm::dfa *n3 = fsm::kleene_dfa(d1);

    n3->out();

    fsm::dfa *n4 = fsm::intersect_dfa(d1, d2);
}