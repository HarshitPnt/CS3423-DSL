#include "../includes/semantic.hh"
#include <string>

VarSymbolTableList *vstl;
FunctionSymbolTable *fst;
VarSymbolTable *global_vst;
StructSymbolTable *sst;
VarSymbolTable *current_vst;

void StructSymbolTable::init()
{
    // insert nterm, term, alphabets, productions, states, start, accept
    // insert terminal
    VarSymbolTable *term = new VarSymbolTable();
    term = NULL;
    StructSymbolTableEntry *sste_term = new StructSymbolTableEntry("states", term);
    // insert alphabets
    VarSymbolTable *alphabets = new VarSymbolTable();
    alphabets = NULL;
    StructSymbolTableEntry *sste_alphabets = new StructSymbolTableEntry("alphabets", alphabets);
    // insert productions
    VarSymbolTable *productions = new VarSymbolTable();
    productions = NULL;
    StructSymbolTableEntry *sste_productions = new StructSymbolTableEntry("productions", productions);
    // insert transitions_dfa
    VarSymbolTable *transitions_dfa = new VarSymbolTable();
    transitions_dfa = NULL;
    StructSymbolTableEntry *sste_transitions_dfa = new StructSymbolTableEntry("transitions_dfa", transitions_dfa);
    // insert transitions_nfa
    VarSymbolTable *transitions_nfa = new VarSymbolTable();
    transitions_nfa = NULL;
    StructSymbolTableEntry *sste_transitions_nfa = new StructSymbolTableEntry("transitions_nfa", transitions_nfa);
    // insert transitions_pda
    VarSymbolTable *transitions_pda = new VarSymbolTable();
    transitions_pda = NULL;
    StructSymbolTableEntry *sste_transitions_pda = new StructSymbolTableEntry("transitions_pda", transitions_pda);
    // insert start
    VarSymbolTable *start = new VarSymbolTable();
    start = NULL;
    StructSymbolTableEntry *sste_start = new StructSymbolTableEntry("start", start);
    // insert accept
    VarSymbolTable *accept = new VarSymbolTable();
    accept = NULL;
    StructSymbolTableEntry *sste_accept = new StructSymbolTableEntry("accept", accept);
    sst->insert(sste_term);
    sst->insert(sste_alphabets);
    sst->insert(sste_productions);
    sst->insert(sste_start);
    sst->insert(sste_accept);
    sst->insert(sste_transitions_dfa);
    sst->insert(sste_transitions_nfa);
    sst->insert(sste_transitions_pda);
    // insert cfg
    VarSymbolTable *cfg = new VarSymbolTable();
    cfg->insert(new VarSymbolTableEntry("N", "alphabets", NULL));
    cfg->insert(new VarSymbolTableEntry("T", "states", NULL));
    cfg->insert(new VarSymbolTableEntry("P", "productions", NULL));
    cfg->insert(new VarSymbolTableEntry("S", "start", NULL));
    StructSymbolTableEntry *sste_cfg = new StructSymbolTableEntry("cfg", cfg);
    // insert dfa
    VarSymbolTable *dfa = new VarSymbolTable();
    dfa->insert(new VarSymbolTableEntry("Q", "states", NULL));
    dfa->insert(new VarSymbolTableEntry("S", "alphabets", NULL));
    dfa->insert(new VarSymbolTableEntry("delta", "transitions_dfa", NULL));
    dfa->insert(new VarSymbolTableEntry("q0", "start", NULL));
    dfa->insert(new VarSymbolTableEntry("F", "accept", NULL));
    StructSymbolTableEntry *sste_dfa = new StructSymbolTableEntry("dfa", dfa);
    // insert nfa
    VarSymbolTable *nfa = new VarSymbolTable();
    nfa->insert(new VarSymbolTableEntry("Q", "states", NULL));
    nfa->insert(new VarSymbolTableEntry("S", "alphabets", NULL));
    nfa->insert(new VarSymbolTableEntry("delta", "transitions_nfa", NULL));
    nfa->insert(new VarSymbolTableEntry("q0", "start", NULL));
    nfa->insert(new VarSymbolTableEntry("F", "accept", NULL));
    StructSymbolTableEntry *sste_nfa = new StructSymbolTableEntry("nfa", nfa);
    // insert pda
    VarSymbolTable *pda = new VarSymbolTable();
    pda->insert(new VarSymbolTableEntry("Q", "states", NULL));
    pda->insert(new VarSymbolTableEntry("S", "alphabets", NULL));
    pda->insert(new VarSymbolTableEntry("delta", "transitions_pda", NULL));
    pda->insert(new VarSymbolTableEntry("q0", "start", NULL));
    pda->insert(new VarSymbolTableEntry("F", "accept", NULL));
    pda->insert(new VarSymbolTableEntry("G", "alphabets", NULL));
    StructSymbolTableEntry *sste_pda = new StructSymbolTableEntry("pda", pda);
    // insert all symboltable entries into symboltable
    sst->insert(sste_cfg);
    sst->insert(sste_dfa);
    sst->insert(sste_nfa);
    sst->insert(sste_pda);
}

