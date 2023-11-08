#pragma once
#include <string>
#include <map>
#include <list>

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

class StructSymbolTableList
{
public:
    std::map<std::string, StructSymbolTable *> entries;
    int insert(StructSymbolTable *sste);
    StructSymbolTable *lookup(std::string name);
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