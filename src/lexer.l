%option yylineno
%option noyywrap
%option stack

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tokens.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

#define printtoken(a) fprintf(seq_token,"%s: %s\n",a,yytext)

// Defining files
FILE *seq_token;
char comment[10000];
int comm_len=0;
extern void yyerror(char *str);

// Defining functions
void error();
%}

/*Some standard Definitons*/
letter              [a-zA-Z] 
digit               [0-9]
whitespace          (" "|"\t"|"\n")


single_quote        "'"
epsilon            "\\e"

/*Constants*/
const_int           (({digit}+))
const_float         (({digit}+)"."({digit}+))
str_punct           "\""
const_string        {str_punct}([^"]|"\\\"")*{str_punct}
const_char          {single_quote}([^']|"\\'"){single_quote}
const_bool          ("true"|"false")

/*Identifiers*/
id                  (({letter}|"_")({letter}|{digit}|"_")*)

/*Opertors*/
oper_comp           ("=="|"!="|"<="|">="|"<"|">")
oper_asn            ("+="|"-="|"*="|"/="|"%="|"&="|"|=")

/*Datatypes: Primitive*/
type_sint           ("int_8"|"int_16"|"int_32"|"int_64")
type_uint           ("uint_8"|"uint_16"|"uint_32"|"uint_64")
type_float          ("float_32"|"float_64")
type_bool           ("bool")
type_char           ("char")
type_primitive       ({type_sint}|{type_uint}|{type_float}|{type_bool}|{type_char})

/*Datatypes: Complex*/
type_string         ("string")
type_oset           ("o_set")
type_uset           ("u_set")
type_regex          ("regex")
type_cfg            ("cfg")
type_dfa            ("dfa")
type_nfa            ("nfa")
type_pda            ("pda")

/*Other Keywords*/
comm_beg            ("<!--")
comm_end            ("--!>")

%x COMMENT
%x REGEX

%%

{whitespace}        {/* Ignoring whitespaces */}

if {printtoken("reserved keyword"); return IF_KW;}
elif {printtoken("reserved keyword"); return ELIF_KW;}
else {printtoken("reserved keyword"); return ELSE_KW;}
while {printtoken("reserved keyword"); return WHILE_KW;}
break {printtoken("reserved keyword"); return BREAK_KW;}
struct {printtoken("reserved keyword"); return STRUCT_KW;}
return {printtoken("reserved keyword"); return RETURN_KW;}

"r"/{single_quote}([^']|"\'")*{single_quote}    {
    printtoken("regex_start");
    BEGIN REGEX;
    return REGEX_R;
}

<REGEX>{single_quote}([^']|"\'")*{single_quote}    {
    printtoken("regex");
    BEGIN INITIAL;
    return REGEX_LIT;
}

{const_int} {printtoken("int_const"); return INT_CONST;}
{const_float} {printtoken("float_const"); return FLOAT_CONST;}
{const_string} {printtoken("string_const"); return STRING_CONST;}
{const_char} {printtoken("char_const"); return CHAR_CONST;}
{const_bool} {printtoken("bool_const"); return BOOL_CONST;}

"(" {printtoken("punctuation"); return LPAREN;}
")" {printtoken("punctuation"); return RPAREN;}
"[" {printtoken("punctuation"); return LBRACK;}
"]" {printtoken("punctuation"); return RBRACK;}
"{" {printtoken("punctuation"); return LBRACE;}
"}" {printtoken("punctuation"); return RBRACE;}


{type_primitive}     {
    printtoken("datatype");
    yylval.dtype_primitive = getPrimitiveType(yytext);
    return TYPE_PRIMITIVE;
}

{type_oset} {printtoken("datatype"); return TYPE_OSET;}
{type_uset} {printtoken("datatype"); return TYPE_USET;}
{type_regex} {printtoken("datatype"); return TYPE_REGEX;}
{type_cfg} {printtoken("datatype"); return TYPE_CFG;}
{type_dfa} {printtoken("datatype"); return TYPE_DFA;}
{type_nfa} {printtoken("datatype"); return TYPE_NFA;}
{type_pda} {printtoken("datatype"); return TYPE_PDA;}
{type_string} {printtoken("datatype"); return TYPE_STRING;}

"/" {printtoken("operator"); return OPER_DIV;}
"%" {printtoken("operator"); return OPER_MOD;}
"@" {printtoken("operator"); return AT_THE_RATE;}
"^2" {printtoken("operator"); return OPER_POWER;}
"+" {printtoken("operator"); return OPER_PLUS;}
"*" {printtoken("operator"); return OPER_MUL;}
"-" {printtoken("operator"); return OPER_MINUS;}

"!" {printtoken("operator"); return OPER_NOT;}
"&&" {printtoken("operator"); return OPER_AND;}
"||" {printtoken("operator"); return OPER_OR;}

"<" {printtoken("operator"); return COMP_LT;}
">" {printtoken("operator"); return COMP_GT;}

"=" {printtoken("operator"); return OPER_ASN_SIMPLE;}

{oper_comp} {printtoken("operator"); return OPER_COMP;}
{oper_asn} {printtoken("operator"); return OPER_ASN;}

"#" {printtoken("operator"); return OPER_HASH;}

"," {printtoken("punctuation"); return COMMA;}
"." {printtoken("punctuation"); return DOT;}
"->" {printtoken("punctuation"); return ARROW;}
":" {printtoken("punctuation"); return COLON;}
";" {printtoken("punctuation"); return SEMICOLON;}
"$" {printtoken("punctuation"); return DOLLAR;}
"_" {printtoken("punctuation"); return UNDERSCORE;}
"\\" {printtoken("punctuation"); return BACKSLASH;}

{id} {
    printtoken("identifier");
    yylval.identifier = strdup(yytext);
    return ID;
}

<COMMENT>{comm_beg} {
    printf("Here\n");
    fflush(stdout);
    yy_push_state(YYSTATE);
    BEGIN COMMENT;
    comment[comm_len] = '<';
    comment[comm_len+1] = '!';
    comment[comm_len+2] = '-';
    comment[comm_len+3] = '-';   
    comment[comm_len+4] = '\0';
    comm_len+=4;
}

{comm_beg} {
    yy_push_state(YYSTATE);
    BEGIN COMMENT;
    fprintf(seq_token,"punctuation: %s\n",yytext);
}

<COMMENT>{comm_end} {
    if(yy_top_state()==INITIAL)
    {
        fprintf(seq_token,"comment: %s\n",comment);
        fprintf(seq_token,"punctuation: %s\n",yytext);
        comment[0] = '\0';
        comm_len=0;
    }
    else
    {
        comment[comm_len] = '-';
        comment[comm_len+1] = '-';
        comment[comm_len+2] = '!';
        comment[comm_len+3] = '>';
        comment[comm_len+4] = '\0';
        comm_len+=4;
    }
    yy_pop_state();
}

<COMMENT>(.|"\n") {
    comment[comm_len] = yytext[0];
    comment[comm_len+1] = '\0';
    comm_len=comm_len+1;
}

<COMMENT><<EOF>> {
    fprintf(seq_token,"comment: %s\n",comment);
    BEGIN INITIAL;
}

{epsilon} {printtoken("epsilon"); return EPSILON;}

. { error();}

%%

// Function to quit program
void error(){
        char *toprint = "Error at line number: ";
        fprintf(seq_token,"%s%d\n", toprint, yylineno);
        printf(RED "%s%d\n" RESET, toprint, yylineno);
        exit(1);
}