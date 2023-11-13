#include "../includes/semantic.hh"

VarSymbolTableList *vstl;
FunctionSymbolTable *fst;
VarSymbolTable *global_vst;
StructSymbolTable *sst;
VarSymbolTable *current_vst;
void initST()
{
    vstl = new VarSymbolTableList();
    fst = new FunctionSymbolTable();
    global_vst = new VarSymbolTable();
    sst = new StructSymbolTable();
    current_vst = global_vst;
    vstl->insert(global_vst);
}

VTYPE_PRIMITIVE getPrimitiveType(char *type)
{
    std::string s = std::string(type);
    if (s.compare("bool") == 0)
        return TYPE_BOOL;
    else if (s.compare("char") == 0)
        return TYPE_CHAR;
    else if (s.compare("int_8") == 0)
        return TYPE_INT_8;
    else if (s.compare("int_16") == 0)
        return TYPE_INT_16;
    else if (s.compare("int_32") == 0)
        return TYPE_INT_32;
    else if (s.compare("int_64") == 0)
        return TYPE_INT_64;
    else if (s.compare("uint_8") == 0)
        return TYPE_UINT_8;
    else if (s.compare("uint_16") == 0)
        return TYPE_UINT_16;
    else if (s.compare("uint_32") == 0)
        return TYPE_UINT_32;
    else if (s.compare("uint_64") == 0)
        return TYPE_UINT_64;
    else if (s.compare("float_32") == 0)
        return TYPE_FLOAT_32;
    else if (s.compare("float_64") == 0)
        return TYPE_FLOAT_64;
    exit(1);
}

VTYPE_AUTOMATA getAutomataType(char *type)
{
    std::string s = std::string(type);
    if (s.compare("dfa") == 0)
        return TYPE_DFA;
    else if (s.compare("nfa") == 0)
        return TYPE_NFA;
    else if (s.compare("pda") == 0)
        return TYPE_PDA;
    else if (s.compare("cfg") == 0)
        return TYPE_CFG;
    exit(1);
}

VTYPE_SET getSetType(char *type)
{
    std::string s = std::string(type);
    if (s.compare("u_set") == 0)
        return TYPE_USET;
    else if (s.compare("o_set") == 0)
        return TYPE_OSET;
    exit(1);
}

VTYPE_SR getSRType(char *type)
{
    std::string s = std::string(type);
    if (s.compare("string") == 0)
        return TYPE_STR;
    else if (s.compare("regex") == 0)
        return TYPE_REGEX;
    exit(1);
}

bool checkRegex(std::string reg)
{
    regex_t regex;
    int reti = regcomp(&regex, reg.c_str(), 0);
    if (reti != 0)
        return false;
    int len = reg.length();
    for (int i = 0; i < len; i++)
    {
        if (i != len - 1 && reg[i] == '$' && reg[i + 1] == '{')
        {
            std::string var = "";
            int j = i + 2;
            while (reg[j] != '}')
            {
                if (reg[j] == '\0')
                    return false;
                var += reg[j];
                j++;
            }
            char *c = (char *)var.c_str();
            if (checkValidID(c) == false)
                return false;
            i = j;
        }
    }
    return true;
}

