#include "../includes/semantic.hh"
#include <string>

VarSymbolTableList *vstl;
FunctionSymbolTable *fst;
VarSymbolTable *global_vst;
StructSymbolTable *sst;
VarSymbolTable *current_vst;
std::vector<std::string> type_maps_prim;
std::vector<std::string> type_maps_auto;
std::vector<std::string> type_maps_set;
std::vector<std::string> type_maps_sr;
std::set<std::string> *set_funcs;

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
    cfg->insert(new VarSymbolTableEntry("N", "states", NULL));
    cfg->insert(new VarSymbolTableEntry("T", "alphabets", NULL));
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

void initData()
{
    type_maps_prim.push_back("char");
    type_maps_prim.push_back("short");
    type_maps_prim.push_back("int");
    type_maps_prim.push_back("long int");
    type_maps_prim.push_back("unsigned char");
    type_maps_prim.push_back("unsigned short");
    type_maps_prim.push_back("unsigned int");
    type_maps_prim.push_back("unsigned long int");
    type_maps_prim.push_back("float");
    type_maps_prim.push_back("double");
    type_maps_prim.push_back("char");
    type_maps_prim.push_back("bool");
    type_maps_set.push_back("fsm::u_set");
    type_maps_set.push_back("fsm::o_set");
    type_maps_auto.push_back("fsm::cfg");
    type_maps_auto.push_back("fsm::dfa");
    type_maps_auto.push_back("fsm::nfa");
    type_maps_auto.push_back("fsm::pda");
    type_maps_sr.push_back("std::string");
    type_maps_sr.push_back("fsm::regex");
}

