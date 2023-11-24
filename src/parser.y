%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fstream>
#include <list>
#include <iostream>
#include <queue>
#include <typeinfo>
#include "../includes/st.hh"


#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

extern int yylex();
void yyerror(char const* str);
extern FILE* yyin;
extern std::fstream seq_token;
FILE* parse_log;
std::fstream cc_file;
std::queue<std::queue<std::string>> st;
std::queue<std::string> *current_queue = NULL;
std::vector<std::string> *current_states = NULL;
std::vector<std::pair<std::string,std::string>> *current_alphabets = NULL;
std::vector<std::string> *cfg_rhs_current = NULL;
std::vector<std::vector<std::string>> *cfg_prods = NULL;
std::vector<std::vector<std::string>> *transition = NULL;
std::vector<std::pair<std::string,std::string>> *pda_lhs = NULL;
std::vector<std::pair<std::string,std::string>> *pda_rhs = NULL;
std::vector<std::string> *nfa_dfa_rhs = NULL;
std::vector<std::string> *nfa_dfa_lhs = NULL;
int current_automata = 0;
extern int yylineno;
void terminate()
{
    fclose(yyin);
    cc_file.close();
    exit(1);
}

int in_function = 0;
int in_loop = 0;
int num_params = 0;
int isTemplateFn = 0;
FunctionSymbolTableEntry *current_function;

#define printlog(a) fprintf(parse_log,"%s declaration at line no: %d\n",a,yylineno)
#define getVTA(a) (a==TYPE_NFA?"NFA":(a==TYPE_DFA?"DFA":(a==TYPE_PDA?"PDA":(a==TYPE_CFG?"CFG":""))))
#define getConst(a) (a->val->type==CINT?a->val->ccint:(a->val->type==CFLOAT?a->val->ccfloat:(a->val->type==CBOOL?a->val->ccbool:a->val->ccchar)))
#define getCTYPE(a) ((a->vtp==TYPE_INT_64 || a->vtp==TYPE_INT_32 || a->vtp==TYPE_INT_16 || a->vtp==TYPE_INT_8)?CINT:((a->vtp==TYPE_FLOAT_64 || a->vtp==TYPE_FLOAT_32)?CFLOAT:((a->vtp==TYPE_BOOL)?CBOOL:CCHAR)))
#define getVTP(a) (a==TYPE_INT_64?"int_64":(a==TYPE_INT_32?"int_32":(a==TYPE_INT_16?"int_16":(a==TYPE_INT_8?"int_8":(a==TYPE_FLOAT_64?"float_64":(a==TYPE_FLOAT_32?"float_32":(a==TYPE_BOOL?"bool":"char")))))))
#define getVTS(a) (a==TYPE_OSET?"o_set":"u_set")
#define getVTSR(a) (a==TYPE_STR?"string":(a==TYPE_REGEX?"regex":"struct"))
#define getFSM(a) (a==TYPE_DFA?"dfa":(a==TYPE_NFA?"nfa":(a==TYPE_PDA?"pda":"cfg")))
%}
%code requires {
    #include "../includes/semantic.hh"
    #include "../includes/attr.hh"
    #include "../includes/helper.hh"
}
%union {
    // Constants
    int cint;
    float cfloat;
    char cchar;
    char* cstring;
    bool cbool;

    // Data types
    expr_attr *expr;
    id_attr *id;
    type_attr *type;
    arg_list_attr *arg;
    func_attr *func;
    id_list_attr *id_lst;
    expr_list_attr *expr_lst;
    param_list_attr *para;
    state_list_attr *state_lst;
    rules_attr *rules;
    rhs_automata_attr *rhs_automata;
    lhs_arrow_attr *lhs_arrow;
    cfg_rule_attr *cfg_rule;
    element_PDA_attr *ele_pda;
    elements_PDA_attr *eles_pda;
    cc_code *c;

    VTYPE_PRIMITIVE dtype_primitive;
    VTYPE_AUTOMATA dtype_automata;
    VTYPE_SET dtype_set;
    VTYPE_SR dtype_SR;

    // Variables
    char* identifier;
    char* comp;
}
%left PSEUDO_LOW
%left <dtype_primitive> TYPE_PRIMITIVE
%left <dtype_SR> TYPE_STRING TYPE_REG
%left <dtype_set> TYPE_SET
%left <dtype_automata> TYPE_AUTOMATA
%token <cint> INT_CONST <cfloat> FLOAT_CONST <cstring> STRING_CONST <cchar> CHAR_CONST <cbool> BOOL_CONST
%left REGEX_R REGEX_LIT
%left <identifier> ID
%token IF_KW ELIF_KW ELSE_KW WHILE_KW BREAK_KW STRUCT_KW RETURN_KW CONTINUE_KW TEMP_FN_KW
%token ARROW COLON
%left COMMA DOT SEMICOLON DOLLAR
%left OPER_AND OPER_OR
%left<comp> OPER_COMP COMP_GT COMP_LT TEMP_LEFT TEMP_RIGHT
%left OPER_PLUS OPER_MINUS OPER_MUL OPER_DIV OPER_MOD
%left AT_THE_RATE OPER_POWER
%left OPER_NOT OPER_HASH
%token<identifier> OPER_ASN OPER_ASN_SIMPLE
%left LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE
%token EPSILON

%nterm<expr> expression
%nterm<id> pseudo_ID param
%nterm<type> rhs dtype set_type return_statement call
%nterm<id_lst> id_list id_list_decl 
%nterm<para> param_list next_param
%nterm<arg> argument_list arg_list_next
%nterm<expr_lst> expression_list
%nterm<state_lst> states_list type_list type_list_call
%nterm<rules> rule rules_list
%nterm<lhs_arrow> rhs_arrow lhs_arrow elements_others 
%nterm<rhs_automata> rhs_automata
%nterm<c> assignment statements function_header cfg_rhs_ele
%nterm<cfg_rule> cfg_rule
%nterm<ele_pda> element_PDA
%nterm<eles_pda> elements_PDA
%start program
%%

program : instruction_list
        {
            if(!fst->lookup("main"))
                yyerror("No main function found");
        }

instruction_list: instruction_list struct_declaration
                | instruction_list function_declaration
                | instruction_list statements
                |
                ;

struct_declaration: STRUCT_KW ID
                                {
                                    //check if struct already exists
                                    if(sst->lookup(std::string($2)))
                                    {
                                        if(sst->lookup(std::string($2))->isTemplate)
                                        {
                                            std::string error = "typename in use: "+std::string($2);
                                            yyerror(error.c_str());
                                        }
                                        std::string error = "Struct redeclaration: "+std::string($2);
                                        yyerror(error.c_str());
                                    }
                                    cc_file<<"struct "<<std::string($2)<<std::string(" ")<<std::string("{\n\tpublic:")<<std::endl;
                                } 
                    LBRACE {
                                //create a new symbol table
                                VarSymbolTable *new_st = new VarSymbolTable();
                                current_vst = new_st;
                                vstl->insert(new_st);
                            } 
                    struct_body RBRACE SEMICOLON
                    {
                        //first get the symbol table for this struct and put it into the members column of the struct symbol table
                        StructSymbolTableEntry *entry = new StructSymbolTableEntry(std::string($2),current_vst);
                        sst->insert(entry);
                        printlog("Struct");
                        //remove struct scope from the varSymbolTableList
                        if(vstl->remove())
                            yyerror("Internal Error");
                        current_vst = vstl->getTop();
                        cc_file<<std::string("};")<<std::endl;
                    }
                ;

struct_body: struct_body struct_member
            | struct_member
            ;

struct_member: dtype id_list_decl SEMICOLON
            {
                //backpatching here
                
                if($1->indicator!=3)
                {
                    for(auto it = $2->lst.begin();it!=$2->lst.end();it++)
                    {
                        if(current_vst->backpatch(it->first,getType($1),$1->inner,NULL))
                        {
                            yyerror("Internal Error");
                        }
                        if($1->indicator==2)//sets (set inner type)
                        {
                            it->first->inner = $1->inner;
                        }
                    }
                }
                else
                {
                    for(auto it = $2->lst.begin();it!=$2->lst.end();it++)
                    {
                        VarSymbolTable *struct_vst = sst->lookup(std::string(getFSM($1->vta)))->fields;
                        if(current_vst->backpatch(it->first,getType($1),NULL,struct_vst))
                        {
                            yyerror("Internal Error");
                        }
                    }
                }
                cc_file<<$1->cc<<$2->cc<<";"<<std::endl;
            }
            | ID id_list_decl SEMICOLON
            {
                //check if struct exists
                if(!sst->lookup(std::string($1)))
                {
                    std::string str = std::string("Error: Struct ")+std::string($1)+std::string(" not defined");
                    yyerror(str.c_str());
                }
                //backpatching here
                //create an empty vector
                std::list<int> *temp;
                temp = new std::list<int>();
                VarSymbolTable *struct_vst = sst->lookup(std::string($1))->fields;
                for(auto it = $2->lst.begin();it!=$2->lst.end();it++)
                {
                    if(current_vst->backpatch(it->first,std::string($1),NULL,struct_vst))
                    {
                        yyerror("Internal Error");
                    }
                }
                cc_file<<std::string($1)<<$2->cc<<";"<<std::endl;
            }
            ;

id_list_decl: ID
            {
                //create a new symbol table entry
                $$ = new id_list_attr();
                //insert this ID in the symbol table (backpatch later)
                if(current_vst->lookup(std::string($1)))
                {
                    std::string error = "Variable redeclaration in struct: "+std::string($1);
                    yyerror(error.c_str());
                }
                VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string($1));
                current_vst->insert(entry);
                type_attr *type = new type_attr();
                type->indicator = 0;
                $$->lst.push_back(std::make_pair(entry,type));
                $$->cc = std::string(" ")+std::string($1);
            }
            | id_list_decl COMMA ID
            {
                //create a new symbol table entry
                $$ = new id_list_attr();
                //insert this ID in the symbol table (backpatch later)
                if(current_vst->lookup(std::string($3)))
                {
                    std::string error = "Variable redeclaration in struct: "+std::string($3);
                    yyerror(error.c_str());
                }
                VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string($3));
                current_vst->insert(entry);
                type_attr *type = new type_attr();
                type->indicator = 0;
                $$->lst = $1->lst;
                $$->lst.push_back(std::make_pair(entry,type));
                $$->cc = $1->cc + std::string(", ") + std::string($3);
            }
            ;

expression_list: expression
                {
                    $$ = new expr_list_attr();
                    $$->inner = getType($1);
                    if(current_queue==NULL)
                    {
                        current_queue = new std::queue<std::string>();
                        current_queue->push($1->cc);
                    }
                    else
                    {
                        current_queue->push($1->cc);
                    }
                }
               | expression_list COMMA expression
               {
                 if(!isCoherent(getType($3),$1->inner))
                 {
                    std::string error = std::string("Error: Invalid type conversion from ")+getType($3)+std::string(" to ")+$1->inner;
                    yyerror(error.c_str());
                 }
                $$ = new expr_list_attr();
                $$->inner = $1->inner;
                current_queue->push($3->cc);
               }
               ;

function_declaration: function_header LBRACE
                    {
                        //create a function scope
                        VarSymbolTable *new_st = new VarSymbolTable();
                        vstl->insert(new_st);
                        current_vst = new_st;
                        cc_file<<$1->cc<<std::string("\t")<<std::string("{")<<std::endl;
                    }    
                    function_body RBRACE 
                    {
                        in_function = 0;
                        //remove function scope
                        if(vstl->remove())
                            yyerror("Internal Error");
                        if(vstl->remove())
                            yyerror("Internal Error");
                        current_vst = vstl->getTop();
                        // if(isTemplateFn)
                        // {
                        //     //remove struct entries
                        //     std::vector<std::string> type_list = current_function->template_params;
                        //     for(auto it = type_list.begin();it!=type_list.end();it++)
                        //     {
                        //         if(sst->remove(*it))
                        //             yyerror("Internal Error");
                        //     }
                        // }
                        isTemplateFn = 0;
                        current_function = NULL;
                        cc_file<<std::string("}")<<std::endl;
                    }
                    ;

