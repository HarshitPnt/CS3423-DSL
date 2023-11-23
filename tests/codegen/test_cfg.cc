#include "../../includes/lang_headers/cfg.hh"

int main()
{
    // Testing cfg
    fsm::cfg cfg_obj;

    bool flag = cfg_obj.add_T("a", "a");
    // cfg_obj.out();
    flag = cfg_obj.add_T("demo", "b");
    // cfg_obj.out();
    // add duplicate
    // flag = cfg_obj.add_T("demo", "b");
    // cfg_obj.out();
    // flag = cfg_obj.add_T("demo", "c");
    // cfg_obj.out();
    // flag = cfg_obj.add_T("ok", "aa");
    // cfg_obj.out();
    // prefix

    // testing add_N
    flag = cfg_obj.add_N("S");
    // cfg_obj.out();
    flag = cfg_obj.add_N("A");
    // cfg_obj.out();
    // duplicate non-terminal
    // flag = cfg_obj.add_N("A");
    // cfg_obj.out();
    // adding productions
    flag = cfg_obj.add_P("S -> %{A}");
    // cfg_obj.out();
    flag = cfg_obj.add_P("A -> ${demo}");
    // cfg_obj.out();
    flag = cfg_obj.add_P("A -> ${demo}${demo}");
    // cfg_obj.out();
    flag = cfg_obj.add_P("A -> ${demo}%{S}");
    // cfg_obj.out();
    flag = cfg_obj.add_P("A -> \\e");
    // cfg_obj.out();
    // adding productions with duplicate
    flag = cfg_obj.add_P("A -> ${a}%{S}");
    // cfg_obj.out();
    // adding productions with non-existant lhs
    flag = cfg_obj.add_P("B -> ${demo}%{S}");
    // cfg_obj.out();
    // adding production with non-existant rhs
    flag = cfg_obj.add_P("A -> ${demo}%{B}");
    // cfg_obj.out();
    // adding production with non-existant lhs terminal
    flag = cfg_obj.add_P("A -> ${A}%{A}");
    // cfg_obj.out();
    // testing remove_T
    flag = cfg_obj.remove_T("a");
    // cfg_obj.out();
    // remove_T with non-existant terminal
    flag = cfg_obj.remove_T("a");
    // cfg_obj.out();
    // test remove_N
    // try to remove the start
    // first set S to start
    flag = cfg_obj.change_start("S");
    flag = cfg_obj.remove_N("S");
    // cfg_obj.out();
    // now change start and then try to remove
    flag = cfg_obj.change_start("A");
    flag = cfg_obj.remove_N("S");
    // cfg_obj.out();
    // try to remove non-existant non-terminal
    flag = cfg_obj.remove_N("S");
    flag = cfg_obj.add_P("S -> %{A}");
    flag = cfg_obj.add_N("B");
    flag = cfg_obj.add_P("A -> %{B}");
    flag = cfg_obj.add_P("B -> ${demo}");
    flag = cfg_obj.add_P("B -> ${demo}%{B}");
    flag = cfg_obj.add_P("B -> \\e");
    cfg_obj.out();
    // flag = cfg_obj.remove_N("B");
    // test remove_P
    flag = cfg_obj.remove_P("A -> %{B}");
    // cfg_obj.out();
    // remove non-existant production
    flag = cfg_obj.remove_P("A -> %{B}");
    flag = cfg_obj.remove_P("C -> ${demo}");
    flag = cfg_obj.remove_P("B -> ${c}");
    // test change_start
    // test CNF
    std::cout << "Testing Chomsky Normal Form" << std::endl;
    fsm::cfg x = cfg_obj._CNF();
    x.out();
}
