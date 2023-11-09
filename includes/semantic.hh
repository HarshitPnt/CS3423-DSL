#include "st.hh"
#include "types.hh"
#include <string>
#include <iostream>
#include <regex.h>

bool checkValidID(char *);
bool checkRegex(std::string);
void initST();

extern VarSymbolTableList *vstl;
extern StructSymbolTableList *sstl;
extern FunctionSymbolTable *fst;

extern VarSymbolTable *global_vst;
extern StructSymbolTable *global_sst;
