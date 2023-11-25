#include "../../../code/includes/fsm.hh"
#include "../../../code/includes/macros.hh"
struct Point {
	public:
long int x, y;
};
char foo(char x , unsigned short y )	{
return x ;
}
void main()	{
char a, b;
a = 10 ;
b = 20 ;
char result = a + b;
result = a - b ;
result = a * b ;
result = a / b ;
result = a % b ;
result = (a + b) * 2 / (a - b + a) % result ;
result +=b ;
result -=a + b ;
result *=result ;
result /=(a * b) ;
result %=10 ;
bool a_bool = 1, b_bool = 0;
a_bool = a > b ;
b_bool = a < b ;
a_bool = a>=b ;
b_bool = a<=b ;
a_bool = a==b ;
b_bool = a!=b ;
a_bool = a_bool && b_bool ;
b_bool = a_bool || b_bool ;
a_bool = !a_bool ;
a_bool = (a_bool && b_bool) || (a!=b) ;
a_bool &=b_bool ;
a_bool |=b_bool ;
;
fsm::o_set<char> set;
set.insert(1);
set.insert(2);
set.insert(3);
;
fsm::o_set<char> set2;
set2.insert(4);
set2.insert(5);
set2.insert(6);
fsm::o_set<char>  results;