void initFSTSet()
{
    // size(o_set<T> S)
    StructSymbolTableEntry *sste_size_o_set = new StructSymbolTableEntry("@T_set_size", NULL);      // template type
    sste_size_o_set->isTemplate = true;                                                             // template type symbol table
    sst->insert(sste_size_o_set);                                                                   // insert template type into struct symbol table
    VarSymbolTable *size_o_set = new VarSymbolTable();                                              // function params
    inner_type *inner_size_o_set = genInnerType("@T_set_size");                                     // param inner type
    VarSymbolTableEntry *vste_size_o_set = new VarSymbolTableEntry("S", "o_set", inner_size_o_set); // param entry
    size_o_set->insert(vste_size_o_set);                                                            // insert param entry into param symbol table
    std::vector<std::string> size_template_params;
    size_template_params.push_back("@T_set_size");                                                                                          // insert template param into template param vector
    FunctionSymbolTableEntry *fste_size_o_set = new FunctionSymbolTableEntry("o_size", 1, size_o_set, "int_8", true, size_template_params); // function entry
    fste_size_o_set->id_list.push_back("S");                                                                                                // set isTemplate to true
    fst->insert(fste_size_o_set);                                                                                                           // insert function entry into function symbol table

    // size(u_set<T> S)
    StructSymbolTableEntry *sste_size_u_set = new StructSymbolTableEntry("@T_u_set_size", NULL);    // template type
    sste_size_u_set->isTemplate = true;                                                             // template type symbol table
    sst->insert(sste_size_u_set);                                                                   // insert template type into struct symbol table
    VarSymbolTable *size_u_set = new VarSymbolTable();                                              // function params
    inner_type *inner_size_u_set = genInnerType("@T_u_set_size");                                   // param inner type
    VarSymbolTableEntry *vste_size_u_set = new VarSymbolTableEntry("S", "u_set", inner_size_u_set); // param entry
    size_u_set->insert(vste_size_u_set);                                                            // insert param entry into param symbol table
    std::vector<std::string> size_template_params_u_set;
    size_template_params_u_set.push_back("@T_u_set_size");                                                                                        // insert template param into template param vector
    FunctionSymbolTableEntry *fste_size_u_set = new FunctionSymbolTableEntry("u_size", 1, size_u_set, "int_8", true, size_template_params_u_set); // function entry
    fste_size_u_set->id_list.push_back("S");                                                                                                      // set isTemplate to true
    fst->insert(fste_size_u_set);                                                                                                                 // insert function entry into function symbol table

    // o_empty(o_set<T> S)
    StructSymbolTableEntry *sste_empty_o_set = new StructSymbolTableEntry("@T_o_set_empty", NULL);    // template type
    sste_empty_o_set->isTemplate = true;                                                              // template type symbol table
    sst->insert(sste_empty_o_set);                                                                    // insert template type into struct symbol table
    VarSymbolTable *empty_o_set = new VarSymbolTable();                                               // function params
    inner_type *inner_empty_o_set = genInnerType("@T_o_set_empty");                                   // param inner type
    VarSymbolTableEntry *vste_empty_o_set = new VarSymbolTableEntry("S", "o_set", inner_empty_o_set); // param entry
    empty_o_set->insert(vste_empty_o_set);                                                            // insert param entry into param symbol table
    std::vector<std::string> empty_template_params;
    empty_template_params.push_back("@T_o_set_empty");                                                                                         // insert template param into template param vector
    FunctionSymbolTableEntry *fste_empty_o_set = new FunctionSymbolTableEntry("o_empty", 1, empty_o_set, "bool", true, empty_template_params); // function entry
    fste_empty_o_set->id_list.push_back("S");                                                                                                  // set isTemplate to true
    fst->insert(fste_empty_o_set);                                                                                                             // insert function entry into function symbol table

    // u_empty(u_set<T> S)
    StructSymbolTableEntry *sste_empty_u_set = new StructSymbolTableEntry("@T_u_set_empty", NULL);    // template type
    sste_empty_u_set->isTemplate = true;                                                              // template type symbol table
    sst->insert(sste_empty_u_set);                                                                    // insert template type into struct symbol table
    VarSymbolTable *empty_u_set = new VarSymbolTable();                                               // function params
    inner_type *inner_empty_u_set = genInnerType("@T_u_set_empty");                                   // param inner type
    VarSymbolTableEntry *vste_empty_u_set = new VarSymbolTableEntry("S", "u_set", inner_empty_u_set); // param entry
    empty_u_set->insert(vste_empty_u_set);                                                            // insert param entry into param symbol table
    std::vector<std::string> empty_template_params_u_set;
    empty_template_params_u_set.push_back("@T_u_set_empty");                                                                                         // insert template param into template param vector
    FunctionSymbolTableEntry *fste_empty_u_set = new FunctionSymbolTableEntry("u_empty", 1, empty_u_set, "bool", true, empty_template_params_u_set); // function entry
    fste_empty_u_set->id_list.push_back("S");                                                                                                        // set isTemplate to true
    fst->insert(fste_empty_u_set);                                                                                                                   // insert function entry into function symbol table

    // o_find(o_set<T> S, T x)
    StructSymbolTableEntry *sste_find_o_set = new StructSymbolTableEntry("@T_o_set_find", NULL);    // template type
    sste_find_o_set->isTemplate = true;                                                             // template type symbol table
    sst->insert(sste_find_o_set);                                                                   // insert template type into struct symbol table
    VarSymbolTable *find_o_set = new VarSymbolTable();                                              // function params
    inner_type *inner_find_o_set = genInnerType("@T_o_set_find");                                   // param inner type
    VarSymbolTableEntry *vste_find_o_set = new VarSymbolTableEntry("S", "o_set", inner_find_o_set); // param entry
    find_o_set->insert(vste_find_o_set);                                                            // param inner type
    VarSymbolTableEntry *vste_find_o_set_2 = new VarSymbolTableEntry("x", "@T_o_set_find", NULL);
    find_o_set->insert(vste_find_o_set_2); // param entry
    std::vector<std::string> find_template_params;
    find_template_params.push_back("@T_o_set_find");                                                                                       // insert template param into template param vector
    FunctionSymbolTableEntry *fste_find_o_set = new FunctionSymbolTableEntry("o_find", 2, find_o_set, "bool", true, find_template_params); // function entry
    fste_find_o_set->id_list.push_back("x");                                                                                               // set isTemplate to true
    fste_find_o_set->id_list.push_back("S");                                                                                               // set isTemplate to true
    fst->insert(fste_find_o_set);                                                                                                          // insert function entry into function symbol table

    // u_find(u_set<T> S, T x)
    StructSymbolTableEntry *sste_find_u_set = new StructSymbolTableEntry("@T_u_set_find", NULL);    // template type
    sste_find_u_set->isTemplate = true;                                                             // template type symbol table
    sst->insert(sste_find_u_set);                                                                   // insert template type into struct symbol table
    VarSymbolTable *find_u_set = new VarSymbolTable();                                              // function params
    inner_type *inner_find_u_set = genInnerType("@T_u_set_find");                                   // param inner type
    VarSymbolTableEntry *vste_find_u_set = new VarSymbolTableEntry("S", "u_set", inner_find_u_set); // param entry
    find_u_set->insert(vste_find_u_set);                                                            // param inner type
    VarSymbolTableEntry *vste_find_u_set_2 = new VarSymbolTableEntry("x", "@T_u_set_find", NULL);
    find_u_set->insert(vste_find_u_set_2); // param entry
    std::vector<std::string> find_template_params_u_set;
    find_template_params_u_set.push_back("@T_u_set_find");                                                                                       // insert template param into template param vector
    FunctionSymbolTableEntry *fste_find_u_set = new FunctionSymbolTableEntry("u_find", 2, find_u_set, "bool", true, find_template_params_u_set); // function entry
    fste_find_u_set->id_list.push_back("x");                                                                                                     // set isTemplate to true
    fste_find_u_set->id_list.push_back("S");                                                                                                     // set isTemplate to true
    fst->insert(fste_find_u_set);                                                                                                                // insert function entry into function symbol table

    // o_insert(o_set<T> S, T x)
    StructSymbolTableEntry *sste_insert_o_set = new StructSymbolTableEntry("@T_o_set_insert", NULL);    // template type
    sste_insert_o_set->isTemplate = true;                                                               // template type symbol table
    sst->insert(sste_insert_o_set);                                                                     // insert template type into struct symbol table
    VarSymbolTable *insert_o_set = new VarSymbolTable();                                                // function params
    inner_type *inner_insert_o_set = genInnerType("@T_o_set_insert");                                   // param inner type
    VarSymbolTableEntry *vste_insert_o_set = new VarSymbolTableEntry("S", "o_set", inner_insert_o_set); // param entry
    insert_o_set->insert(vste_insert_o_set);                                                            // param inner type
    VarSymbolTableEntry *vste_insert_o_set_2 = new VarSymbolTableEntry("x", "@T_o_set_insert", NULL);
    insert_o_set->insert(vste_insert_o_set_2); // param entry
    std::vector<std::string> insert_template_params;
    insert_template_params.push_back("@T_o_set_insert");                                                                                           // insert template param into template param vector
    FunctionSymbolTableEntry *fste_insert_o_set = new FunctionSymbolTableEntry("o_insert", 2, insert_o_set, "bool", true, insert_template_params); // function entry
    fste_insert_o_set->id_list.push_back("x");                                                                                                     // set isTemplate to true
    fste_insert_o_set->id_list.push_back("S");                                                                                                     // set isTemplate to true
    fst->insert(fste_insert_o_set);                                                                                                                // insert function entry into function symbol table

    // u_insert(u_set<T> S, T x)
    StructSymbolTableEntry *sste_insert_u_set = new StructSymbolTableEntry("@T_u_set_insert", NULL);    // template type
    sste_insert_u_set->isTemplate = true;                                                               // template type symbol table
    sst->insert(sste_insert_u_set);                                                                     // insert template type into struct symbol table
    VarSymbolTable *insert_u_set = new VarSymbolTable();                                                // function params
    inner_type *inner_insert_u_set = genInnerType("@T_u_set_insert");                                   // param inner type
    VarSymbolTableEntry *vste_insert_u_set = new VarSymbolTableEntry("S", "u_set", inner_insert_u_set); // param entry
    insert_u_set->insert(vste_insert_u_set);                                                            // param inner type
    VarSymbolTableEntry *vste_insert_u_set_2 = new VarSymbolTableEntry("x", "@T_u_set_insert", NULL);
    insert_u_set->insert(vste_insert_u_set_2); // param entry
    std::vector<std::string> insert_template_params_u_set;
    insert_template_params_u_set.push_back("@T_u_set_insert");                                                                                           // insert template param into template param vector
    FunctionSymbolTableEntry *fste_insert_u_set = new FunctionSymbolTableEntry("u_insert", 2, insert_u_set, "bool", true, insert_template_params_u_set); // function entry
    fste_insert_u_set->id_list.push_back("x");                                                                                                           // set isTemplate to true
    fste_insert_u_set->id_list.push_back("S");                                                                                                           // set isTemplate to true
    fst->insert(fste_insert_u_set);                                                                                                                      // insert function entry into function symbol table

    // o_remove(o_set<T> S, T x)
    StructSymbolTableEntry *sste_remove_o_set = new StructSymbolTableEntry("@T_o_set_remove", NULL);    // template type
    sste_remove_o_set->isTemplate = true;                                                               // template type symbol table
    sst->insert(sste_remove_o_set);                                                                     // insert template type into struct symbol table
    VarSymbolTable *remove_o_set = new VarSymbolTable();                                                // function params
    inner_type *inner_remove_o_set = genInnerType("@T_o_set_remove");                                   // param inner type
    VarSymbolTableEntry *vste_remove_o_set = new VarSymbolTableEntry("S", "o_set", inner_remove_o_set); // param entry
    remove_o_set->insert(vste_remove_o_set);                                                            // param inner type
    VarSymbolTableEntry *vste_remove_o_set_2 = new VarSymbolTableEntry("x", "@T_o_set_remove", NULL);
    remove_o_set->insert(vste_remove_o_set_2); // param entry
    std::vector<std::string> remove_template_params;
    remove_template_params.push_back("@T_o_set_remove");                                                                                           // insert template param into template param vector
    FunctionSymbolTableEntry *fste_remove_o_set = new FunctionSymbolTableEntry("o_remove", 2, remove_o_set, "bool", true, remove_template_params); // function entry
    fste_remove_o_set->id_list.push_back("x");                                                                                                     // set isTemplate to true
    fste_remove_o_set->id_list.push_back("S");                                                                                                     // set isTemplate to true
    fst->insert(fste_remove_o_set);                                                                                                                // insert function entry into function symbol table

    // u_remove(u_set<T> S, T x)
    StructSymbolTableEntry *sste_remove_u_set = new StructSymbolTableEntry("@T_u_set_remove", NULL);    // template type
    sste_remove_u_set->isTemplate = true;                                                               // template type symbol table
    sst->insert(sste_remove_u_set);                                                                     // insert template type into struct symbol table
    VarSymbolTable *remove_u_set = new VarSymbolTable();                                                // function params
    inner_type *inner_remove_u_set = genInnerType("@T_u_set_remove");                                   // param inner type
    VarSymbolTableEntry *vste_remove_u_set = new VarSymbolTableEntry("S", "u_set", inner_remove_u_set); // param entry
    remove_u_set->insert(vste_remove_u_set);                                                            // param inner type
    VarSymbolTableEntry *vste_remove_u_set_2 = new VarSymbolTableEntry("x", "@T_u_set_remove", NULL);
    remove_u_set->insert(vste_remove_u_set_2); // param entry
    std::vector<std::string> remove_template_params_u_set;
    remove_template_params_u_set.push_back("@T_u_set_remove");                                                                                           // insert template param into template param vector
    FunctionSymbolTableEntry *fste_remove_u_set = new FunctionSymbolTableEntry("u_remove", 2, remove_u_set, "bool", true, remove_template_params_u_set); // function entry
    fste_remove_u_set->id_list.push_back("x");                                                                                                           // set isTemplate to true
    fste_remove_u_set->id_list.push_back("S");                                                                                                           // set isTemplate to true
    fst->insert(fste_remove_u_set);                                                                                                                      // insert function entry into function symbol table

    // o_output(o_set<T> S)
    StructSymbolTableEntry *sste_output_o_set = new StructSymbolTableEntry("@T_o_set_output", NULL);    // template type
    sste_output_o_set->isTemplate = true;                                                               // template type symbol table
    sst->insert(sste_output_o_set);                                                                     // insert template type into struct symbol table
    VarSymbolTable *output_o_set = new VarSymbolTable();                                                // function params
    inner_type *inner_output_o_set = genInnerType("@T_o_set_output");                                   // param inner type
    VarSymbolTableEntry *vste_output_o_set = new VarSymbolTableEntry("S", "o_set", inner_output_o_set); // param entry
    output_o_set->insert(vste_output_o_set);                                                            // param inner type
    std::vector<std::string> output_template_params;
    output_template_params.push_back("@T_o_set_output");                                                                                           // insert template param into template param vector
    FunctionSymbolTableEntry *fste_output_o_set = new FunctionSymbolTableEntry("o_output", 1, output_o_set, "void", true, output_template_params); // function entry
    fste_output_o_set->id_list.push_back("S");                                                                                                     // set isTemplate to true
    fst->insert(fste_output_o_set);                                                                                                                // insert function entry into function symbol table

    // u_output(u_set<T> S)
    StructSymbolTableEntry *sste_output_u_set = new StructSymbolTableEntry("@T_u_set_output", NULL);    // template type
    sste_output_u_set->isTemplate = true;                                                               // template type symbol table
    sst->insert(sste_output_u_set);                                                                     // insert template type into struct symbol table
    VarSymbolTable *output_u_set = new VarSymbolTable();                                                // function params
    inner_type *inner_output_u_set = genInnerType("@T_u_set_output");                                   // param inner type
    VarSymbolTableEntry *vste_output_u_set = new VarSymbolTableEntry("S", "u_set", inner_output_u_set); // param entry
    output_u_set->insert(vste_output_u_set);                                                            // param inner type
    std::vector<std::string> output_template_params_u_set;
    output_template_params_u_set.push_back("@T_u_set_output");                                                                                           // insert template param into template param vector
    FunctionSymbolTableEntry *fste_output_u_set = new FunctionSymbolTableEntry("u_output", 1, output_u_set, "void", true, output_template_params_u_set); // function entry
    fste_output_u_set->id_list.push_back("S");                                                                                                           // set isTemplate to true
    fst->insert(fste_output_u_set);                                                                                                                      // insert function entry into function symbol table
}

