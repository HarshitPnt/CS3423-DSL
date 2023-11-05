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
special_char        ("@"|"#"|"*"|"-"|"+"|"/"|"_"|"\\")
whitespace          (" "|"\t"|"\n")

/*Punctuations*/
/* Note that BRACE: {} BRACKETS: [] PARENTHESIS: () */
brackets            "("|")"|"["|"]"|"{"|"}"
punctuation         ","|"."|"->"|";"|":"|"$"
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

/*Opeartors*/
oper_ari            ("/"|"%")
oper_auto           ("@")
oper_set            ("^2")
oper_ovr_auto_set_ari ("+"|"*")
oper_ovr_set_ari    ("-")
oper_ovr_log_auto   ("!")
oper_bi_log         ("&&"|"||")
oper_comp           ("=="|"!="|"<="|">="|"<"|">")
oper_asn            ("+="|"-="|"*="|"/="|"%="|"&="|"|=")
oper_asn_simple     ("=")

/*Datatypes: Standard*/
type_sint           ("int_8"|"int_16"|"int_32"|"int_64")
type_uint           ("uint_8"|"uint_16"|"uint_32"|"uint_64")
type_float          ("float_32"|"float_64")
type_bool           ("bool")
type_string         ("string")
type_char           ("char")
type_standard       ({type_sint}|{type_uint}|{type_float}|{type_bool}|{type_string}|{type_char})

/*Datatypes: Non-Standard*/
type_oset           ("o_set")
type_uset           ("u_set")
type_regex          ("regex")
type_cfg            ("cfg")
type_dfa            ("dfa")
type_nfa            ("nfa")
type_pda            ("pda")
type_non_standard   ({type_oset}|{type_uset}|{type_regex}|{type_cfg}|{type_dfa}|{type_nfa}|{type_pda})

/*Other Keywords*/
comm_beg            ("<!--")
comm_end            ("--!>")

%x COMMENT
%x REGEX
%x REGEX_START
%x REGEX_LIMIT
%x REGEX_SQ
%x REGEX_RANGE
%x REGEX_VAR

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
    fprintf(seq_token,"regex: %s\n",yytext);
    BEGIN REGEX;
    return REGEX_R;
}

<REGEX>{single_quote} {
    fprintf(seq_token,"punctuation: %s\n",yytext);
    BEGIN REGEX_START;
    return SIN_QUOTE;
}


<REGEX_START>{single_quote} {
    fprintf(seq_token,"punctuation: %s\n",yytext);
    BEGIN INITIAL;
    return SIN_QUOTE;
}

<REGEX_START>{letter}|{whitespace} {
    fprintf(seq_token,"regex_lit: %s\n",yytext);
    return REGEX_LIT;
}

<REGEX_START>{digit}+ {
    fprintf(seq_token,"regex_num: %s\n",yytext);
    return REGEX_LIT;
}

<REGEX_START>"|" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    return REGEX_OR;
}

<REGEX_START>"*" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    return REGEX_STAR;
}

<REGEX_START>"+" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    return REGEX_PLUS;
}

<REGEX_START>"?" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    return REGEX_QUE;
}

<REGEX_START>"^" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    return REGEX_CARET;
}

<REGEX_START>"(" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    return LPAREN;
}

<REGEX_START>")" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    return RPAREN;
}

<REGEX_START>"{"/{digit}+","?({digit}+)?"}" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_LIMIT;
    return LBRACE;
}

<REGEX_LIMIT>{digit}+ {
    fprintf(seq_token,"regex_num: %s\n",yytext);
    return REGEX_NUM;
}

<REGEX_LIMIT>"," {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    return COMMA;
}

<REGEX_LIMIT>"}" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_START;
    return RBRACE;
}

<REGEX_START>"["/(("^")?[^\]']|"\\]")+"]" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_SQ;
    return LBRACK;
}

<REGEX_START>"[" {
    printf("Error at line no: %d\n",yylineno);
    exit(1);
}

<REGEX_SQ>"^" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    return REGEX_CARET;
}

<REGEX_SQ>{letter}|{digit}/("-"{letter}|{digit}) {
    fprintf(seq_token,"regex_lit: %s\n",yytext);
    BEGIN REGEX_RANGE;
    return REGEX_LRANGE;
}

<REGEX_RANGE>"-" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    return REGEX_HYPHEN;
}

