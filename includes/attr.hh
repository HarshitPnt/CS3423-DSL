#include "types.hh"
#include <iostream>
#include <vector>
#include <list>
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
    std::string inner;
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
    std::string ifStruct;
    int indicator;
    std::list<int> dimensions;
    inner_type *inner = NULL;
};

class id_list_attr
{
public:
    std::vector<std::pair<VarSymbolTableEntry *, type_attr *>> lst;
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
    int num;
};

class arg_list_attr
{
public:
    std::vector<std::string> lst;
};

class expr_list_attr
{
public:
    std::string inner;
};
#endif