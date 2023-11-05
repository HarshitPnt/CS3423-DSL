%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"
// #include "semantic.h"

extern int yylex();
void yyerror(char const* str);
extern FILE* yyin;
extern FILE* seq_token;
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
%}
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
    VTYPE_STANDARD dtype_standard;


    // Variables
    char* identifier;


    
}

%left STRING BOOL CHAR INT_8 INT_16 INT_32 INT_64 UINT_8 UINT_16 UINT_32 UINT_64 FLOAT_32 FLOAT_64 REG

%left O_SET U_SET CFG DFA NFA PDA

%left <identifier> ID

%token IF_KW ELIF_KW ELSE_KW WHILE_KW BREAK_KW STRUCT_KW RETURN_KW

%token ARROW COLON

%left OPER_AND OPER_OR

%left OPER_COMP COMP_GT COMP_LT

%left OPER_PLUS OPER_MINUS

%left OPER_MUL OPER_DIV OPER_MOD

%left AT_THE_RATE

%left OPER_POWER

%left OPER_NOT OPER_HASH

%token OPER_ASN OPER_ASN_SIMPLE

%token LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE

%left COMMA DOT SEMICOLON SIN_QUOTE DOLLAR

%token <cint> INT_CONST <cfloat> FLOAT_CONST <cstring> STRING_CONST <cchar> CHAR_CONST <cbool> BOOL_CONST

%left REGEX_R REGEX_LIT REGEX_NUM REGEX_OR REGEX_STAR REGEX_PLUS REGEX_QUE REGEX_CARET REGEX_LRANGE REGEX_HYPHEN REGEX_RRANGE REGEX_DOLLAR 

%left LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE

%token EPSILON

%precedence PSEUDO_HIGH

%start program
%%

program: instruction_list
       ;


instruction_list: /* empty */
                | instruction_list struct_declaration
                | instruction_list function_declaration
                | instruction_list statement
                ;


statement: variable_declaration
         | expression_assignment
         | control_statement
         | call_statement
         ;

variable_declaration: primitive_dtype id_list_arith SEMICOLON {fprintf(parse_log,"variable declaration at line no: %d\n",yylineno);}
                    | set_type id_list_set SEMICOLON {fprintf(parse_log,"variable declaration at line no: %d\n",yylineno);}
                    | STRING id_list_string SEMICOLON {fprintf(parse_log,"variable declaration at line no: %d\n",yylineno);}
                    | REG id_list_reg SEMICOLON {fprintf(parse_log,"variable declaration at line no: %d\n",yylineno);}
                    | automata_dtype id_list_auto SEMICOLON {fprintf(parse_log,"variable declaration at line no: %d\n",yylineno);}
                    | ID id_lists SEMICOLON {fprintf(parse_log,"variable declaration of structs at line no: %d\n",yylineno);}
                    ;

id_list_arith : ID
              | ID OPER_ASN_SIMPLE expression
              | ID COMMA id_list_arith
              | ID OPER_ASN_SIMPLE expression COMMA id_list_arith
              ;

id_list_string : ID
              | ID OPER_ASN_SIMPLE STRING_CONST
              | ID OPER_ASN_SIMPLE call
              | ID COMMA id_list_string
              | ID OPER_ASN_SIMPLE STRING_CONST COMMA id_list_string
              | ID OPER_ASN_SIMPLE call COMMA id_list_string
              ;

id_list_set: ID
           | ID OPER_ASN_SIMPLE set_values
           | ID OPER_ASN_SIMPLE call
           | ID COMMA id_list_set
           | ID OPER_ASN_SIMPLE set_values COMMA id_list_set
           | ID OPER_ASN_SIMPLE call COMMA id_list_set
           ;

id_list_reg : ID
            | ID OPER_ASN_SIMPLE REGEX_R SIN_QUOTE regex_expression SIN_QUOTE
            | ID OPER_ASN_SIMPLE call
            | ID COMMA id_list_reg
            | ID OPER_ASN_SIMPLE REGEX_R SIN_QUOTE regex_expression SIN_QUOTE id_list_reg
            | ID OPER_ASN_SIMPLE call COMMA id_list_reg
            ;

