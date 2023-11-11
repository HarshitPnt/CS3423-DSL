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

VarSymbolTableEntry::VarSymbolTableEntry(std::string name, std::string type, std::string inner_type, int num_dim, std::vector<uint64_t> &dimensions)
{
    this->name = name;
    this->type = type;
    this->inner_type = inner_type;
    this->num_dim = num_dim;
    this->dimensions = dimensions;
}

VarSymbolTableEntry::VarSymbolTableEntry(std::string name)
{
    this->name = name;
    this->type = "";
    this->inner_type = "";
    this->num_dim = 0;
    this->dimensions.clear();
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
    std::cout << this->name << " " << this->type << " " << this->inner_type << " " << this->num_dim << " " << std::endl;
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