bool checkValidID(char *id)
{
    try
    {
        regex_t regex;
        int reti = regcomp(&regex, "^[a-zA-Z_][a-zA-Z0-9_]*", 0);
        if (reti == 0)
        {
            int val = regexec(&regex, id, 0, NULL, 0);
            std::cout << val << std::endl;
            if (val == REG_NOMATCH)
                return false;
            return true;
        }
        return false;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return false;
}

VarSymbolTableEntry::VarSymbolTableEntry(std::string name, std::string type, inner_type *inner)
{
    this->name = name;
    this->type = type;
    this->inner = inner;
}

VarSymbolTableEntry::VarSymbolTableEntry(std::string name)
{
    this->name = name;
    this->type = "";
    this->inner = NULL;
}

int VarSymbolTable::insert(VarSymbolTableEntry *vste)
{
    if (this->entries.find(vste->name) != this->entries.end())
        return 1;
    this->entries[vste->name] = vste;
    return 0;
}

VarSymbolTableEntry *VarSymbolTable::lookup(std::string name)
{
    if (this->entries.find(name) == this->entries.end())
        return NULL;
    return this->entries[name];
}

int VarSymbolTableList::insert(VarSymbolTable *vst)
{
    this->entries.push_front(vst);
    return 0;
}

VarSymbolTable *VarSymbolTableList::lookup(std::string name)
{
    for (auto it = this->entries.begin(); it != this->entries.end(); it++)
    {
        if ((*it)->lookup(name) != NULL)
            return *it;
    }
    return NULL;
}

bool VarSymbolTable::backpatch(VarSymbolTableEntry *vste, std::string type, inner_type *inner, VarSymbolTable *struct_vst)
{
    if (this->entries.find(vste->name) == this->entries.end())
        return 1;
    vste->type = type;
    vste->inner = inner;
    vste->struct_vst = struct_vst;
    return 0;
}

StructSymbolTableEntry::StructSymbolTableEntry(std::string name, VarSymbolTable *fields)
{
    this->name = name;
    this->fields = fields;
}
bool StructSymbolTable::insert(StructSymbolTableEntry *sste)
{
    if (this->entries.find(sste->name) != this->entries.end())
        return 1;
    this->entries[sste->name] = sste;
    return 0;
}

StructSymbolTableEntry *StructSymbolTable::lookup(std::string name)
{
    if (this->entries.find(name) == this->entries.end())
        return NULL;
    return this->entries[name];
}

FunctionSymbolTableEntry::FunctionSymbolTableEntry(std::string name, int num_params, VarSymbolTable *params, std::string return_type)
{
    this->name = name;
    this->num_params = num_params;
    this->params = params;
    this->return_type = return_type;
}

bool FunctionSymbolTable::insert(FunctionSymbolTableEntry *fste)
{
    if (this->entries.find(fste->name) != this->entries.end())
        return 1;
    this->entries[fste->name] = fste;
    return 0;
}

FunctionSymbolTableEntry *FunctionSymbolTable::lookup(std::string name)
{
    if (this->entries.find(name) == this->entries.end())
        return NULL;
    return this->entries[name];
}

bool isInteger(VTYPE_PRIMITIVE vtp)
{
    if (vtp == TYPE_INT_64 || vtp == TYPE_INT_32 || vtp == TYPE_INT_16 || vtp == TYPE_INT_8 || vtp == TYPE_UINT_8 || vtp == TYPE_UINT_16 || vtp == TYPE_UINT_32 || vtp == TYPE_UINT_64)
        return true;
    return false;
}

void VarSymbolTableEntry::print()
{
    std::cout << this->name << " " << this->type << " ";
    this->inner->print();
    std::cout << std::endl;
}

void VarSymbolTable::print()
{
    for (auto it = this->entries.begin(); it != this->entries.end(); it++)
    {
        (*it).second->print();
    }
}

void VarSymbolTableList::print()
{
    for (auto it = this->entries.begin(); it != this->entries.end(); it++)
    {
        (*it)->print();
    }
}

std::string getType(type_attr *t_attr)
{
    if (t_attr->indicator == 1)
    {
        switch (t_attr->vtp)
        {
        case TYPE_INT_8:
            return std::string("int_8");
        case TYPE_INT_16:
            return std::string("int_16");
        case TYPE_INT_32:
            return std::string("int_32");
        case TYPE_INT_64:
            return std::string("int_64");
        case TYPE_UINT_8:
            return std::string("uint_8");
        case TYPE_UINT_16:
            return std::string("uint_16");
        case TYPE_UINT_32:
            return std::string("uint_32");
        case TYPE_UINT_64:
            return std::string("uint_64");
        case TYPE_FLOAT_32:
            return std::string("float_32");
        case TYPE_FLOAT_64:
            return std::string("float_64");
        case TYPE_CHAR:
            return std::string("char");
        case TYPE_BOOL:
            return std::string("bool");
        }
    }
    if (t_attr->indicator == 2)
    {
        switch (t_attr->vts)
        {
        case TYPE_USET:
            return std::string("u_set");
        case TYPE_OSET:
            return std::string("o_set");
        }
    }
    if (t_attr->indicator == 3)
    {
        switch (t_attr->vta)
        {
        case TYPE_DFA:
            return std::string("dfa");
        case TYPE_NFA:
            return std::string("nfa");
        case TYPE_PDA:
            return std::string("pda");
        case TYPE_CFG:
            return std::string("cfg");
        }
    }
    if (t_attr->indicator == 4)
    {
        switch (t_attr->vtsr)
        {
            {
            case TYPE_STR:
                return std::string("string");
            case TYPE_REGEX:
                return std::string("regex");
            }
        }
    }
    if (t_attr->indicator == 5)
    {
        return std::string("struct");
    }
    return std::string("sets");
}

inner_type::inner_type(inner_type *inner, std::string type)
{
    this->inner = inner;
    this->type = type;
}

void inner_type::print()
{
    inner_type *current = this;
    while (current)
    {
        std::cout << current->type << " ";
        current = current->inner;
    }
}

bool VarSymbolTableList::remove()
{
    if (this->entries.size() == 0)
        return 1;
    this->entries.pop_front();
    return 0;
}

VarSymbolTable *VarSymbolTableList::getTop()
{
    if (this->entries.size() == 0)
        return NULL;
    return this->entries.front();
}

void StructSymbolTable::print()
{
    for (auto it = this->entries.begin(); it != this->entries.end(); it++)
    {
        std::cout << (*it).first << " ";
        (*it).second->fields->print();
    }
}

bool isCoherent(std::string type1, std::string type2)
{
    if (type1.compare(type2) == 0)
        return true;
    if (type1 == "int_8" || type1 == "int_16" || type1 == "int_32" || type1 == "int_64" || type1 == "uint_8" || type1 == "uint_16" || type1 == "uint_32" || type1 == "uint_64")
    {
        if (type2 == "int_8" || type2 == "int_16" || type2 == "int_32" || type2 == "int_64" || type2 == "uint_8" || type2 == "uint_16" || type2 == "uint_32" || type2 == "uint_64")
            return true;
        if (type2 == "float_32" || type2 == "float_64")
            return true;
        if (type2 == "char")
            return true;
        if (type2 == "bool")
            return true;
        return false;
    }
    if (type1 == "float_32" || type1 == "float_64")
    {
        if (type2 == "int_8" || type2 == "int_16" || type2 == "int_32" || type2 == "int_64" || type2 == "uint_8" || type2 == "uint_16" || type2 == "uint_32" || type2 == "uint_64")
            return true;
        if (type2 == "float_32" || type2 == "float_64")
            return true;
        if (type2 == "char")
            return true;
        if (type2 == "bool")
            return true;
        return false;
    }
    if (type1 == "char")
    {
        if (type2 == "int_8" || type2 == "int_16" || type2 == "int_32" || type2 == "int_64" || type2 == "uint_8" || type2 == "uint_16" || type2 == "uint_32" || type2 == "uint_64")
            return true;
        if (type2 == "float_32" || type2 == "float_64")
            return true;
        if (type2 == "char")
            return true;
        if (type2 == "bool")
            return true;
        return false;
    }
    if (type1 == "bool")
    {
        if (type2 == "int_8" || type2 == "int_16" || type2 == "int_32" || type2 == "int_64" || type2 == "uint_8" || type2 == "uint_16" || type2 == "uint_32" || type2 == "uint_64")
            return true;
        if (type2 == "float_32" || type2 == "float_64")
            return true;
        if (type2 == "char")
            return true;
        if (type2 == "bool")
            return true;
        return false;
    }
    return false;
}
