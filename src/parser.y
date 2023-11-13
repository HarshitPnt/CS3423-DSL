%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fstream>
#include <list>
#include <iostream>
#include "../includes/st.hh"


#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

extern int yylex();
void yyerror(char const* str);
extern FILE* yyin;
extern std::fstream seq_token;
FILE* parse_log;
extern int yylineno;
void terminate()
{
    fclose(yyin);
    exit(1);
}

int in_function = 0;
int in_loop = 0;
int num_params = 0;
FunctionSymbolTableEntry *current_function;

#define printlog(a) fprintf(parse_log,"%s declaration at line no: %d\n",a,yylineno)
#define getVTA(a) (a==TYPE_NFA?"NFA":(a==TYPE_DFA?"DFA":(a==TYPE_PDA?"PDA":(a==TYPE_CFG?"CFG":""))))
#define getConst(a) (a.val->type==CINT?a.val->ccint:(a.val->type==CFLOAT?a.val->ccfloat:(a.val->type==CBOOL?a.val->ccbool:a.val->ccchar)))
#define getCTYPE(a) ((a.vtp==TYPE_INT_64 || a.vtp==TYPE_INT_32 || a.vtp==TYPE_INT_16 || a.vtp==TYPE_INT_8)?CINT:((a.vtp==TYPE_FLOAT_64 || a.vtp==TYPE_FLOAT_32)?CFLOAT:((a.vtp==TYPE_BOOL)?CBOOL:CCHAR)))

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
    struct {
        VTYPE_PRIMITIVE vtp;
        VTYPE_AUTOMATA vta;
        VTYPE_SET vts;
        VTYPE_SR vtsr;
        int indicator;
        constant *val;
        type_attr *type;
        int isConst;
        int isVar;
        id_attr *id;
    } expression_attr;

    id_attr *id;
    type_attr *type;
    func_attr *func;
    id_list_attr *id_lst;
    param_list_attr *para;
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
%token IF_KW ELIF_KW ELSE_KW WHILE_KW BREAK_KW STRUCT_KW RETURN_KW CONTINUE_KW
%token ARROW COLON
%left COMMA DOT SEMICOLON DOLLAR
%left OPER_AND OPER_OR
%left<comp> OPER_COMP COMP_GT COMP_LT
%left OPER_PLUS OPER_MINUS OPER_MUL OPER_DIV OPER_MOD
%left AT_THE_RATE OPER_POWER
%left OPER_NOT OPER_HASH
%token OPER_ASN OPER_ASN_SIMPLE
%left LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE
%token EPSILON

%nterm<expression_attr> expression
%nterm<id> pseudo_ID param
%nterm<type> rhs dtype set_type return_statement
%nterm<id_lst> id_list id_list_decl
%nterm<para> param_list next_param
%start program
%%

program : instruction_list

instruction_list: instruction_list struct_declaration
                | instruction_list function_declaration
                | instruction_list statements
                |
                ;

struct_declaration: STRUCT_KW ID
                                {
                                    //check if struct already exists
                                    // sst->print();
                                    if(sst->lookup(std::string($2)))
                                    {
                                        std::string error = "Struct redeclaration: "+std::string($2);
                                        yyerror(error.c_str());
                                    }
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
                        // entry->fields->print();
                        sst->insert(entry);
                        printlog("Struct");
                        //remove struct scope from the varSymbolTableList
                        if(vstl->remove())
                            yyerror("Internal Error");
                        current_vst = vstl->getTop();
                    }
                ;

struct_body: struct_body struct_member
            | struct_member
            ;

struct_member: dtype id_list_decl SEMICOLON
            {
                //backpatching here
                for(auto it = $2->lst.begin();it!=$2->lst.end();it++)
                {
                    if(current_vst->backpatch(it->first,getType($1),$1->inner,NULL))
                    {
                        yyerror("Internal Error");
                    }
                }
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
                VarSymbolTable *struct_vst = sst->lookup(std::string($1))->fields;
                for(auto it = $2->lst.begin();it!=$2->lst.end();it++)
                {
                    if(current_vst->backpatch(it->first,std::string($1),NULL,struct_vst))
                    {
                        yyerror("Internal Error");
                    }
                }

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
            }
            ;

expression_list: expression
               | expression_list COMMA expression
               ;

