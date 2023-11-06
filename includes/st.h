#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct InnerType {

} InnerType;

typedef struct Type {

} Type;

typedef struct VarSymTabItem {

} VarSymTabItem;

typedef struct VarSymTab {

} VarSymTab;

typedef struct VarSymTabList {

} VarSymTabList;


typedef struct FuncSymTabItem {

} FuncSymTabItem;

typedef struct FuncSymTab {

} FuncSymTab;

typedef struct StructSymTabItem {

} StructSymTabItem;

typedef struct StructSymTab {

} StructSymTab;


void insertToVarSymTab(char *); // To edit
VarSymTabItem * VarSearch(char *); // To edit
void printVarSymTab(VarSymTab *); // To edit
void printVarSymTabList(); // To edit

void insertToFuncSymTab(char *); // To edit
FuncSymTabItem * FuncSearch(char *); // To edit
void printFuncSymTab(FuncSymTab *); // To edit

void insertToStructSymTab(char *); // To edit
StructSymTabItem * StructSearch(char *); // To edit
void printStructSymTab(StructSymTab *); // To edit