function_header: dtype ID LPAREN param_list RPAREN {
                        //check if function exists
                        if(fst->lookup(std::string($2)))
                        {
                            std::string error = "Function redeclaration: "+std::string($2);
                            yyerror(error.c_str());
                        }
                        printlog("Function");
                        if(in_function)
                            yyerror("Nested function declaration");
                        in_function = 1;
                        //handling param_list
                        //push new function to function table
                        FunctionSymbolTableEntry *entry = new FunctionSymbolTableEntry(std::string($2),num_params,current_vst,getType($1));
                        vstl->insert(entry->params);
                        current_vst = entry->params;
                        //handling return type
                        std::string outer;
                        if($1->indicator==2)//set
                        {
                            outer = getType($1);
                            outer= outer + std::string(" ") + $1->inner->print();
                            entry->return_type = outer;
                        }
                        else
                        {
                            outer = getType($1);
                            entry->return_type = outer;
                        }
                        current_function = entry;
                        //insert function into function table
                        for(auto it = $4->lst.begin();it!=$4->lst.end();it++)
                        {
                            entry->id_list.push_back(*it);
                            if(entry->params->lookup(*it)->type=="template")
                            {
                                std::string error = "Invalid type for argument: "+std::string(*it);
                                yyerror(error.c_str());
                            }
                        }
                        fst->insert(entry);
                        $$ = new cc_code();
                        $$->cc = $1->cc + std::string(" ") + std::string($2) + std::string("(") + $4->cc + std::string(")");
                    }
                | ID ID LPAREN param_list RPAREN {
                        //check if function exists

                        if(fst->lookup(std::string($2)))
                        {
                            std::string error = "Function redeclaration: "+std::string($2);
                            yyerror(error.c_str());
                        }
                        printlog("Function");
                        if(in_function)
                            yyerror("Nested function declaration");
                        in_function = 1;
                        //check if struct exists
                        if(std::string($1)!=std::string("void"))
                        {
                            if(!sst->lookup(std::string($1)))
                            {
                                std::string str = std::string("Error: Struct ")+std::string($1)+std::string(" not defined");
                                yyerror(str.c_str());
                            }
                        }
                        //push new function to function table
                        FunctionSymbolTableEntry *entry = new FunctionSymbolTableEntry(std::string($2),num_params,current_vst,std::string($1));
                        vstl->insert(entry->params);
                        current_vst = entry->params;
                        current_function = entry;
                        //insert function into function table
                        for(auto it = $4->lst.begin();it!=$4->lst.end();it++)
                        {
                            entry->id_list.push_back(*it);
                            if(entry->params->lookup(*it)->type=="template")
                            {
                                std::string error = "Invalid type for argument: "+std::string(*it);
                                yyerror(error.c_str());
                            }
                        }
                        fst->insert(entry);
                        std::string str = std::string($1) + std::string(" ") + std::string($2) + std::string("(") + $4->cc + std::string(")");
                        // $$->cc = str;
                        cc_file<<str;
                    }
                | TEMP_FN_KW TEMP_LEFT type_list TEMP_RIGHT ID ID LPAREN param_list RPAREN {
                        // struct return type
                        // need to insert the typenames into the struct symbol table and after the function need to remove them
                        if(in_function)
                            yyerror("Nested function declaration");
                        in_function = 1;
                        isTemplateFn = 1;
                        //check for function
                        if(fst->lookup(std::string($6)))
                        {
                            std::string error = "Function redeclaration: "+std::string($6);
                            yyerror(error.c_str());
                        }
                        //check if struct exists
                        FunctionSymbolTableEntry *entry;
                        std::vector<std::string> type_list;
                        for(auto it = $3->lst.begin();it!=$3->lst.end();it++)
                        {
                            type_list.push_back(*it);
                        }
                        if(std::string($5)!=std::string("void"))
                        {
                            if(sst->lookup(std::string($5)))
                            {
                                //return type is struct
                                entry = new FunctionSymbolTableEntry(std::string($6),num_params,current_vst,std::string($5),true,type_list);
                                vstl->insert(entry->params);
                                current_vst = entry->params;
                            }
                            else
                            {
                                std::string str = std::string("Error: struct ")+std::string($5)+std::string(" not defined");
                                yyerror(str.c_str());
                            }
                        }
                        else
                        {
                            //return type is void
                            entry = new FunctionSymbolTableEntry(std::string($6),num_params,current_vst,std::string($5),true,type_list);
                            vstl->insert(entry->params);
                            current_vst = entry->params;
                        }
                        //type checking for arguments
                        current_function = entry;
                        for(auto it = $8->lst.begin();it!=$8->lst.end();it++)
                        {
                            std::string type = entry->params->lookup(*it)->type;
                            if(isPrimitive(type) || isAutomata(type))
                                ;
                            else if(isSet(type))
                            {
                                //recurisvely find the inner template/struct
                                std::string inner = entry->params->lookup(*it)->inner->print();
                                inner = trim(inner);
                                if(inner.find(" ")==std::string::npos)
                                {
                                    //check structs
                                    if(sst->lookup(inner) || isAutomata(inner) || isPrimitive(inner))
                                        ;
                                    else
                                    {
                                        std::string error = "Invalid type for argument Struct/typename not defined: "+std::string(*it);
                                        yyerror(error.c_str());
                                    }
                                }
                                else
                                {
                                    std::string inner_next = inner.substr(0,inner.find(" "));
                                    while(isSet(inner_next))
                                    {
                                        inner = inner.substr(inner.find(" ")+1);
                                        inner_next = inner.substr(0,inner.find(" "));
                                    }
                                    if(sst->lookup(inner_next) || isPrimitive(inner_next) || isAutomata(inner_next))
                                        ;
                                    else
                                    {
                                        std::string error = "Invalid type for argument Struct/typename not defined: "+std::string(*it);
                                        yyerror(error.c_str());
                                    }
                                }
                            }
                            else if(sst->lookup(type))
                                ;
                            else if(std::find(type_list.begin(),type_list.end(),type)!=type_list.end())
                                ;
                            else
                            {
                                std::string error = "Invalid type for argument Struct/typename not defined: "+std::string(*it);
                                yyerror(error.c_str());
                            }
                            entry->id_list.push_back(*it);
                        }
                        fst->insert(entry);
                        
                        $$ = new cc_code();
                        $$->cc = "template <" + $3->cc + std::string("> ") + std::string($5) + std::string(" ") + std::string($6) + std::string("(") + $8->cc + std::string(")");
                        std::cout<<$$->cc<<std::endl;
                        cc_file<<$$->cc;
                        $$->cc = "";
                    }
                | TEMP_FN_KW TEMP_LEFT type_list TEMP_RIGHT dtype ID LPAREN param_list RPAREN {
                    if(in_function)
                            yyerror("Nested function declaration");
                    in_function = 1;
                    isTemplateFn = 1;
                    //check for function
                    if(fst->lookup(std::string($6)))
                    {
                        std::string error = "Function redeclaration: "+std::string($6);
                        yyerror(error.c_str());
                    }
                    //make a functionsymboltable entry
                    std::vector<std::string> type_list;
                    for(auto it = $3->lst.begin();it!=$3->lst.end();it++)
                    {
                        type_list.push_back(*it);
                    }
                    FunctionSymbolTableEntry *entry = new FunctionSymbolTableEntry(std::string($6),num_params,current_vst,getType($5),true,type_list);
                    vstl->insert(entry->params);
                    current_vst = entry->params;
                    std::string outer;
                    if($5->indicator==2)//set
                    {
                        outer = getType($5);
                        outer= outer + std::string(" ") + $5->inner->print();
                        entry->return_type = outer;
                    }
                    else
                    {
                        outer = getType($5);
                        entry->return_type = outer;
                    }
                    outer = trim(outer);
                    current_function = entry;
                    fst->insert(entry);
                    //type checking of arguments
                    for(auto it = $8->lst.begin();it!=$8->lst.end();it++)
                    {
                        std::string type = entry->params->lookup(*it)->type;
                        if(isSet(type))
                        {
                                std::string inner = entry->params->lookup(*it)->inner->print();
                                inner = trim(inner);
                                if(inner.find(" ")==std::string::npos)
                                {
                                    //check structs
                                    if(sst->lookup(inner) || isPrimitive(inner) || isAutomata(inner))
                                        ;
                                    else
                                    {
                                        std::string error = "Invalid type for argument Struct/typename not defined: "+std::string(*it);
                                        yyerror(error.c_str());
                                    }
                                }
                                else
                                {
                                    std::string inner_next = inner.substr(0,inner.find(" "));
                                    while(isSet(inner_next))
                                    {
                                        inner = inner.substr(inner.find(" ")+1);
                                        inner_next = inner.substr(0,inner.find(" "));
                                    }
                                    if(sst->lookup(inner_next) || isPrimitive(inner_next) || isAutomata(inner_next))
                                        ;
                                    else
                                    {
                                        std::string error = "Invalid type for argument Struct/typename not defined: "+std::string(*it);
                                        yyerror(error.c_str());
                                    }
                                }
                        }
                        else if(isPrimitive(type) || isAutomata(type))
                            ;
                        else if(sst->lookup(type))
                            ;
                        else if(std::find(type_list.begin(),type_list.end(),type)!=type_list.end())
                            ;
                        else
                        {
                            std::string error = "Invalid type for argument Struct/typename not defined: "+std::string(*it);
                            yyerror(error.c_str());
                        }
                        //insert into param list
                        entry->id_list.push_back(*it);

                    }
                        $$ = new cc_code();
                        $$->cc = "template <" + $3->cc + std::string("> ") + $5->cc + std::string(" ") + std::string($6) + std::string("(") + $8->cc + std::string(")");
                        std::cout<<$$->cc<<std::endl;
                        cc_file<<$$->cc;
                        $$->cc = "";
                }
                ;

type_list : ID
          {
            
            //check if ID exists as a struct
            if(sst->lookup(std::string($1)))
            {
                std::string error = "Cannot be used as typename as Struct with same name exists: "+std::string($1);
                yyerror(error.c_str());
            }
            if(std::string($1)=="void")
            {
                yyerror("Cannot use void as typename");
            }
            $$ = new state_list_attr();
            $$->lst.push_back(std::string($1));
            //insert this ID in the struct symbol table
            VarSymbolTable *table = new VarSymbolTable();
            StructSymbolTableEntry *entry_struct = new StructSymbolTableEntry(std::string($1),table);
            entry_struct->isTemplate = true;
            sst->insert(entry_struct);
            $$->cc = "typename " + std::string($1);
          }
          | type_list COMMA ID
          {
            //check if ID exists as a struct
            if(sst->lookup(std::string($3)))
            {
                std::string error = "Cannot be used as typename as Struct with same name exists: "+std::string($3);
                yyerror(error.c_str());
            }
            if(std::string($3)=="void")
            {
                yyerror("Cannot use void as typename");
            }
            $$ = new state_list_attr();
            $$->lst = $1->lst;
            $$->lst.push_back(std::string($3));
            //insert this ID in the struct symbol table
            VarSymbolTable *table = new VarSymbolTable();
            StructSymbolTableEntry *entry_struct = new StructSymbolTableEntry(std::string($3),table);
            entry_struct->isTemplate = true;
            sst->insert(entry_struct);
            $$->cc = $1->cc + std::string(", typename ") + std::string($3);
          }
          ;

param_list: 
            {
                //no params
                $$ = new param_list_attr();
                $$->num = 0;
                VarSymbolTable *new_st = new VarSymbolTable();
                current_vst = new_st;
                vstl->insert(new_st);
                $$->cc = std::string("");
            }
          | param next_param
          {
            if(vstl->lookup($1->name))
            {
                std::string error = "Variable redeclaration: "+$1->name;
                yyerror(error.c_str());
            }
            if($1->indicator==7)
            {
                //check if struct exists
                if(!sst->lookup($1->ifStruct))
                {
                    std::string str = std::string("Error: Struct ")+$1->ifStruct+std::string(" not defined");
                    yyerror(str.c_str());
                }
                VarSymbolTableEntry *entry = new VarSymbolTableEntry($1->name);
                entry->type = $1->ifStruct;
                entry->struct_vst = sst->lookup($1->ifStruct)->fields;
                current_vst->insert(entry);
            }
            else
            {
                VarSymbolTableEntry *entry = new VarSymbolTableEntry($1->name);
                if($1->indicator!=8)
                    entry->type = getType($1);
                else
                    entry->type = std::string("template");
                if($1->indicator==2)
                {
                    entry->inner = genInnerType($1->inner);
                }
                current_vst->insert(entry);
            }
            $$ = new param_list_attr();
            $$->num = num_params;
            $$->lst = $2->lst;
            $$->lst.push_back($1->name);
            $$->cc = $1->cc + std::string(" ") + $2->cc;
          }
          ;

param: dtype ID
     {
        $$ = new id_attr();
        $$->name = std::string($2);
        $$->indicator = $1->indicator;
        $$->vtp = $1->vtp;
        $$->vta = $1->vta;
        $$->vts = $1->vts;
        std::string inner = $1->inner->print();
        if(inner[inner.length()-1]==' ')
            inner = inner.substr(0,inner.length()-1);
        $$->inner = inner;
        ++num_params;
        $$->cc = $1->cc + std::string(" ") + std::string($2);
     }
     | ID ID
     {
        $$ = new id_attr();
        $$->name = std::string($2);
        $$->indicator = 7;
        if(!sst->lookup(std::string($1)))
        {
            $$->indicator = 8;
        }
        $$->vtsr = TYPE_STRU;
        $$->ifStruct = std::string($1);
        ++num_params;
        $$->cc = std::string($1) + std::string(" ") + std::string($2);
     }
     ;

