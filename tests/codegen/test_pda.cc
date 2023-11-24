#include "../../includes/fsm.hh"
#include <iostream>

using namespace std;

int main()
{
    fsm::pda p;

    p.insert_state("q0");
    p.insert_state("q1");
    p.insert_state("q2");

    p.insert_alphabet(")", ")");
    p.insert_alphabet("(", "(");

    p.insert_stack_symbol("$", "$");
    p.insert_stack_symbol("(", "(");

    p.change_start("q0");

    p.insert_final("q2");

    p.insert_transition("q0", "\\e", "\\e", "q1", "$");
    p.insert_transition("q1", "(", "\\e", "q1", "(");
    p.insert_transition("q1", ")", "(", "q1", "\\e");
    p.insert_transition("q1", "\\e", "$", "q2", "\\e");

    p.out();

    cout << "Simulate: " << p.simulate("()") << endl;

    return 0;
}