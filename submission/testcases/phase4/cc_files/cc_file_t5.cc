#include "../../../code/includes/fsm.hh"
#include "../../../code/includes/macros.hh"
long int main()	{
fsm::dfa a;
a.insert_state("A");
a.insert_state("B");
a.insert_state("C");

a.insert_final("C");

a.insert_alphabet("a", "0");
a.insert_alphabet("b", "1");

a.insert_transition("A", "a", "B");
a.insert_transition("A", "b", "A");
a.insert_transition("B", "b", "C");
a.insert_transition("B", "a", "B");
a.insert_transition("C", "a", "B");
a.insert_transition("C", "b", "C");

a.change_start("A");

std::cout<<dfa_simulate(a, "001")<<std::endl ;
std::cout<<dfa_simulate(a, "010")<<std::endl ;
}
