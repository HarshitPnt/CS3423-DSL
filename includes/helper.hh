#ifndef __HELPER_HH__
#define __HELPER_HH__
#include "types.hh"
#include "attr.hh"
bool isInteger(VTYPE_PRIMITIVE vtp);
bool isFloat(VTYPE_PRIMITIVE vtp);
std::string getType(type_attr *t_attr);
#endif