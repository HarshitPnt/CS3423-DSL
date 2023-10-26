%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

%}

%token IDENTIFIER INTEGER FLOAT STRING

%token INT_8 INT_16 INT_32 INT_64

%token UINT_8 UINT_16 UINT_32 UINT_64

%token FLOAT_32 FLOAT_64

%token BOOL CHAR

%token O_SET U_SET REGEX CFG DFA NFA PDA

%token IF_KW ELIF_KW ELSE_KW WHILE_KW

%token OUT_KW INP_KW

%token ARROW COLON

%token PLUS MINUS MULTIPLY DIVIDE MODULUS

%token LOGICAL_AND LOGICAL_OR LOGICAL_NOT

%token EQUALS NOT_EQUALS LESS_THAN GREATER_THAN LESS_OR_EQUAL GREATER_OR_EQUAL

%token ASSIGNMENT PLUS_ASSIGN MINUS_ASSIGN MULTIPLY_ASSIGN DIVIDE_ASSIGN MODULUS_ASSIGN AND_ASSIGN OR_ASSIGN

%token LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE

%token COMMA DOT SEMICOLON

%token INT_CONST FLOAT_CONST STRING_CONST CHAR_CONST BOOL_CONST

%token REGEX_LITERAL

%token Epsilon


%union {

    char* identifier;
    int int_value;
    float float_value;
    char* string_value;
    char char_value;
    bool bool_value;
    char* regex_literal;
    YAFSMOrderedSet* ordered_set;
    YAFSMUnorderedSet* unordered_set;
    YAFSMStruct* yafsm_struct;

    // Here adding structures for sets, structs, DFAs, NFAs, CFGs, is pending
}

%%

program: statement_list
        ;


statement_list: statement
              | statement_list statement
              ;


statement: variable_declaration
         | assignment_statement
         | expression_statement
         | ordered_set_declaration
         | unordered_set_declaration
         | control_statement
         | input_output_statement
         | comment
         | regex_declaration
         | dfa_declaration
         | nfa_declaration
         | pda_declaration
         ;


variable_declaration: data_type IDENTIFIER SEMICOLON
                  ;


data_type: standard_type
         | non_standard_type
         ;


standard_type: INT_8
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
            | STRING
            | CHAR
            ;


non_standard_type: O_SET
                | U_SET
                | REGEX
                | CFG
                | DFA
                | NFA
                | PDA
                ;


assignment_statement: IDENTIFIER ASSIGNMENT expression SEMICOLON
                  ;


expression_statement: expression SEMICOLON
                  ;


expression: INT_CONST
          | FLOAT_CONST
          | STRING_CONST
          | CHAR_CONST
          | BOOL_CONST
          | IDENTIFIER
          | expression PLUS expression
          | expression MINUS expression
          | expression MULTIPLY expression
          | expression DIVIDE expression
          | expression MODULUS expression
          | expression LOGICAL_AND expression
          | expression LOGICAL_OR expression
          | LOGICAL_NOT expression
          | expression EQUALS expression
          | expression NOT_EQUALS expression
          | expression LESS_THAN expression
          | expression GREATER_THAN expression
          | expression LESS_OR_EQUAL expression
          | expression GREATER_OR_EQUAL expression
          ;



ordered_set_declaration: O_SET '<'ordered_set_type'>' IDENTIFIER SEMICOLON
                    | O_SET '<'ordered_set_type'>' IDENTIFIER ASSIGNMENT ordered_set_values SEMICOLON
                    ;


ordered_set_type: INT_8
            | INT_16
            | INT_32
            | INT_64
            | UINT_8
            | UINT_16
            | UINT_32
            | UINT_64
            | FLOAT_32
            | FLOAT_64
               ;


ordered_set_values: LEFT_CURLY_BRACE ordered_set_value_list RIGHT_CURLY_BRACE
                 ;


ordered_set_value_list: /* empty */
                     | ordered_set_value
                     | ordered_set_value_list COMMA ordered_set_value
                     ;


ordered_set_value: INT_CONST
                   |FLOAT_CONST
                   |CHAR_CONST
                    ;


unordered_set_declaration: U_SET '<'unordered_set_type'>' IDENTIFIER SEMICOLON
                      | U_SET '<'unordered_set_type'>' IDENTIFIER ASSIGNMENT unordered_set_values SEMICOLON
                      ;


unordered_set_type:  INT_8
            | INT_16
            | INT_32
            | INT_64
            | UINT_8
            | UINT_16
            | UINT_32
            | UINT_64
            | FLOAT_32
            | FLOAT_64
                 ;


unordered_set_values: LEFT_CURLY_BRACE unordered_set_value_list RIGHT_CURLY_BRACE
                 ;



unordered_set_value_list: /* empty */
                     | unordered_set_value
                     | unordered_set_value_list COMMA unordered_set_value
                     ;


unordered_set_value: INT_CONST
                   |FLOAT_CONST
                   |CHAR_CONST
                    ;





control_statement: if_statement
                | elif_statement
                | else_statement
                | while_statement
                ;


if_statement: IF_KW LEFT_PAREN expression RIGHT_PAREN LEFT_CURLY_BRACE statement_list RIGHT_CURLY_BRACE
           ;


elif_statement: ELIF_KW LEFT_PAREN expression RIGHT_PAREN LEFT_CURLY_BRACE statement_list RIGHT_CURLY_BRACE
             ;


else_statement: ELSE_KW LEFT_CURLY_BRACE statement_list RIGHT_CURLY_BRACE
             ;


while_statement: WHILE_KW LEFT_PAREN expression RIGHT_PAREN LEFT_CURLY_BRACE statement_list RIGHT_CURLY_BRACE
              ;


input_output_statement: OUT_KW IDENTIFIER SEMICOLON
                    | INP_KW IDENTIFIER SEMICOLON
                    ;


comment: COMMENT
       ;


regex_declaration: REGEX IDENTIFIER ASSIGNMENT REGEX_LITERAL SEMICOLON
               ;



//State machines ,comment , struct yet to handled .
//check lex return of <, >
//check lex return of ( ->LEFT_PAREN )->RIGHT_PAREN
//check lex return of {->LEFT_CURLY_BRACE }->RIGHT_CURLY_BRACE
%%

void yyerror(const char *s) {

    fprintf(stderr, "Parser error: %s\n", s);

}

int main() {

    yyparse();
    return 0;

}
