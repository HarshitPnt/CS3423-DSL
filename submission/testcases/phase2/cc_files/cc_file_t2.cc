#include "../../../code/includes/fsm.hh"
#include "../../../code/includes/macros.hh"
void main()	{
fsm::regex a;
a = *(new fsm::regex("a"));

a = *(new fsm::regex("(a)"));

a = *(new fsm::regex("[a-z]"));

a = *(new fsm::regex("[a-]"));

a = *(new fsm::regex("[-a]"));

a = *(new fsm::regex("a{1}"));

a = *(new fsm::regex("a{1,}"));

a = *(new fsm::regex("a{1,2}"));

