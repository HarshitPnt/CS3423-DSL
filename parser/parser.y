%{

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    extern int yylex();
    void yyerror(char const* str);
    extern FILE* yyin;
    extern FILE* seq_token;
    FILE* parse_log;
    extern int yylineno;
    int ret = 1;

    void terminate()
    {
        fclose(yyin);
        exit(1);
    }

%}

%left PSEUDO_LOW

%left STRING BOOL CHAR INT_8 INT_16 INT_32 INT_64 UINT_8 UINT_16 UINT_32 UINT_64 FLOAT_32 FLOAT_64 REG

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

variable_declaration: primitive_dtype id_list SEMICOLON {fprintf(parse_log,"variable declaration at line no: %d\n",yylineno);}
                    | set_type id_list SEMICOLON {fprintf(parse_log,"variable declaration at line no: %d\n",yylineno);}
                    | STRING id_list SEMICOLON {fprintf(parse_log,"variable declaration at line no: %d\n",yylineno);}
                    | REG id_list SEMICOLON {fprintf(parse_log,"variable declaration at line no: %d\n",yylineno);}
                    | automata_dtype id_list SEMICOLON {fprintf(parse_log,"variable declaration at line no: %d\n",yylineno);}
                    ;

id_list: ID
       | id_list COMMA ID
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

assignment_statement: declaration_assignment
                    | expression_assignment
                    ;

declaration_assignment: primitive_dtype ID OPER_ASN_SIMPLE expression SEMICOLON {
                            // semantic analysis needs to be done
                            fprintf(parse_log,"decl assignment statement at line no: %d\n",yylineno);
                        }
                      | STRING ID OPER_ASN_SIMPLE STRING_CONST SEMICOLON {
                            // semantic analysis needs to be done
                        fprintf(parse_log,"decl assignment statement at line no: %d\n",yylineno);
                        }
                      | set_type ID OPER_ASN_SIMPLE set_values SEMICOLON {
                            // semantic analysis needs to be done
                            fprintf(parse_log,"decl assignment statement at line no: %d\n",yylineno);
                        }
                      | REG ID OPER_ASN_SIMPLE REGEX_R SIN_QUOTE regex_expression SIN_QUOTE SEMICOLON {
                            // semantic analysis needs to be done
                            fprintf(parse_log,"decl assignment statement at line no: %d\n",yylineno);
                        }
                      ;

pseudo_ID : ID
          | ID DOT pseudo_ID
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
          | expression OPER_OR expression
          | OPER_NOT expression
          | expression COMP_GT expression
          | expression COMP_LT expression
          | INT_CONST
          | OPER_MINUS INT_CONST %prec PSEUDO_TOKEN
          | OPER_MINUS FLOAT_CONST %prec PSEUDO_TOKEN
          | FLOAT_CONST
          | BOOL_CONST
          | CHAR_CONST
          | pseudo_ID
          | call_statement
          ;

regex_expression: LPAREN regex_expression RPAREN
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
                      | pseudo_ID OPER_ASN_SIMPLE STRING_CONST SEMICOLON {fprintf(parse_log,"expr assignment statement at line no: %d\n",yylineno);}
                      | pseudo_ID OPER_ASN_SIMPLE set_values SEMICOLON {fprintf(parse_log,"expr(automata) assignment statement at line no: %d\n",yylineno);}
                      | pseudo_ID OPER_ASN_SIMPLE LBRACE cfg_terminal_list RBRACE SEMICOLON {fprintf(parse_log,"expr(automata) assignment statement at line no: %d\n",yylineno);}
                      | pseudo_ID OPER_ASN_SIMPLE LBRACE cfg_production_list RBRACE SEMICOLON {fprintf(parse_log,"expr(automata) assignment statement at line no: %d\n",yylineno);}
                      | pseudo_ID OPER_ASN_SIMPLE LBRACE fsm_transition_list RBRACE SEMICOLON {fprintf(parse_log,"expr(automata) assignment statement at line no: %d\n",yylineno);}
                      ;

cfg_terminal_list: /* empty */
                 | cfg_terminal
                 | cfg_terminal_list COMMA cfg_terminal
                 ;

cfg_terminal: ID COLON STRING_CONST
            ;

cfg_production_list: /* empty */
                   | cfg_production
                   | cfg_production_list COMMA cfg_production
                   ;

cfg_production: pseudo_ID ARROW cfg_prod_rhs
              ;

cfg_prod_rhs: LBRACE cfg_rhs cfg_rhs_list RBRACE
            | cfg_rhs
            ;

cfg_rhs_list: /* empty */
            | COMMA cfg_rhs cfg_rhs_list
            ;

cfg_rhs : LBRACE ID RBRACE pseudo_ID
        | EPSILON
        ;

fsm_transition_list: /* empty */
                   | fsm_transition
                   | fsm_transition_list COMMA fsm_transition
                   ;

fsm_transition: pseudo_ID COMMA transition_symb ARROW transition_rhs
              ;

transition_symb: pseudo_ID
               | EPSILON
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

elif_statement: ELIF_KW LPAREN expression RPAREN LBRACE statement_list_extended RBRACE {fprintf(parse_log,"ELIF Statement at line no: %d\n",yylineno);}
              |
              ;


else_statement: ELSE_KW LBRACE statement_list_extended RBRACE {fprintf(parse_log,"ELSE Statement at line no: %d\n",yylineno);}
              |
              ;


while_statement: WHILE_KW LPAREN expression RPAREN LBRACE statement_list_extended RBRACE {fprintf(parse_log,"WHILE Statement at line no: %d\n",yylineno);}
              ;

return_statement: RETURN_KW expression SEMICOLON {fprintf(parse_log,"RETURN Statement at line no: %d\n",yylineno);}
                | RETURN_KW SEMICOLON {fprintf(parse_log,"RETURN Statement at line no: %d\n",yylineno);}
                ;

call_statement: ID LPAREN argument_list RPAREN SEMICOLON {fprintf(parse_log,"CALL Statement at line no: %d\n",yylineno);}
              ;

argument_list: /* empty */
             | expression
             | argument_list COMMA expression
             ;

struct_declaration: STRUCT_KW ID LBRACE struct_body RBRACE SEMICOLON {fprintf(parse_log,"STRUCT Declaration at line no: %d\n",yylineno);}
                  ;

struct_body: struct_variable_declaration
           | struct_body struct_variable_declaration
           ;

struct_variable_declaration: primitive_dtype id_list SEMICOLON
                           | complex_dtype id_list SEMICOLON
                           | set_type id_list SEMICOLON
                           | automata_dtype id_list SEMICOLON
                           ;

function_declaration: function_header LBRACE instruction_list RBRACE {fprintf(parse_log,"FUNCTION Declaration at line no: %d\n",yylineno);}
                     ;

function_header: primitive_dtype ID LPAREN parameter_list RPAREN
               | complex_dtype ID LPAREN parameter_list RPAREN
               | set_type ID LPAREN parameter_list RPAREN
               | automata_dtype ID LPAREN parameter_list RPAREN
               ;

parameter_list: /* empty */
              | parameter
              | parameter_list COMMA parameter
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

#ifdef YYDEBUG
  int yydebug = 1;
#endif

int main(int argc, char **argv) {
    yyin = fopen(argv[1],"r");
    char *test = (char*)malloc(sizeof(char)*100);
    // fscanf(yyin,"%s",test);
    seq_token = fopen("seq_tokens_test.tok","w");
    parse_log = fopen("parser_test.log","w");
    // printf("%s\n",test);
    fflush(stdout);
    yyparse();
    fclose(yyin);
    fclose(seq_token);
    return 0;

}
