%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fstream>
#include <iostream>
#include "../includes/semantic.hh"

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
int in_condition = 0;

VarSymbolTableList *vstl;
StructSymbolTableList *sstl;
FunctionSymbolTable *fst;

VarSymbolTable *global_vst;
StructSymbolTable *global_sst;

#define printlog(a) fprintf(parse_log,"%s declaration at line no: %d\n",a,yylineno)
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
    VTYPE_PRIMITIVE dtype_primitive;
    VTYPE_AUTOMATA dtype_automata;
    VTYPE_SET dtype_set;

    // Variables
    char* identifier;

    
}

%left <dtype_primitive> TYPE_PRIMITIVE
%left STRING REG
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

%precedence PSEUDO_HIGH



%start program
%%

program: instruction_list
       ;

instruction_list: /* empty */
                | instruction_list statement
                | instruction_list struct_declaration
                | instruction_list function_declaration
                ;

statement: variable_declaration
         | expression_assignment
         | control_statement
         | call_statement
         ;

regex: REGEX_R REGEX_LIT;

complex_dtype : STRING
              | REG
              ;

automata_dtype: TYPE_AUTOMATA
              ;

dtype_noset: TYPE_PRIMITIVE
     | complex_dtype
     | automata_dtype
     ;

set_type: TYPE_SET COMP_LT dtype_noset COMP_GT
        | TYPE_SET COMP_LT set_type COMP_GT
        | TYPE_SET COMP_LT ID COMP_GT
        ;

dtype: set_type
     | dtype_noset
     ;

variable_declaration: TYPE_PRIMITIVE id_list_arith SEMICOLON {printlog("variable");}
                    | set_type id_list_set SEMICOLON {printlog("set");}
                    | STRING id_list_string SEMICOLON {printlog("string");}
                    | REG id_list_reg SEMICOLON {printlog("regex");}
                    | automata_dtype id_list_auto SEMICOLON {printlog("automata");}
                    | ID id_lists SEMICOLON {printlog("custom type variable");}
                    ;

id_list_arith : ID
              | ID OPER_ASN_SIMPLE expression
              | id_list_arith COMMA id_list_arith
              ;

id_list_string : ID
              | ID OPER_ASN_SIMPLE STRING_CONST
              | ID OPER_ASN_SIMPLE call
              | id_list_string COMMA id_list_string
              ;

id_list_set: ID
           | ID OPER_ASN_SIMPLE set_values
           | ID OPER_ASN_SIMPLE call
           | id_list_set COMMA id_list_set
           ;

id_list_reg : ID
            | ID OPER_ASN_SIMPLE regex
            | ID OPER_ASN_SIMPLE call
            | id_list_reg COMMA id_list_reg
            ;

id_list_auto : ID
             | ID OPER_ASN_SIMPLE call
             | id_list_auto COMMA id_list_auto
             ;

id_lists: id_lists COMMA id_lists
        | ID
        ;


pseudo_ID : ID
          | pseudo_ID DOT pseudo_ID
          | ID LBRACK expression RBRACK
          ;

expression: LPAREN expression RPAREN
          | expression OPER_PLUS expression
          | expression OPER_MINUS expression
          | expression OPER_MUL expression
          | expression OPER_DIV expression
          | expression OPER_MOD expression
          | expression OPER_COMP expression
          | expression OPER_AND expression
          | expression OPER_POWER
          | expression AT_THE_RATE expression
          | expression OPER_OR expression
          | OPER_NOT expression
          | expression COMP_GT expression
          | expression COMP_LT expression
          | expression OPER_HASH
          | INT_CONST
          | OPER_MINUS expression %prec PSEUDO_HIGH
          | OPER_PLUS expression %prec PSEUDO_HIGH
          | FLOAT_CONST
          | BOOL_CONST
          | CHAR_CONST
          | pseudo_ID
          | call
          ;


set_values: LBRACE set_value_list RBRACE
          ;

set_value_list: /* empty */
              | set_value
              | set_value_list COMMA set_value
              ;

set_value: expression
         | regex
         ;

expression_assignment : pseudo_ID OPER_ASN expression SEMICOLON {printlog("expression assignment");}
                      | pseudo_ID OPER_ASN_SIMPLE expression SEMICOLON {printlog("expression assignment");;}
                      | pseudo_ID OPER_ASN_SIMPLE regex SEMICOLON {printlog("expression assignment(regex)");}
                      | pseudo_ID OPER_ASN_SIMPLE STRING_CONST SEMICOLON {printlog("expression assignment(string)");}
                      | pseudo_ID OPER_ASN_SIMPLE set_values SEMICOLON {printlog("expression assignment(set)");}
                      | pseudo_ID OPER_ASN_SIMPLE LBRACE cfg_fsm_symb_list RBRACE SEMICOLON {printlog("expression assignment(automata)");}
                      | pseudo_ID OPER_ASN_SIMPLE LBRACE prod_transition_list RBRACE SEMICOLON {printlog("expression assignment(automata)");}
                      ;

cfg_fsm_symb_list: cfg_fsm_symb
                 | cfg_fsm_symb_list COMMA cfg_fsm_symb
                 ;

cfg_fsm_symb: ID COLON STRING_CONST
            ;

prod_transition_list: prod_transition
                    | prod_transition_list COMMA prod_transition
                    ;

