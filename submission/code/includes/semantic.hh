#include "st.hh"
#include "types.hh"
#include <string>
#include <iostream>
#include <regex.h>
#include "helper.hh"
#include <set>

#ifndef __SEMANTIC_HH__
#define __SEMANTIC_HH__
bool checkValidID(char *);
bool checkRegex(std::string);
void initST();
void initData();

extern VarSymbolTableList *vstl;
extern FunctionSymbolTable *fst;
extern VarSymbolTable *global_vst;
extern StructSymbolTable *sst;
extern VarSymbolTable *current_vst;
extern std::set<std::string> *set_funcs;
#endif
