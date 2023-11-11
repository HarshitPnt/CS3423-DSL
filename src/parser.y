%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fstream>
#include <iostream>
#include "../includes/st.hh"

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

VarSymbolTableList *vstl;

StructSymbolTable *sst;
FunctionSymbolTable *fst;
VarSymbolTable *global_vst;

#define printlog(a) fprintf(parse_log,"%s declaration at line no: %d\n",a,yylineno)
#define getVTA(a) (a==TYPE_NFA?"NFA":(a==TYPE_DFA?"DFA":(a==TYPE_PDA?"PDA":(a==TYPE_CFG?"CFG":""))))
%}
%code requires {
    #include "../includes/semantic.hh"
}
%union {
    // Constants
    int cint;
    float cfloat;
    char cchar;
    char* cstring;
    bool cbool;
    struct {
        void* val;
        CTYPE type;
    } constant;

    // Data types
    struct {
        VTYPE_PRIMITIVE vtp;
        VTYPE_AUTOMATA vta;
        VTYPE_SET vts;
        int indicator;
    } expression_attr;

    struct {
        char* identifier;
        VTYPE_PRIMITIVE vtp;
        VTYPE_AUTOMATA vta;
        VTYPE_SET vts;
        std::string val;
        int indicator;
    } id_attr;
    VTYPE_PRIMITIVE dtype_primitive;
    VTYPE_AUTOMATA dtype_automata;
    VTYPE_SET dtype_set;

    // Variables
    char* identifier;

    
}
%left PSEUDO_LOW
%left <dtype_primitive> TYPE_PRIMITIVE
%left TYPE_STRING TYPE_REG
%left <dtype_set> TYPE_SET
%left <dtype_automata> TYPE_AUTOMATA
%token <cint> INT_CONST <cfloat> FLOAT_CONST <cstring> STRING_CONST <cchar> CHAR_CONST <cbool> BOOL_CONST
%left REGEX_R REGEX_LIT
%left <identifier> ID
%token IF_KW ELIF_KW ELSE_KW WHILE_KW BREAK_KW STRUCT_KW RETURN_KW CONTINUE_KW
%token ARROW COLON
%left COMMA DOT SEMICOLON DOLLAR
%left OPER_AND OPER_OR
%left OPER_COMP COMP_GT COMP_LT
%left OPER_PLUS OPER_MINUS OPER_MUL OPER_DIV OPER_MOD
%left AT_THE_RATE OPER_POWER
%left OPER_NOT OPER_HASH
%token OPER_ASN OPER_ASN_SIMPLE
%left LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE
%token EPSILON

%nterm<expression_attr> expression
%nterm pseudo_ID
%start program
%%

program : instruction_list

instruction_list: instruction_list struct_declaration
                | instruction_list function_declaration
                | instruction_list statements
                |
                ;

struct_declaration: STRUCT_KW ID LBRACE struct_body RBRACE SEMICOLON
                {
                    printlog("Struct");
                }
                ;

struct_body: struct_body struct_member
            | struct_member
            ;

struct_member: dtype id_list_decl SEMICOLON
            ;

id_list_decl: ID
            | id_list_decl COMMA ID
            ;

expression_list: expression
               | expression_list COMMA expression
               ;

function_declaration: function_header LBRACE function_body RBRACE {in_function = 0;}
                    ;

function_header: dtype ID LPAREN param_list RPAREN {
                        printlog("Function");
                        if(in_function)
                            yyerror("Nested function declaration");
                        in_function = 1;
                    }
                | ID ID LPAREN param_list RPAREN {
                        printlog("Function");
                        if(in_function)
                            yyerror("Nested function declaration");
                        in_function = 1;
                    }
                ;

param_list: 
          | param next_param
          ;

param: dtype ID
     | ID ID
     ;

next_param : 
           | COMMA param next_param
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
          | LBRACE statements RBRACE {printlog("Block");}
          ;

variable_declaration: dtype id_list SEMICOLON
                    | ID id_list SEMICOLON
                    ;

id_list: ID
       | ID OPER_ASN_SIMPLE rhs
       | id_list COMMA ID
       | id_list COMMA ID OPER_ASN_SIMPLE rhs
       ;

pseudo_ID: pseudo_ID LBRACK expression RBRACK
         | pseudo_ID DOT pseudo_ID
         | ID
         ;

assignment: pseudo_ID OPER_ASN rhs SEMICOLON
          | pseudo_ID OPER_ASN_SIMPLE rhs SEMICOLON
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
   | LBRACE expression_list RBRACE
   | REGEX_R REGEX_LIT
   ;

