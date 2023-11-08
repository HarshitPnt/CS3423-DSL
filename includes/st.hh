#pragma once
#include <string>
#include <map>
#include <list>

/*
Symbol Table:

VarSymbolTableList: List of VarSymbolTables. 
VarSymbolTable: Map of VarSymbolTableEntries.
VarSymbolTableEntry: name, type, inner_type, dimension, value.
name: name of variable.
type: int, float, char, struct, void, set, user-defined type(struct).
inner_type: int, float, char, struct, void, set, user-defined type(struct).
dimension: Number of dimensions of the variable. 0 if not an array.
value: Value of dimension. 0 if not an array.

StructSymbolTable: Map of StructSymbolTableEntries.
StructSymbolTableEntry: name, map of VarSymbolTableEntries.
name: name of struct.
map of VarSymbolTableEntries: contains all the fields of the struct.

FunctionSymbolTable: Map of FunctionSymbolTableEntries.
FunctionSymbolTableEntry: name, VarSymbolTable, return_type.
name: name of function.
VarSymbolTable: Map of VarSymbolTableEntries.
return_type: int, float, char, struct, void, set, user-defined type(struct).

*/

class VarSymbolTableEntry
{
public:
    std::string name;
    std::string type;
    std::string inner_type;
    std::string dimension;
    std::string value;
    VarSymbolTableEntry(std::string name, std::string type, std::string inner_type, std::string dimension, std::string value);
};

class VarSymbolTable
{
public:
    std::map<std::string, VarSymbolTableEntry *> entries;
    int insert(VarSymbolTableEntry *vste);
    VarSymbolTableEntry *lookup(std::string name);
};

class VarSymbolTableList
{
public:
    std::list<VarSymbolTable *> entries;
    int insert(VarSymbolTable *vst);
    VarSymbolTable *lookup(std::string name);
};

class StructSymbolTableEntry
{
public:
    std::string name;
    std::map<std::string, VarSymbolTableEntry *> fields;
    StructSymbolTableEntry(std::string name, std::map<std::string, VarSymbolTableEntry *> fields);
};

class StructSymbolTable
{
public:
    std::map<std::string, StructSymbolTableEntry *> entries;
    int insert(StructSymbolTableEntry *sste);
    StructSymbolTableEntry *lookup(std::string name);
};

class FunctionSymbolTableEntry
{
public:
    std::string name;
    VarSymbolTable *params;
    std::string return_type;
    FunctionSymbolTableEntry(std::string name, VarSymbolTable *params, std::string return_type);
};

class FunctionSymbolTable
{
public:
    std::map<std::string, FunctionSymbolTableEntry *> entries;
    int insert(FunctionSymbolTableEntry *fste);
    FunctionSymbolTableEntry *lookup(std::string name);
};

