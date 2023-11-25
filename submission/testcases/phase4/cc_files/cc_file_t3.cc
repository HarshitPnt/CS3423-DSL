#include "../../../code/includes/fsm.hh"
#include "../../../code/includes/macros.hh"
template <typename T>
char insert(fsm::o_set<T> x, T y)
{
    return y;
}
void main()
{
    fsm::o_set<char> x;
    char y = insert<char>(x, 8);
}
