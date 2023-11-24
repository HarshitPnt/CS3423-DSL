#include "../../includes/fsm.hh"
#include <iostream>

using namespace std;
//ERROR1 -> deleting transition that doesnot exist return true.
int main()
{
    fsm::dfa d;
    fsm::dfa d1;

    //Initializing states of dfa d
     d.insert_state("q0");
     d.insert_state("q1");
     d.insert_state("q2");

     //Initializing states of dfa d1
     d1.insert_state("q0");
     d1.insert_state("q1");
     d1.insert_state("q2");

     //Initializing statr state of dfa d
        d.change_start("q0");

        //Initializing statr state of dfa d1
        d1.change_start("q0");

        //Initializing final state of dfa d
        d.insert_final("q1");

        //Initializing final state of dfa d1
        d1.insert_final("q1");

        //Initializing alphabets of dfa d

        d.insert_alphabet("a","0");

        //Initializing alphabets of dfa d1

        d1.insert_alphabet("a","0");


        //Initializing transitions of dfa d

        d.add_transition("q0","a","q1");
        d.add_transition("q1","a","q2");
        d.add_transition("q2","a","q0");

        //Initializing transitions of dfa d1
        cout<<"d:"<< d.__simulate("0")<<endl;

        d1.add_transition("q0","a","q1");
        d1.add_transition("q1","a","q2");
        d1.add_transition("q2","a","q0");

        cout<<"d1:" <<d1.__simulate("0")<<endl;
        //Concatenating dfa d and dfa d1

        fsm::dfa *d2 = fsm::concat_dfa(d,d1);

cout << "HELLO" << endl;
        //Printing dfa d2
        cout<<"d2 00"<<d2->__simulate("00")<<endl;

        cout<<"d2 000"<<d2->__simulate("000")<<endl;
        // cout<<d2->__simulate("aaaa")<<endl;  

     



//     // Test 1: Insertion of states
//     d.insert_state("q0");
//     d.insert_state("q1");
//     d.insert_state("q2");
//     d.insert_state("q3");

//     // Test2 :Inserting alrady existing state
//     d.insert_state("q0");

//     // Test 2: Insertion of alphabet
//     d.insert_alphabet("a", "0");
//     d.insert_alphabet("b", "1");
//     d.insert_alphabet("c", "2");

//     // Test 3: Insertion of initial state
//     d.insert_final("q1");

//     // Test 4: Insertion of transitions
//     d.add_transition("q0", "a", "q1");
//     d.add_transition("q0", "b", "q0");
//     d.add_transition("q1", "a", "q2");
//     d.add_transition("q1", "b", "q1");
//     d.add_transition("q2", "b", "q2");

//     // Test 5: Test of the dfa
//     // cout << "000 : " << d.simulate("000") << endl;
//     // cout << "0000 : " << d.simulate("0000") << endl;

//     // Test 6: Insertion of a start state

//     // This should throw error as we have not initialized the start state.
//    // d.out();

//      d.change_start("q0");
//   //   cout<< d.insert_state("q0")<<endl ;
//   //   d.out();

//      cout << d.remove_alphabet("b") << "\n";
//      d.add_transition("q2", "a", "q0");

// //     d.out();
//     d.add_transition("q0", "c", "q0");
//     d.add_transition("q1", "c", "q1");
//     d.add_transition("q2", "c", "q2");
//     d.add_transition("q3", "c", "q3");
//     d.add_transition("q3", "a", "q1");
//   //   d.out();
//      d.remove_final("q1");

// //     // At this point the dfa should be invalid as there is no final state.
//    //  d.out();

//      d.remove_state("q1");
//      d.insert_final("q2");
//      d.insert_state("q4");

//      // Here a from q2 takes to both q0 and q4. So the dfa should be invalid.
//      d.add_transition("q2", "a", "q4");
//  //   d.out();

// //     // Now we remove the transition from q2 to q4 Should return false as it was never added.
// //     cout << d.remove_transition("q2", "a", "q4") << endl;
//      d.remove_transition("q2", "c", "q2");
//    d.add_transition("q4", "a", "q3");
//     d.add_transition("q4", "c", "q3");
//     d.add_transition("q2", "c", "q4");
//     d.add_transition("q3", "a", "q3");
//     d.add_transition("q0", "a", "q0");

//  //    // No out bound transition from q3..
//      d.change_start("q3");
// //
//    //  d.out();
//      d.remove_transition("q3", "a", "q3");
//      d.add_transition("q3", "a", "q4");
// //
//      d.remove_state("q4");
//      //next 3 instruction 
//     //  d.remove_state("q3");
//     //  d.add_transition("q2","c","q2");
//     //  d.change_start("q3");
// //     // No out bound transition from q3.Only state in the dfa is q3 and q0 and q1 are not reachable from q3.
// //     d.out();

// //     // This should throw error as we have no q5 state .
//  //    cout << d.insert_final("q5") << endl;

//      d.add_transition("q2", "c", "q2");
//     d.insert_state("q5");

// //     // insering a state that is already present.
// //     cout << d.insert_state("q5") << endl;

// //     // This should throw error as we have no q6 state .
// //     cout << d.add_transition("q5", "a", "q6") << endl;

// //     // This should return false as there is no alphabet "d".
//  //    cout << d.add_transition("q3", "d", "q5") << endl;

// //     // This should return false as q1 has been deleted.
//  //    cout << d.add_transition("q5", "a", "q1") << endl;
     

//      d.add_transition("q3", "a", "q5");
//  //    d.out();
// //     // Should return false.
//  //    cout << "011 : " << d.simulate("011") << endl;
 


//      d.add_transition("q5", "c", "q5");

// //     // This should return false as transition from q5 for alphabet c already exists.
//  //    cout << d.add_transition("q5", "c", "q3") << endl;

// //     // This should return false as there is no state q6.
// //     cout<<d.change_start("q6")<<endl;

//      d.remove_state("q0");
// //     d.out();
// //     // This should return false as q1 has been deleted.
// //    cout<<d.remove_state("q1")<<endl;

//      d.remove_state("q2");
//    //  d.out();
//      d.insert_final("q5");
//      d.add_transition("q5","a","q3");
//      d.out();
// //     // Should return true.
//      cout << "000 : " << d.simulate("000") << endl;

// //     // Should return false.
//      cout << "0000 : " << d.simulate("0000") << endl;
//     //Alphabets checks
//      cout<<d.remove_alphabet("f")<<endl;
//     cout<<d.insert_alphabet("a","0")<<endl;
//         cout<<d.insert_alphabet("a","1")<<endl;
//     cout<<d.insert_alphabet("b","0")<<endl;

//      fsm::dfa dcomp = !d;
//      dcomp.out();
    return 0;
}