#include "../../../code/includes/fsm.hh"
#include "../../../code/includes/macros.hh"
struct A {
	public:
fsm::o_set<char> a;
};
struct B {
	public:
short b;
fsm::o_set<fsm::o_set<fsm::o_set<A>>> c;
};
struct B b;
char i;
void main()	{
b.c[i][i][i].a[i] = 5 ;
}
