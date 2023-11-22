#include "../../includes/fsm.hh"
#include <iostream>

using namespace std;

int main()
{
    fsm::dfa d;

    // Test 1: Insertion of states
    d.insert_state("q0");
    d.insert_state("q1");
    d.insert_state("q2");

    // Test 2: Insertion of alphabet
    d.insert_alphabet("a","0");
    d.insert_alphabet("b","1");

    // Test 3: Insertion of initial state
    d.insert_final("q1");

    // Test 4: Insertion of transitions
    d.add_transition("q0","a","q1");
    d.add_transition("q0","b","q0");
    d.add_transition("q1","a","q2");
    d.add_transition("q1","b","q1");
    d.add_transition("q2","b","q2");
    
    // Test 5: Test of the dfa
    // cout << "000 : " << d.simulate("000") << endl;
    // cout << "0000 : " << d.simulate("0000") << endl;

    // Test 6: Insertion of a start state
    d.out();

    d.change_start("q0");
    // cout << "000 : " << d.simulate("000") << endl;
    // cout << "0000 : " << d.simulate("0000") << endl;

    // Test 7: Deletion of a state
    // cout << d.remove_state("q2")<< "\n";
    cout << d.remove_alphabet("b")<< "\n";
    d.add_transition("q2","a","q0");

    d.out();
    // d.out();
    // cout << "000 : " << d.simulate("000") << endl;
    // cout << "0000 : " << d.simulate("0000") << endl;


    return 0;
}