void initFSTDFA()
{
    // dfa_insert_state(dfa D, string q)
    VarSymbolTable *dfa_insert_state = new VarSymbolTable();
    VarSymbolTableEntry *vste_dfa_insert_state = new VarSymbolTableEntry("D", "dfa", NULL);
    VarSymbolTableEntry *vste_dfa_insert_state_2 = new VarSymbolTableEntry("q", "string", NULL);
    dfa_insert_state->insert(vste_dfa_insert_state);
    dfa_insert_state->insert(vste_dfa_insert_state_2);
    FunctionSymbolTableEntry *fste_dfa_insert_state = new FunctionSymbolTableEntry("dfa_insert_state", 2, dfa_insert_state, "void");
    fste_dfa_insert_state->id_list.push_back("q");
    fste_dfa_insert_state->id_list.push_back("D");
    fst->insert(fste_dfa_insert_state);

    // dfa_insert_alphabet(dfa D, string s1, string s2)
    VarSymbolTable *dfa_insert_alphabet = new VarSymbolTable();
    VarSymbolTableEntry *vste_dfa_insert_alphabet = new VarSymbolTableEntry("D", "dfa", NULL);
    VarSymbolTableEntry *vste_dfa_insert_alphabet_2 = new VarSymbolTableEntry("s1", "string", NULL);
    VarSymbolTableEntry *vste_dfa_insert_alphabet_3 = new VarSymbolTableEntry("s2", "string", NULL);
    dfa_insert_alphabet->insert(vste_dfa_insert_alphabet);
    dfa_insert_alphabet->insert(vste_dfa_insert_alphabet_2);
    dfa_insert_alphabet->insert(vste_dfa_insert_alphabet_3);
    FunctionSymbolTableEntry *fste_dfa_insert_alphabet = new FunctionSymbolTableEntry("dfa_insert_alphabet", 3, dfa_insert_alphabet, "void");
    fste_dfa_insert_alphabet->id_list.push_back("s2");
    fste_dfa_insert_alphabet->id_list.push_back("s1");
    fste_dfa_insert_alphabet->id_list.push_back("D");
    fst->insert(fste_dfa_insert_alphabet);

    // dfa_insert_transition(dfa D, string q1, string s, string q2)
    VarSymbolTable *dfa_insert_transition = new VarSymbolTable();
    VarSymbolTableEntry *vste_dfa_insert_transition = new VarSymbolTableEntry("D", "dfa", NULL);
    VarSymbolTableEntry *vste_dfa_insert_transition_2 = new VarSymbolTableEntry("q1", "string", NULL);
    VarSymbolTableEntry *vste_dfa_insert_transition_3 = new VarSymbolTableEntry("s", "string", NULL);
    VarSymbolTableEntry *vste_dfa_insert_transition_4 = new VarSymbolTableEntry("q2", "string", NULL);
    dfa_insert_transition->insert(vste_dfa_insert_transition);
    dfa_insert_transition->insert(vste_dfa_insert_transition_2);
    dfa_insert_transition->insert(vste_dfa_insert_transition_3);
    dfa_insert_transition->insert(vste_dfa_insert_transition_4);
    FunctionSymbolTableEntry *fste_dfa_insert_transition = new FunctionSymbolTableEntry("dfa_insert_transition", 4, dfa_insert_transition, "void");
    fste_dfa_insert_transition->id_list.push_back("q2");
    fste_dfa_insert_transition->id_list.push_back("s");
    fste_dfa_insert_transition->id_list.push_back("q1");
    fste_dfa_insert_transition->id_list.push_back("D");
    fst->insert(fste_dfa_insert_transition);

    // dfa_change_start(dfa D, string q)
    VarSymbolTable *dfa_change_start = new VarSymbolTable();
    VarSymbolTableEntry *vste_dfa_change_start = new VarSymbolTableEntry("D", "dfa", NULL);
    VarSymbolTableEntry *vste_dfa_change_start_2 = new VarSymbolTableEntry("q", "string", NULL);
    dfa_change_start->insert(vste_dfa_change_start);
    dfa_change_start->insert(vste_dfa_change_start_2);
    FunctionSymbolTableEntry *fste_dfa_change_start = new FunctionSymbolTableEntry("dfa_change_start", 2, dfa_change_start, "void");
    fste_dfa_change_start->id_list.push_back("q");
    fste_dfa_change_start->id_list.push_back("D");
    fst->insert(fste_dfa_change_start);

    // dfa_insert_accept(dfa D, string q)
    VarSymbolTable *dfa_insert_accept = new VarSymbolTable();
    VarSymbolTableEntry *vste_dfa_insert_accept = new VarSymbolTableEntry("D", "dfa", NULL);
    VarSymbolTableEntry *vste_dfa_insert_accept_2 = new VarSymbolTableEntry("q", "string", NULL);
    dfa_insert_accept->insert(vste_dfa_insert_accept);
    dfa_insert_accept->insert(vste_dfa_insert_accept_2);
    FunctionSymbolTableEntry *fste_dfa_insert_accept = new FunctionSymbolTableEntry("dfa_insert_accept", 2, dfa_insert_accept, "void");
    fste_dfa_insert_accept->id_list.push_back("q");
    fste_dfa_insert_accept->id_list.push_back("D");
    fst->insert(fste_dfa_insert_accept);

    // dfa_remove_accept(dfa D, string q)
    VarSymbolTable *dfa_remove_accept = new VarSymbolTable();
    VarSymbolTableEntry *vste_dfa_remove_accept = new VarSymbolTableEntry("D", "dfa", NULL);
    VarSymbolTableEntry *vste_dfa_remove_accept_2 = new VarSymbolTableEntry("q", "string", NULL);
    dfa_remove_accept->insert(vste_dfa_remove_accept);
    dfa_remove_accept->insert(vste_dfa_remove_accept_2);
    FunctionSymbolTableEntry *fste_dfa_remove_accept = new FunctionSymbolTableEntry("dfa_remove_accept", 2, dfa_remove_accept, "void");
    fste_dfa_remove_accept->id_list.push_back("q");
    fste_dfa_remove_accept->id_list.push_back("D");
    fst->insert(fste_dfa_remove_accept);

    // dfa_remove_state(dfa D, string q)
    VarSymbolTable *dfa_remove_state = new VarSymbolTable();
    VarSymbolTableEntry *vste_dfa_remove_state = new VarSymbolTableEntry("D", "dfa", NULL);
    VarSymbolTableEntry *vste_dfa_remove_state_2 = new VarSymbolTableEntry("q", "string", NULL);
    dfa_remove_state->insert(vste_dfa_remove_state);
    dfa_remove_state->insert(vste_dfa_remove_state_2);
    FunctionSymbolTableEntry *fste_dfa_remove_state = new FunctionSymbolTableEntry("dfa_remove_state", 2, dfa_remove_state, "void");
    fste_dfa_remove_state->id_list.push_back("q");
    fste_dfa_remove_state->id_list.push_back("D");
    fst->insert(fste_dfa_remove_state);

    // dfa_remove_alphabet(dfa D, string s)
    VarSymbolTable *dfa_remove_alphabet = new VarSymbolTable();
    VarSymbolTableEntry *vste_dfa_remove_alphabet = new VarSymbolTableEntry("D", "dfa", NULL);
    VarSymbolTableEntry *vste_dfa_remove_alphabet_2 = new VarSymbolTableEntry("s", "string", NULL);
    dfa_remove_alphabet->insert(vste_dfa_remove_alphabet);
    dfa_remove_alphabet->insert(vste_dfa_remove_alphabet_2);
    FunctionSymbolTableEntry *fste_dfa_remove_alphabet = new FunctionSymbolTableEntry("dfa_remove_alphabet", 2, dfa_remove_alphabet, "void");
    fste_dfa_remove_alphabet->id_list.push_back("s");
    fste_dfa_remove_alphabet->id_list.push_back("D");
    fst->insert(fste_dfa_remove_alphabet);

    // dfa_remove_transition(dfa D, string q1, string s, string q2)
    VarSymbolTable *dfa_remove_transition = new VarSymbolTable();
    VarSymbolTableEntry *vste_dfa_remove_transition = new VarSymbolTableEntry("D", "dfa", NULL);
    VarSymbolTableEntry *vste_dfa_remove_transition_2 = new VarSymbolTableEntry("q1", "string", NULL);
    VarSymbolTableEntry *vste_dfa_remove_transition_3 = new VarSymbolTableEntry("s", "string", NULL);
    VarSymbolTableEntry *vste_dfa_remove_transition_4 = new VarSymbolTableEntry("q2", "string", NULL);
    dfa_remove_transition->insert(vste_dfa_remove_transition);
    dfa_remove_transition->insert(vste_dfa_remove_transition_2);
    dfa_remove_transition->insert(vste_dfa_remove_transition_3);
    dfa_remove_transition->insert(vste_dfa_remove_transition_4);
    FunctionSymbolTableEntry *fste_dfa_remove_transition = new FunctionSymbolTableEntry("dfa_remove_transition", 4, dfa_remove_transition, "void");
    fste_dfa_remove_transition->id_list.push_back("q2");
    fste_dfa_remove_transition->id_list.push_back("s");
    fste_dfa_remove_transition->id_list.push_back("q1");
    fste_dfa_remove_transition->id_list.push_back("D");
    fst->insert(fste_dfa_remove_transition);

    // dfa_output(dfa D)
    VarSymbolTable *dfa_output = new VarSymbolTable();
    VarSymbolTableEntry *vste_dfa_output = new VarSymbolTableEntry("D", "dfa", NULL);
    dfa_output->insert(vste_dfa_output);
    FunctionSymbolTableEntry *fste_dfa_output = new FunctionSymbolTableEntry("dfa_output", 1, dfa_output, "void");
    fste_dfa_output->id_list.push_back("D");
    fst->insert(fste_dfa_output);

    // dfa_simulate(dfa D, string s)
    VarSymbolTable *dfa_simulate = new VarSymbolTable();
    VarSymbolTableEntry *vste_dfa_simulate = new VarSymbolTableEntry("D", "dfa", NULL);
    VarSymbolTableEntry *vste_dfa_simulate_2 = new VarSymbolTableEntry("s", "string", NULL);
    dfa_simulate->insert(vste_dfa_simulate);
    dfa_simulate->insert(vste_dfa_simulate_2);
    FunctionSymbolTableEntry *fste_dfa_simulate = new FunctionSymbolTableEntry("dfa_simulate", 2, dfa_simulate, "bool");
    fste_dfa_simulate->id_list.push_back("s");
    fste_dfa_simulate->id_list.push_back("D");
    fst->insert(fste_dfa_simulate);
}