id_list_auto : ID
             | ID COMMA id_list_auto
             | ID OPER_ASN_SIMPLE call 
             | ID OPER_ASN_SIMPLE call id_list_auto
             ;

primitive_dtype: INT_8
               | INT_16
               | INT_32
               | INT_64
               | UINT_8
               | UINT_16
               | UINT_32
               | UINT_64
               | FLOAT_32
               | FLOAT_64
               | BOOL
               | CHAR
               ;

complex_dtype : STRING
              | REG
              ;

automata_dtype: CFG
              | DFA
              | NFA
              | PDA
              | ID
              ;

set_type: O_SET COMP_LT primitive_dtype COMP_GT
        | O_SET COMP_LT complex_dtype COMP_GT
        | O_SET COMP_LT set_type COMP_GT
        | O_SET COMP_LT automata_dtype COMP_GT
        | O_SET COMP_LT ID COMP_GT
        | U_SET COMP_LT primitive_dtype COMP_GT
        | U_SET COMP_LT complex_dtype COMP_GT
        | U_SET COMP_LT set_type COMP_GT
        | U_SET COMP_LT automata_dtype COMP_GT
        | U_SET COMP_LT ID COMP_GT
        ;

pseudo_ID : ID
          | ID DOT pseudo_ID
          | pseudo_ID DOT ID
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

regex_expression: LPAREN regex_expression RPAREN
                | REGEX_CARET regex_expression
                | regex_expression REGEX_OR regex_expression
                | regex_expression REGEX_STAR
                | regex_expression REGEX_PLUS
                | regex_expression REGEX_QUE
                | regex_expression REGEX_DOLLAR
                | regex_expression REGEX_DOLLAR LBRACE pseudo_ID RBRACE
                | regex_expression LBRACK regex_class RBRACK
                | regex_expression LBRACE REGEX_NUM RBRACE
                | regex_expression LBRACE REGEX_NUM COMMA RBRACE
                | regex_expression LBRACE REGEX_NUM COMMA REGEX_NUM RBRACE
                | regex_expression REGEX_LIT
                |
                ;

regex_class: REGEX_CARET regex_class
           | REGEX_LRANGE REGEX_HYPHEN REGEX_RRANGE regex_class
           | REGEX_LRANGE REGEX_HYPHEN REGEX_RRANGE
           | REGEX_LIT regex_class
           | REGEX_LIT
           ;

set_values: LBRACE set_value_list RBRACE
          ;

set_value_list: /* empty */
              | set_value
              | set_value_list COMMA set_value
              ;

set_value: expression
         | REGEX_R SIN_QUOTE regex_expression SIN_QUOTE
         ;

expression_assignment : pseudo_ID OPER_ASN expression SEMICOLON {fprintf(parse_log,"expr assignment statement at line no: %d\n",yylineno);}
                      | pseudo_ID OPER_ASN_SIMPLE expression SEMICOLON {fprintf(parse_log,"expr assignment statement at line no: %d\n",yylineno);}
                      | pseudo_ID OPER_ASN_SIMPLE REGEX_R  SIN_QUOTE regex_expression SIN_QUOTE SEMICOLON {fprintf(parse_log,"expr assignment statement at line no: %d\n",yylineno);}
                      | pseudo_ID OPER_ASN_SIMPLE STRING_CONST SEMICOLON {fprintf(parse_log,"expr assignment statement at line no: %d\n",yylineno);}
                      | pseudo_ID OPER_ASN_SIMPLE set_values SEMICOLON {fprintf(parse_log,"expr assignment statement for sets at line no: %d\n",yylineno);}
                      | pseudo_ID OPER_ASN_SIMPLE LBRACE cfg_fsm_symb_list RBRACE SEMICOLON {fprintf(parse_log,"expr(automata) assignment statement at line no: %d\n",yylineno);}
                      | pseudo_ID OPER_ASN_SIMPLE LBRACE prod_transition_list RBRACE SEMICOLON {fprintf(parse_log,"expr(automata) assignment statement at line no: %d\n",yylineno);}
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
         | SEMICOLON REGEX_R SIN_QUOTE LBRACK regex_expression_vars RBRACK SIN_QUOTE
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

