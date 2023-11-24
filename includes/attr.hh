#include "types.hh"
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "st.hh"
#include <utility>
#ifndef __attr_hh__
#define __attr_hh__
struct constant
{
    int ccint;
    float ccfloat;
    bool ccbool;
    char ccchar;
    CTYPE type;
};

struct id_attr
{
    std::string name;
    VTYPE_AUTOMATA vta;
    VTYPE_PRIMITIVE vtp;
    VTYPE_SET vts;
    VTYPE_SR vtsr;
    int indicator;
    std::string ifStruct;
    std::string inner, cc;
    constant *val;
    id_attr()
    {
        val = NULL;
    }
};

class type_attr
{
public:
    VTYPE_AUTOMATA vta;
    VTYPE_PRIMITIVE vtp;
    VTYPE_SET vts;
    VTYPE_SR vtsr;
    bool isConst;
    constant *val;
    std::string ifStruct, cc;
    int indicator;
    inner_type *inner = NULL;
};

class id_list_attr
{
public:
    std::vector<std::pair<VarSymbolTableEntry *, type_attr *>> lst;
    std::string cc;
    id_list_attr()
    {
        lst.clear();
    }
};

class expr_attr
{
public:
    VTYPE_PRIMITIVE vtp;
    VTYPE_AUTOMATA vta;
    VTYPE_SET vts;
    VTYPE_SR vtsr;
    int indicator;
    constant *val;
    std::string ifStruct;
    int isConst;
    int isVar;
    std::string cc;
    inner_type *inner;
};

class func_attr
{
public:
    std::string name;
    std::string return_type;
    int num;
};

class param_list_attr
{
public:
    std::vector<std::string> lst;
    std::string cc;
    int num;
};

class arg_list_attr
{
public:
    std::vector<std::string> lst;
    std::string cc;
};

class expr_list_attr
{
public:
    std::string inner;
};

class state_list_attr
{
public:
    std::list<std::string> lst;
    std::string cc;
};

class rhs_automata_attr
{
public:
    std::string type;
    std::string automata_type;
};

class rules_attr
{
public:
    std::string type;
};

class lhs_arrow_attr
{
public:
    std::string type;
    std::vector<std::string> lst;
};

class cc_code
{
public:
    std::string cc;
    cc_code()
    {
        cc = std::string("");
    }
};

class cfg_rule_attr
{
public:
    std::string init;
    std::string alpha;
    std::string final_state;
};

class element_PDA_attr
{
public:
    std::string state_alpha;
    std::string stack;
};

class elements_PDA_attr
{
public:
    std::vector<element_PDA_attr *> lst;
};
#endif