prod_transition: pseudo_ID arrow_lhs ARROW arrow_rhs
               | pseudo_ID ARROW cfg_rhs_rule
               ;

arrow_lhs: SEMICOLON id_lhs
         | SEMICOLON regex
         | SEMICOLON set_values_vars
         | SEMICOLON id_lhs COMMA id_lhs
         | SEMICOLON set_values_pda
         ;

arrow_rhs: pseudo_ID DOLLAR
         | set_values DOLLAR
         | set_values_pda_rhs DOLLAR
         | EPSILON DOLLAR
         ;

id_lhs : DOLLAR LBRACE ID RBRACE
       | EPSILON
       ;

set_values_vars: LBRACE set_value_list_vars RBRACE
               ;

set_value_list_vars: set_value_vars
                   | set_value_list_vars COMMA set_value_vars
                   ;

set_value_vars: DOLLAR LBRACE ID RBRACE
              ;

set_values_pda: LBRACE set_value_list_pda RBRACE
              ;

set_values_pda_rhs: LBRACE set_value_list_pda_rhs RBRACE
                  | ID COMMA DOLLAR LBRACE ID RBRACE
                  | ID COMMA EPSILON
                  ;

set_value_list_pda_rhs: set_value_pda_rhs
                      | set_value_list_pda_rhs COMMA set_value_pda_rhs
                      ;

set_value_pda_rhs: LPAREN ID COMMA DOLLAR LBRACE ID RBRACE RPAREN
                 | LPAREN ID COMMA EPSILON RPAREN
                 ;

set_value_list_pda: set_value_pda
                  | set_value_list_pda COMMA set_value_pda
                  ;

set_value_pda: LPAREN DOLLAR LBRACE ID RBRACE COMMA DOLLAR LBRACE ID RBRACE RPAREN
             | LPAREN EPSILON COMMA DOLLAR LBRACE ID RBRACE RPAREN
             | LPAREN DOLLAR LBRACE ID RBRACE COMMA EPSILON RPAREN
             | LPAREN EPSILON COMMA EPSILON RPAREN
             ;

cfg_rhs_rule: LBRACE cfg_rhs_rule_list RBRACE
            | cfg_rhs_rule_item
            ;

cfg_rhs_rule_list: cfg_rhs_rule_item
                 | cfg_rhs_rule_list COMMA cfg_rhs_rule_item
                 ;

cfg_rhs_rule_item : DOLLAR LBRACE ID RBRACE cfg_rhs_rule
                  | DOLLAR LBRACE ID RBRACE DOLLAR
                  | ID cfg_rhs_rule
                  | ID DOLLAR
                  | EPSILON DOLLAR
                 ;

control_statement: if_statement
                 | while_statement
                 | return_statement
                 | continue_statement
                 | break_statement
                 ;


if_statement: IF_KW LPAREN expression RPAREN {printlog("IF");} LBRACE instruction_list RBRACE elif_statement else_statement
            ;

elif_statement: elif_statement ELIF_KW LPAREN expression RPAREN {printlog("ELIF");} LBRACE instruction_list RBRACE
              | /* empty */
              ;


else_statement: ELSE_KW {printlog("ELSE");} LBRACE instruction_list RBRACE
              | /* empty */
              ;


while_statement: WHILE_KW LPAREN expression RPAREN {in_loop++; printlog("while");} LBRACE instruction_list RBRACE {in_loop--;}
               ;

return_statement: RETURN_KW expression SEMICOLON {printlog("return"); if(in_function == 0) yyerror("Not in function, return statement");} 
                | RETURN_KW SEMICOLON {printlog("return"); if(in_function == 0) yyerror("Not in function, return statement");}
                ;

continue_statement: CONTINUE_KW SEMICOLON {printlog("continue"); if(in_loop <= 0) yyerror("Not in loop, continue statement");}
                  ;

break_statement: BREAK_KW SEMICOLON {printlog("break"); if(in_loop <= 0) yyerror("Not in loop, break statement");}
                ;

call : ID LPAREN argument_list RPAREN {printlog("call");}
     ;

call_statement: call SEMICOLON {printlog("call");}
              ;

argument_list: /* empty */
                | argument_list COMMA expression
                | expression
             ;

struct_declaration: STRUCT_KW ID {printlog("struct");} LBRACE struct_body RBRACE SEMICOLON 
                  ;

struct_body: struct_variable_declaration
           | struct_body struct_variable_declaration
           ;


struct_variable_declaration: dtype id_lists SEMICOLON {printlog("struct variable");}
                            | ID id_lists SEMICOLON {printlog("struct variable");}
                           ;

function_declaration: function_header {if(in_function == 1) yyerror("In function, function declaration"); in_function = 1;} LBRACE instruction_list RBRACE {in_function = 0;}
                    ;

function_header: dtype ID LPAREN parameter_list RPAREN {printlog("function");}
                | ID ID LPAREN parameter_list RPAREN {printlog("function");}
               ;

parameter_list: /* empty */
              | parameter_list COMMA parameter
              | parameter 
              ;

parameter: dtype ID
        | ID ID
         ;

%%

void yyerror(const char *s) {

    fprintf(parse_log, "Parser error: %d\n", yylineno);
    fprintf(stderr, "Parser error: %s\n", s);
    terminate();

}

/* #ifdef YYDEBUG
int yydebug = 1;
#endif */

int main(int argc, char **argv) {
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