next_param : 
            {
                //end of params
                $$ = new param_list_attr();
                $$->num = num_params;

                VarSymbolTable *new_st = new VarSymbolTable();
                current_vst = new_st;
                $$->cc = std::string("");
            }
           | COMMA param next_param
           {
                $$ = new param_list_attr();
                $$->num = num_params;
                $$->lst = $3->lst;
                $$->lst.push_back($2->name);
                //check if variable redeclaration
                if(vstl->lookup($2->name))
                {
                    std::string error = "Variable redeclaration: "+$2->name;
                    yyerror(error.c_str());
                }
                if($2->indicator ==7)
                {
                    //check if struct exists
                    if(!sst->lookup($2->ifStruct))
                    {
                        std::string str = std::string("Error: Struct ")+$2->ifStruct+std::string(" not defined");
                        yyerror(str.c_str());
                    }
                    VarSymbolTableEntry *entry = new VarSymbolTableEntry($2->name);
                    entry->type = $2->ifStruct;
                    entry->struct_vst = sst->lookup($2->ifStruct)->fields;
                    current_vst->insert(entry);
                }
                else
                {
                    VarSymbolTableEntry *entry = new VarSymbolTableEntry($2->name);
                    entry->type = getType($2);
                    if($2->indicator==2)
                    {
                        entry->inner = genInnerType($2->inner);
                    }
                    current_vst->insert(entry);
                }
                $$->cc = std::string(", ")+$2->cc + std::string(" ") + $3->cc;
           }
           ;

function_body: function_body statements
             | SEMICOLON
             |
             ;

statements: variable_declaration {
            printlog("Variable declaration");
            }
          | assignment {
            printlog("Assignment");
            $$ = new cc_code();
            $$->cc = $1->cc;
            cc_file<<$$->cc<<std::endl;
            }
          | if_statement
          {
            $$ = new cc_code();
            $$->cc = std::string("");
          }
          | while_statement
          {
            $$ = new cc_code();
            $$->cc = std::string("");
          }
          | return_statement {printlog("Return");}
          | break_statement {printlog("Break");}
          | continue_statement {printlog("Continue");}
          | call_statement {printlog("Function call");}
          | LBRACE {
                        //create a new symbol table
                        VarSymbolTable *new_st = new VarSymbolTable();
                        current_vst = new_st;
                        vstl->insert(new_st);
                    }
          control_body RBRACE {
            //remove symbol table
            if(vstl->remove())
                yyerror("Internal Error");
            current_vst = vstl->getTop();
            printlog("Block");
            }
          ;

variable_declaration: dtype id_list SEMICOLON
                    {
                        // backpatch id_list with dtype

                        for(auto it = $2->lst.begin();it!=$2->lst.end();it++)
                        {
                            if(it->second->indicator)
                            {
                                if(it->second->indicator!=1 && $1->indicator==1) //Primitive DTYPE
                                {
                                    std::string str = std::string("Error: Invalid type conversion from ")+getType(it->second)+std::string(" to ")+getType($1);
                                    yyerror(str.c_str());
                                }
                                // for dynamic set initialization also need to check inner type (to be done)
                                if($1->indicator==2 && (it->second->indicator!=2 && it->second->indicator!=6)) //Set DTYPE
                                {
                                    std::string str = std::string("Error: Invalid type conversion from ")+getType(it->second)+std::string(" to ")+getType($1);
                                    yyerror(str.c_str());
                                    // *** sets
                                }
                                if($1->indicator==3 && it->second->indicator!=3 || ($1->indicator==3 && $1->vta != it->second->vta))
                                {
                                    std::string str = std::string("Error: Invalid type conversion from ")+getType(it->second)+std::string(" to ")+getType($1);
                                    yyerror(str.c_str());
                                }
                                if($1->indicator==4 && it->second->indicator!=4)
                                {
                                    std::string str = std::string("Error: Invalid type conversion from ")+getType(it->second)+std::string(" to ")+getType($1);
                                    yyerror(str.c_str());
                                }
                                if($1->indicator==5 && it->second->indicator!=5)
                                {
                                    std::string str = std::string("Error: Invalid type conversion from ")+getType(it->second)+std::string(" to ")+getType($1);
                                    yyerror(str.c_str());
                                }
                            }
                        }
                        // safe to backpatch
                        if($1->indicator!=3)
                        {
                            for(auto it = $2->lst.begin();it!=$2->lst.end();it++)
                            {
                                if(current_vst->backpatch(it->first,getType($1),$1->inner,NULL))
                                {
                                    yyerror("Internal Error");
                                }

                            }
                            if($1->indicator!=2)
                            {
                                cc_file<<$1->cc + std::string(" ") + $2->cc +std::string(";")<<std::endl;
                            }  
                            else
                            {
                                int i = 0;
                                bool flag = false;
                                for(auto it=$2->lst.begin();it!=$2->lst.end();it++)
                                {
                                   if(it->second->indicator!=6 && i)
                                   {
                                     cc_file<<std::string(" ,")<<it->first->name;
                                     ++i;
                                     flag = false;
                                   }
                                   else if(it->second->indicator!=6)
                                   {
                                     cc_file<<$1->cc+ std::string(" ");
                                     cc_file<<std::string(" ")<<it->first->name;
                                     ++i;
                                     flag = false;
                                   }
                                   else
                                   {
                                    std::queue<std::string> stk;
                                    stk = st.front();
                                    cc_file<<";\n"<<$1->cc + std::string(" ")<<it->first->name<<";"<<std::endl;
                                    st.pop();
                                    i=0;
                                    while(!stk.empty())
                                    {
                                        // add inserts
                                        std::string str = stk.front();
                                        stk.pop();
                                        cc_file<<it->first->name<<".insert("<<str<<");"<<std::endl;
                                    }
                                    flag = true;    
                                   }
                                } 
                                if(!flag)
                                    cc_file<<";"<<std::endl;
                            }    
                        }
                        else
                        {
                            for(auto it=$2->lst.begin();it!=$2->lst.end();it++)
                            {
                                VarSymbolTable *struct_vst = sst->lookup(std::string(getFSM($1->vta)))->fields;
                                if(current_vst->backpatch(it->first,getType($1),NULL,struct_vst))
                                {
                                    yyerror("Internal Error");
                                }
                            }
                            cc_file<<$1->cc + std::string(" ") + $2->cc +std::string(";")<<std::endl;
                        }
                    }
                    | ID id_list SEMICOLON
                    {
                        //check if struct exists
                        if(!sst->lookup(std::string($1)))
                        {
                            std::string str = std::string("Error: Struct ")+std::string($1)+std::string(" not defined");
                            yyerror(str.c_str());
                        }
                        std::list<int> *temp;
                        temp = new std::list<int>();
                        VarSymbolTable *struct_fields = sst->lookup(std::string($1))->fields;
                        for(auto it = $2->lst.begin();it!=$2->lst.end();it++)
                        {
                            if(current_vst->backpatch(it->first,std::string($1),NULL,struct_fields))
                            {
                                yyerror("Internal Error");
                            }
                        }
                        // before backpatching check if rhs are variables of same struct type (to be done)
                        cc_file<<"struct "<<std::string($1)<<" "<<$2->cc<<";"<<std::endl;
                    }
                    ;

id_list: ID {
                $$ = new id_list_attr();
                //insert this ID in the symbol table (backpatch later)
                if(current_vst->lookup(std::string($1)))
                {
                    std::string error = "Variable redeclaration: "+std::string($1);
                    yyerror(error.c_str());
                }
                //check in function params also
                if(current_function)
                {
                    if(current_function->params->lookup(std::string($1)))
                    {
                        std::string error = "Variable redeclaration: "+std::string($1);
                        yyerror(error.c_str());
                    }
                }
                VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string($1));
                current_vst->insert(entry);
                type_attr *type = new type_attr();
                type->indicator = 0;
                $$->lst.push_back(std::make_pair(entry,type));
                $$->cc = std::string($1);
            }
       | ID OPER_ASN_SIMPLE rhs
       {
            $$ = new id_list_attr();
            //insert this ID in the symbol table (backpatch later)
            if(current_vst->lookup(std::string($1)))
            {
                std::string error = "Variable redeclaration: "+std::string($1);
                yyerror(error.c_str());
            }
            //check if function params also
            if(current_function)
            {
                if(current_function->params->lookup(std::string($1)))
                {
                    std::string error = "Variable redeclaration: "+std::string($1);
                    yyerror(error.c_str());
                }
            }
            VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string($1));
            current_vst->insert(entry);
            type_attr *type = new type_attr();
            type->indicator = $3->indicator;
            type->vtp = $3->vtp;
            type->vta = $3->vta;
            type->vts = $3->vts;
            if(!current_function && !$3->isConst)
                yyerror("Cannot initialize global variable with a non-constant value");
            $$->lst.push_back(std::make_pair(entry,type));
            $$->cc = std::string($1) + std::string(" = ") + std::string($3->cc);
       }
       | id_list COMMA ID
       {
            $$ = new id_list_attr();
            //insert this ID in the symbol table (backpatch later)
            if(current_vst->lookup(std::string($3)))
            {
                std::string error = "Variable redeclaration: "+std::string($3);
                yyerror(error.c_str());
            }
            VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string($3));
            current_vst->insert(entry);
            type_attr *type = new type_attr();
            type->indicator = 0;
            //append to list
            $$->lst = $1->lst;
            $$->lst.push_back(std::make_pair(entry,type));
            $$->cc = $1->cc + std::string(", ") + std::string($3);
       }
       | id_list COMMA ID OPER_ASN_SIMPLE rhs
       {
            $$ = new id_list_attr();
            //insert this ID in the symbol table (backpatch later)
            if(current_vst->lookup(std::string($3)))
            {
                std::string error = "Variable redeclaration: "+std::string($3);
                yyerror(error.c_str());
            }
            VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string($3));
            current_vst->insert(entry);
            type_attr *type = new type_attr();
            type->indicator = $5->indicator;
            type->vtp = $5->vtp;
            type->vta = $5->vta;
            type->vts = $5->vts;
            //append to list
            $$->lst = $1->lst;
            $$->lst.push_back(std::make_pair(entry,type));
            $$->cc = $1->cc + std::string(", ") + std::string($3) + std::string(" = ") + $5->cc;
       }
       ;

pseudo_ID: pseudo_ID LBRACK expression RBRACK
         {
            //accessing the set member
            if($3->indicator != 1)
                yyerror("Invalid operation: Set can only be accessed using integer index");
            if(!isInteger($3->vtp))
                yyerror("Invalid operation: Set can only be accessed using integer/unsigned integer index");
            //idea is to build the entire pseudo_ID and check whenever it is used somewhere
            $$ = new id_attr();
            if($3->isConst)
                $$->name = std::string($1->name)+std::string("[")+std::to_string($3->val->ccint)+std::string("]");
            else //first need to build expression
                $$->name = std::string($1->name)+std::string("[")+std::string("_expr_")+std::string("]");
            $$->cc = $1->cc + "[" + $3->cc + "]";
         }
         | pseudo_ID DOT pseudo_ID
         {
            //accessing the inner member
            $$ = new id_attr();
            $$->name = std::string($1->name)+std::string(".")+std::string($3->name);
            $$->cc = $1->cc + "." + $3->cc;
         }
         | ID {
                //check if ID exists
                $$ = new id_attr();
                $$->name = $1;
                $$->cc = std::string($1);
              }
         ;