regex_expression_vars: REGEX_DOLLAR LBRACE ID RBRACE regex_expression_vars
                     | REGEX_DOLLAR LBRACE ID RBRACE
                     ;

control_statement: if_statement
                 | while_statement
                 | return_statement
                 ;


if_statement: IF_KW LPAREN expression RPAREN {fprintf(parse_log,"IF Statement at line no: %d\n",yylineno);} LBRACE statement_list_extended RBRACE elif_statement else_statement
            ;

statement_list_extended: instruction_list
                       | instruction_list BREAK_KW SEMICOLON
                       | SEMICOLON
                       ;

elif_statement: ELIF_KW LPAREN expression RPAREN LBRACE statement_list_extended RBRACE elif_statement {fprintf(parse_log,"ELIF Statement at line no: %d\n",yylineno);}
              | /* empty */
              ;


else_statement: ELSE_KW LBRACE statement_list_extended RBRACE {fprintf(parse_log,"ELSE Statement at line no: %d\n",yylineno);}
              | /* empty */
              ;


while_statement: WHILE_KW LPAREN expression RPAREN LBRACE statement_list_extended RBRACE {fprintf(parse_log,"WHILE Statement at line no: %d\n",yylineno);}
               ;

return_statement: RETURN_KW expression SEMICOLON {fprintf(parse_log,"RETURN Statement at line no: %d\n",yylineno);}
                | RETURN_KW SEMICOLON {fprintf(parse_log,"RETURN Statement at line no: %d\n",yylineno);}
                ;

call : ID LPAREN argument_list RPAREN {fprintf(parse_log,"CALL Statement at line no: %d\n",yylineno);}
     ;

call_statement: call SEMICOLON {fprintf(parse_log,"CALL Statement at line no: %d\n",yylineno);}
              ;

argument_list: /* empty */
             | expression argument_list_cont
             ;

argument_list_cont: /* empty */
                  | COMMA expression argument_list_cont
                  ;

struct_declaration: STRUCT_KW {fprintf(parse_log,"STRUCT Declaration at line no: %d\n",yylineno);} ID LBRACE struct_body RBRACE SEMICOLON 
                  ;

struct_body: struct_variable_declaration
           | struct_body struct_variable_declaration
           ;

id_lists: ID
        | ID COMMA id_lists
        ;

struct_variable_declaration: primitive_dtype id_lists SEMICOLON
                           | complex_dtype id_lists SEMICOLON
                           | set_type id_lists SEMICOLON
                           | automata_dtype id_lists SEMICOLON
                           ;

function_declaration: function_header LBRACE instruction_list RBRACE
                    ;

function_header: primitive_dtype ID LPAREN parameter_list RPAREN {fprintf(parse_log,"Function Declaration at line no: %d\n",yylineno);}
               | complex_dtype ID LPAREN parameter_list RPAREN {fprintf(parse_log,"Function Declaration at line no: %d\n",yylineno);}
               | set_type ID LPAREN parameter_list RPAREN {fprintf(parse_log,"Function Declaration at line no: %d\n",yylineno);}
               | automata_dtype ID LPAREN parameter_list RPAREN {fprintf(parse_log,"Function Declaration at line no: %d\n",yylineno);}
               ;

parameter_list: /* empty */
              | parameter_list COMMA parameter
              | parameter 
              ;

parameter: primitive_dtype ID
         | complex_dtype ID
         | set_type ID
         | automata_dtype ID
         ;

%%

void yyerror(const char *s) {

    fprintf(parse_log, "Parser error: %d\n", yylineno);
    fprintf(stderr, "Parser error: %s\n", s);
    terminate();

}

// #ifdef YYDEBUG
//   int yydebug = 1;
// #endif

int main(int argc, char **argv) {
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
    seq_token = fopen(seq, "w");
    parse_log = fopen(parser_log,"w");
    yyparse();
    fclose(yyin);
    fclose(seq_token);
    fclose(parse_log);
    return 0;

}