function_declaration: function_header
                    {
                        vstl->remove(); //remove the parameter scope
                        current_vst = vstl->getTop();
                    } 
                    LBRACE
                    {
                        //create a function scope
                        VarSymbolTable *new_st = new VarSymbolTable();
                        vstl->insert(new_st);
                        current_vst = new_st;
                    }    
                    function_body RBRACE 
                    {
                        in_function = 0;
                        //remove function scope
                        if(vstl->remove())
                            yyerror("Internal Error");
                        current_vst = vstl->getTop();
                        current_function = NULL;
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
                        current_function = entry;
                        //insert function into function table
                        for(auto it = $4->lst.begin();it!=$4->lst.end();it++)
                        {
                            entry->id_list.push_back(*it);
                        }
                        fst->insert(entry);
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
                        //insert function into function table
                        for(auto it = $4->lst.begin();it!=$4->lst.end();it++)
                        {
                            entry->id_list.push_back(*it);
                        }
                        fst->insert(entry);
                    }
                ;

param_list: 
            {
                //no params
                $$ = new param_list_attr();
                $$->num = 0;
            }
          | param next_param
          {
            $$ = new param_list_attr();
            $$->num = num_params;
            $$->lst = $2->lst;
            $$->lst.push_back($1->name);
          }
          ;

param: dtype ID
     {
        $$ = new id_attr();
        $$->name = std::string($2);
        //check if ID already present
        if(current_vst->lookup(std::string($2)))
        {
            std::string error = "Variable redeclaration: "+std::string($2);
            yyerror(error.c_str());
        }
        VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string($2));
        entry->type = getType($1);
        current_vst->insert(entry);
        ++num_params;
     }
     | ID ID
     {
        $$ = new id_attr();
        $$->name = std::string($2);
        //check if ID already present
        if(current_vst->lookup(std::string($2)))
        {
            std::string error = "Variable redeclaration: "+std::string($2);
            yyerror(error.c_str());
        }
        //check if struct exists
        if(!sst->lookup(std::string($1)))
        {
            std::string str = std::string("Error: Struct ")+std::string($1)+std::string(" not defined");
            yyerror(str.c_str());
        }
        VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string($2));
        entry->type = std::string($1);
        current_vst->insert(entry);
        ++num_params;
     }
     ;

next_param : 
            {
                //end of params
                $$ = new param_list_attr();
                $$->num = num_params;
            }
           | COMMA param next_param
           {
                $$ = new param_list_attr();
                $$->num = num_params;
                $$->lst = $3->lst;
                $$->lst.push_back($2->name);
           }
           ;

function_body: function_body statements
             | SEMICOLON
             |
             ;

statements: variable_declaration {printlog("Variable declaration");}
          | assignment {printlog("Assignment");}
          | if_statement
          | while_statement
          | return_statement {printlog("Return");}
          | break_statement {printlog("Break");}
          | continue_statement {printlog("Continue");}
          | call_statement {printlog("Function call");}
          | LBRACE control_body RBRACE {printlog("Block");}
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
                                }
                                if($1->indicator==3 && it->second->indicator!=3)
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
                        for(auto it = $2->lst.begin();it!=$2->lst.end();it++)
                        {
                            if(current_vst->backpatch(it->first,getType($1),$1->inner,NULL))
                            {
                                yyerror("Internal Error");
                            }
                        }
                        // vstl->print();
                    }
                    | ID id_list SEMICOLON
                    {
                        //check if struct exists
                        if(!sst->lookup(std::string($1)))
                        {
                            std::string str = std::string("Error: Struct ")+std::string($1)+std::string(" not defined");
                            yyerror(str.c_str());
                        }
                        VarSymbolTable *struct_fields = sst->lookup(std::string($1))->fields;
                        for(auto it = $2->lst.begin();it!=$2->lst.end();it++)
                        {
                            if(current_vst->backpatch(it->first,std::string($1),NULL,struct_fields))
                            {
                                yyerror("Internal Error");
                            }
                        }
                        // before backpatching check if rhs are variables of same struct type (to be done)
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
                VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string($1));
                current_vst->insert(entry);
                type_attr *type = new type_attr();
                type->indicator = 0;
                $$->lst.push_back(std::make_pair(entry,type));
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
            VarSymbolTableEntry *entry = new VarSymbolTableEntry(std::string($1));
            current_vst->insert(entry);
            type_attr *type = new type_attr();
            type->indicator = $3->indicator;
            type->vtp = $3->vtp;
            type->vta = $3->vta;
            type->vts = $3->vts;
            $$->lst.push_back(std::make_pair(entry,type));
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
       }
       ;

pseudo_ID: pseudo_ID LBRACK expression RBRACK
         {
            //accessing the set member
            if($3.indicator != 1)
                yyerror("Invalid operation: Set can only be accessed using integer index");
            if(!isInteger($3.vtp))
                yyerror("Invalid operation: Set can only be accessed using integer/unsigned integer index");
            //idea is to build the entire pseudo_ID and check whenever it is used somewhere
            $$ = new id_attr();
            if($3.isConst)
                $$->name = std::string($1->name)+std::string("[")+std::to_string($3.val->ccint)+std::string("]");
            else //first need to build expression
                $$->name = std::string($1->name)+std::string("[")+std::string("_expr_")+std::string("]");
         }
         | pseudo_ID DOT pseudo_ID
         {
            //accessing the inner member
            $$ = new id_attr();
            $$->name = std::string($1->name)+std::string(".")+std::string($3->name);
         }
         | ID {
                //check if ID exists
                $$ = new id_attr();
                $$->name = $1;
                
              }
         ;