assignment: pseudo_ID OPER_ASN rhs SEMICOLON
            {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,$1->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            //we need to match rhs type with type of pseudo_ID
            std::string type_lhs = ret.second.substr(ret.second.find(" ")+1);
            std::string type_rhs = getType($3);
            if(type_rhs[type_rhs.length()-1]==' ')
                    type_rhs=type_rhs.substr(0,type_rhs.length()-1);
            if(!isPrimitive(type_rhs) || !isPrimitive(type_lhs))
            {   
                //error
                std::string outer_lhs = type_lhs.find(" ")!=std::string::npos?type_lhs.substr(0,type_lhs.find(" ")):type_lhs;
                std::string error = std::string("Invalid operation: Cannot use operator ") + std::string($2) + std::string(" on ") +outer_lhs +std::string(" and ")+type_rhs;
                yyerror(error.c_str());
            }
            if(!isCoherent(type_lhs,type_rhs))
            {
                std::string error = std::string("Error: Invalid type conversion from ")+type_rhs+std::string(" to ")+type_lhs;
                yyerror(error.c_str());
            }
            // need to be done
            $$->cc = std::string($1->cc) + " " +std::string($2) + std::string($3->cc)+std::string(" ;");
            }
          | pseudo_ID OPER_ASN_SIMPLE rhs SEMICOLON {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,$1->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            std::string type_lhs = ret.second.substr(ret.second.find(" ")+1);
            std::string type_rhs = getType($3);
            if(type_rhs[type_rhs.length()-1]==' ')
                    type_rhs=type_rhs.substr(0,type_rhs.length()-1);
            if(type_rhs=="o_set"||type_rhs=="u_set"||type_rhs=="sets")
            {   
                type_rhs+=std::string(" ")+$3->inner->print();
                if(type_rhs[type_rhs.length()-1]==' ')
                    type_rhs=type_rhs.substr(0,type_rhs.length()-1);
            }
            if(!isCoherent(type_lhs,type_rhs))
            {
                std::string error = std::string("Error: Invalid type conversion from ")+type_rhs+std::string(" to ")+type_lhs;
                yyerror(error.c_str());
            }
            // need to be done
            if($3->indicator==6)
            {
                //set initialization
                std::queue<std::string> stk;
                stk = st.front();
                st.pop();
                $$->cc = "";
                while(!stk.empty())
                {
                    // add inserts
                    std::string str = stk.front();
                    stk.pop();
                    cc_file<<$1->cc<<".insert("<<str<<");"<<std::endl;
                }
            }
            else
                $$->cc = std::string($1->cc)+" = "+std::string($3->cc) + std::string(" ;");
            }    
          | pseudo_ID OPER_ASN_SIMPLE REGEX_R REGEX_LIT SEMICOLON
          {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,$1->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            std::string type_lhs = ret.second.substr(ret.second.find(" ")+1);
            std::string type_rhs("regex");
            if(!isCoherent(type_lhs,type_rhs))
            {
                std::string error = std::string("Error: Invalid type conversion from ")+type_rhs+std::string(" to ")+type_lhs;
                yyerror(error.c_str());
            }
          }
          | pseudo_ID OPER_ASN_SIMPLE STRING_CONST SEMICOLON
          {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,$1->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            std::string type_lhs = ret.second.substr(ret.second.find(" ")+1);
            std::string type_rhs("string");
            if(!isCoherent(type_lhs,type_rhs))
            {
                std::string error = std::string("Error: Invalid type conversion from ")+type_rhs+std::string(" to ")+type_lhs;
                yyerror(error.c_str());
            }
            $$->cc = std::string($1->cc)+" = "+std::string($3)+std::string(" ;");
          }
          | pseudo_ID COLON OPER_ASN_SIMPLE rhs_automata SEMICOLON
          {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,$1->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            std::string type = stripFound(ret.second);
            if(type!="alphabets" && type!="transitions_nfa" && type!="transitions_dfa" && type!="transitions_pda")
            {
                std::string error = std::string("Error: Invalid type conversion from transition function to ")+type;
                yyerror(error.c_str());
            }
            if(type=="alphabets" && $4->type!="alphabets")
            {
                std::string error = std::string("Error: Invalid type conversion from ")+$4->type+std::string(" to ")+type;
                yyerror(error.c_str());
            }
            if(type=="transitions_dfa" && ($4->type!="transitions" || $4->automata_type!="dfa"))
            {
                std::string error = std::string("Error: Invalid type conversion from ")+($4->type=="transitions"?(std::string("transitions_")+$4->automata_type):"alphabets")+std::string(" to ")+type;
                yyerror(error.c_str());
            }
            if(type=="transitions_pda" && ($4->type!="transitions" || $4->automata_type!="pda"))
            {
                std::string error = std::string("Error: Invalid type conversion from")+($4->type=="transitions"?(std::string("transitions_")+$4->automata_type):"alphabets")+std::string(" to ")+type;
                yyerror(error.c_str());
            }
            if(type=="transitions_nfa" && ($4->type!="transitions" || ($4->automata_type!="nfa" && $4->automata_type!="dfa")))
            {
                std::string error = std::string("Error: Invalid type conversion from")+($4->type=="transitions"?(std::string("transitions_")+$4->automata_type):"alphabets")+std::string(" to ")+type;
                yyerror(error.c_str());
            }
            //codegen
            if(type=="alphabets")
            {
                std::string str = $1->cc.substr(0,$1->cc.find_last_of("."));
                for(auto it = current_alphabets->begin(); it!=current_alphabets->end();it++)
                {
                    cc_file<<str<<".insert_alphabet("<<(*it).first<<", "<<(*it).second<<");"<<std::endl;
                }
                current_alphabets = NULL;
            }
            if(type=="transitions_nfa")
            {
                std::string str = $1->cc.substr(0,$1->cc.find_last_of("."));
                for(auto it = transition->begin(); it!=transition->end();it++)
                {
                    cc_file<<str<<".insert_transition(\""<<(*it)[0]<<"\", \""<<(*it)[1]<<"\", \""<<(*it)[2]<<"\");"<<std::endl;
                }
                transition = NULL;
            }
            if(type=="transitions_dfa")
            {
                std::string str = $1->cc.substr(0,$1->cc.find_last_of("."));
                for(auto it = transition->begin(); it!=transition->end();it++)
                {
                    cc_file<<str<<".insert_transition(\""<<(*it)[0]<<"\", \""<<(*it)[1]<<"\", \""<<(*it)[2]<<"\");"<<std::endl;
                }
                transition = NULL;
            }
            if(type=="transitions_pda")
            {
                std::string str = $1->cc.substr(0,$1->cc.find_last_of("."));
                for(auto it = transition->begin(); it!=transition->end();it++)
                {
                    cc_file<<str<<".insert_transition(\""<<(*it)[0]<<"\", \""<<(*it)[1]<<"\", \""<<(*it)[2]<<"\", \""<<(*it)[3]<<"\", \""<<(*it)[4]<<"\");"<<std::endl;
                }
                transition = NULL;
            }
          $$->cc = std::string("");
          current_automata = 0;
          }
          | pseudo_ID COLON OPER_ASN_SIMPLE cfg_rules SEMICOLON
          {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,$1->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            std::string type = stripFound(ret.second);
            if(type!="productions")
            {
                std::string error = std::string("Error: Invalid type conversion from productions to ")+type;
                yyerror(error.c_str());
            }
            //codegen
            std::string str = $1->cc.substr(0,$1->cc.find_last_of("."));
            $$->cc = std::string("");
            for(auto &it: *cfg_prods)
            {
                if(it[0].find(".")!=std::string::npos || it[0].find("[")!=std::string::npos)   
                    yyerror("Incorrect format of cfg non-terminal in lhs of rule");
                std::string init = it[0];
                std::string prod = it[1];
                cc_file<<str<<".add_P(\""<<init<<" -> "<<prod<<"\");"<<std::endl;
                
            }
            cfg_prods = NULL;
          }
          | pseudo_ID COLON OPER_ASN_SIMPLE ID SEMICOLON
          {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,$1->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            std::string type = stripFound(ret.second);
            if(type!="start")
            {
                std::string error = std::string("Error: Invalid type conversion from start state to")+type;
                yyerror(error.c_str());
            }
            $$->cc = std::string("");
            //codegen
            std::string str = $1->cc.substr(0,$1->cc.find_last_of("."));
            cc_file<<str<<".change_start(\""<<std::string($4)<<"\");"<<std::endl;
          }
          | pseudo_ID COLON OPER_ASN_SIMPLE LBRACE states_list RBRACE SEMICOLON
          {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,$1->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            // stateslist and accept states list
            std::string type = stripFound(ret.second);
            if(type!="states" && type!="accept")
            {
                std::string error = std::string("Error: Invalid type conversion from list of states to ")+type;
                yyerror(error.c_str());
            }
            if(type=="states")
            {
                std::string str = $1->cc.substr(0,$1->cc.find_last_of("."));
                for(auto &it: *current_states)
                {
                    cc_file<<str<<".insert_state("<<it<<");"<<std::endl;
                }
                current_states = NULL;
            }
            if(type=="accept")
            {
                std::string str = $1->cc.substr(0,$1->cc.find_last_of("."));
                for(auto &it: *current_states)
                {
                    cc_file<<str<<".insert_final("<<it<<");"<<std::endl;
                }
                current_states = NULL;
            }
            $$->cc = std::string("");
          }
          ;

states_list: ID
           {
                //need to accumulate IDs which will be used as states and non-terminals
                $$ = new state_list_attr();
                $$->lst.push_back(std::string($1));
                if(current_states==NULL)
                    current_states = new std::vector<std::string>();
                current_states->push_back("\""+std::string($1)+"\"");

           }
           | states_list COMMA ID
           {
                $$ = new state_list_attr();
                $$->lst = $1->lst;
                $$->lst.push_back(std::string($3));
                if(current_states==NULL)
                    current_states = new std::vector<std::string>();
                current_states->push_back("\""+std::string($3)+"\"");
           }
           ;

cfg_rules : LBRACE cfg_rule_list RBRACE
          ;

cfg_rule_list : cfg_rule
              | cfg_rule_list COMMA cfg_rule
              ;

cfg_rule : pseudo_ID ARROW cfg_rhs
            {
                //codegen
                std::string str = $1->cc.substr(0,$1->cc.find_last_of("."));
                for(auto &it: *cfg_rhs_current)
                {
                    std::vector<std::string> *temp = new std::vector<std::string>();
                    temp->push_back($1->cc);
                    temp->push_back(it);
                    if(cfg_prods==NULL)
                        cfg_prods = new std::vector<std::vector<std::string>>();
                    cfg_prods->push_back(*temp);
                }
                // std::cout<<"HERE"<<std::endl;
                cfg_rhs_current = NULL;
                
            }
         ;

rhs: expression
    {
        $$ = new type_attr();
        $$->vtp = $1->vtp;
        $$->vta = $1->vta;
        $$->vts = $1->vts;
        $$->inner = $1->inner;
        $$->isConst = $1->isConst;
        $$->indicator = $1->indicator;
        if($$->isConst)
        {
            $$->val = new constant();
            $$->val->type = getCTYPE($$);
            if($$->val->type==CINT)
                $$->val->ccint = getConst($1);
            else if($$->val->type==CFLOAT)
                $$->val->ccfloat = getConst($1);
            else if($$->val->type==CBOOL)
                $$->val->ccbool = getConst($1);
            else if($$->val->type==CCHAR)
                $$->val->ccchar = getConst($1);
        }
        $$->cc = std::string($1->cc);
    }
   | LBRACE expression_list RBRACE
   {
     /*
        indicator = 1 arithmetic expressions
        indicator = 2 set expressions
        indicator = 3 automata expressions
        indicator = 4 string initialization
        indicator = 5 regex initialization
        indicator = 6 dynamic set initialization
        indicator = 7 struct
     */
     $$ = new type_attr();
     $$->indicator = 6;
     //based on the type of the element set inner type
     $$->inner = genInnerType($2->inner);
     st.push(*current_queue);
     current_queue = NULL;
   }
   | REGEX_R REGEX_LIT
   {
    $$ = new type_attr();
    $$->indicator = 5;
    $$->vtsr = TYPE_REGEX;
   }
   ;