<REGEX_RANGE>{letter}|{digit} {
    fprintf(seq_token,"regex_lit: %s\n",yytext);
    BEGIN REGEX_SQ;
    return REGEX_RRANGE;
}

<REGEX_SQ>"]" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_START;
    return RBRACK;
}

<REGEX_SQ>"$"/"{"{id}"}" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    yy_push_state(YYSTATE);
    BEGIN REGEX_VAR;
    return REGEX_DOLLAR;
}

<REGEX_START,REGEX_SQ>"\\("|"\\)"|"\\{"|"\\}"|"\\["|"\\]"|"\\|"|"\\*"|"\\+"|"\\?"|"\\^"|"\\$"|"\\\\"|{digit}|{letter}|{whitespace}|{special_char}|{brackets} {
    fprintf(seq_token,"regex_lit: %s\n",yytext);
    return REGEX_LIT;
}

<REGEX_START>"$"/"{"{id}"}" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    yy_push_state(YYSTATE);
    BEGIN REGEX_VAR;
    return REGEX_DOLLAR;
}
<REGEX_START>"$"/"'" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    return REGEX_DOLLAR;
}

<REGEX_START>"$" {
    printf("Error at line no: %d\n",yylineno);
    exit(1);
}

<REGEX_VAR>"{" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    return LBRACE;
}

<REGEX_VAR>{id} {
    fprintf(seq_token,"regex_var: %s\n",yytext);
    return ID;
}

<REGEX_VAR>"}" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    yy_pop_state();
    return RBRACE;
}

<REGEX_START,REGEX_LIMIT,REGEX_SQ,REGEX_RANGE,REGEX_VAR>. {
    fprintf(seq_token,"regex pattern error: %s\n",yytext);
    printf(RED "Error at line number: %d\n" RESET, yylineno);
    exit(1);
}

"(" {printtoken("punctuation"); return LPAREN;}
")" {printtoken("punctuation"); return RPAREN;}
"[" {printtoken("punctuation"); return LBRACK;}
"]" {printtoken("punctuation"); return RBRACK;}
"{" {printtoken("punctuation"); return LBRACE;}
"}" {printtoken("punctuation"); return RBRACE;}


{type_standard}     {
    fprintf(seq_token,"datatype: %s\n",yytext);
    if(strcmp(yytext,"int_8")==0) {
        return INT_8;
    }
    else if(strcmp(yytext,"int_16")==0) {
        return INT_16;
    }
    else if(strcmp(yytext,"int_32")==0) {
        return INT_32;
    }
    else if(strcmp(yytext,"int_64")==0) {
        return INT_64;
    }
    else if(strcmp(yytext,"uint_8")==0) {
        return UINT_8;
    }
    else if(strcmp(yytext,"uint_16")==0) {
        return UINT_16;
    }
    else if(strcmp(yytext,"uint_32")==0) {
        return UINT_32;
    }
    else if(strcmp(yytext,"uint_64")==0) {
        return UINT_64;
    }
    else if(strcmp(yytext,"float_32")==0) {
        return FLOAT_32;
    }
    else if(strcmp(yytext,"float_64")==0) {
        return FLOAT_64;
    }
    else if(strcmp(yytext,"bool")==0) {
        return BOOL;
    }
    else if(strcmp(yytext,"string")==0) {
        return STRING;
    }
    else if(strcmp(yytext,"char")==0) {
        return CHAR;
    }
}

{type_non_standard} {
    fprintf(seq_token,"datatype: %s\n",yytext);
    if(strcmp(yytext,"o_set")==0) {
        return O_SET;
    }
    if(strcmp(yytext,"u_set")==0) {
        return U_SET;
    }
    if(strcmp(yytext,"regex")==0) {
        return REG;
    }
    if(strcmp(yytext,"cfg")==0) {
        return CFG;
    }
    if(strcmp(yytext,"dfa")==0) {
        return DFA;
    }
    if(strcmp(yytext,"nfa")==0) {
        return NFA;
    }
    if(strcmp(yytext,"pda")==0) {
        return PDA;
    }
}

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

{const_int} {printtoken("int_const"); return INT_CONST;}
{const_float} {printtoken("float_const"); return FLOAT_CONST;}
{const_string} {printtoken("string_const"); return STRING_CONST;}
{const_char} {printtoken("char_const"); return CHAR_CONST;}
{const_bool} {printtoken("bool_const"); return BOOL_CONST;}

{id} {printtoken("identifier"); return ID;}

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