assignment: pseudo_ID OPER_ASN rhs SEMICOLON 
          | pseudo_ID OPER_ASN_SIMPLE rhs SEMICOLON {
            std::pair<bool,std::string> ret = checkPseudoID(NULL,$1->name,"");
            if(!ret.first)
                yyerror(ret.second.c_str());
            // std::cout<<$1->name<<std::endl;
          }
          | pseudo_ID OPER_ASN_SIMPLE REGEX_R REGEX_LIT SEMICOLON
          | pseudo_ID OPER_ASN_SIMPLE STRING_CONST SEMICOLON
          | pseudo_ID COLON OPER_ASN_SIMPLE rhs_automata SEMICOLON
          | pseudo_ID COLON OPER_ASN_SIMPLE cfg_rules SEMICOLON
          | pseudo_ID COLON OPER_ASN_SIMPLE ID SEMICOLON
          | pseudo_ID COLON OPER_ASN_SIMPLE LBRACE states_list RBRACE SEMICOLON
          ;

states_list: ID
           | states_list COMMA ID
           ;

cfg_rules : LBRACE cfg_rule_list RBRACE
          ;

cfg_rule_list : cfg_rule
              | cfg_rule_list COMMA cfg_rule
              ;

cfg_rule : pseudo_ID ARROW cfg_rhs
         ;

rhs: expression
    {
        $$ = new type_attr();
        $$->vtp = $1.vtp;
        $$->vta = $1.vta;
        $$->vts = $1.vts;
        $$->indicator = $1.indicator;
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
     */
     $$ = new type_attr();
     $$->indicator = 6;
   }
   | REGEX_R REGEX_LIT
   {
    $$ = new type_attr();
    $$->indicator = 5;
   }
   ;