void initSTNFA()
{
    // nfa_insert_state(nfa N, string q)
    VarSymbolTable *nfa_insert_state = new VarSymbolTable();
    VarSymbolTableEntry *vste_nfa_insert_state = new VarSymbolTableEntry("N", "nfa", NULL);
    VarSymbolTableEntry *vste_nfa_insert_state_2 = new VarSymbolTableEntry("q", "string", NULL);
    nfa_insert_state->insert(vste_nfa_insert_state);
    nfa_insert_state->insert(vste_nfa_insert_state_2);
    FunctionSymbolTableEntry *fste_nfa_insert_state = new FunctionSymbolTableEntry("nfa_insert_state", 2, nfa_insert_state, "void");
    fste_nfa_insert_state->id_list.push_back("q");
    fste_nfa_insert_state->id_list.push_back("N");
    fst->insert(fste_nfa_insert_state);

    // nfa_insert_alphabet(nfa N, string s1, string s2)
    VarSymbolTable *nfa_insert_alphabet = new VarSymbolTable();
    VarSymbolTableEntry *vste_nfa_insert_alphabet = new VarSymbolTableEntry("N", "nfa", NULL);
    VarSymbolTableEntry *vste_nfa_insert_alphabet_2 = new VarSymbolTableEntry("s1", "string", NULL);
    VarSymbolTableEntry *vste_nfa_insert_alphabet_3 = new VarSymbolTableEntry("s2", "string", NULL);
    nfa_insert_alphabet->insert(vste_nfa_insert_alphabet);
    nfa_insert_alphabet->insert(vste_nfa_insert_alphabet_2);
    nfa_insert_alphabet->insert(vste_nfa_insert_alphabet_3);
    FunctionSymbolTableEntry *fste_nfa_insert_alphabet = new FunctionSymbolTableEntry("nfa_insert_alphabet", 3, nfa_insert_alphabet, "void");
    fste_nfa_insert_alphabet->id_list.push_back("s2");
    fste_nfa_insert_alphabet->id_list.push_back("s1");
    fste_nfa_insert_alphabet->id_list.push_back("N");
    fst->insert(fste_nfa_insert_alphabet);

    // nfa_insert_transition(nfa N, string q1, string s, string q2)
    VarSymbolTable *nfa_insert_transition = new VarSymbolTable();
    VarSymbolTableEntry *vste_nfa_insert_transition = new VarSymbolTableEntry("N", "nfa", NULL);
    VarSymbolTableEntry *vste_nfa_insert_transition_2 = new VarSymbolTableEntry("q1", "string", NULL);
    VarSymbolTableEntry *vste_nfa_insert_transition_3 = new VarSymbolTableEntry("s", "string", NULL);
    VarSymbolTableEntry *vste_nfa_insert_transition_4 = new VarSymbolTableEntry("q2", "string", NULL);
    nfa_insert_transition->insert(vste_nfa_insert_transition);
    nfa_insert_transition->insert(vste_nfa_insert_transition_2);
    nfa_insert_transition->insert(vste_nfa_insert_transition_3);
    nfa_insert_transition->insert(vste_nfa_insert_transition_4);
    FunctionSymbolTableEntry *fste_nfa_insert_transition = new FunctionSymbolTableEntry("nfa_insert_transition", 4, nfa_insert_transition, "void");
    fste_nfa_insert_transition->id_list.push_back("q2");
    fste_nfa_insert_transition->id_list.push_back("s");
    fste_nfa_insert_transition->id_list.push_back("q1");
    fste_nfa_insert_transition->id_list.push_back("N");
    fst->insert(fste_nfa_insert_transition);

    // nfa_change_start(nfa N, string q)
    VarSymbolTable *nfa_change_start = new VarSymbolTable();
    VarSymbolTableEntry *vste_nfa_change_start = new VarSymbolTableEntry("N", "nfa", NULL);
    VarSymbolTableEntry *vste_nfa_change_start_2 = new VarSymbolTableEntry("q", "string", NULL);
    nfa_change_start->insert(vste_nfa_change_start);
    nfa_change_start->insert(vste_nfa_change_start_2);
    FunctionSymbolTableEntry *fste_nfa_change_start = new FunctionSymbolTableEntry("nfa_change_start", 2, nfa_change_start, "void");
    fste_nfa_change_start->id_list.push_back("q");
    fste_nfa_change_start->id_list.push_back("N");
    fst->insert(fste_nfa_change_start);

    // nfa_insert_accept(nfa N, string q)
    VarSymbolTable *nfa_insert_accept = new VarSymbolTable();
    VarSymbolTableEntry *vste_nfa_insert_accept = new VarSymbolTableEntry("N", "nfa", NULL);
    VarSymbolTableEntry *vste_nfa_insert_accept_2 = new VarSymbolTableEntry("q", "string", NULL);
    nfa_insert_accept->insert(vste_nfa_insert_accept);
    nfa_insert_accept->insert(vste_nfa_insert_accept_2);
    FunctionSymbolTableEntry *fste_nfa_insert_accept = new FunctionSymbolTableEntry("nfa_insert_accept", 2, nfa_insert_accept, "void");
    fste_nfa_insert_accept->id_list.push_back("q");
    fste_nfa_insert_accept->id_list.push_back("N");
    fst->insert(fste_nfa_insert_accept);

    // nfa_remove_accept(nfa N, string q)
    VarSymbolTable *nfa_remove_accept = new VarSymbolTable();
    VarSymbolTableEntry *vste_nfa_remove_accept = new VarSymbolTableEntry("N", "nfa", NULL);
    VarSymbolTableEntry *vste_nfa_remove_accept_2 = new VarSymbolTableEntry("q", "string", NULL);
    nfa_remove_accept->insert(vste_nfa_remove_accept);
    nfa_remove_accept->insert(vste_nfa_remove_accept_2);
    FunctionSymbolTableEntry *fste_nfa_remove_accept = new FunctionSymbolTableEntry("nfa_remove_accept", 2, nfa_remove_accept, "void");
    fste_nfa_remove_accept->id_list.push_back("q");
    fste_nfa_remove_accept->id_list.push_back("N");
    fst->insert(fste_nfa_remove_accept);

    // nfa_remove_state(nfa N, string q)
    VarSymbolTable *nfa_remove_state = new VarSymbolTable();
    VarSymbolTableEntry *vste_nfa_remove_state = new VarSymbolTableEntry("N", "nfa", NULL);
    VarSymbolTableEntry *vste_nfa_remove_state_2 = new VarSymbolTableEntry("q", "string", NULL);
    nfa_remove_state->insert(vste_nfa_remove_state);
    nfa_remove_state->insert(vste_nfa_remove_state_2);
    FunctionSymbolTableEntry *fste_nfa_remove_state = new FunctionSymbolTableEntry("nfa_remove_state", 2, nfa_remove_state, "void");
    fste_nfa_remove_state->id_list.push_back("q");
    fste_nfa_remove_state->id_list.push_back("N");
    fst->insert(fste_nfa_remove_state);

    // nfa_remove_alphabet(nfa N, string s)
    VarSymbolTable *nfa_remove_alphabet = new VarSymbolTable();
    VarSymbolTableEntry *vste_nfa_remove_alphabet = new VarSymbolTableEntry("N", "nfa", NULL);
    VarSymbolTableEntry *vste_nfa_remove_alphabet_2 = new VarSymbolTableEntry("s", "string", NULL);
    nfa_remove_alphabet->insert(vste_nfa_remove_alphabet);
    nfa_remove_alphabet->insert(vste_nfa_remove_alphabet_2);
    FunctionSymbolTableEntry *fste_nfa_remove_alphabet = new FunctionSymbolTableEntry("nfa_remove_alphabet", 2, nfa_remove_alphabet, "void");
    fste_nfa_remove_alphabet->id_list.push_back("s");
    fste_nfa_remove_alphabet->id_list.push_back("N");
    fst->insert(fste_nfa_remove_alphabet);

    // nfa_remove_transition(nfa N, string q1, string s, string q2)
    VarSymbolTable *nfa_remove_transition = new VarSymbolTable();
    VarSymbolTableEntry *vste_nfa_remove_transition = new VarSymbolTableEntry("N", "nfa", NULL);
    VarSymbolTableEntry *vste_nfa_remove_transition_2 = new VarSymbolTableEntry("q1", "string", NULL);
    VarSymbolTableEntry *vste_nfa_remove_transition_3 = new VarSymbolTableEntry("s", "string", NULL);
    VarSymbolTableEntry *vste_nfa_remove_transition_4 = new VarSymbolTableEntry("q2", "string", NULL);
    nfa_remove_transition->insert(vste_nfa_remove_transition);
    nfa_remove_transition->insert(vste_nfa_remove_transition_2);
    nfa_remove_transition->insert(vste_nfa_remove_transition_3);
    nfa_remove_transition->insert(vste_nfa_remove_transition_4);
    FunctionSymbolTableEntry *fste_nfa_remove_transition = new FunctionSymbolTableEntry("nfa_remove_transition", 4, nfa_remove_transition, "void");
    fste_nfa_remove_transition->id_list.push_back("q2");
    fste_nfa_remove_transition->id_list.push_back("s");
    fste_nfa_remove_transition->id_list.push_back("q1");
    fste_nfa_remove_transition->id_list.push_back("N");
    fst->insert(fste_nfa_remove_transition);

    // nfa_output(nfa N)
    VarSymbolTable *nfa_output = new VarSymbolTable();
    VarSymbolTableEntry *vste_nfa_output = new VarSymbolTableEntry("N", "nfa", NULL);
    nfa_output->insert(vste_nfa_output);
    FunctionSymbolTableEntry *fste_nfa_output = new FunctionSymbolTableEntry("nfa_output", 1, nfa_output, "void");
    fste_nfa_output->id_list.push_back("N");
    fst->insert(fste_nfa_output);

    // nfa_to_dfa(nfa N)
    VarSymbolTable *nfa_to_dfa = new VarSymbolTable();
    VarSymbolTableEntry *vste_nfa_to_dfa = new VarSymbolTableEntry("N", "nfa", NULL);
    nfa_to_dfa->insert(vste_nfa_to_dfa);
    FunctionSymbolTableEntry *fste_nfa_to_dfa = new FunctionSymbolTableEntry("nfa_to_dfa", 1, nfa_to_dfa, "dfa");
    fste_nfa_to_dfa->id_list.push_back("N");
    fst->insert(fste_nfa_to_dfa);

    // nfa_simulate(nfa N, string s)
    VarSymbolTable *nfa_simulate = new VarSymbolTable();
    VarSymbolTableEntry *vste_nfa_simulate = new VarSymbolTableEntry("N", "nfa", NULL);
    VarSymbolTableEntry *vste_nfa_simulate_2 = new VarSymbolTableEntry("s", "string", NULL);
    nfa_simulate->insert(vste_nfa_simulate);
    nfa_simulate->insert(vste_nfa_simulate_2);
    FunctionSymbolTableEntry *fste_nfa_simulate = new FunctionSymbolTableEntry("nfa_simulate", 2, nfa_simulate, "bool");
    fste_nfa_simulate->id_list.push_back("s");
    fste_nfa_simulate->id_list.push_back("N");
    fst->insert(fste_nfa_simulate);
}

