#ifndef ST_HH
#define ST_HH
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <list>

/*
Symbol Table:

VarSymbolTableList: List of VarSymbolTables.
VarSymbolTable: unordered_map of VarSymbolTableEntries.
VarSymbolTableEntry: name, type, inner_type, dimension, value.
name: name of variable.
type: int, float, char, struct, void, set, user-defined type(struct).
inner_type: int, float, char, struct, void, set, user-defined type(struct).
inner_type is pointer
num_dim: Number of dimensions of the variable. 0 if not an array.
dimensions: Value of dimension. 0 if not an array.

StructSymbolTable: unordered_map of StructSymbolTableEntries.
StructSymbolTableEntry: name, unordered_map of VarSymbolTableEntries.
name: name of struct.
unordered_map of VarSymbolTableEntries: contains all the fields of the struct.

FunctionSymbolTable: unordered_map of FunctionSymbolTableEntries.
FunctionSymbolTableEntry: name, VarSymbolTable, return_type.
name: name of function.
VarSymbolTable: unordered_map of VarSymbolTableEntries.
return_type: int, float, char, struct, void, set, user-defined type(struct).

*/
// reursiverly store the inner type in the symbol table
class VarSymbolTable;

class inner_type
{
public:
    inner_type *inner;
    std::string type;
    inner_type(inner_type *inner, std::string type);
    std::string print();
};

class VarSymbolTableEntry
{
public:
    std::string name;
    std::string type;
    inner_type *inner;
    VarSymbolTable *struct_vst;
    void print();
    VarSymbolTableEntry(std::string name);
    VarSymbolTableEntry(std::string name, std::string type, inner_type *inner);
};

class VarSymbolTable
{
public:
    std::unordered_map<std::string, VarSymbolTableEntry *> entries;
    int insert(VarSymbolTableEntry *vste);
    VarSymbolTableEntry *lookup(std::string name);
    bool backpatch(VarSymbolTableEntry *vste, std::string type, inner_type *inner, VarSymbolTable *struct_vst);
    void print();
};

class VarSymbolTableList
{
public:
    std::list<VarSymbolTable *> entries;
    int insert(VarSymbolTable *vst);
    VarSymbolTable *lookup(std::string name);
    bool remove();
    VarSymbolTable *getTop();
    void print();
};

class StructSymbolTableEntry
{
public:
    std::string name;
    VarSymbolTable *fields;
    bool isTemplate = false;
    StructSymbolTableEntry(std::string name, VarSymbolTable *fields);
};

class StructSymbolTable
{
public:
    std::unordered_map<std::string, StructSymbolTableEntry *> entries;
    bool insert(StructSymbolTableEntry *sste);
    bool remove(std::string name);
    StructSymbolTableEntry *lookup(std::string name);
    void init();
    void print();
};

class FunctionSymbolTableEntry
{
public:
    std::string name;
    int num_params;
    VarSymbolTable *params;
    std::vector<std::string> id_list;
    std::string return_type;
    bool isTemplate;
    std::vector<std::string> template_params;

    FunctionSymbolTableEntry(std::string name, int num_params, VarSymbolTable *params, std::string return_type);
    FunctionSymbolTableEntry(std::string name, int num_params, VarSymbolTable *params, std::string return_type, bool isTemplate, std::vector<std::string> template_params);
};

class FunctionSymbolTable
{
public:
    std::unordered_map<std::string, FunctionSymbolTableEntry *> entries;
    bool insert(FunctionSymbolTableEntry *fste);
    FunctionSymbolTableEntry *lookup(std::string name);
};

#endif