void initST()
{
    vstl = new VarSymbolTableList();
    fst = new FunctionSymbolTable();
    global_vst = new VarSymbolTable();
    sst = new StructSymbolTable();
    sst->init();
    current_vst = global_vst;
    vstl->insert(global_vst);
}

VTYPE_PRIMITIVE getPrimitiveType(const char *type)
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

VTYPE_AUTOMATA getAutomataType(const char *type)
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

VTYPE_SET getSetType(const char *type)
{
    std::string s = std::string(type);
    if (s.compare("u_set") == 0)
        return TYPE_USET;
    else if (s.compare("o_set") == 0)
        return TYPE_OSET;
    exit(1);
}

VTYPE_SR getSRType(const char *type)
{
    std::string s = std::string(type);
    if (s.compare("string") == 0)
        return TYPE_STR;
    else if (s.compare("regex") == 0)
        return TYPE_REGEX;
    else
        return TYPE_STRU;
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
    std::cout << this->inner->print();
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
    std::cout << this->entries.size() << std::endl;
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
        return std::string("string");
    }
    if (t_attr->indicator == 5)
    {
        return std::string("regex");
    }
    if (t_attr->indicator == 7)
    {
        return std::string("struct");
    }
    return std::string("sets");
}

std::string getType(id_attr *t_attr)
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
        return std::string("string");
    }
    if (t_attr->indicator == 5)
    {
        return std::string("regex");
    }
    if (t_attr->indicator == 7)
    {
        return std::string("struct");
    }
    return std::string("sets");
}

inner_type *genInnerType(std::string inner)
{
    if (inner.find(" ") == std::string::npos || inner.find(" ") == inner.length() - 1)
        return new inner_type(NULL, inner);
    else
    {
        size_t space = inner.find(" ");
        std::string type = inner.substr(0, space);
        inner_type *inner_inner = genInnerType(inner.substr(space + 1));
        return new inner_type(inner_inner, type);
    }
}

inner_type::inner_type(inner_type *inner, std::string type)
{
    this->inner = inner;
    this->type = type;
}