expression: LPAREN expression RPAREN {
                                      $$.indicator = $2.indicator;
                                      $$.vtp = $2.vtp;
                                      $$.vta = $2.vta;
                                      $$.vts = $2.vts;
                                      $$.isConst = false;
                                      if($2.isConst)
                                      {
                                        $$.isConst = true;
                                        $$.val = $2.val;
                                      }
                                     }
          | expression OPER_PLUS expression 
          {
                if($1.indicator ==1 || $3.indicator==1)
                {
                    $$.indicator = 1;
                    if($1.vtp==TYPE_FLOAT_64 || $3.vtp==TYPE_FLOAT_64)
                    $$.vtp = TYPE_FLOAT_64;
                    else if($1.vtp==TYPE_FLOAT_32 || $3.vtp==TYPE_FLOAT_32)
                        $$.vtp = TYPE_FLOAT_32;
                    else
                        $$.vtp = TYPE_INT_64;
                    $$.isConst = false;
                    if($1.isConst && $3.isConst)
                    {
                        $$.isConst = true;
                        $$.val = new constant();
                        $$.val->type = getCTYPE($$);
                        if($$.val->type==CINT)
                            $$.val->ccint = getConst($1)+getConst($3);
                        else if($$.val->type==CFLOAT)
                            $$.val->ccfloat = getConst($1)+getConst($3);
                        else if($$.val->type==CBOOL)
                            $$.val->ccbool = getConst($1)+getConst($3);
                        else if($$.val->type==CCHAR)
                            $$.val->ccchar = getConst($1)+getConst($3);
                    }
                }
                else if($1.indicator ==2 || $3.indicator==2)
                {
                    $$.indicator = 2;
                    $$.vts = TYPE_OSET;
                }
                else if($1.indicator ==3 || $3.indicator==3)
                {
                    if(($1.vta == TYPE_NFA && $3.vta == TYPE_DFA) || ($3.vta == TYPE_NFA && $1.vta == TYPE_DFA) || ($1.vta == TYPE_NFA && $3.vta == TYPE_NFA))
                        $$.vta = TYPE_NFA;
                    else if($1.vta == TYPE_DFA && $3.vta == TYPE_DFA)
                        $$.vta = TYPE_DFA;
                    else if($1.vta == TYPE_PDA && $3.vta == TYPE_PDA)
                        $$.vta = TYPE_PDA;
                    else if($1.vta == TYPE_CFG && $3.vta == TYPE_CFG)
                        $$.vta = TYPE_CFG;
                    else 
                        {
                            std::string error = std::string("Invalid operation:")+std::string(getVTA($1.vta))+std::string(", ")+std::string(getVTA($3.vta))+std::string(" union  not defined");
                            yyerror(error.c_str());
                        }
                }
                else
                    yyerror("Invalid operation: Addition can only be done between 'primitive' types");
                
          }
          | expression OPER_MINUS expression
          {
                // Set difference
                if($1.indicator==1 && $3.indicator==1)
                {
                    $$.indicator = 1;
                    $$.isConst = false;
                    if($1.vtp==TYPE_FLOAT_64 || $3.vtp==TYPE_FLOAT_64)
                        $$.vtp = TYPE_FLOAT_64;
                    else if($1.vtp==TYPE_FLOAT_32 || $3.vtp==TYPE_FLOAT_32)
                        $$.vtp = TYPE_FLOAT_32;
                    else
                        $$.vtp = TYPE_INT_64;
                    if($1.isConst && $3.isConst)
                    {
                        $$.isConst = true;
                        $$.val = new constant();
                        $$.val->type = getCTYPE($$);
                        if($$.val->type==CINT)
                            $$.val->ccint = getConst($1)-getConst($3);
                        else if($$.val->type==CFLOAT)
                            $$.val->ccfloat = getConst($1)-getConst($3);
                        else if($$.val->type==CBOOL)
                            $$.val->ccbool = getConst($1)-getConst($3);
                        else if($$.val->type==CCHAR)
                            $$.val->ccchar = getConst($1)-getConst($3);
                    }
                }
                else if($1.indicator==2 && $3.indicator==2)
                {
                    $$.indicator = 2;
                    $$.vts = TYPE_OSET;
                }
                else
                    yyerror("Invalid operation: Subtrction can only be done between 'primitive' and 'set' types");
          }
          | expression OPER_MUL expression
          {
                //Kleene star and intersection
                $$.isConst = false;
                if($1.indicator ==1 && $3.indicator ==1)
                {
                    $$.indicator = 1;
                    if($1.vtp==TYPE_FLOAT_64 || $3.vtp==TYPE_FLOAT_64)
                        $$.vtp = TYPE_FLOAT_64;
                    else if($1.vtp==TYPE_FLOAT_32 || $3.vtp==TYPE_FLOAT_32)
                        $$.vtp = TYPE_FLOAT_32;
                    else
                        $$.vtp = TYPE_INT_64;
                    if($1.isConst && $3.isConst)
                    {
                        $$.isConst = true;
                        $$.val = new constant();
                        $$.val->type = getCTYPE($$);
                        if($$.val->type==CINT)
                            $$.val->ccint = getConst($1)*getConst($3);
                        else if($$.val->type==CFLOAT)
                            $$.val->ccfloat = getConst($1)*getConst($3);
                        else if($$.val->type==CBOOL)
                            $$.val->ccbool = getConst($1)*getConst($3);
                        else if($$.val->type==CCHAR)
                            $$.val->ccchar = getConst($1)*getConst($3);
                    }
                }
                else if($1.indicator ==2 && $3.indicator ==2)
                {
                    $$.indicator = 2;
                    $$.vts = TYPE_OSET;
                }
                else
                    yyerror("Invalid operation: Multiplication can only be done between 'primitive' and 'set' types");
          }
          | expression OPER_DIV expression
          {
            if($1.indicator !=1 || $3.indicator !=1)
                yyerror("Invalid operation: Division can only be done between 'primitive' types");
            //check for division by zero (to be done)
            if($3.val && (($3.val->type == CINT && $3.val->ccint == 0) || ($3.val->type == CFLOAT && $3.val->ccfloat == 0.0) || ($3.val->type == CBOOL && $3.val->ccbool == false)||( $3.val->type == CCHAR && $3.val->ccchar == '\0')))
                yyerror("Invalid operation: Division by zero");
            $$.indicator = 1;
            $$.isConst = false;
            if($1.vtp==TYPE_FLOAT_64 || $3.vtp==TYPE_FLOAT_64)
                $$.vtp = TYPE_FLOAT_64;
            else if($1.vtp==TYPE_FLOAT_32 || $3.vtp==TYPE_FLOAT_32)
                $$.vtp = TYPE_FLOAT_32;
            else
                $$.vtp = TYPE_INT_64;
            if($1.isConst && $3.isConst)
            {
                $$.isConst = true;
                $$.val = new constant();
                $$.val->type = getCTYPE($$);
                if($$.val->type==CINT)
                    $$.val->ccint = getConst($1)/getConst($3);
                else if($$.val->type==CFLOAT)
                    $$.val->ccfloat = getConst($1)/getConst($3);
                else if($$.val->type==CBOOL)
                    $$.val->ccbool = getConst($1)/getConst($3);
                else if($$.val->type==CCHAR)
                    $$.val->ccchar = getConst($1)/getConst($3);
            }
          }
          | expression OPER_MOD expression
          {
            if($1.indicator !=1 || $3.indicator !=1)
                yyerror("Invalid operation: Modulo can only be done between 'integer' types");
            if($1.vtp==TYPE_FLOAT_64 || $3.vtp==TYPE_FLOAT_64 || $1.vtp==TYPE_FLOAT_32 || $3.vtp==TYPE_FLOAT_32)
                yyerror("Invalid operation: Modulo can only be done between 'integer' types");
            $$.indicator = 1;
            $$.isConst = false;
            $$.vtp = TYPE_INT_64;
            if($1.isConst && $3.isConst)
            {
                $$.isConst = true;
                $$.val = new constant();
                $$.val->type = getCTYPE($$);
                if($$.val->type==CINT)
                    $$.val->ccint = $1.val->ccint % $3.val->ccint;
            }
          }
          | expression OPER_COMP expression
          {
            if($1.indicator !=1 || $3.indicator !=1)
                yyerror("Invalid comparison: Comparison can only be done between primitive types");
            $$.indicator = 1;
            $$.vtp = TYPE_BOOL;
            std::string comp($2); //"<=",">=","==","!="
            $$.isConst = false;
            if(comp=="<=")
            {
                if($1.isConst && $3.isConst)
                {
                    $$.isConst = true;
                    $$.val = new constant();
                    $$.val->type = CBOOL;
                    $$.val->ccbool = getConst($1)<=getConst($3);
                }
            }
            if(comp==">=")
            {
                if($1.isConst && $3.isConst)
                {
                    $$.isConst = true;
                    $$.val = new constant();
                    $$.val->type = CBOOL;
                    $$.val->ccbool = getConst($1)>=getConst($3);
                }
            }
            if(comp=="==")
            {
                if($1.isConst && $3.isConst)
                {
                    $$.isConst = true;
                    $$.val = new constant();
                    $$.val->type = CBOOL;
                    $$.val->ccbool = getConst($1)==getConst($3);
                }
            }
            if(comp=="!=")
            {
                if($1.isConst && $3.isConst)
                {
                    $$.isConst = true;
                    $$.val = new constant();
                    $$.val->type = CBOOL;
                    $$.val->ccbool = getConst($1)!=getConst($3);
                }
            }
          }
          | expression OPER_POWER
          {
            if($1.indicator !=2)
                yyerror("Invalid operation: Power set can only be computed for a set");
            $$.indicator = 2;
            $$.vts = TYPE_OSET;
            $$.isConst = false;
          }
          | expression AT_THE_RATE expression 
          {
            // What about regex? (to be done) cfg + pdas (to be done)
            if($1.indicator !=2 || $3.indicator != 2)
                yyerror("Invalid operation: Automata can only be concatenated with Automata");
            $$.indicator = 2;
            if(($1.vta == TYPE_NFA && $3.vta == TYPE_DFA) || ($3.vta == TYPE_NFA && $1.vta == TYPE_DFA) || ($1.vta == TYPE_NFA && $3.vta == TYPE_NFA))
                $$.vta = TYPE_NFA;
            else if($1.vta == TYPE_DFA && $3.vta == TYPE_DFA)
                $$.vta = TYPE_DFA;
            else if($1.vta == TYPE_PDA && $3.vta == TYPE_PDA)
                $$.vta = TYPE_PDA;
            else if($1.vta == TYPE_CFG && $3.vta == TYPE_CFG)
                $$.vta = TYPE_CFG;
            else
                yyerror("Invalid operation: Automata can only be concatenated with Automata");
            $$.isConst = false;
          }
          | expression OPER_OR expression
          {
            if($1.indicator ==3 || $3.indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if($1.indicator == 2 || $3.indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            $$.indicator = 1;
            $$.vtp = TYPE_BOOL;
            $$.isConst = false;
            if($1.isConst && $3.isConst)
            {
                $$.isConst = true;
                $$.val = new constant();
                $$.val->type = CBOOL;
                $$.val->ccbool = getConst($1) || getConst($3);
            }
            else if($1.isConst)
            {
                if(($1.val->type==CINT && $1.val->ccint!=0) || ($1.val->type==CFLOAT && $1.val->ccfloat!=0.0) || ($1.val->type==CBOOL && $1.val->ccbool!=false) || ($1.val->type==CCHAR && $1.val->ccchar!='\0'))
                {
                    $$.isConst = true;
                    $$.val = new constant();
                    $$.val->type = CBOOL;
                    $$.val->ccbool = true;
                }
            }
            else if($3.isConst)
            {
                if(($3.val->type==CINT && $3.val->ccint!=0) || ($3.val->type==CFLOAT && $3.val->ccfloat!=0.0) || ($3.val->type==CBOOL && $3.val->ccbool!=false) || ($3.val->type==CCHAR && $3.val->ccchar!='\0'))
                {
                    $$.isConst = true;
                    $$.val = new constant();
                    $$.val->type = CBOOL;
                    $$.val->ccbool = true;
                }
            }
          }
          | expression OPER_AND expression
          {
            if($1.indicator ==3 || $3.indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if($1.indicator == 2 || $3.indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            $$.indicator = 1;
            $$.vtp = TYPE_BOOL;
            $$.isConst = false;
            if($1.isConst && $3.isConst)
            {
                $$.val->type = CBOOL;
                $$.val->ccbool = getConst($1) && getConst($3);
            }
            else if($1.isConst)
            {
                if(($1.val->type==CINT && $1.val->ccint==0) || ($1.val->type==CFLOAT && $1.val->ccfloat==0.0) || ($1.val->type==CBOOL && $1.val->ccbool==false) || ($1.val->type==CCHAR && $1.val->ccchar=='\0'))
                {
                    $$.isConst = true;
                    $$.val = new constant();
                    $$.val->type = CBOOL;
                    $$.val->ccbool = false;
                }
            }
            else if($3.isConst)
            {
                if(($3.val->type==CINT && $3.val->ccint==0) || ($3.val->type==CFLOAT && $3.val->ccfloat==0.0) || ($3.val->type==CBOOL && $3.val->ccbool==false) || ($3.val->type==CCHAR && $3.val->ccchar=='\0'))
                {
                    $$.isConst = true;
                    $$.val = new constant();
                    $$.val->type = CBOOL;
                    $$.val->ccbool = false;
                }
            }
          }
          | expression COMP_GT expression
          {
            if($1.indicator ==3 || $3.indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if($1.indicator == 2 || $3.indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            $$.indicator = 1;
            $$.vtp = TYPE_BOOL;
            $$.isConst = false;
            //constant check
            if($1.isConst && $3.isConst)
            {
                $$.isConst = true;
                $$.val = new constant();
                $$.val->type = CBOOL;
                $$.val->ccbool = getConst($1)>getConst($3);
            }
          }
          | expression COMP_LT expression 
          {
            if($1.indicator ==3 || $3.indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if($1.indicator == 2 || $3.indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            $$.indicator = 1;
            $$.vtp = TYPE_BOOL;
            $$.isConst = false;
            //constant check
            if($1.isConst && $3.isConst)
            {
                $$.isConst = true;
                $$.val = new constant();
                $$.val->type = CBOOL;
                $$.val->ccbool = getConst($1)<getConst($3);
            }
          }
          | OPER_NOT expression { 
            if($2.indicator ==2)
                yyerror("Invalid operator: Negation of Set not defined");
            if($2.indicator ==3 && ($2.vta == TYPE_CFG || $2.vta == TYPE_PDA))
                yyerror("Invalid operator: CFG/NDPDA not closed under complement");
            $$.indicator = $2.indicator;
            $$.isConst = false;
            if($2.indicator == 1)
            {
                if($2.isConst)
                {
                    $$.isConst = true;
                    $$.val = new constant();
                    $$.val->type = CBOOL;
                    if($2.val->type == CINT)
                        $$.val->ccbool = !($2.val->ccint);
                    else if($2.val->type == CFLOAT)
                        $$.val->ccbool = !($2.val->ccfloat);
                    else if($2.val->type == CBOOL)
                        $$.val->ccbool = !($2.val->ccbool);
                    else if($2.val->type == CCHAR)
                        $$.val->ccbool = !($2.val->ccchar);
                }
                else
                    $$.isConst = false;
                $$.vtp = TYPE_BOOL;
            }
            else if($2.indicator == 3)
                {$$.vta = $2.vta; $$.isConst = false;}

          }
          | expression OPER_HASH { 
            if($1.indicator !=3)
                yyerror("Invalid operator: Kleene Star can only be applied to Automata");
            $$.indicator = 3;
            $$.vta = $1.vta;
            $$.isConst = false;
          }
          | OPER_MINUS expression { 
                                    $$.indicator = $2.indicator; 
                                    $$.vtp = $2.vtp; 
                                    $$.vta = $2.vta; 
                                    $$.vts = $2.vts;
                                    $$.isConst = $2.isConst;
                                    $$.val = $2.val;
                                    switch($$.val->type)
                                    {
                                        case CINT:
                                                $$.val->ccint = -($$.val->ccint);
                                                break;
                                        case CFLOAT:
                                                $$.val->ccfloat = -($$.val->ccfloat);
                                                break;
                                        case CBOOL:
                                                $$.val->ccbool = !($$.val->ccbool);
                                                break;
                                        case CCHAR:
                                                $$.val->ccchar = -($$.val->ccchar);
                                                break;
                                    }
                                }
          | OPER_PLUS expression { 
                                  $$.indicator = $2.indicator;
                                  $$.vtp = $2.vtp; 
                                  $$.vta = $2.vta; 
                                  $$.vts = $2.vts;
                                  $$.isConst = $2.isConst;
                                  $$.val = $2.val;
                                 }
          | INT_CONST { 
                        $$.indicator = 1; 
                        $$.vtp = TYPE_INT_64; 
                        $$.val = new constant();
                        $$.val->ccint = $1;
                        $$.val->type = CINT;
                        $$.isConst = true;
                      }
          | FLOAT_CONST { 
                          $$.indicator = 1; 
                          $$.vtp = TYPE_FLOAT_64; 
                          $$.val = new constant();
                          $$.val->ccfloat = $1;
                          $$.val->type = CFLOAT;
                          $$.isConst = true;
                        }
          | BOOL_CONST { 
                         $$.indicator = 1; 
                         $$.vtp = TYPE_BOOL; 
                         $$.val = new constant();
                         $$.val->ccbool = $1;
                         $$.val->type = CBOOL;
                         $$.isConst = true;
                       }
          | CHAR_CONST { 
                        $$.indicator = 1; 
                        $$.vtp = TYPE_CHAR;
                        $$.val = new constant();
                        $$.val->ccchar = $1;
                        $$.val->type = CBOOL;
                        $$.isConst = true;
                       }
          | pseudo_ID { 
                        $$.indicator = $1->indicator; 
                        $$.vtp = $1->vtp; 
                        $$.vta = $1->vta; 
                        $$.vts = $1->vts;
                        std::pair<bool,std::string> ret = checkPseudoID(NULL,$1->name,"");
                        if(!ret.first)
                            yyerror(ret.second.c_str());
                        else
                        {
                            $$.isConst = false;
                            std::string type = ret.second.substr(ret.second.find(' ')+1);
                            if(type=="int_8")
                            {
                                $$.indicator = 1;
                                $$.vtp = TYPE_INT_8;
                            }
                            else if(type=="int_16")
                            {
                                $$.indicator = 1;
                                $$.vtp = TYPE_INT_16;
                            }
                            else if(type=="int_32")
                            {
                                $$.indicator = 1;
                                $$.vtp = TYPE_INT_32;
                            }
                            else if(type=="int_64")
                            {
                                $$.indicator = 1;
                                $$.vtp = TYPE_INT_64;
                            }
                            else if(type=="float_32")
                            {
                                $$.indicator = 1;
                                $$.vtp = TYPE_FLOAT_32;
                            }
                            else if(type=="float_64")
                            {
                                $$.indicator = 1;
                                $$.vtp = TYPE_FLOAT_64;
                            }
                            else if(type=="bool")
                            {
                                $$.indicator = 1;
                                $$.vtp = TYPE_BOOL;
                            }
                            else if(type=="char")
                            {
                                $$.indicator = 1;
                                $$.vtp = TYPE_CHAR;
                            }
                            else if(type=="string")
                            {
                                $$.indicator = 4;
                                $$.vtsr = TYPE_STR;
                            }
                            else if(type=="regex")
                            {
                                $$.indicator = 5;
                                $$.vtsr = TYPE_REGEX;
                            }
                            else if(type=="set")
                            {
                                $$.indicator = 2;
                                $$.vts = TYPE_OSET;
                            }
                            else if(type=="nfa")
                            {
                                $$.indicator = 3;
                                $$.vta = TYPE_NFA;
                            }
                            else if(type=="dfa")
                            {
                                $$.indicator = 3;
                                $$.vta = TYPE_DFA;
                            }
                            else if(type=="pda")
                            {
                                $$.indicator = 3;
                                $$.vta = TYPE_PDA;
                            }
                            else if(type=="cfg")
                            {
                                $$.indicator = 3;
                                $$.vta = TYPE_CFG;
                            }
                            //structs (to be done)
                        }
                      }
          | call {
                    // To be handled (to be done)
                    $$.indicator = 1;
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
        //check if argument type matches (to be done)
        //create type of call
     }
     ;

argument_list: 
             | expression
             | argument_list COMMA expression
             ;

rhs_automata: LBRACE alphabet_list RBRACE
            | LBRACE rules_list RBRACE
            ;

alphabet_list: alphabet
           | alphabet_list COMMA alphabet
           ;

alphabet : ID COLON STRING_CONST
         ;

rules_list : rule
           | rules_list COMMA rule
           ;

rule :LPAREN pseudo_ID lhs_arrow ARROW rhs_arrow RPAREN
     ;

lhs_arrow : COMMA ID
          | COMMA element_PDA
          | COMMA EPSILON
          | COMMA REGEX_R REGEX_LIT
          | COMMA LBRACE elements_PDA RBRACE
          | COMMA LBRACE elements_others RBRACE
          ;

elements_PDA : element_PDA
             | elements_PDA COMMA element_PDA
             ;

element_PDA : LPAREN ID COMMA ID RPAREN
            | LPAREN ID COMMA EPSILON RPAREN
            ;

elements_others : ID
                | elements_others COMMA ID
                ;

rhs_arrow : pseudo_ID
          | LBRACE elements_others RBRACE
          | element_PDA
          | LBRACE elements_PDA RBRACE
          ;

cfg_rhs : cfg_rhs_ele
        | cfg_rhs_list
        ;

cfg_rhs_ele : cfg_rhs_ele ID
            | cfg_rhs_ele DOLLAR LBRACE ID RBRACE
            | cfg_rhs_ele EPSILON
            | ID
            | EPSILON
            | DOLLAR LBRACE ID RBRACE

cfg_rhs_list : LBRACE cfg_rhs_ele_list RBRACE
             ;

cfg_rhs_ele_list : cfg_rhs_ele
                 | cfg_rhs_ele_list COMMA cfg_rhs_ele
                 ;

control_body : statements
             | SEMICOLON
             | statements control_body
             ;

if_statement : ifexp LBRACE control_body RBRACE elif_statement else_statement
             ;

ifexp : IF_KW LPAREN expression RPAREN {printlog("If");}
      ;

elif_statement : elif LBRACE control_body RBRACE
               |
               ;

elif : ELIF_KW LPAREN expression RPAREN {printlog("Elif");}
     ;

else_statement : ELSE_KW {printlog("Else");} LBRACE control_body RBRACE
               |
               ;

while_statement : whileexp LBRACE {in_loop++;} control_body RBRACE {in_loop--;}
                ;

whileexp : WHILE_KW LPAREN expression RPAREN {printlog("While");}
         ;

call_statement : call SEMICOLON
               ;

return_statement : RETURN_KW expression SEMICOLON
                 {
                    type_attr *type = new type_attr();
                    type->indicator = $2.indicator;
                    type->vtp = $2.vtp;
                    type->vta = $2.vta;
                    type->vts = $2.vts;
                    if(current_function->return_type == std::string("void"))
                        yyerror("Return type mismatch/ function returns void");
                    if(!isCoherent(current_function->return_type,getType(type)))
                        yyerror("Return type mismatch");
                    //struct handling (to be done)
                    $$->indicator = $2.indicator;
                    $$->vtp = $2.vtp;
                    $$->vta = $2.vta;
                    $$->vts = $2.vts;
                 }
                 | RETURN_KW SEMICOLON
                 {
                    if(current_function->return_type != "void")
                    {
                        std::string error = "Return type mismatch/ function returns "+current_function->return_type;
                        yyerror(error.c_str());
                    }
                    $$->indicator = 0;
                 }
                 ;

break_statement : BREAK_KW SEMICOLON {if(!in_loop) yyerror("Break statement outside loop");}
                ;

continue_statement : CONTINUE_KW SEMICOLON {if(!in_loop) yyerror("Continue statement outside loop");}
                   ;

dtype : TYPE_PRIMITIVE { 
                        $$ = new type_attr();
                        $$->indicator = 1;
                        $$->vtp = $1;
                      }
      | TYPE_SET COMP_LT set_type COMP_GT {
                                            $$ = new type_attr();
                                            $$->indicator = 2;
                                            $$->vts = $1; 
                                            // start from here 
                                            $$->inner = $3->inner;
                                          }
      | TYPE_AUTOMATA {
                        $$ = new type_attr();
                        $$->indicator = 3;
                        $$->vta = $1;
                      }
      | TYPE_STRING {
                        $$ = new type_attr();
                        $$->indicator = 4;
                        $$->vtsr = $1;
                    }
      | TYPE_REG {
                        $$ = new type_attr();
                        $$->indicator = 5;
                        $$->vtsr = $1;
                 }
      ;

set_type : dtype {
                    $$ = new type_attr();
                    $$->inner = new inner_type($1->inner,getType($1));
                 }
         | ID {
                $$ = new type_attr();
                $$->inner = new inner_type(NULL,std::string("struct"));
              }
         ;

%%

void yyerror(const char *s) {

    fprintf(parse_log, "Parser error: %d\n", yylineno);
    std::cout<<RED<<"Parser error: "<<yylineno<<RESET;
    std::cout<<" :"<<s<<std::endl;
    terminate();

}

int main(int argc, char **argv) {
    // #ifdef YYDEBUG
    //      yydebug = 1;
    // #endif
    initST();

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
    return 0;

}
