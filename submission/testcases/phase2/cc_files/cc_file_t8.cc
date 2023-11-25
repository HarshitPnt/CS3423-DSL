#include "../../../code/includes/fsm.hh"
#include "../../../code/includes/macros.hh"
struct A {
	public:
char x;
};
struct B {
	public:
fsm::o_set<fsm::o_set<A>> y;
};
struct C {
	public:
B z;
};
void main()	{
struct C c;
c.z.y[0][0].x = 5 ;
fsm::o_set<fsm::o_set<A>>  b;
b[0][0].x = 5 ;
}
