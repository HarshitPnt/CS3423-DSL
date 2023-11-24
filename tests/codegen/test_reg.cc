#include "../../includes/fsm.hh"

using namespace std;

int main()
{
    fsm::regex reg("(a|b*)*c(a|bcd)");
    cout << reg.simulate("a") << endl;
    cout << reg.simulate("b") << endl;
    cout << reg.simulate("bbbcab") << endl;
    cout << reg.is_valid() << endl;

    fsm::regex reg2("^a{2,3}$");
    cout << reg2.is_valid() << endl;
    cout << reg2.simulate("a") << endl;
    cout << reg2.simulate("aa") << endl;
    cout << reg2.simulate("aaa") << endl;
    cout << reg2.simulate("aaaa") << endl;

    // fsm::nfa *n = fsm::reg_to_nfa(reg, 0);
    // fsm::dfa *d = fsm::nfa_to_dfa(*n);

    // n->out();
    // d->out();

    return 0;
}