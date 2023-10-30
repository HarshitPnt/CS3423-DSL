%{

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    extern int yylex();
    void yyerror(char const* str);
    extern FILE* yyin;
    extern FILE* seq_token;
    int ret = 1;

    void terminate()
    {
        fclose(yyin);
        exit(1);
    }

%}

%left PSEUDO_LOW

%left STRING BOOL CHAR INT_8 INT_16 INT_32 INT_64 UINT_8 UINT_16 UINT_32 UINT_64 FLOAT_32 FLOAT_64 REGEX

%left O_SET U_SET CFG DFA NFA PDA

%left ID

%token IF_KW ELIF_KW ELSE_KW WHILE_KW BREAK_KW STRUCT_KW RETURN_KW

%token ARROW COLON

%left OPER_AND OPER_OR

%left OPER_COMP COMP_GT COMP_LT

%left OPER_PLUS OPER_MINUS

%left OPER_MUL OPER_DIV OPER_MOD

%left AT_THE_RATE

%left OPER_POWER

%left OPER_NOT

%token OPER_ASN OPER_ASN_SIMPLE

%token LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE

%left COMMA DOT SEMICOLON SIN_QUOTE

%token INT_CONST FLOAT_CONST STRING_CONST CHAR_CONST BOOL_CONST

%left REGEX_R REGEX_LIT REGEX_NUM REGEX_OR REGEX_STAR REGEX_PLUS REGEX_QUE REGEX_CARET REGEX_LRANGE REGEX_HYPHEN REGEX_RRANGE REGEX_DOLLAR 

%left LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE

%token EPSILON

%precedence PSEUDO_TOKEN

%start program
%%

program: instruction_list
        ;


instruction_list: statement
                | instruction_list struct_declaration
                | instruction_list function_declaration
                | instruction_list statement
                ;


statement: variable_declaration
         | assignment_statement
         | control_statement
         | call_statement
         ;

variable_declaration: data_type id_list SEMICOLON
                  ;

id_list: ID
       | id_list COMMA ID
       ;


data_type: int_type %prec INT_8
         | float_type %prec FLOAT_32
         | BOOL
         | STRING
         | CHAR
         | set_type %prec O_SET
         | REGEX
         | CFG
         | DFA
         | NFA
         | PDA
         | ID
         ;

int_type : INT_8
         | INT_16
         | INT_32
         | INT_64
         | UINT_8
         | UINT_16
         | UINT_32
         | UINT_64

float_type : FLOAT_32
           | FLOAT_64
           ;

set_type : O_SET COMP_LT data_type COMP_GT
         | U_SET COMP_LT data_type COMP_GT
         ;

assignment_statement: declaration_assignment
                    | expression_assignment
                    ;

declaration_assignment: int_type ID OPER_ASN_SIMPLE expression SEMICOLON %prec PSEUDO_TOKEN
                      | float_type ID OPER_ASN_SIMPLE expression SEMICOLON
                      | BOOL ID OPER_ASN_SIMPLE expression SEMICOLON
                      | STRING ID OPER_ASN_SIMPLE STRING_CONST SEMICOLON
                      | CHAR ID OPER_ASN_SIMPLE CHAR_CONST SEMICOLON
                      | set_type ID OPER_ASN_SIMPLE set_values SEMICOLON
                      | REGEX ID OPER_ASN_SIMPLE REGEX_R SIN_QUOTE regex_expression SIN_QUOTE SEMICOLON
                      ;

pseudo_ID : ID
          | ID DOT pseudo_ID
          ;

expression : LPAREN expression RPAREN
           | expression OPER_PLUS expression
           | expression OPER_MINUS expression
           | expression OPER_MUL expression
           | expression OPER_DIV expression
           | expression OPER_MOD expression
           | expression OPER_COMP expression
           | expression OPER_AND expression
           | expression OPER_OR expression
           | OPER_NOT expression
           | expression COMP_GT expression
           | expression COMP_LT expression
           | INT_CONST
           | OPER_MINUS INT_CONST %prec PSEUDO_TOKEN
           | OPER_MINUS FLOAT_CONST %prec PSEUDO_TOKEN
           | FLOAT_CONST
           | BOOL_CONST
           | pseudo_ID
           | call_statement
           ;

regex_expression : LPAREN regex_expression RPAREN
                 | REGEX_CARET regex_expression
                 | regex_expression REGEX_OR regex_expression
                 | regex_expression REGEX_STAR
                 | regex_expression REGEX_PLUS
                 | regex_expression REGEX_QUE
                 | regex_expression REGEX_DOLLAR
                 | regex_expression REGEX_DOLLAR LBRACE pseudo_ID RBRACE REGEX_DOLLAR
                 | regex_expression LBRACK regex_class RBRACK
                 | regex_expression LBRACE REGEX_NUM RBRACE
                 | regex_expression LBRACE REGEX_NUM COMMA RBRACE
                 | regex_expression LBRACE REGEX_NUM COMMA REGEX_NUM RBRACE
                 | regex_expression REGEX_LIT
                 | REGEX_LIT
                 ;

regex_class : REGEX_CARET regex_class
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

expression_assignment : pseudo_ID OPER_ASN expression SEMICOLON
                      | pseudo_ID OPER_ASN_SIMPLE expression SEMICOLON
                      ;

control_statement: if_statement
                | while_statement
                | return_statement
                ;


if_statement: IF_KW LPAREN expression RPAREN LBRACE statement_list_extended RBRACE elif_statement else_statement
           ;

statement_list_extended: instruction_list
                       | instruction_list BREAK_KW SEMICOLON
                       | SEMICOLON
                       ;

elif_statement: ELIF_KW LPAREN expression RPAREN LBRACE statement_list_extended RBRACE
             |
             ;


else_statement: ELSE_KW LBRACE statement_list_extended RBRACE
             |
             ;


while_statement: WHILE_KW LPAREN expression RPAREN LBRACE statement_list_extended RBRACE
              ;

return_statement: RETURN_KW expression SEMICOLON
                | RETURN_KW SEMICOLON
                ;

call_statement: ID LPAREN argument_list RPAREN SEMICOLON
              ;

argument_list: /* empty */
             | expression
             | argument_list COMMA expression
             ;

struct_declaration: STRUCT_KW ID LBRACE struct_body RBRACE SEMICOLON
                  ;

struct_body: struct_variable_declaration
           | struct_body struct_variable_declaration
           ;

struct_variable_declaration: data_type id_list SEMICOLON
                           ;

function_declaration: function_header LBRACE instruction_list RBRACE
                     ;

function_header: data_type ID LPAREN parameter_list RPAREN
               ;

parameter_list: /* empty */
              | parameter
              | parameter_list COMMA parameter
              ;

parameter: data_type ID
         ;

%%

void yyerror(const char *s) {

    fprintf(stderr, "Parser error: %s\n", s);
    terminate();

}

#ifdef YYDEBUG
  int yydebug = 1;
#endif

int main(int argc, char **argv) {
    yyin = fopen(argv[1],"r");
    char *test = (char*)malloc(sizeof(char)*100);
    // fscanf(yyin,"%s",test);
    seq_token = fopen("seq_tokens_test.tok","w");
    // printf("%s\n",test);
    fflush(stdout);
    yyparse();
    fclose(yyin);
    fclose(seq_token);
    return 0;

}