void initCFG()
{
    // cfg_add_T(cfg a, string s1, string s2)
    VarSymbolTable *cfg_add_Terminal = new VarSymbolTable();
    VarSymbolTableEntry *vste_cfg_add_Terminal = new VarSymbolTableEntry("a", "cfg", NULL);
    VarSymbolTableEntry *vste_cfg_add_Terminal_2 = new VarSymbolTableEntry("s1", "string", NULL);
    VarSymbolTableEntry *vste_cfg_add_Terminal_3 = new VarSymbolTableEntry("s2", "string", NULL);
    cfg_add_Terminal->insert(vste_cfg_add_Terminal);
    cfg_add_Terminal->insert(vste_cfg_add_Terminal_2);
    cfg_add_Terminal->insert(vste_cfg_add_Terminal_3);
    FunctionSymbolTableEntry *fste_cfg_add_Terminal = new FunctionSymbolTableEntry("cfg_add_T", 2, cfg_add_Terminal, "void");
    fste_cfg_add_Terminal->id_list.push_back("s2");
    fste_cfg_add_Terminal->id_list.push_back("s1");
    fste_cfg_add_Terminal->id_list.push_back("a");
    fst->insert(fste_cfg_add_Terminal);

    // cfg_add_N(cfg a, string s)
    VarSymbolTable *cfg_add_NonTerminal = new VarSymbolTable();
    VarSymbolTableEntry *vste_cfg_add_NonTerminal = new VarSymbolTableEntry("a", "cfg", NULL);
    VarSymbolTableEntry *vste_cfg_add_NonTerminal_2 = new VarSymbolTableEntry("s", "string", NULL);
    cfg_add_NonTerminal->insert(vste_cfg_add_NonTerminal);
    cfg_add_NonTerminal->insert(vste_cfg_add_NonTerminal_2);
    FunctionSymbolTableEntry *fste_cfg_add_NonTerminal = new FunctionSymbolTableEntry("cfg_add_N", 2, cfg_add_NonTerminal, "void");
    fste_cfg_add_NonTerminal->id_list.push_back("s");
    fste_cfg_add_NonTerminal->id_list.push_back("a");
    fst->insert(fste_cfg_add_NonTerminal);

    // cfg_add_P(cfg a, string s1, string s2)
    VarSymbolTable *cfg_add_Production = new VarSymbolTable();
    VarSymbolTableEntry *vste_cfg_add_Production = new VarSymbolTableEntry("a", "cfg", NULL);
    VarSymbolTableEntry *vste_cfg_add_Production_2 = new VarSymbolTableEntry("s1", "string", NULL);
    VarSymbolTableEntry *vste_cfg_add_Production_3 = new VarSymbolTableEntry("s2", "string", NULL);
    cfg_add_Production->insert(vste_cfg_add_Production);
    cfg_add_Production->insert(vste_cfg_add_Production_2);
    cfg_add_Production->insert(vste_cfg_add_Production_3);
    FunctionSymbolTableEntry *fste_cfg_add_Production = new FunctionSymbolTableEntry("cfg_add_P", 2, cfg_add_Production, "void");
    fste_cfg_add_Production->id_list.push_back("s2");
    fste_cfg_add_Production->id_list.push_back("s1");
    fste_cfg_add_Production->id_list.push_back("a");
    fst->insert(fste_cfg_add_Production);

    // cfg_remove_T(cfg a, string s)
    VarSymbolTable *cfg_remove_Terminal = new VarSymbolTable();
    VarSymbolTableEntry *vste_cfg_remove_Terminal = new VarSymbolTableEntry("a", "cfg", NULL);
    VarSymbolTableEntry *vste_cfg_remove_Terminal_2 = new VarSymbolTableEntry("s", "string", NULL);
    cfg_remove_Terminal->insert(vste_cfg_remove_Terminal);
    cfg_remove_Terminal->insert(vste_cfg_remove_Terminal_2);
    FunctionSymbolTableEntry *fste_cfg_remove_Terminal = new FunctionSymbolTableEntry("cfg_remove_T", 2, cfg_remove_Terminal, "void");
    fste_cfg_remove_Terminal->id_list.push_back("s");
    fste_cfg_remove_Terminal->id_list.push_back("a");
    fst->insert(fste_cfg_remove_Terminal);

    // cfg_remove_N(cfg a, string s)
    VarSymbolTable *cfg_remove_NonTerminal = new VarSymbolTable();
    VarSymbolTableEntry *vste_cfg_remove_NonTerminal = new VarSymbolTableEntry("a", "cfg", NULL);
    VarSymbolTableEntry *vste_cfg_remove_NonTerminal_2 = new VarSymbolTableEntry("s", "string", NULL);
    cfg_remove_NonTerminal->insert(vste_cfg_remove_NonTerminal);
    cfg_remove_NonTerminal->insert(vste_cfg_remove_NonTerminal_2);
    FunctionSymbolTableEntry *fste_cfg_remove_NonTerminal = new FunctionSymbolTableEntry("cfg_remove_N", 2, cfg_remove_NonTerminal, "void");
    fste_cfg_remove_NonTerminal->id_list.push_back("s");
    fste_cfg_remove_NonTerminal->id_list.push_back("a");
    fst->insert(fste_cfg_remove_NonTerminal);

    // cfg_remove_P(cfg a, string s1, string s2)
    VarSymbolTable *cfg_remove_Production = new VarSymbolTable();
    VarSymbolTableEntry *vste_cfg_remove_Production = new VarSymbolTableEntry("a", "cfg", NULL);
    VarSymbolTableEntry *vste_cfg_remove_Production_2 = new VarSymbolTableEntry("s1", "string", NULL);
    VarSymbolTableEntry *vste_cfg_remove_Production_3 = new VarSymbolTableEntry("s2", "string", NULL);
    cfg_remove_Production->insert(vste_cfg_remove_Production);
    cfg_remove_Production->insert(vste_cfg_remove_Production_2);
    cfg_remove_Production->insert(vste_cfg_remove_Production_3);
    FunctionSymbolTableEntry *fste_cfg_remove_Production = new FunctionSymbolTableEntry("cfg_remove_P", 2, cfg_remove_Production, "void");
    fste_cfg_remove_Production->id_list.push_back("s2");
    fste_cfg_remove_Production->id_list.push_back("s1");
    fste_cfg_remove_Production->id_list.push_back("a");
    fst->insert(fste_cfg_remove_Production);

    // cfg_output(cfg a)
    VarSymbolTable *cfg_output = new VarSymbolTable();
    VarSymbolTableEntry *vste_cfg_output = new VarSymbolTableEntry("a", "cfg", NULL);
    cfg_output->insert(vste_cfg_output);
    FunctionSymbolTableEntry *fste_cfg_output = new FunctionSymbolTableEntry("cfg_output", 1, cfg_output, "void");
    fste_cfg_output->id_list.push_back("a");
    fst->insert(fste_cfg_output);
}

