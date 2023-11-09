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
%left PSEUDO_LOW
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

program : instruction_list

instruction_list: struct_delaration
                | function_declaration
                | statements
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

function_declaration: function_header LBRACE function_body RBRACE
                    ;

function_header: dtype ID LPAREN param_list RPAREN {
                        printlog("Function");
                    }
                | ID ID LPAREN param_list RPAREN {
                        printlog("Function");
                    }
                ;

param_list: 
          | param_list COMMA dtype ID
          | param_list COMMA ID ID
          ;

function_body: statements
             ;

statements: variable_declaration
          | assignment
          | if_statement
          | while_statement
          | return_statement
          | break_statement
          | continue_statement
          ;

variable_declaration: dtype id_list SEMICOLON
                    | ID id_list SEMICOLON
                    ;

id_list: ID
       | ID OPER_ASN_SIMPLE expression
       | id_list COMMA ID
       | id_list COMMA ID OPER_ASN_SIMPLE expression
       ;

pseudo_ID: pseudo_ID LBRACK expression RBRACK
         | pseudo_ID DOT pseudo_ID
         | ID
         ;

assignment: pseudo_ID OPER_ASN rhs SEMICOLON
          | pseudo_ID OPER_ASN_SIMPLE rhs SEMICOLON
          | pseudo_ID COLON OPER_ASN_SIMPLE rhs_automata SEMICOLON
          ;

rhs: expression
   | LBRACE expression_list RBRACE
   ;

expression_list: expression
               | expression_list COMMA expression
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
          | expression COMP_GT expression
          | expression COMP_LT expression
          | OPER_NOT expression
          | expression OPER_HASH
          | OPER_MINUS expression
          | OPER_PLUS expression
          | INT_CONST
          | FLOAT_CONST
          | BOOL_CONST
          | CHAR_CONST
          | pseudo_ID
          | call
          ;

call : ID LPAREN argument_list RPAREN
     ;

argument_list: 
             | expression
             | argument_list COMMA expression
             ;

rhs_automata: LBRACE RBRACE


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