std::string inner_type::print()
{
    inner_type *current = this;
    std::string ret("");
    while (current)
    {
        ret += current->type + std::string(" ");
        current = current->inner;
    }
    return ret;
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

bool isCoherent(std::string type_1, std::string type_2)
{
    // std::cout << type_1.length() << " " << type_2.length() << std::endl;
    if (type_1.compare(type_2) == 0)
        return true;
    if ((!type_1.length() && type_2.length()) || (type_1.length() && !type_2.length()))
        return false;
    std::string type1;
    std::string type2;
    bool flag1_end = false, flag2_end = false;
    if (type_1.find(' ') == std::string::npos)
    {
        type1 = type_1;
        flag1_end = true;
    }
    else
        type1 = type_1.substr(0, type_1.find(' '));
    if (type_2.find(' ') == std::string::npos)
    {
        type2 = type_2;
        flag2_end = true;
    }
    else
        type2 = type_2.substr(0, type_2.find(' '));
    // std::cout << type1 << " " << type2 << std::endl;
    if (type1 == "int_8" || type1 == "int_16" || type1 == "int_32" || type1 == "int_64" || type1 == "uint_8" || type1 == "uint_16" || type1 == "uint_32" || type1 == "uint_64")
    {
        if (type2 == "int_8" || type2 == "int_16" || type2 == "int_32" || type2 == "int_64" || type2 == "uint_8" || type2 == "uint_16" || type2 == "uint_32" || type2 == "uint_64")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        if (type2 == "float_32" || type2 == "float_64")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        if (type2 == "char")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        if (type2 == "bool")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        return false;
    }
    if (type1 == "float_32" || type1 == "float_64")
    {
        if (type2 == "int_8" || type2 == "int_16" || type2 == "int_32" || type2 == "int_64" || type2 == "uint_8" || type2 == "uint_16" || type2 == "uint_32" || type2 == "uint_64")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        if (type2 == "float_32" || type2 == "float_64")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        if (type2 == "char")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        if (type2 == "bool")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        return false;
    }
    if (type1 == "char")
    {
        if (type2 == "int_8" || type2 == "int_16" || type2 == "int_32" || type2 == "int_64" || type2 == "uint_8" || type2 == "uint_16" || type2 == "uint_32" || type2 == "uint_64")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        if (type2 == "float_32" || type2 == "float_64")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        if (type2 == "char")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        if (type2 == "bool")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        return false;
    }
    if (type1 == "bool")
    {
        if (type2 == "int_8" || type2 == "int_16" || type2 == "int_32" || type2 == "int_64" || type2 == "uint_8" || type2 == "uint_16" || type2 == "uint_32" || type2 == "uint_64")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        if (type2 == "float_32" || type2 == "float_64")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        if (type2 == "char")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        if (type2 == "bool")
            return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
        return false;
    }
    if (type1 == "o_set" && (type2 == "o_set" || type2 == "sets"))
    {
        return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
    }
    if (type1 == "u_set" && (type2 == "u_set" || type2 == "sets"))
    {
        return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
    }
    if (type1 == type2)
        return isCoherent((flag1_end ? std::string("") : type_1.substr(type_1.find(' ') + 1)), (flag2_end ? std::string("") : type_2.substr(type_2.find(' ') + 1)));
    return false;
}

bool isStruct(std::string type)
{
    if (type != "int_8" && type != "int_16" && type != "int_32" && type != "int_64" && type != "uint_8" && type != "uint_16" && type != "uint_32" && type != "uint_64" && type != "float_32" && type != "float_64" && type != "char" && type != "bool" && type != "string" && type != "regex" && type != "u_set" && type != "o_set")
        return true;
    return false;
}

bool isPrimitive(std::string type)
{
    if (type == "int_8" || type == "int_16" || type == "int_32" || type == "int_64" || type == "uint_8" || type == "uint_16" || type == "uint_32" || type == "uint_64" || type == "float_32" || type == "float_64" || type == "char" || type == "bool")
        return true;
    return false;
}

bool isSet(std::string type)
{
    if (type == "u_set" || type == "o_set")
        return true;
    return false;
}

bool isAutomata(std::string type)
{
    if (type == "dfa" || type == "nfa" || type == "pda" || type == "cfg")
        return true;
    return false;
}

bool isSR(std::string type)
{
    if (type == "string" || type == "regex")
        return true;
    return false;
}

std::pair<bool, std::string> checkInner(std::string inner, std::string &name)
{
    while (true)
    {
        if (name.length() == 0 || name[0] == '.')
            return std::make_pair(true, inner);
        else
        {
            size_t space = inner.find(" ");
            std::string next;
            if (space == std::string::npos)
                next = inner;
            else
                next = inner.substr(0, space);
            if (next != "o_set" && next != "string")
                return std::make_pair(false, next + std::string(" : not a o_set/string"));
            if (next == "string")
            {
                std::string copy = name;
                if (copy.find("]") != copy.length() - 1)
                {
                    size_t l_sq = copy.find("]");
                    if (copy[l_sq + 1] == '.')
                    {
                        return std::make_pair(false, std::string("char is not a struct"));
                    }
                    else
                    {
                        return std::make_pair(false, std::string("char is not a o_set"));
                    }
                }
                else
                {
                    return std::make_pair(true, std::string("char"));
                }
            }
            size_t f_sq = name.find("[");
            size_t l_sq = name.find("]");
            if (name.substr(f_sq + 1, l_sq - f_sq - 1) != "__expr__")
            {
                // check dims
            }
            name = name.substr(l_sq + 1);
            return checkInner(inner.substr(space + 1), name);
        }
    }
}

std::pair<bool, std::string> checkPseudoID(VarSymbolTable *entry, std::string name, std::string struct_name)
{
    // find occurrence of first . and []
    // std::cout << name << std::endl;
    size_t f_dot = name.find(".");
    size_t f_sq = name.find("[");
    size_t l_sq = name.find("]");
    if (f_dot == std::string::npos && f_sq == std::string::npos)
    {
        // std::cout << "HERE SIMPLE" << std::endl;
        // normal id
        if (entry == NULL)
        {
            if (vstl->lookup(name) == NULL)
                return std::make_pair(false, name + std::string(" : not defined"));
            else
            {
                std::string type = vstl->lookup(name)->lookup(name)->type;
                // std::cout << type.length() << std::endl;
                if (type == "o_set" || type == "u_set")
                    return std::make_pair(true, std::string("@found ") + type + std::string(" ") + vstl->lookup(name)->lookup(name)->inner->print());
                else
                    return std::make_pair(true, std::string("@found ") + type);
            }
        }
        else
        {
            if (entry->lookup(name) == NULL)
                return std::make_pair(false, name + std::string(" : not a member of struct ") + std::string(struct_name));
            else
            {
                if (entry->lookup(name)->type == "o_set" || entry->lookup(name)->type == "u_set")
                    return std::make_pair(true, std::string("@found ") + entry->lookup(name)->type + std::string(" ") + entry->lookup(name)->inner->print());
                else
                    return std::make_pair(true, std::string("@found ") + entry->lookup(name)->type);
            }
        }
    }
    else if (f_dot != std::string::npos && (f_sq == std::string::npos || f_dot < f_sq))
    {
        // vstl->print();
        std::string id1 = name.substr(0, f_dot);
        // std::cout << "HERE DOT" << std::endl;
        if (entry == NULL)
        {
            // std::cout << "GLOBAL" << std::endl;
            if (vstl->lookup(id1) == NULL)
                return make_pair(false, id1 + std::string(" : not defined"));
            else
            {
                // A.a
                // std::cout << "HERE" << std::endl;
                VarSymbolTable *vst_local = vstl->lookup(id1);
                // if (!vst_local)
                //     std::cout << "error" << std::endl;
                // else
                //     std::cout << "no error" << std::endl;
                // searching for A
                VarSymbolTableEntry *entry_local = vst_local->lookup(id1); // found A
                // std::cout << "found id" << std::endl;
                // if (entry_local)
                //     std::cout << "no error" << std::endl;
                // entry_local->print();
                // entry_local->struct_vst->print();
                if (!isStruct(entry_local->type)) // checking if A is a struct
                    return make_pair(false, id1 + std::string(" : not a struct"));
                // std::cout << "OK Struct Verified" << std::endl;
                VarSymbolTable *next = entry_local->struct_vst; // retrieving the struct_vst for A
                // extract the member from expression
                std::string id2;
                size_t next_f_dot = name.find(".", f_dot + 1);
                if (next_f_dot == std::string::npos && f_sq == std::string::npos)
                    id2 = name.substr(f_dot + 1);
                else if (next_f_dot == std::string::npos)
                    id2 = name.substr(f_dot + 1, f_sq - f_dot - 1);
                else
                    id2 = name.substr(f_dot + 1, std::min(f_sq, next_f_dot) - f_dot - 1);
                // next->print();
                // std::cout << id2 << std::endl;
                if (next->lookup(id2) == NULL) // check if a is member of A
                    return make_pair(false, id2 + std::string(" : not a member of struct ") + id1);
                return checkPseudoID(next, name.substr(f_dot + 1), entry_local->type);
            }
        }
        else
        {
            // std::cout << "Struct" << std::endl;
            // check in the struct symbol table
            if (entry->lookup(id1) == NULL)
                return make_pair(false, id1 + std::string(" : not a member of struct ") + std::string(struct_name));
            else
            {
                if (!isStruct(entry->lookup(id1)->type))
                    return make_pair(false, id1 + std::string(" : not a struct"));
                VarSymbolTable *vst_local = entry->lookup(id1)->struct_vst;
                std::string id2;
                size_t next_f_dot = name.find(".", f_dot + 1);
                if (next_f_dot == std::string::npos && f_sq == std::string::npos)
                    id2 = name.substr(f_dot + 1);
                else if (next_f_dot == std::string::npos)
                    id2 = name.substr(f_dot + 1, f_sq - f_dot - 1);
                else
                    id2 = name.substr(f_dot + 1, std::min(f_sq, next_f_dot) - f_dot - 1);

                if (!vst_local->lookup(id2))
                    return make_pair(false, id2 + std::string(" : not a member of struct ") + id1);
                return checkPseudoID(vst_local, name.substr(f_dot + 1), id2);
            }
        }
    }
    else if ((f_dot == std::string::npos && f_sq != std::string::npos) || (f_sq != std::string::npos && (f_sq < f_dot)))
    {
        // std::cout << "HERE BRACKS" << std::endl;
        std::string id2 = name.substr(f_sq + 1, l_sq - f_sq - 1);
        std::string id1 = name.substr(0, f_sq);
        // std::cout << id1 << " " << id2 << std::endl;
        if (id2 != "__expr__") // check dimensions
        {
            // check dims
        }
        if (l_sq == name.length() - 1)
        {
            if (entry == NULL)
            {
                // std::cout << "GLOBAL BRACKS" << std::endl;
                if (vstl->lookup(id1) == NULL)
                    return make_pair(false, id1 + std::string(" : not defined"));
                else
                {
                    if (vstl->lookup(id1)->lookup(id1)->type != "string" && vstl->lookup(id1)->lookup(id1)->type != "o_set")
                        return make_pair(false, id1 + std::string(" : not a o_set/string"));
                    else
                    {
                        std::string type = vstl->lookup(id1)->lookup(id1)->type;
                        if (type == "o_set" || type == "string")
                            return make_pair(true, std::string("@found ") + type + (type == "o_set" ? (std::string(" ") + vstl->lookup(id1)->lookup(id1)->inner->print()) : std::string("")));
                        else
                            return make_pair(true, std::string("@found ") + type);
                    }
                }
            }
            else
            {
                if (entry->lookup(id1) == NULL)
                    return make_pair(false, id1 + std::string(" : not a member of struct ") + std::string(struct_name));
                else
                {
                    if (entry->lookup(id1)->type != "string" && entry->lookup(id1)->type != "o_set")
                        return make_pair(false, id1 + std::string(" : not a o_set/string"));
                    else
                    {
                        if (entry->lookup(id1)->type == "o_set")
                        {
                            std::string inner = entry->lookup(id1)->inner->print();
                            return make_pair(true, std::string("@found ") + inner);
                        }
                        else
                        {
                            return make_pair(true, std::string("@found char"));
                        }
                    }
                }
            }
        }
        else
        {
            // check inner with pseudo_ID
            std::string inner;
            if (entry == NULL)
            {
                if (vstl->lookup(id1) == NULL)
                    return make_pair(false, id1 + std::string(" : not defined"));
                else
                {
                    if (vstl->lookup(id1)->lookup(id1)->type != "string" && vstl->lookup(id1)->lookup(id1)->type != "o_set")
                        return make_pair(false, id1 + std::string(" : not a o_set/string"));
                    else
                    {
                        if (vstl->lookup(id1)->lookup(id1)->type == "string")
                            return make_pair(false, std::string(" char: not a o_set/struct"));
                        inner = vstl->lookup(id1)->lookup(id1)->inner->print();
                        // std::cout << inner << std::endl;
                        if (name[l_sq + 1] == '.')
                        {
                            // check if next inner is struct
                            size_t space = inner.find(" ");
                            std::string next;
                            if (space == std::string::npos)
                                next = inner;
                            else
                                next = inner.substr(0, space);
                            if (isStruct(next))
                            {
                                VarSymbolTable *next_vst = sst->lookup(next)->fields;
                                return checkPseudoID(next_vst, name.substr(l_sq + 2), next);
                            }
                            else
                            {
                                return make_pair(false, next + std::string(": is not a 'struct'"));
                            }
                        }
                        else
                        {
                            // check inner
                            name = name.substr(l_sq + 1);
                            std::pair<bool, std::string> ret = checkInner(inner, name);
                            if (ret.first == false)
                                return ret;
                            else
                            {
                                // now recurse with next A.a[1][2](here).b or A.a[1][2]
                                f_dot = name.find(".");
                                f_sq = name.find("[");
                                if (f_sq == std::string::npos && f_dot == std::string::npos)
                                    return make_pair(true, std::string("@found ") + ret.second);
                                else
                                {
                                    // check once then recurse
                                    std::string current_struct;
                                    if (ret.second[ret.second.length() - 1] == ' ')
                                        current_struct = ret.second.substr(0, ret.second.length() - 1);
                                    else
                                        current_struct = ret.second;
                                    if (sst->lookup(current_struct) == NULL)
                                        return make_pair(false, current_struct + std::string(" : not a struct"));
                                    VarSymbolTable *next_vst = sst->lookup(current_struct)->fields;
                                    size_t f_sq = name.find("[");
                                    size_t l_sq = name.find("]");
                                    size_t f_dot = name.find(".", 1);
                                    std::string next_name;
                                    if (f_dot == std::string::npos && f_sq == std::string::npos)
                                        next_name = name.substr(1);
                                    else if (f_dot == std::string::npos && f_sq != std::string::npos)
                                        next_name = name.substr(1, f_sq - 1);
                                    else if (f_dot != std::string::npos && f_sq == std::string::npos)
                                        next_name = name.substr(1, f_dot - 1);
                                    else
                                    {
                                        size_t minimum = std::min(f_sq, f_dot);
                                        next_name = name.substr(1, minimum - 1);
                                    }
                                    if (!next_vst->lookup(next_name))
                                        return make_pair(false, next_name + std::string(" : not a member of struct ") + ret.second);
                                    else
                                        return checkPseudoID(next_vst, name.substr(1), ret.second);
                                }
                            }
                            return checkPseudoID(vstl->lookup(id1), name.substr(f_sq + 1), inner);
                        }
                    }
                }
            }
            else
            {
                if (entry->lookup(id1) == NULL)
                    return make_pair(false, id1 + std::string(" : not a member of struct ") + std::string(struct_name));
                else
                {
                    if (entry->lookup(id1)->type != "o_set" && entry->lookup(id1)->type != "string")
                        return make_pair(false, id1 + std::string(" : not a o_set/string"));
                    else
                    {
                        std::string inner;
                        if (entry->lookup(id1)->type == "string")
                        {
                            inner = std::string("char");
                            if (name[l_sq + 1] == '.')
                                return make_pair(false, std::string("char : not a struct"));
                            else if (name[l_sq + 1] == '[')
                                return make_pair(false, std::string("char : not a set"));
                            else
                                return make_pair(true, std::string("@found char"));
                        }
                        else
                            inner = entry->lookup(id1)->inner->print();
                        // std::cout << inner << std::endl;
                        if (name[l_sq + 1] == '.')
                        {
                            // check if next inner is struct
                            size_t space = inner.find(" ");
                            std::string next;
                            if (space == std::string::npos)
                                next = inner;
                            else
                                next = inner.substr(0, space);
                            if (isStruct(next))
                            {
                                VarSymbolTable *next_vst = sst->lookup(next)->fields;
                                return checkPseudoID(next_vst, name.substr(l_sq + 2), next);
                            }
                            else
                            {
                                return make_pair(false, id1 + std::string(": is not a 'struct'"));
                            }
                        }
                        else
                        {
                            // check inner
                            name = name.substr(l_sq + 1);
                            std::pair<bool, std::string> ret = checkInner(inner, name);
                            if (ret.first == false)
                                return ret;
                            else
                            {
                                // now recurse with next A.a[1][2](here).b or A.a[1][2]
                                f_dot = name.find(".");
                                f_sq = name.find("[");
                                if (f_sq == std::string::npos && f_dot == std::string::npos)
                                    return make_pair(true, std::string("@found ") + ret.second);
                                else
                                {
                                    // check once then recurse
                                    // extract the first word from ret.second
                                    std::string current_struct;
                                    size_t x = ret.second.find(" ");
                                    if (x == std::string::npos)
                                        current_struct = ret.second;
                                    else
                                        current_struct = ret.second.substr(0, x);
                                    if (sst->lookup(current_struct) == NULL)
                                        return make_pair(false, current_struct + std::string(" : not a struct"));
                                    VarSymbolTable *next_vst = sst->lookup(current_struct)->fields;
                                    f_sq = name.find("[");
                                    l_sq = name.find("]");
                                    f_dot = name.find(".", 1);
                                    std::string next_name;
                                    if (f_dot == std::string::npos && f_sq == std::string::npos)
                                        next_name = name.substr(1);
                                    else if (f_dot == std::string::npos && f_sq != std::string::npos)
                                        next_name = name.substr(1, f_sq - 1);
                                    else if (f_dot != std::string::npos && f_sq == std::string::npos)
                                        next_name = name.substr(1, f_dot - 1);
                                    else
                                    {
                                        size_t minimum = std::min(f_sq, f_dot);
                                        next_name = name.substr(1, minimum - 1);
                                    }
                                    if (!next_vst->lookup(next_name))
                                        return make_pair(false, next_name + std::string(" : not a member of struct ") + ret.second);
                                    else
                                        return checkPseudoID(next_vst, name.substr(1), ret.second);
                                }
                            }
                            return checkPseudoID(entry, name.substr(f_sq + 1), inner);
                        }
                    }
                }
            }
        }
    }
    return make_pair(false, std::string("error"));
}

std::string getType(expr_attr *t_attr)
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
            return std::string("u_set ") + t_attr->inner->print();
        case TYPE_OSET:
            return std::string("o_set ") + t_attr->inner->print();
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
        return std::string("string");
    }
    if (t_attr->indicator == 5)
    {
        return std::string("regex");
    }
    if (t_attr->indicator == 7)
    {
        return t_attr->ifStruct;
    }
    return std::string("sets");
}

std::string stripFound(std::string ret)
{
    return ret.substr(ret.find(" ") + 1);
}

std::string trim(std::string str)
{
    while (str[str.length() - 1] == ' ' && str.length())
        str = str.substr(0, str.length() - 1);
    return str;
}