void initFSTPDA()
{
    // pda_insert_state(pda P, string q)
    VarSymbolTable *pda_insert_state = new VarSymbolTable();
    VarSymbolTableEntry *vste_pda_insert_state = new VarSymbolTableEntry("P", "pda", NULL);
    VarSymbolTableEntry *vste_pda_insert_state_2 = new VarSymbolTableEntry("q", "string", NULL);
    pda_insert_state->insert(vste_pda_insert_state);
    pda_insert_state->insert(vste_pda_insert_state_2);
    FunctionSymbolTableEntry *fste_pda_insert_state = new FunctionSymbolTableEntry("pda_insert_state", 2, pda_insert_state, "void");
    fste_pda_insert_state->id_list.push_back("q");
    fste_pda_insert_state->id_list.push_back("P");
    fst->insert(fste_pda_insert_state);

    // pda_insert_input_alphabet(pda P, string s1, string s2)
    VarSymbolTable *pda_insert_alphabet = new VarSymbolTable();
    VarSymbolTableEntry *vste_pda_insert_alphabet = new VarSymbolTableEntry("P", "pda", NULL);
    VarSymbolTableEntry *vste_pda_insert_alphabet_2 = new VarSymbolTableEntry("s1", "string", NULL);
    VarSymbolTableEntry *vste_pda_insert_alphabet_3 = new VarSymbolTableEntry("s2", "string", NULL);
    pda_insert_alphabet->insert(vste_pda_insert_alphabet);
    pda_insert_alphabet->insert(vste_pda_insert_alphabet_2);
    pda_insert_alphabet->insert(vste_pda_insert_alphabet_3);
    FunctionSymbolTableEntry *fste_pda_insert_alphabet = new FunctionSymbolTableEntry("pda_insert_input_alphabet", 3, pda_insert_alphabet, "void");
    fste_pda_insert_alphabet->id_list.push_back("s2");
    fste_pda_insert_alphabet->id_list.push_back("s1");
    fste_pda_insert_alphabet->id_list.push_back("P");
    fst->insert(fste_pda_insert_alphabet);

    // pda_insert_stack_alphabet(pda P, string s1, string s2)
    VarSymbolTable *pda_insert_stack_alphabet = new VarSymbolTable();
    VarSymbolTableEntry *vste_pda_insert_stack_alphabet = new VarSymbolTableEntry("P", "pda", NULL);
    VarSymbolTableEntry *vste_pda_insert_stack_alphabet_2 = new VarSymbolTableEntry("s1", "string", NULL);
    VarSymbolTableEntry *vste_pda_insert_stack_alphabet_3 = new VarSymbolTableEntry("s2", "string", NULL);
    pda_insert_stack_alphabet->insert(vste_pda_insert_stack_alphabet);
    pda_insert_stack_alphabet->insert(vste_pda_insert_stack_alphabet_2);
    pda_insert_stack_alphabet->insert(vste_pda_insert_stack_alphabet_3);
    FunctionSymbolTableEntry *fste_pda_insert_stack_alphabet = new FunctionSymbolTableEntry("pda_insert_stack_alphabet", 3, pda_insert_stack_alphabet, "void");
    fste_pda_insert_stack_alphabet->id_list.push_back("s2");
    fste_pda_insert_stack_alphabet->id_list.push_back("s1");
    fste_pda_insert_stack_alphabet->id_list.push_back("P");
    fst->insert(fste_pda_insert_stack_alphabet);

    // pda_insert_transition(pda P, string q1, string s1, string s2, string q2, string s3)
    VarSymbolTable *pda_insert_transition = new VarSymbolTable();
    VarSymbolTableEntry *vste_pda_insert_transition = new VarSymbolTableEntry("P", "pda", NULL);
    VarSymbolTableEntry *vste_pda_insert_transition_2 = new VarSymbolTableEntry("q1", "string", NULL);
    VarSymbolTableEntry *vste_pda_insert_transition_3 = new VarSymbolTableEntry("s1", "string", NULL);
    VarSymbolTableEntry *vste_pda_insert_transition_4 = new VarSymbolTableEntry("s2", "string", NULL);
    VarSymbolTableEntry *vste_pda_insert_transition_5 = new VarSymbolTableEntry("q2", "string", NULL);
    VarSymbolTableEntry *vste_pda_insert_transition_6 = new VarSymbolTableEntry("s3", "string", NULL);
    pda_insert_transition->insert(vste_pda_insert_transition);
    pda_insert_transition->insert(vste_pda_insert_transition_2);
    pda_insert_transition->insert(vste_pda_insert_transition_3);
    pda_insert_transition->insert(vste_pda_insert_transition_4);
    pda_insert_transition->insert(vste_pda_insert_transition_5);
    pda_insert_transition->insert(vste_pda_insert_transition_6);
    FunctionSymbolTableEntry *fste_pda_insert_transition = new FunctionSymbolTableEntry("pda_insert_transition", 6, pda_insert_transition, "void");
    fste_pda_insert_transition->id_list.push_back("s3");
    fste_pda_insert_transition->id_list.push_back("q2");
    fste_pda_insert_transition->id_list.push_back("s2");
    fste_pda_insert_transition->id_list.push_back("s1");
    fste_pda_insert_transition->id_list.push_back("q1");
    fste_pda_insert_transition->id_list.push_back("P");
    fst->insert(fste_pda_insert_transition);

    // pda_change_start(pda P, string q)
    VarSymbolTable *pda_change_start = new VarSymbolTable();
    VarSymbolTableEntry *vste_pda_change_start = new VarSymbolTableEntry("P", "pda", NULL);
    VarSymbolTableEntry *vste_pda_change_start_2 = new VarSymbolTableEntry("q", "string", NULL);
    pda_change_start->insert(vste_pda_change_start);
    pda_change_start->insert(vste_pda_change_start_2);
    FunctionSymbolTableEntry *fste_pda_change_start = new FunctionSymbolTableEntry("pda_change_start", 2, pda_change_start, "void");
    fste_pda_change_start->id_list.push_back("q");
    fste_pda_change_start->id_list.push_back("P");
    fst->insert(fste_pda_change_start);

    // pda_insert_accept(pda P, string q)
    VarSymbolTable *pda_insert_accept = new VarSymbolTable();
    VarSymbolTableEntry *vste_pda_insert_accept = new VarSymbolTableEntry("P", "pda", NULL);
    VarSymbolTableEntry *vste_pda_insert_accept_2 = new VarSymbolTableEntry("q", "string", NULL);
    pda_insert_accept->insert(vste_pda_insert_accept);
    pda_insert_accept->insert(vste_pda_insert_accept_2);
    FunctionSymbolTableEntry *fste_pda_insert_accept = new FunctionSymbolTableEntry("pda_insert_accept", 2, pda_insert_accept, "void");
    fste_pda_insert_accept->id_list.push_back("q");
    fste_pda_insert_accept->id_list.push_back("P");
    fst->insert(fste_pda_insert_accept);

    // pda_remove_accept(pda P, string q)
    VarSymbolTable *pda_remove_accept = new VarSymbolTable();
    VarSymbolTableEntry *vste_pda_remove_accept = new VarSymbolTableEntry("P", "pda", NULL);
    VarSymbolTableEntry *vste_pda_remove_accept_2 = new VarSymbolTableEntry("q", "string", NULL);
    pda_remove_accept->insert(vste_pda_remove_accept);
    pda_remove_accept->insert(vste_pda_remove_accept_2);
    FunctionSymbolTableEntry *fste_pda_remove_accept = new FunctionSymbolTableEntry("pda_remove_accept", 2, pda_remove_accept, "void");
    fste_pda_remove_accept->id_list.push_back("q");
    fste_pda_remove_accept->id_list.push_back("P");
    fst->insert(fste_pda_remove_accept);

    // pda_remove_state(pda P, string q)
    VarSymbolTable *pda_remove_state = new VarSymbolTable();
    VarSymbolTableEntry *vste_pda_remove_state = new VarSymbolTableEntry("P", "pda", NULL);
    VarSymbolTableEntry *vste_pda_remove_state_2 = new VarSymbolTableEntry("q", "string", NULL);
    pda_remove_state->insert(vste_pda_remove_state);
    pda_remove_state->insert(vste_pda_remove_state_2);
    FunctionSymbolTableEntry *fste_pda_remove_state = new FunctionSymbolTableEntry("pda_remove_state", 2, pda_remove_state, "void");
    fste_pda_remove_state->id_list.push_back("q");
    fste_pda_remove_state->id_list.push_back("P");
    fst->insert(fste_pda_remove_state);

    // pda_remove_input_alphabet(pda P, string s)
    VarSymbolTable *pda_remove_input_alphabet = new VarSymbolTable();
    VarSymbolTableEntry *vste_pda_remove_input_alphabet = new VarSymbolTableEntry("P", "pda", NULL);
    VarSymbolTableEntry *vste_pda_remove_input_alphabet_2 = new VarSymbolTableEntry("s", "string", NULL);
    pda_remove_input_alphabet->insert(vste_pda_remove_input_alphabet);
    pda_remove_input_alphabet->insert(vste_pda_remove_input_alphabet_2);
    FunctionSymbolTableEntry *fste_pda_remove_input_alphabet = new FunctionSymbolTableEntry("pda_remove_input_alphabet", 2, pda_remove_input_alphabet, "void");
    fste_pda_remove_input_alphabet->id_list.push_back("s");
    fste_pda_remove_input_alphabet->id_list.push_back("P");
    fst->insert(fste_pda_remove_input_alphabet);

    // pda_remove_stack_alphabet(pda P, string s)
    VarSymbolTable *pda_remove_stack_alphabet = new VarSymbolTable();
    VarSymbolTableEntry *vste_pda_remove_stack_alphabet = new VarSymbolTableEntry("P", "pda", NULL);
    VarSymbolTableEntry *vste_pda_remove_stack_alphabet_2 = new VarSymbolTableEntry("s", "string", NULL);
    pda_remove_stack_alphabet->insert(vste_pda_remove_stack_alphabet);
    pda_remove_stack_alphabet->insert(vste_pda_remove_stack_alphabet_2);
    FunctionSymbolTableEntry *fste_pda_remove_stack_alphabet = new FunctionSymbolTableEntry("pda_remove_stack_alphabet", 2, pda_remove_stack_alphabet, "void");
    fste_pda_remove_stack_alphabet->id_list.push_back("s");
    fste_pda_remove_stack_alphabet->id_list.push_back("P");
    fst->insert(fste_pda_remove_stack_alphabet);

    // pda_remove_transition(pda P, string q1, string s1, string s2, string q2, string s3)
    // VarSymbolTable *pda_remove_transition = new VarSymbolTable();
    // VarSymbolTableEntry *vste_pda_remove_transition = new VarSymbolTableEntry("P", "pda", NULL);
    // VarSymbolTableEntry *vste_pda_remove_transition_2 = new VarSymbolTableEntry("q1", "string", NULL);
    // VarSymbolTableEntry *vste_pda_remove_transition_3 = new VarSymbolTableEntry("s1", "string", NULL);
    // VarSymbolTableEntry *vste_pda_remove_transition_4 = new VarSymbolTableEntry("s2", "string", NULL);
    // VarSymbolTableEntry *vste_pda_remove_transition_5 = new VarSymbolTableEntry("q2", "string", NULL);
    // VarSymbolTableEntry *vste_pda_remove_transition_6 = new VarSymbolTableEntry("s3", "string", NULL);
    // pda_remove_transition->insert(vste_pda_remove_transition);
    // pda_remove_transition->insert(vste_pda_remove_transition_2);
    // pda_remove_transition->insert(vste_pda_remove_transition_3);
    // pda_remove_transition->insert(vste_pda_remove_transition_4);
    // pda_remove_transition->insert(vste_pda_remove_transition_5);
    // pda_remove_transition->insert(vste_pda_remove_transition_6);
    // FunctionSymbolTableEntry *fste_pda_remove_transition = new FunctionSymbolTableEntry("pda_remove_transition", 6, pda_remove_transition, "void");
    // fste_pda_remove_transition->id_list.push_back("s3");
    // fste_pda_remove_transition->id_list.push_back("q2");
    // fste_pda_remove_transition->id_list.push_back("s2");
    // fste_pda_remove_transition->id_list.push_back("s1");
    // fste_pda_remove_transition->id_list.push_back("q1");
    // fste_pda_remove_transition->id_list.push_back("P");
    // fst->insert(fste_pda_remove_transition);

    // pda_output(pda P)
    VarSymbolTable *pda_output = new VarSymbolTable();
    VarSymbolTableEntry *vste_pda_output = new VarSymbolTableEntry("P", "pda", NULL);
    pda_output->insert(vste_pda_output);
    FunctionSymbolTableEntry *fste_pda_output = new FunctionSymbolTableEntry("pda_output", 1, pda_output, "void");
    fste_pda_output->id_list.push_back("P");
    fst->insert(fste_pda_output);

    // pda_simulate(pda P, string s)
    VarSymbolTable *pda_simulate = new VarSymbolTable();
    VarSymbolTableEntry *vste_pda_simulate = new VarSymbolTableEntry("P", "pda", NULL);
    VarSymbolTableEntry *vste_pda_simulate_2 = new VarSymbolTableEntry("s", "string", NULL);
    pda_simulate->insert(vste_pda_simulate);
    pda_simulate->insert(vste_pda_simulate_2);
    FunctionSymbolTableEntry *fste_pda_simulate = new FunctionSymbolTableEntry("pda_simulate", 2, pda_simulate, "bool");
    fste_pda_simulate->id_list.push_back("s");
    fste_pda_simulate->id_list.push_back("P");
    fst->insert(fste_pda_simulate);
}

