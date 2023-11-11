#include "types.hh"
#include <iostream>
#include <vector>
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
    int indicator;
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
#endif