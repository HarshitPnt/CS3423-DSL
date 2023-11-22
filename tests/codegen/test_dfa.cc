#include "../../includes/fsm.hh"
#include <iostream>

using namespace std;

int main()
{
    fsm::dfa d;
    // Test 1: Insertion
    d.insert_state("1");
    d.insert_state("2");
    d.insert_state("3");
    d.insert_alphabet("a", "1");
    d.insert_alphabet("b", "2");
    try{
        d.insert_alphabet("c", "22");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    d.insert_alphabet("c", "3");

    d.insert_final("3");
    d.insert_final("4");

    return 0;
}