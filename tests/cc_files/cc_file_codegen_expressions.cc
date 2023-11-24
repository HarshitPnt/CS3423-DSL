#include "../../includes/fsm.hh"
struct A {
	public:
char type;
};
char func(char x , unsigned char y )	{
return x ;
}
bool isTrue(unsigned char x )	{
return 1 ;
}
int main()	{
char result = 5, abcd_;
abcd_ +=result ;
struct A aa;
fsm::o_set<char>  x;
fsm::o_set<fsm::o_set<long int>>  y;
fsm::o_set<fsm::u_set<A>>  z ,xxxxx;
;
fsm::o_set<char> xxx;
xxx.insert(1);
xxx.insert(2);
xxx.insert(3);
;
fsm::o_set<char> yyy;
yyy.insert(12);
yyy.insert(12.000000);
yyy.insert(134);
xxx.insert(4);
xxx.insert(5);
xxx.insert(6);

abcd_ = func(result, result) + result ;
if(isTrue(result))
	{
char yy = abcd_ + result;
}
fsm::cfg a;
a.insert_alphabet("a", "a");
a.insert_alphabet("demo", "b");

a.insert_state("A");
a.insert_state("B");

a.change_start("A");

a.add_P("A -> ${a}%{B}");
a.add_P("B -> ${demo}%{A}");
a.add_P("A -> ${a}%{A}");
a.add_P("A -> \e");

fsm::dfa aaa;
aaa.insert_state("q0");
aaa.insert_state("q1");
aaa.insert_state("q2");

aaa.insert_alphabet("a", "0");
aaa.insert_alphabet("b", "1");
aaa.insert_alphabet("c", "2");

aaa.insert_transition("q0", "a", "q1");
aaa.insert_transition("q1", "b", "q3");
aaa.insert_transition("q1", "b", "q2");
aaa.insert_transition("q2", "a", "q1");
aaa.insert_transition("q2", "b", "q1");

aaa.change_start("q0");

aaa.insert_final("q1");
aaa.insert_final("q2");

fsm::pda bbb;
bbb.insert_state("A");
bbb.insert_state("B");
bbb.insert_state("C");

bbb.insert_alphabet("a", "a");
bbb.insert_alphabet("b", "b");
bbb.insert_alphabet("c", "c");

bbb.insert_alphabet("a", "a");
bbb.insert_alphabet("b", "b");
bbb.insert_alphabet("c", "d");

bbb.insert_transition("A", "a", "a", "A", "a");
bbb.insert_transition("A", "b", "a", "B", "a");
bbb.insert_transition("A", "b", "a", "A", "c");
bbb.insert_transition("A", "b", "c", "B", "a");
bbb.insert_transition("A", "b", "c", "A", "c");
bbb.insert_transition("B", "b", "a", "B", "a");
bbb.insert_transition("B", "b", "c", "B", "a");
bbb.insert_transition("B", "c", "a", "C", "\e");
bbb.insert_transition("C", "c", "a", "C", "\e");
bbb.insert_transition("C", "c", "a", "C", "a");

bbb.change_start("A");

bbb.insert_final("C");

fsm::nfa dd;
dd.insert_state("q0");
dd.insert_state("q1");
dd.insert_state("q2");

dd.insert_alphabet("a", "0");
dd.insert_alphabet("b", "1");
dd.insert_alphabet("c", "2");

dd.insert_transition("q0", "a", "q1");
dd.insert_transition("q0", "a", "q2");
dd.insert_transition("q1", "b", "q2");
dd.insert_transition("q1", "c", "q2");
dd.insert_transition("q2", "a", "q1");
dd.insert_transition("q2", "c", "q1");
dd.insert_transition("q2", "\e", "q0");

dd.change_start("q0");

dd.insert_final("q1");
dd.insert_final("q2");

}