expression: LPAREN expression RPAREN {
                                      $$ = new expr_attr();
                                      $$->indicator = $2->indicator;
                                      $$->vtp = $2->vtp;
                                      $$->vta = $2->vta;
                                      $$->vts = $2->vts;
                                      $$->isConst = false;
                                      if($2->isConst)
                                      {
                                        $$->isConst = true;
                                        $$->val = $2->val;
                                      }
                                      $$->cc = std::string("(")+$2->cc+std::string(")");
                                     }
          | expression OPER_PLUS expression 
          {
                $$ = new expr_attr();
                if($1->indicator ==1 && $3->indicator==1)
                {
                    $$->indicator = 1;
                    if($1->vtp==TYPE_FLOAT_64 || $3->vtp==TYPE_FLOAT_64)
                    $$->vtp = TYPE_FLOAT_64;
                    else if($1->vtp==TYPE_FLOAT_32 || $3->vtp==TYPE_FLOAT_32)
                        $$->vtp = TYPE_FLOAT_32;
                    else
                        $$->vtp = TYPE_INT_64;
                    $$->isConst = false;
                    if($1->isConst && $3->isConst)
                    {
                        $$->isConst = true;
                        $$->val = new constant();
                        $$->val->type = getCTYPE($$);
                        if($$->val->type==CINT)
                            $$->val->ccint = getConst($1)+getConst($3);
                        else if($$->val->type==CFLOAT)
                            $$->val->ccfloat = getConst($1)+getConst($3);
                        else if($$->val->type==CBOOL)
                            $$->val->ccbool = getConst($1)+getConst($3);
                        else if($$->val->type==CCHAR)
                            $$->val->ccchar = getConst($1)+getConst($3);
                    }
                    $$->cc = $1->cc + std::string(" + ") + $3->cc;
                }
                else if($1->indicator ==2 && $3->indicator==2)
                {
                    $$->indicator = 2;
                    if($1->vts==TYPE_OSET || $3->vts==TYPE_OSET)
                    {
                        $$->vts = TYPE_OSET;
                    }
                    else if($1->vts==TYPE_USET || $3->vts==TYPE_USET)
                    {
                        $$->vts = TYPE_USET;
                    }
                    else
                    {
                        $$->vts = TYPE_OSET;
                    }
                    $$->cc = $1->cc + std::string(" + ") + $3->cc;
                }
                else if($1->indicator==3 && $3->indicator==3)
                {
                    if(($1->vta == TYPE_NFA && $3->vta == TYPE_DFA) || ($3->vta == TYPE_NFA && $1->vta == TYPE_DFA) || ($1->vta == TYPE_NFA && $3->vta == TYPE_NFA))
                    {
                        $$->vta = TYPE_DFA;
                        if($1->vta==TYPE_NFA && $3->vta ==TYPE_NFA)
                            $$->cc = std::string("(*fsm::union_nfa(")+$1->cc+std::string(", ")+$3->cc+std::string("))");
                        else
                        {
                            $$->vta = TYPE_NFA;
                            $$->cc = std::string("(*fsm::union_nfa_dfa(")+$1->cc+std::string(", ")+$3->cc+std::string("))");
                        }
                    }
                    else if($1->vta == TYPE_DFA && $3->vta == TYPE_DFA)
                    {
                        $$->vta = TYPE_DFA;
                        $$->cc = std::string("(*fsm::union_dfa(")+$1->cc+std::string(", ")+$3->cc+std::string("))");
                    }
                    else if($1->vta == TYPE_PDA && $3->vta == TYPE_PDA)
                    {
                        $$->vta = TYPE_PDA;
                        $$->cc = std::string("(*fsm::union_pda(")+$1->cc+std::string(", ")+$3->cc+std::string("))");
                    }
                    else if($1->vta == TYPE_CFG && $3->vta == TYPE_CFG)
                    {
                        $$->vta = TYPE_CFG;
                        $$->cc = std::string("(*fsm::union_cfg(")+$1->cc+std::string(", ")+$3->cc+std::string("))");
                    }
                    else 
                    {
                        std::string error = std::string("Invalid operation:")+std::string(getVTA($1->vta))+std::string(", ")+std::string(getVTA($3->vta))+std::string(" union  not defined");
                        yyerror(error.c_str());
                    }
                }
                else
                    yyerror("Invalid operation: Addition can only be done between 'primitive' types");
          }
          | expression OPER_MINUS expression
          {
                // Set difference
                $$ = new expr_attr();
                if($1->indicator==1 && $3->indicator==1)
                {
                    $$->indicator = 1;
                    $$->isConst = false;
                    if($1->vtp==TYPE_FLOAT_64 || $3->vtp==TYPE_FLOAT_64)
                        $$->vtp = TYPE_FLOAT_64;
                    else if($1->vtp==TYPE_FLOAT_32 || $3->vtp==TYPE_FLOAT_32)
                        $$->vtp = TYPE_FLOAT_32;
                    else
                        $$->vtp = TYPE_INT_64;
                    if($1->isConst && $3->isConst)
                    {
                        $$->isConst = true;
                        $$->val = new constant();
                        $$->val->type = getCTYPE($$);
                        if($$->val->type==CINT)
                            $$->val->ccint = getConst($1)-getConst($3);
                        else if($$->val->type==CFLOAT)
                            $$->val->ccfloat = getConst($1)-getConst($3);
                        else if($$->val->type==CBOOL)
                            $$->val->ccbool = getConst($1)-getConst($3);
                        else if($$->val->type==CCHAR)
                            $$->val->ccchar = getConst($1)-getConst($3);
                    }
                $$->cc = $1->cc + std::string(" - ") + $3->cc;
                }
                else if($1->indicator==2 && $3->indicator==2)
                {
                    $$->indicator = 2;
                    if($1->vts==TYPE_OSET || $3->vts==TYPE_OSET)
                    {
                        $$->vts = TYPE_OSET;
                    }
                    else if($1->vts==TYPE_USET || $3->vts==TYPE_USET)
                    {
                        $$->vts = TYPE_USET;
                    }
                    else
                    {
                        $$->vts = TYPE_OSET;
                    }
                    $$->cc = $1->cc + std::string(" - ") + $3->cc;
                }
                else
                    yyerror("Invalid operation: Subtrction can only be done between 'primitive' and 'set' types");
          }
          | expression OPER_MUL expression
          {
                $$ = new expr_attr();
                //intersection
                $$->isConst = false;
                if($1->indicator ==1 && $3->indicator ==1)
                {
                    $$->indicator = 1;
                    if($1->vtp==TYPE_FLOAT_64 || $3->vtp==TYPE_FLOAT_64)
                        $$->vtp = TYPE_FLOAT_64;
                    else if($1->vtp==TYPE_FLOAT_32 || $3->vtp==TYPE_FLOAT_32)
                        $$->vtp = TYPE_FLOAT_32;
                    else
                        $$->vtp = TYPE_INT_64;
                    if($1->isConst && $3->isConst)
                    {
                        $$->isConst = true;
                        $$->val = new constant();
                        $$->val->type = getCTYPE($$);
                        if($$->val->type==CINT)
                            $$->val->ccint = getConst($1)*getConst($3);
                        else if($$->val->type==CFLOAT)
                            $$->val->ccfloat = getConst($1)*getConst($3);
                        else if($$->val->type==CBOOL)
                            $$->val->ccbool = getConst($1)*getConst($3);
                        else if($$->val->type==CCHAR)
                            $$->val->ccchar = getConst($1)*getConst($3);
                    }
                }
                else if($1->indicator ==2 && $3->indicator ==2)
                {
                    $$->indicator = 2;
                    if($1->vts==TYPE_OSET || $3->vts==TYPE_OSET)
                    {
                        $$->vts = TYPE_OSET;
                    }
                    else if($1->vts==TYPE_USET || $3->vts==TYPE_USET)
                    {
                        $$->vts = TYPE_USET;
                    }
                    else
                    {
                        $$->vts = TYPE_OSET;
                    }
                }
                else
                    yyerror("Invalid operation: Multiplication can only be done between 'primitive' and 'set' types");
                $$->cc = $1->cc + std::string(" * ") + $3->cc;
          }
          | expression OPER_DIV expression
          {
            $$ = new expr_attr();
            if($1->indicator !=1 || $3->indicator !=1)
                yyerror("Invalid operation: Division can only be done between 'primitive' types");
            //check for division by zero (to be done)
            if($3->val && (($3->val->type == CINT && $3->val->ccint == 0) || ($3->val->type == CFLOAT && $3->val->ccfloat == 0.0) || ($3->val->type == CBOOL && $3->val->ccbool == false)||( $3->val->type == CCHAR && $3->val->ccchar == '\0')))
                yyerror("Invalid operation: Division by zero");
            $$->indicator = 1;
            $$->isConst = false;
            if($1->vtp==TYPE_FLOAT_64 || $3->vtp==TYPE_FLOAT_64)
                $$->vtp = TYPE_FLOAT_64;
            else if($1->vtp==TYPE_FLOAT_32 || $3->vtp==TYPE_FLOAT_32)
                $$->vtp = TYPE_FLOAT_32;
            else
                $$->vtp = TYPE_INT_64;
            if($1->isConst && $3->isConst)
            {
                $$->isConst = true;
                $$->val = new constant();
                $$->val->type = getCTYPE($$);
                if($$->val->type==CINT)
                    $$->val->ccint = getConst($1)/getConst($3);
                else if($$->val->type==CFLOAT)
                    $$->val->ccfloat = getConst($1)/getConst($3);
                else if($$->val->type==CBOOL)
                    $$->val->ccbool = getConst($1)/getConst($3);
                else if($$->val->type==CCHAR)
                    $$->val->ccchar = getConst($1)/getConst($3);
            }
            $$->cc = $1->cc + std::string(" / ") + $3->cc;
          }
          | expression OPER_MOD expression
          {
            $$ = new expr_attr();
            if($1->indicator !=1 || $3->indicator !=1)
                yyerror("Invalid operation: Modulo can only be done between 'integer' types");
            if($1->vtp==TYPE_FLOAT_64 || $3->vtp==TYPE_FLOAT_64 || $1->vtp==TYPE_FLOAT_32 || $3->vtp==TYPE_FLOAT_32)
                yyerror("Invalid operation: Modulo can only be done between 'integer' types");
            $$->indicator = 1;
            $$->isConst = false;
            $$->vtp = TYPE_INT_64;
            if($1->isConst && $3->isConst)
            {
                $$->isConst = true;
                $$->val = new constant();
                $$->val->type = getCTYPE($$);
                if($$->val->type==CINT)
                    $$->val->ccint = $1->val->ccint % $3->val->ccint;
            }
            $$->cc = $1->cc + std::string(" % ") + $3->cc;
          }
          | expression OPER_COMP expression
          {
            $$ = new expr_attr();
            if($1->indicator !=1 || $3->indicator !=1)
                yyerror("Invalid comparison: Comparison can only be done between primitive types");
            $$->indicator = 1;
            $$->vtp = TYPE_BOOL;
            std::string comp($2); //"<=",">=","==","!="
            $$->isConst = false;
            if(comp=="<=")
            {
                if($1->isConst && $3->isConst)
                {
                    $$->isConst = true;
                    $$->val = new constant();
                    $$->val->type = CBOOL;
                    $$->val->ccbool = getConst($1)<=getConst($3);
                }
            }
            if(comp==">=")
            {
                if($1->isConst && $3->isConst)
                {
                    $$->isConst = true;
                    $$->val = new constant();
                    $$->val->type = CBOOL;
                    $$->val->ccbool = getConst($1)>=getConst($3);
                }
            }
            if(comp=="==")
            {
                if($1->isConst && $3->isConst)
                {
                    $$->isConst = true;
                    $$->val = new constant();
                    $$->val->type = CBOOL;
                    $$->val->ccbool = getConst($1)==getConst($3);
                }
            }
            if(comp=="!=")
            {
                if($1->isConst && $3->isConst)
                {
                    $$->isConst = true;
                    $$->val = new constant();
                    $$->val->type = CBOOL;
                    $$->val->ccbool = getConst($1)!=getConst($3);
                }
            }
            $$->cc = $1->cc + comp + $3->cc;
          }
          | expression OPER_POWER
          {
            $$ = new expr_attr();
            if($1->indicator !=2)
                yyerror("Invalid operation: Power set can only be computed for a set");
            $$->indicator = 2;
            $$->vts = TYPE_OSET;
            $$->isConst = false;
            $$->cc = $1->cc+std::string(".power_set()");
          }
          | expression AT_THE_RATE expression 
          {
            $$ = new expr_attr();
            // What about regex? (to be done) cfg + pdas (to be done)
            if($1->indicator !=2 || $3->indicator != 2)
                yyerror("Invalid operation: Automata can only be concatenated with Automata");
            $$->indicator = 2;
            if(($1->vta == TYPE_NFA && $3->vta == TYPE_DFA) || ($3->vta == TYPE_NFA && $1->vta == TYPE_DFA) || ($1->vta == TYPE_NFA && $3->vta == TYPE_NFA))
                $$->vta = TYPE_NFA;
            else if($1->vta == TYPE_DFA && $3->vta == TYPE_DFA)
                $$->vta = TYPE_DFA;
            else if($1->vta == TYPE_PDA && $3->vta == TYPE_PDA)
                $$->vta = TYPE_PDA;
            else if($1->vta == TYPE_CFG && $3->vta == TYPE_CFG)
                $$->vta = TYPE_CFG;
            else
                yyerror("Invalid operation: Automata can only be concatenated with Automata");
            $$->isConst = false;
            // codegen required
          }
          | expression OPER_OR expression
          {
            $$ = new expr_attr();
            if($1->indicator ==3 || $3->indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if($1->indicator == 2 || $3->indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            $$->indicator = 1;
            $$->vtp = TYPE_BOOL;
            $$->isConst = false;
            if($1->isConst && $3->isConst)
            {
                $$->isConst = true;
                $$->val = new constant();
                $$->val->type = CBOOL;
                $$->val->ccbool = getConst($1) || getConst($3);
            }
            else if($1->isConst)
            {
                if(($1->val->type==CINT && $1->val->ccint!=0) || ($1->val->type==CFLOAT && $1->val->ccfloat!=0.0) || ($1->val->type==CBOOL && $1->val->ccbool!=false) || ($1->val->type==CCHAR && $1->val->ccchar!='\0'))
                {
                    $$->isConst = true;
                    $$->val = new constant();
                    $$->val->type = CBOOL;
                    $$->val->ccbool = true;
                }
            }
            else if($3->isConst)
            {
                if(($3->val->type==CINT && $3->val->ccint!=0) || ($3->val->type==CFLOAT && $3->val->ccfloat!=0.0) || ($3->val->type==CBOOL && $3->val->ccbool!=false) || ($3->val->type==CCHAR && $3->val->ccchar!='\0'))
                {
                    $$->isConst = true;
                    $$->val = new constant();
                    $$->val->type = CBOOL;
                    $$->val->ccbool = true;
                }
            }
            $$->cc = $1->cc + std::string(" || ") + $3->cc;
          }
          | expression OPER_AND expression
          {
            $$ = new expr_attr();
            if($1->indicator ==3 || $3->indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if($1->indicator == 2 || $3->indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            $$->indicator = 1;
            $$->vtp = TYPE_BOOL;
            $$->isConst = false;
            if($1->isConst && $3->isConst)
            {
                $$->val->type = CBOOL;
                $$->val->ccbool = getConst($1) && getConst($3);
            }
            else if($1->isConst)
            {
                if(($1->val->type==CINT && $1->val->ccint==0) || ($1->val->type==CFLOAT && $1->val->ccfloat==0.0) || ($1->val->type==CBOOL && $1->val->ccbool==false) || ($1->val->type==CCHAR && $1->val->ccchar=='\0'))
                {
                    $$->isConst = true;
                    $$->val = new constant();
                    $$->val->type = CBOOL;
                    $$->val->ccbool = false;
                }
            }
            else if($3->isConst)
            {
                if(($3->val->type==CINT && $3->val->ccint==0) || ($3->val->type==CFLOAT && $3->val->ccfloat==0.0) || ($3->val->type==CBOOL && $3->val->ccbool==false) || ($3->val->type==CCHAR && $3->val->ccchar=='\0'))
                {
                    $$->isConst = true;
                    $$->val = new constant();
                    $$->val->type = CBOOL;
                    $$->val->ccbool = false;
                }
            }
            $$->cc = $1->cc + std::string(" && ") + $3->cc;
          }
          | expression COMP_GT expression
          {
            $$ = new expr_attr();
            if($1->indicator ==3 || $3->indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if($1->indicator == 2 || $3->indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            $$->indicator = 1;
            $$->vtp = TYPE_BOOL;
            $$->isConst = false;
            //constant check
            if($1->isConst && $3->isConst)
            {
                $$->isConst = true;
                $$->val = new constant();
                $$->val->type = CBOOL;
                $$->val->ccbool = getConst($1)>getConst($3);
            }
            $$->cc = $1->cc + std::string(" > ") + $3->cc;
          }
          | expression COMP_LT expression 
          {
            $$ = new expr_attr();
            if($1->indicator ==3 || $3->indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if($1->indicator == 2 || $3->indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            $$->indicator = 1;
            $$->vtp = TYPE_BOOL;
            $$->isConst = false;
            //constant check
            if($1->isConst && $3->isConst)
            {
                $$->isConst = true;
                $$->val = new constant();
                $$->val->type = CBOOL;
                $$->val->ccbool = getConst($1)<getConst($3);
            }
            $$->cc = $1->cc + std::string(" < ") + $3->cc;
          }
          | OPER_NOT expression { 
            $$ = new expr_attr();
            if($2->indicator ==2)
                yyerror("Invalid operator: Negation of Set not defined");
            if($2->indicator ==3 && ($2->vta == TYPE_CFG || $2->vta == TYPE_PDA))
                yyerror("Invalid operator: CFG/NDPDA not closed under complement");
            $$->indicator = $2->indicator;
            $$->isConst = false;
            if($2->indicator == 1)
            {
                if($2->isConst)
                {
                    $$->isConst = true;
                    $$->val = new constant();
                    $$->val->type = CBOOL;
                    if($2->val->type == CINT)
                        $$->val->ccbool = !($2->val->ccint);
                    else if($2->val->type == CFLOAT)
                        $$->val->ccbool = !($2->val->ccfloat);
                    else if($2->val->type == CBOOL)
                        $$->val->ccbool = !($2->val->ccbool);
                    else if($2->val->type == CCHAR)
                        $$->val->ccbool = !($2->val->ccchar);
                }
                else
                    $$->isConst = false;
                $$->vtp = TYPE_BOOL;
            }
            else if($2->indicator == 3)
                {$$->vta = $2->vta; $$->isConst = false;}
            $$->cc = std::string("!")+($2->cc);

          }
          | expression OPER_HASH { 
            $$ = new expr_attr();
            if($1->indicator !=3)
                yyerror("Invalid operator: Kleene Star can only be applied to Automata");
            $$->indicator = 3;
            $$->vta = $1->vta;
            $$->isConst = false;
            //codegen required
          }
          | OPER_MINUS expression { 
                                    $$ = new expr_attr();
                                    $$->indicator = $2->indicator; 
                                    $$->vtp = $2->vtp; 
                                    $$->vta = $2->vta; 
                                    $$->vts = $2->vts;
                                    $$->isConst = $2->isConst;
                                    $$->val = $2->val;
                                    if($$->val)
                                    {
                                        switch($$->val->type)
                                        {
                                            case CINT:
                                                    $$->val->ccint = -($$->val->ccint);
                                                    break;
                                            case CFLOAT:
                                                    $$->val->ccfloat = -($$->val->ccfloat);
                                                    break;
                                            case CBOOL:
                                                    $$->val->ccbool = !($$->val->ccbool);
                                                    break;
                                            case CCHAR:
                                                    $$->val->ccchar = -($$->val->ccchar);
                                                    break;
                                        }
                                    }
                                    $$->cc = std::string("-")+($2->cc);
                                }
          | OPER_PLUS expression { 
                                  $$ = new expr_attr();
                                  $$->indicator = $2->indicator;
                                  $$->vtp = $2->vtp; 
                                  $$->vta = $2->vta; 
                                  $$->vts = $2->vts;
                                  $$->isConst = $2->isConst;
                                  $$->val = $2->val;
                                  $$->cc = std::string("+")+($2->cc);
                                 }
          | INT_CONST { 
                        $$ = new expr_attr();
                        $$->indicator = 1; 
                        $$->vtp = TYPE_INT_64; 
                        $$->val = new constant();
                        $$->val->ccint = $1;
                        $$->val->type = CINT;
                        $$->isConst = true;
                        $$->cc = std::to_string($1);
                      }
          | FLOAT_CONST { 
                          $$ = new expr_attr();
                          $$->indicator = 1; 
                          $$->vtp = TYPE_FLOAT_64; 
                          $$->val = new constant();
                          $$->val->ccfloat = $1;
                          $$->val->type = CFLOAT;
                          $$->isConst = true;
                          $$->cc = std::to_string($1);
                        }
          | BOOL_CONST { 
                         $$ = new expr_attr();
                         $$->indicator = 1; 
                         $$->vtp = TYPE_BOOL; 
                         $$->val = new constant();
                         $$->val->ccbool = $1;
                         $$->val->type = CBOOL;
                         $$->isConst = true;
                        $$->cc = std::to_string($1);
                       }
          | CHAR_CONST { 
                        $$ = new expr_attr();
                        $$->indicator = 1; 
                        $$->vtp = TYPE_CHAR;
                        $$->val = new constant();
                        $$->val->ccchar = $1;
                        $$->val->type = CBOOL;
                        $$->isConst = true;
                        $$->cc = std::string(1,$1);
                       }
          | pseudo_ID { 
                        $$ = new expr_attr();
                        $$->indicator = $1->indicator; 
                        $$->vtp = $1->vtp; 
                        $$->vta = $1->vta; 
                        $$->vts = $1->vts;
                        std::pair<bool,std::string> ret = checkPseudoID(NULL,$1->name,"");
                        if(!ret.first)
                            yyerror(ret.second.c_str());
                        else
                        {
                            $$->isConst = false;
                            std::string type = ret.second.substr(ret.second.find(' ')+1);
                            if(type.find(" ")!=std::string::npos && type.find(" ")!=type.length()-1)
                                type = type.substr(0,type.find(' ') );
                            if(type=="int_8")
                            {
                                $$->indicator = 1;
                                $$->vtp = TYPE_INT_8;
                            }
                            else if(type=="int_16")
                            {
                                $$->indicator = 1;
                                $$->vtp = TYPE_INT_16;
                            }
                            else if(type=="int_32")
                            {
                                $$->indicator = 1;
                                $$->vtp = TYPE_INT_32;
                            }
                            else if(type=="int_64")
                            {
                                $$->indicator = 1;
                                $$->vtp = TYPE_INT_64;
                            }
                            else if(type=="float_32")
                            {
                                $$->indicator = 1;
                                $$->vtp = TYPE_FLOAT_32;
                            }
                            else if(type=="float_64")
                            {
                                $$->indicator = 1;
                                $$->vtp = TYPE_FLOAT_64;
                            }
                            else if(type=="bool")
                            {
                                $$->indicator = 1;
                                $$->vtp = TYPE_BOOL;
                            }
                            else if(type=="char")
                            {
                                $$->indicator = 1;
                                $$->vtp = TYPE_CHAR;
                            }
                            else if(type=="string")
                            {
                                $$->indicator = 4;
                                $$->vtsr = TYPE_STR;
                            }
                            else if(type=="regex")
                            {
                                $$->indicator = 5;
                                $$->vtsr = TYPE_REGEX;
                            }
                            else if(type=="o_set" || type=="u_set")
                            {
                                $$->indicator = 2;
                                $$->vts = getSetType(type.c_str());
                                size_t first_space = ret.second.find(" ");
                                size_t second = ret.second.find(" ",first_space+1);
                                $$->inner = genInnerType(ret.second.substr(second+1));
                            }
                            else if(type=="nfa")
                            {
                                $$->indicator = 3;
                                $$->vta = TYPE_NFA;
                            }
                            else if(type=="dfa")
                            {
                                $$->indicator = 3;
                                $$->vta = TYPE_DFA;
                            }
                            else if(type=="pda")
                            {
                                $$->indicator = 3;
                                $$->vta = TYPE_PDA;
                            }
                            else if(type=="cfg")
                            {
                                $$->indicator = 3;
                                $$->vta = TYPE_CFG;
                            }
                            else
                            {
                                $$->indicator = 7;
                                $$->vtsr = TYPE_STRU;
                                $$->ifStruct = type;
                            }
                        }
                        $$->cc = $1->cc;
                      }
          | call {
                    // To be handled (to be done)
                    $$ = new expr_attr();
                    $$->indicator = $1->indicator;
                    if($1->indicator==1)
                        $$->vtp = $1->vtp;
                    else if($1->indicator==2)
                    {
                        $$->vts = $1->vts;
                        $$->inner = $1->inner;
                    }
                    else if($1->indicator==3)
                        $$->vta = $1->vta;
                    else if($1->indicator==4)
                        $$->vtsr = $1->vtsr;
                    else if($1->indicator==5)
                        $$->vtsr = $1->vtsr;
                    else if($1->indicator==7)
                    {
                        $$->vtsr = $1->vtsr;
                        $$->ifStruct = $1->ifStruct;
                    }
                    $$->cc = $1->cc;
                 }
          ;

call : ID LPAREN argument_list RPAREN
     {
        //check if function exists
        if(!fst->lookup(std::string($1)))
        {
            std::string error = "Function "+std::string($1)+std::string(" not defined");
            yyerror(error.c_str());
        }
        if(fst->lookup(std::string($1))->isTemplate)
            yyerror("Function is a template function");
        //check if argument type matches (to be done)
        //create type of call from return type of function
        FunctionSymbolTableEntry *entry = fst->lookup(std::string($1));
        // return_type is complete with inner types as well(in case of sets)
        $$ = new type_attr();
        //get first word
        std::string type = entry->return_type;
        std::string outer_type = type.substr(0,type.find(' '));
        if(isSet(outer_type)) //set
        {
            $$->indicator = 2;
            $$->vts = getSetType(outer_type.c_str());
            //recursively generate all inner types
            type = type.substr(type.find(' ')+1);
            $$->inner = genInnerType(type);
        }
        else if(isPrimitive(outer_type))
        {
            $$->indicator = 1;
            $$->vtp = getPrimitiveType(outer_type.c_str());
        }
        else if(isAutomata(outer_type))
        {
            $$->indicator = 3;
            $$->vta = getAutomataType(outer_type.c_str());
        }
        else if(isSR(outer_type))
        {
            if(outer_type=="string")
                $$->indicator = 4;
            else
                $$->indicator = 5;
            $$->vtsr = getSRType(outer_type.c_str());
        }
        else
        {
            $$->indicator = 7;
            $$->vtsr = TYPE_STRU;
            $$->ifStruct = outer_type;
        }
        // we also need to check argument types
        std::vector<std::string> arg_pos_list_rev = entry->id_list;
        VarSymbolTable *params_table = entry->params;
        auto it_list = arg_pos_list_rev.begin();
        auto it_arg_list = $3->lst.begin();
        //compare types
        int i=1;
        while(it_list!=arg_pos_list_rev.end() && it_arg_list!=$3->lst.end())
        {
            std::string type_expected = params_table->lookup(*it_list)->type;
            std::string type_actual = *it_arg_list;
            type_actual = trim(type_actual);
            if(type_expected=="o_set"||type_expected=="u_set"||type_expected=="o_set "|| type_expected=="u_set ")
            {
                //concat inner types
                type_expected=trim(trim(type_expected)+std::string(" ")+params_table->lookup(*it_list)->inner->print());
            }
            if(!isCoherent(type_expected,type_actual))
            {
                std::string error = std::string("Argument type mismatch at pos " + std::to_string(i)+ ": Expected ")+type_expected+std::string(" but found ")+type_actual;
                yyerror(error.c_str());
            }
            ++it_list;
            ++it_arg_list;
            ++i;
        }
        if(it_list!=arg_pos_list_rev.end())
            yyerror("Too few arguments");
        else if(it_arg_list!=$3->lst.end())
            yyerror("Too many arguments");
        $$->cc = std::string($1) + std::string("(") + $3->cc + std::string(")");
     }
     | ID TEMP_LEFT type_list_call TEMP_RIGHT LPAREN argument_list RPAREN
     {
        //check if function exists and is a template function
        FunctionSymbolTableEntry *entry = fst->lookup(std::string($1));
        if(!entry)
        {
            std::string error = "Function "+std::string($1)+std::string(" not defined");
            yyerror(error.c_str());
        }
        if(!entry->isTemplate)
            yyerror("Function is not a template function");
        //check type_list
        if(entry->template_params.size()!=$3->lst.size())
            yyerror("Invalid number of template arguments");
        // handling return type
        $$ = new type_attr();
        std::string type = entry->return_type;
        std::string outer_type = type.substr(0,type.find(' '));
        if(isSet(outer_type)) //set
        {
            $$->indicator = 2;
            $$->vts = getSetType(outer_type.c_str());
            //recursively generate all inner types
            type = type.substr(type.find(' ')+1);
            $$->inner = genInnerType(type);
        }
        else if(isPrimitive(outer_type))
        {
            $$->indicator = 1;
            $$->vtp = getPrimitiveType(outer_type.c_str());
        }
        else if(isAutomata(outer_type))
        {
            $$->indicator = 3;
            $$->vta = getAutomataType(outer_type.c_str());
        }
        else if(isSR(outer_type))
        {
            if(outer_type=="string")
                $$->indicator = 4;
            else
                $$->indicator = 5;
            $$->vtsr = getSRType(outer_type.c_str());
        }
        else
        {
            $$->indicator = 7;
            $$->vtsr = TYPE_STRU;
            $$->ifStruct = outer_type;
        }
        // we also need to check argument types
        std::vector<std::string> arg_pos_list_rev = entry->id_list;
        VarSymbolTable *params_table = entry->params;
        auto it_list = arg_pos_list_rev.begin();
        auto it_arg_list = $6->lst.begin();
        //compare types
        int i=1;
        while(it_list!=arg_pos_list_rev.end() && it_arg_list!=$6->lst.end())
        {
            std::string type_expected = params_table->lookup(*it_list)->type;
            std::string type_actual = *it_arg_list;
            type_actual = trim(type_actual);
            if(type_expected=="template")
                continue;
            if(type_expected=="o_set"||type_expected=="u_set"||type_expected=="o_set "|| type_expected=="u_set ")
            {
                //concat inner types
                type_expected=trim(trim(type_expected)+std::string(" ")+params_table->lookup(*it_list)->inner->print());
            }
            if(!isCoherent(type_expected,type_actual))
            {
                std::string error = std::string("Argument type mismatch at pos " + std::to_string(i)+ ": Expected ")+type_expected+std::string(" but found ")+type_actual;
                yyerror(error.c_str());
            }
            ++it_list;
            ++it_arg_list;
            ++i;
        }
        if(it_list!=arg_pos_list_rev.end())
            yyerror("Too few arguments");
        else if(it_arg_list!=$6->lst.end())
            yyerror("Too many arguments");

     }
     ;

type_list_call: type_call
              {
                $$ = new state_list_attr();
                $$->lst.push_back(std::string("temp"));
              }
              | type_list_call COMMA type_call
              {
                $$ = new state_list_attr();
                $$->lst = $1->lst;
                $$->lst.push_back(std::string("temp"));
              }
              ;

type_call: dtype
         | ID
         {
            //check if struct exists
            if(!sst->lookup(std::string($1)))
            {
                std::string error = "Struct "+std::string($1)+std::string(" not defined");
                yyerror(error.c_str());
            }
         }
         ;

argument_list: 
             {
                //argument list is empty
                $$ = new arg_list_attr();
                $$->cc = std::string("");
             }
             | expression arg_list_next
             {
                $$ = new arg_list_attr();
                $$->lst = $2->lst;
                std::string type;
                if($1->indicator==1)
                    type = getVTP($1->vtp);
                else if($1->indicator==2)
                {
                    type = getVTS($1->vts);
                    type= type+std::string(" ")+$1->inner->print();
                }
                else if($1->indicator==3)
                    type = getVTA($1->vta);
                else if($1->indicator==4)
                    type=std::string("string");
                else if($1->indicator==5)
                    type=std::string("regex");
                else if($1->indicator ==7)
                    type=std::string($1->ifStruct);
                $$->lst.push_back(type);
                $$->cc = $1->cc + $2->cc;
             }
             ;

arg_list_next:
             {
                $$ = new arg_list_attr();
                $$->cc = std::string("");
             }
             | COMMA expression arg_list_next
             {
                $$ = new arg_list_attr();
                $$->lst = $3->lst;
                std::string type;
                if($2->indicator==1)
                    type = getVTP($2->vtp);
                else if($2->indicator==2)
                {
                    type = getVTS($2->vts);
                    type= type+std::string(" ")+$2->inner->print();
                }
                else if($2->indicator==3)
                    type = getVTA($2->vta);
                else if($2->indicator==4)
                    type=std::string("string");
                else if($2->indicator==5)
                    type=std::string("regex");
                else if($2->indicator ==7)
                    type=std::string($2->ifStruct);
                $$->lst.push_back(type);
                $$->cc = std::string(", ")+$2->cc + $3->cc;
             }

rhs_automata: LBRACE alphabet_list RBRACE
            {
                $$ = new rhs_automata_attr();
                $$->type=std::string("alphabets");
                $$->automata_type = std::string("");
            }
            | LBRACE rules_list RBRACE
            {
                $$ = new rhs_automata_attr();
                $$->type=std::string("transitions");
                $$->automata_type = $2->type;
            }
            ;

alphabet_list: alphabet
           | alphabet_list COMMA alphabet
           ;

alphabet : ID COLON STRING_CONST
         {
            if(current_alphabets==NULL)
                current_alphabets = new std::vector<std::pair<std::string,std::string>>();
            current_alphabets->push_back(std::make_pair(std::string("\"")+std::string($1)+std::string("\""),std::string($3)));
         }
         ;

rules_list : rule
           {
                $$ = new rules_attr();
                $$->type = $1->type;
           }
           | rules_list COMMA rule
           {
                $$ = new rules_attr();
                if($1->type==$3->type)
                    $$->type = $1->type;
                else if(($1->type=="nfa" && $3->type=="dfa") || ($1->type=="dfa" && $3->type=="nfa"))
                    $$->type = std::string("nfa");
                else
                    yyerror("Invalid rule: All rules must be of same type");
           }
           ;

rule :LPAREN ID lhs_arrow ARROW rhs_arrow RPAREN
     {
        $$ = new rules_attr();
        if($3->type==$5->type)
            $$->type = $3->type;
        else if(($3->type=="nfa" && $5->type=="dfa") || ($3->type=="dfa" && $5->type=="nfa"))
            $$->type = std::string("nfa");
        else
            yyerror("Invalid rule: All rules must be of same type");
        if($3->type=="dfa" && ($5->type!="nfa" && $5->type!="dfa"))
            yyerror("Invalid rule");
        if($3->type=="nfa" && ($5->type!="nfa" && $5->type!="dfa"))
            yyerror("Invalid rule");
        if($3->type=="pda" && ($5->type!="pda"))
            yyerror("Invalid rule");
        if(current_automata==0)
        {
            if($3->type=="dfa" && $5->type=="dfa")
                current_automata = 1;
            else if($3->type=="nfa" || $5->type=="nfa" )
                current_automata = 2;
            else if($3->type=="pda" && $5->type=="pda")
                current_automata = 3;
            // now insert the rules
            if(current_automata==1 || current_automata==2)
            {
                transition = new std::vector<std::vector<std::string>>();
                for(auto &it: *nfa_dfa_lhs)
                {
                    for(auto &it2: *nfa_dfa_rhs)
                    {
                        std::string alphabet = it;
                        std::string fin = it2;
                        std::string init = std::string($2);
                        std::vector<std::string> *temp;
                        temp = new std::vector<std::string>();
                        temp->push_back(init);
                        temp->push_back(alphabet);
                        temp->push_back(fin);
                        transition->push_back(*temp);
                    }
                }
                nfa_dfa_lhs = NULL;
                nfa_dfa_rhs = NULL;
            }
            if(current_automata==3)
            {
                transition = new std::vector<std::vector<std::string>>();
                for(auto &it: *pda_lhs)
                {
                    for(auto &it2: *pda_rhs)
                    {
                        std::string state_alpha = it.first;
                        std::string stack = it.second;
                        std::string state_alpha2 = it2.first;
                        std::string stack2 = it2.second;
                        std::string init = std::string($2);
                        std::vector<std::string> *temp;
                        temp = new std::vector<std::string>();
                        temp->push_back(init);
                        temp->push_back(state_alpha);
                        temp->push_back(stack);
                        temp->push_back(state_alpha2);
                        temp->push_back(stack2);
                        transition->push_back(*temp);
                    }
                }
                pda_lhs = NULL;
                pda_rhs = NULL;
            }
        }
        else 
        {
            if((current_automata==1 || current_automata==2) && (($3->type=="dfa" || $3->type=="nfa") && ($5->type=="dfa" || $5->type=="nfa")))
            {
                if($3->type=="nfa" || $5->type=="nfa")
                    current_automata = 2;
                for(auto &it: *nfa_dfa_lhs)
                {
                    for(auto &it2: *nfa_dfa_rhs)
                    {
                        std::string alphabet = it;
                        std::string fin = it2;
                        std::string init = std::string($2);
                        std::vector<std::string> *temp;
                        temp = new std::vector<std::string>();
                        temp->push_back(init);
                        temp->push_back(alphabet);
                        temp->push_back(fin);
                        transition->push_back(*temp);
                    }
                }
                nfa_dfa_lhs = NULL;
                nfa_dfa_rhs = NULL;
            }
            else if(current_automata==3 && $3->type=="pda" && $5->type=="pda")
            {
                for(auto &it: *pda_lhs)
                {
                    for(auto &it2: *pda_rhs)
                    {
                        std::string state_alpha = it.first;
                        std::string stack = it.second;
                        std::string state_alpha2 = it2.first;
                        std::string stack2 = it2.second;
                        std::string init = std::string($2);
                        std::vector<std::string> *temp;
                        temp = new std::vector<std::string>();
                        temp->push_back(init);
                        temp->push_back(state_alpha);
                        temp->push_back(stack);
                        temp->push_back(state_alpha2);
                        temp->push_back(stack2);
                        transition->push_back(*temp);
                    }
                }
                pda_lhs = NULL;
                pda_rhs = NULL;
            }
            else
                yyerror("Invalid set of rules");
        }
     }
     ;

lhs_arrow : COMMA ID
          {
            $$ = new lhs_arrow_attr();
            $$->type = std::string("dfa");
            nfa_dfa_lhs = new std::vector<std::string>();
            nfa_dfa_lhs->push_back(std::string($2));
          }
          | COMMA element_PDA
          {
            $$ = new lhs_arrow_attr();
            $$->type = std::string("pda");
            pda_lhs = new std::vector<std::pair<std::string,std::string>>();
            std::pair<std::string,std::string> str;
            str = std::make_pair($2->state_alpha,$2->stack);
            pda_lhs->push_back(str);
          }
          | COMMA EPSILON
          {
            $$ = new lhs_arrow_attr();
            $$->type = std::string("nfa");
            nfa_dfa_lhs = new std::vector<std::string>();
            nfa_dfa_lhs->push_back("\\\\e");
          }
          | COMMA LBRACE elements_PDA RBRACE
          {
            $$ = new lhs_arrow_attr();
            $$->type = std::string("pda");
            pda_lhs = new std::vector<std::pair<std::string,std::string>>();
            for(auto &it: *($3->lst))
            {
                std::pair<std::string,std::string> str;
                str = std::make_pair(it->state_alpha,it->stack);
                pda_lhs->push_back(str);
            }
          }
          | COMMA LBRACE elements_others RBRACE
          {
            $$ = new lhs_arrow_attr();
            $$->type = $3->type;
            nfa_dfa_lhs = new std::vector<std::string>();
            for(auto &it: $3->lst)
            {
                nfa_dfa_lhs->push_back(it);
            }
          }
          ;

elements_PDA : element_PDA
             {
                $$ = new elements_PDA_attr();
                $$->lst = new std::vector<element_PDA_attr*>();
                $$->lst->push_back($1);
             }
             | elements_PDA COMMA element_PDA
             {
                $$ = $1;
                $$->lst->push_back($3);
             }
             ;

element_PDA : LPAREN ID COMMA ID RPAREN
            {
                $$ = new element_PDA_attr();
                $$->state_alpha = std::string($2);
                $$->stack = std::string($4);
            }
            | LPAREN ID COMMA EPSILON RPAREN
            {
                $$ = new element_PDA_attr();
                $$->state_alpha = std::string($2);
                $$->stack = std::string("\\\\e");
            }
            ;

elements_others : ID
                {
                    $$ = new lhs_arrow_attr();
                    $$->type = std::string("dfa");
                    $$->lst = *(new std::vector<std::string>());
                    $$->lst.push_back(std::string($1));
                }
                | EPSILON
                {
                    $$ = new lhs_arrow_attr();
                    $$->type = std::string("nfa");
                    $$->lst = *(new std::vector<std::string>());
                    $$->lst.push_back(std::string("\\\\e"));
                }
                | elements_others COMMA ID
                {
                    $$ = new lhs_arrow_attr();
                    if($1->type=="dfa")
                        $$->type = std::string("dfa");
                    else
                        $$->type = std::string("nfa");
                    $$->lst = $1->lst;
                    $$->lst.push_back(std::string($3));

                }
                | elements_others COMMA EPSILON
                {
                    $$ = new lhs_arrow_attr();
                    $$->type = std::string("nfa");
                    $$->lst = $1->lst;
                    $$->lst.push_back(std::string("\\\\e"));
                }
                ;

rhs_arrow : ID
          {
            $$ = new lhs_arrow_attr();
            $$->type = std::string("dfa");
            nfa_dfa_rhs = new std::vector<std::string>();
            nfa_dfa_rhs->push_back(std::string($1));
          }
          | LBRACE elements_others RBRACE
          {
            $$ = new lhs_arrow_attr();
            $$->type = std::string("nfa");
            nfa_dfa_rhs = new std::vector<std::string>();
            for(auto &it: $2->lst)
            {
                nfa_dfa_rhs->push_back(it);
            }
          }
          | element_PDA
          {
            $$ = new lhs_arrow_attr();
            $$->type = std::string("pda");
            pda_rhs = new std::vector<std::pair<std::string,std::string>>();
            std::pair<std::string,std::string> str;
            str=std::make_pair($1->state_alpha,$1->stack);
            pda_rhs->push_back(str);
          }
          | LBRACE elements_PDA RBRACE
          {
            $$ = new lhs_arrow_attr();
            $$->type = std::string("pda");
            pda_rhs = new std::vector<std::pair<std::string,std::string>>();
            for(auto &it: *($2->lst))
            {
                std::pair<std::string,std::string> str;
                str = std::make_pair(it->state_alpha,it->stack);
                pda_rhs->push_back(str);
            }
          }
          ;

cfg_rhs : cfg_rhs_ele
        {
            cfg_rhs_current = new std::vector<std::string>();
            cfg_rhs_current->push_back($1->cc);
        }
        | cfg_rhs_list
        ;

cfg_rhs_ele : cfg_rhs_ele OPER_MOD LBRACE ID RBRACE
            {
                $$ = new cc_code();
                $$->cc = $1->cc + std::string("%{")+std::string($4)+"}";
            }
            | cfg_rhs_ele DOLLAR LBRACE ID RBRACE
            {
                $$ = new cc_code();
                $$->cc = $1->cc + std::string("${")+std::string($4) +"}";
            }
            | cfg_rhs_ele EPSILON
            {
                $$ = new cc_code();
                $$->cc = $1->cc + std::string("");
            }
            | OPER_MOD LBRACE ID RBRACE
            {
                $$ = new cc_code();
                $$->cc = std::string("%{")+std::string($3)+"}";
            }
            | EPSILON
            {
                $$ = new cc_code();
                $$->cc = std::string("");
            }
            | DOLLAR LBRACE ID RBRACE
            {
                $$ = new cc_code();
                $$->cc = std::string("${")+std::string($3) +"}";
            }

cfg_rhs_list : LBRACE cfg_rhs_ele_list RBRACE
             ;

cfg_rhs_ele_list : cfg_rhs_ele
                 {
                    if(cfg_rhs_current==NULL)
                        cfg_rhs_current = new std::vector<std::string>();
                    if($1->cc!="")
                        cfg_rhs_current->push_back($1->cc);
                    else
                        cfg_rhs_current->push_back(std::string("\\\\e"));
                 }
                 | cfg_rhs_ele_list COMMA cfg_rhs_ele
                 {
                    if(cfg_rhs_current==NULL)
                        cfg_rhs_current = new std::vector<std::string>();
                    if($3->cc!="")
                        cfg_rhs_current->push_back($3->cc);
                    else
                        cfg_rhs_current->push_back(std::string("\\\\e"));
                 }
                 ;

control_body : statements
             | SEMICOLON
             | statements control_body
             ;

if_statement : ifexp LBRACE
               {
                 //create a new symbol table
                 VarSymbolTable *table = new VarSymbolTable();
                 vstl->insert(table);
                 current_vst = table;
                 cc_file<<"\t{"<<std::endl;
               }
               control_body RBRACE
               {
                    //delete the symbol table
                    vstl->remove();
                    current_vst = vstl->getTop();
                    cc_file<<"}"<<std::endl;
               } 
               elif_statement else_statement
             ;

ifexp : IF_KW LPAREN expression RPAREN {
        if($3->indicator!=1)
            yyerror("Invalid expression in if statement");
        printlog("If");
        cc_file<<"if("<<$3->cc<<")"<<std::endl;
        }
      ;

elif_statement : elif LBRACE 
                {
                    //create a new symbol table
                    VarSymbolTable *table = new VarSymbolTable();
                    vstl->insert(table);
                    current_vst = table;
                    cc_file<<"\t{"<<std::endl;
                }
                control_body RBRACE
                {
                    //delete the symbol table
                    vstl->remove();
                    current_vst = vstl->getTop();
                    cc_file<<"}"<<std::endl;
                }
               |
               ;

elif : ELIF_KW LPAREN expression RPAREN 
       {
        if($3->indicator!=1)
            yyerror("Invalid expression in elif statement");
        printlog("Elif");
        cc_file<<"else if("<<$3->cc<<")"<<std::endl;
       }
       ;

else_statement : ELSE_KW LBRACE 
                {
                    //create a new symbol table
                    VarSymbolTable *table = new VarSymbolTable();
                    vstl->insert(table);
                    current_vst = table;
                    printlog("Else");
                    cc_file<<"else \t{"<<std::endl;
                } control_body RBRACE
                {
                    //delete the symbol table
                    vstl->remove();
                    current_vst = vstl->getTop();
                    cc_file<<"}"<<std::endl;
                }
               |
               ;

while_statement : whileexp LBRACE 
                {
                   //create a new symbol table
                   VarSymbolTable *table = new VarSymbolTable();
                   vstl->insert(table);
                   current_vst = table;
                   in_loop++;
                } control_body RBRACE 
                {
                    //delete the symbol table
                    vstl->remove();
                    current_vst = vstl->getTop();
                    in_loop--;
                }
                ;

whileexp : WHILE_KW LPAREN expression RPAREN 
           {
                if($3->indicator!=1)
                    yyerror("Invalid expression in while statement");
                printlog("While");
           }
         ;

call_statement : call SEMICOLON
                {
                    cc_file<<$1->cc<<" ;"<<std::endl;
                }
               ;

return_statement : RETURN_KW expression SEMICOLON
                 {
                    if(!current_function)
                        yyerror("Return statement outside function");
                    type_attr *type = new type_attr();
                    type->indicator = $2->indicator;
                    type->vtp = $2->vtp;
                    type->vta = $2->vta;
                    type->vts = $2->vts;
                    type->vtsr = $2->vtsr;
                    type->ifStruct = $2->ifStruct;
                    type->inner = $2->inner;
                    if(current_function->return_type == std::string("void"))
                        yyerror("Return type mismatch/ function returns void");
                    std::string inner = type->inner->print();
                    if(inner[inner.length()-1]==' ')
                        inner = inner.substr(0,inner.length()-1);
                    
                    if(!isCoherent(current_function->return_type,(trim(getType(type) + std::string(" ")+inner))))
                    {
                        std::string str = std::string("Return type mismatch, expecting ")+current_function->return_type;
                        yyerror(str.c_str());
                    }
                    //struct handling (to be done)
                    $$ = new type_attr();
                    $$->indicator = $2->indicator;
                    $$->vtp = $2->vtp;
                    $$->vta = $2->vta;
                    $$->vts = $2->vts;
                   cc_file<<"return "<<$2->cc<<" ;"<<std::endl;
                 }
                 | RETURN_KW SEMICOLON
                 {
                    if(!current_function)
                        yyerror("Return statement outside function");
                    if(current_function->return_type != "void")
                    {
                        std::string error = "Return type mismatch/ function returns "+current_function->return_type;
                        yyerror(error.c_str());
                    }
                    $$ = new type_attr();
                    $$->indicator = 0;
                    cc_file<<"return ;"<<std::endl;

                 }
                 ;

break_statement : BREAK_KW SEMICOLON {
                                    if(!in_loop) 
                                        yyerror("Break statement outside loop");
                                    cc_file<<"break ;"<<std::endl;
                                    }
                ;

continue_statement : CONTINUE_KW SEMICOLON {
                                            if(!in_loop) 
                                                yyerror("Continue statement outside loop");
                                            cc_file<<"continue ;"<<std::endl;
                                            }
                   ;

dtype : TYPE_PRIMITIVE { 
                        $$ = new type_attr();
                        $$->indicator = 1;
                        $$->vtp = $1;
                        $$->cc = type_maps_prim[$$->vtp];
                      }
      | TYPE_SET COMP_LT set_type COMP_GT {
                                            $$ = new type_attr();
                                            $$->indicator = 2;
                                            $$->vts = $1; 
                                            // start from here 
                                            $$->inner = $3->inner;
                                            $$->cc = type_maps_set[$$->vts] +"<"+$3->cc+">";
                                          }
      | TYPE_AUTOMATA {
                        $$ = new type_attr();
                        $$->indicator = 3;
                        $$->vta = $1;
                        $$->cc = type_maps_auto[$$->vta];
                      }
      | TYPE_STRING {
                        $$ = new type_attr();
                        $$->indicator = 4;
                        $$->vtsr = $1;
                        $$->cc = type_maps_sr[$$->vtsr];
                    }
      | TYPE_REG {
                        $$ = new type_attr();
                        $$->indicator = 5;
                        $$->vtsr = $1;
                        $$->cc = type_maps_sr[$$->vtsr];
                 }
      ;

set_type : dtype {
                    $$ = new type_attr();
                    $$->inner = new inner_type($1->inner,getType($1));
                    $$->cc = $1->cc;

                 }
         | ID {
                $$ = new type_attr();
                $$->inner = new inner_type(NULL,std::string($1));
                $$->cc = std::string($1);
              }
         ;

%%

void yyerror(const char *s) {

    fprintf(parse_log, "Parser error: %d\n", yylineno);
    std::cout<<RED<<"Parser error: "<<yylineno<<RESET;
    std::cout<<": "<<s<<std::endl;
    terminate();

}

int main(int argc, char **argv) {
    // #ifdef YYDEBUG
    //      yydebug = 1;
    // #endif
    initST();
    initData();
    yyin = fopen(argv[1],"r");
    char *filename = (char*)malloc(sizeof(char)*strlen(argv[1]));
     //position of last '.' in file name
    char *pos = strrchr(argv[1],'.'); 

    //position of last '/' in file name
    char *x = strrchr(argv[1],'/');

    // file name of the input file after removing .txt at the end
    // This requires the input file to have an extension
    if(x==NULL)
        strncpy(filename,argv[1],pos-argv[1]);
    else
        strncpy(filename,x+1,pos-x-1);

    // path to the folder of test file
    char *path = (char*)malloc(sizeof(char)*strlen(argv[1]));
    strncpy(path,argv[1],x-argv[1]);
    x = strrchr(path,'/');
    path[x-path] = '\0';
    char *seq = (char*)malloc(sizeof(char)*(strlen(path)+50));
    char *parser_log = (char*)malloc(sizeof(char)*(strlen(path)+50));
    sprintf(seq,"%s/logs/seq_tokens_%s.tok",path,filename);
    sprintf(parser_log,"%s/logs/parser_log_%s.log",path,filename);
    char *cc_file_name = (char*)malloc(sizeof(char)*(strlen(path)+50));
    sprintf(cc_file_name,"%s/cc_files/cc_file_%s.cc",path,filename);
    cc_file.open(cc_file_name,std::ios::out);
    cc_file<<"#include \"../../includes/fsm.hh\"\n";
    // tokens file path
    
    if(argc==3)
    {
        sprintf(seq,"%s/seq_tokens_%s.tok",argv[2],filename);
        sprintf(parser_log,"%s/parser_log_%s.log",argv[2],filename);
    }
    seq_token.open(seq,std::ios::out);
    parse_log = fopen(parser_log,"w");
    yyparse();
    fclose(yyin);
    seq_token.close();
    fclose(parse_log);
    cc_file.close();
    return 0;
}
