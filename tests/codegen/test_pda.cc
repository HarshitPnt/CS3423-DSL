#include "../../includes/fsm.hh"
#include <iostream>

using namespace std;

int main()
{
    fsm::pda p;
    cout << p.q0 << endl;
    p.insert_state("q0");
    p.insert_state("q1");
    p.insert_state("q2");

    p.insert_alphabet("a", "a");

    p.insert_stack_symbol("b", "b");

    p.insert_final("q2");

    p.change_start("q0");

    cout << p.add_transition("q0", "a", "\\e", "q1", "b");
    cout << p.add_transition("q1", "a", "b", "q2", "\\e");
    cout << p.add_transition("q2", "a", "\\e", "q0", "\\e");

    cout << endl;

    // p.remove_state("q0");
    // p.remove_alphabet("a");
    // p.remove_alphabet("b");

    p.out();

    cout << "Simulate: " << p.simulate("aaaaa") << endl;

    return 0;
}