expression: LPAREN expression RPAREN {
                                      $$.indicator = $2.indicator;
                                      $$.vtp = $2.vtp;
                                      $$.vta = $2.vta;
                                      $$.vts = $2.vts;
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
                        yyerror("Invalid operation: %s union %s not defined",getVTA($1.vta),getVTA($3.vta));
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
                    if($1.vtp==TYPE_FLOAT_64 || $3.vtp==TYPE_FLOAT_64)
                        $$.vtp = TYPE_FLOAT_64;
                    else if($1.vtp==TYPE_FLOAT_32 || $3.vtp==TYPE_FLOAT_32)
                        $$.vtp = TYPE_FLOAT_32;
                    else
                        $$.vtp = TYPE_INT_64;
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
                if($1.indicator ==1 && $3.indicator ==1)
                {
                    $$.indicator = 1;
                    if($1.vtp==TYPE_FLOAT_64 || $3.vtp==TYPE_FLOAT_64)
                        $$.vtp = TYPE_FLOAT_64;
                    else if($1.vtp==TYPE_FLOAT_32 || $3.vtp==TYPE_FLOAT_32)
                        $$.vtp = TYPE_FLOAT_32;
                    else
                        $$.vtp = TYPE_INT_64;
                }
                else if($1.indicator ==2 && $3.indicator ==2)
                {
                    $$.indicator = 2;
                    $$.vts = TYPE_OSET;
                }
                else
                    yyerror("Invalid operation: Multiplication can only be done between 'primitive' and 'set' types"
          }
          | expression OPER_DIV expression
          {
            if($1.indicator !=1 || $3.indicator !=1)
                yyerror("Invalid operation: Division can only be done between 'primitive' types");
            //check for division by zero (to be done)
            $$.indicator = 1;
            if($1.vtp==TYPE_FLOAT_64 || $3.vtp==TYPE_FLOAT_64)
                $$.vtp = TYPE_FLOAT_64;
            else if($1.vtp==TYPE_FLOAT_32 || $3.vtp==TYPE_FLOAT_32)
                $$.vtp = TYPE_FLOAT_32;
            else
                $$.vtp = TYPE_INT_64;
          }
          | expression OPER_MOD expression
          {
            if($1.indicator !=1 || $3.indicator !=1)
                yyerror("Invalid operation: Modulo can only be done between 'integer' types");
            if($1.vtp==TYPE_FLOAT_64 || $3.vtp==TYPE_FLOAT_64 || $1.vtp==TYPE_FLOAT_32 || $3.vtp==TYPE_FLOAT_32)
                yyerror("Invalid operation: Modulo can only be done between 'integer' types");
            $$.indicator = 1;
            $$.vtp = TYPE_INT_64;
          }
          | expression OPER_COMP expression
          {
            if($1.indicator !=1 || $3.indicator !=1)
                yyerror("Invalid comparison: Comparison can only be done between primitive types");
            $$.indicator = 1;
            $$.vtp = TYPE_BOOL;
          }
          | expression OPER_POWER
          {
            if($1.indicator !=2 || $3.indicator !=2)
                yyerror("Invalid operation: Power set can only be computed for a set");
            $$.indicator = 2;
            $$.vts = TYPE_OSET;
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
          }
          | expression OPER_OR expression
          {
            if($1.indicator ==3 || $3.indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if($1.indicator == 2 || $3.indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            $$.indicator = 1;
            $$.vtp = TYPE_BOOL;
          }
          | expression OPER_AND expression
          {
            if($1.indicator ==3 || $3.indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if($1.indicator == 2 || $3.indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            $$.indicator = 1;
            $$.vtp = TYPE_BOOL;
          }
          | expression COMP_GT expression
          {
            if($1.indicator ==3 || $3.indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if($1.indicator == 2 || $3.indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            $$.indicator = 1;
            $$.vtp = TYPE_BOOL;
          }
          | expression COMP_LT expression 
          {
            if($1.indicator ==3 || $3.indicator == 3)
                yyerror("Invalid comparison: Set cannot be compared");
            if($1.indicator == 2 || $3.indicator == 2)
                yyerror("Invalid comparison: Automata cannot be compared");
            $$.indicator = 1;
            $$.vtp = TYPE_BOOL;
          }
          | OPER_NOT expression { // PDAs and CFGs are not closed under complementation $$.indicator = $2.indicator; $$.vtp = $2.vtp; $$.vta = $2.vta; $$.vts = $2.vts;
          }
          | expression OPER_HASH { // kleene star $$.indicator = $2.indicator; $$.vtp = $2.vtp; $$.vta = $2.vta; $$.vts = $2.vts;
          }
          | OPER_MINUS expression { $$.indicator = $2.indicator; $$.vtp = $2.vtp; $$.vta = $2.vta; $$.vts = $2.vts;}
          | OPER_PLUS expression { $$.indicator = $2.indicator; $$.vtp = $2.vtp; $$.vta = $2.vta; $$.vts = $2.vts;}
          | INT_CONST { $$.indicator = 1; $$.vtp = TYPE_INT_64; }
          | FLOAT_CONST { $$.indicator = 1; $$.vtp = TYPE_FLOAT_64; }
          | BOOL_CONST { $$.indicator = 1; $$.vtp = TYPE_BOOL; }
          | CHAR_CONST { $$.indicator = 1; $$.vtp = TYPE_CHAR; }
          | pseudo_ID { $$.indicator = $1.indicator; $$.vtp = $1.vtp; $$.vta = $1.vta; $$.vts = $1.vts; }
          | call
          ;

call : ID LPAREN argument_list RPAREN
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
                 | RETURN_KW SEMICOLON
                 ;

break_statement : BREAK_KW SEMICOLON {if(!in_loop) yyerror("Break statement outside loop");}
                ;

continue_statement : CONTINUE_KW SEMICOLON {if(!in_loop) yyerror("Continue statement outside loop");}
                   ;

dtype : TYPE_PRIMITIVE
      | TYPE_SET COMP_LT set_type COMP_GT
      | TYPE_AUTOMATA
      | TYPE_STRING
      | TYPE_REG
      ;

set_type : dtype
         | ID
         ;

%%
void yyerror(const char *s) {

    fprintf(parse_log, "Parser error: %d\n", yylineno);
    fprintf(stderr, "Parser error: %s\n", s);
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