void initSetFuncs()
{
    set_funcs = new std::set<std::string>();
    set_funcs->insert("o_size");
    set_funcs->insert("o_insert");
    set_funcs->insert("o_remove");
    set_funcs->insert("o_output");
    set_funcs->insert("o_find");
    set_funcs->insert("u_size");
    set_funcs->insert("u_insert");
    set_funcs->insert("u_remove");
    set_funcs->insert("u_output");
    set_funcs->insert("u_find");
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
    initFSTSet();
    initFSTDFA();
    initSTNFA();
    initCFG();
    initFSTPDA();
    initSetFuncs();
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
    int reti = regcomp(&regex, reg.c_str(), REG_EXTENDED);
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
            if (val == REG_NOMATCH)
                return false;
            return true;
        }
        return false;
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
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
    this->isTemplate = false;
    this->template_params.clear();
}

FunctionSymbolTableEntry::FunctionSymbolTableEntry(std::string name, int num_params, VarSymbolTable *params, std::string return_type, bool isTemplate, std::vector<std::string> template_params)
{
    this->name = name;
    this->num_params = num_params;
    this->params = params;
    this->return_type = return_type;
    this->isTemplate = isTemplate;
    this->template_params = template_params;
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

bool StructSymbolTable::remove(std::string name)
{
    if (sst->lookup(name) == NULL)
        return 1;
    this->entries.erase(name);
    return 0;
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
        return t_attr->ifStruct;
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
    if (sst->lookup(type1) && sst->lookup(type1)->isTemplate)
        return true;
    if (sst->lookup(type2) && sst->lookup(type2)->isTemplate)
        return true;
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