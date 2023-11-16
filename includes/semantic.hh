#include "st.hh"
#include "types.hh"
#include <string>
#include <iostream>
#include <regex.h>
#include "helper.hh"

#ifndef __SEMANTIC_HH__
#define __SEMANTIC_HH__
bool checkValidID(char *);
bool checkRegex(std::string);
void initST();

extern VarSymbolTableList *vstl;
extern FunctionSymbolTable *fst;
extern VarSymbolTable *global_vst;
extern StructSymbolTable *sst;
extern VarSymbolTable *current_vst;
#endif
