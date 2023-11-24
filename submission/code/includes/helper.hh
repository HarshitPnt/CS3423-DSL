#ifndef __HELPER_HH__
#define __HELPER_HH__
#include "types.hh"
#include "attr.hh"
#include <utility>
#include <vector>
bool isInteger(VTYPE_PRIMITIVE vtp);
bool isFloat(VTYPE_PRIMITIVE vtp);
std::string getType(type_attr *t_attr);
bool isCoherent(std::string type1, std::string type2);
std::pair<bool, std::string> checkPseudoID(VarSymbolTable *entry, std::string name, std::string struct_name);
bool isStruct(std::string type);
std::string getType(expr_attr *t_attr);
std::string getType(id_attr *t_attr);
std::string stripFound(std::string ret);
std::string trim(std::string str);
extern std::vector<std::string> type_maps_prim;
extern std::vector<std::string> type_maps_auto;
extern std::vector<std::string> type_maps_set;
extern std::vector<std::string> type_maps_sr;
#endif