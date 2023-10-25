%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "y.tab.h"
    // maintaining line number for error statement
    int line_no = 0;
%} 

letter              [a-zA-Z]
digit               [0-9]
special_char        ("@"|"#"|"*"|"-"|"+"|"/"|"_"|"\\")

id                  (({letter}|"_")({letter}|{digit}|"_")*)

int_const           (({digit}+))
float_const         (({digit}+)"."({digit}+))
string_const        ("\""({special_char}|{digit}|{letter}|" "|"'"|"\\\"")*"\"")
char_const          ("\'"({letter}|{digit}|{special_char})"\'")
bool_const          ("true"|"false")

s_integer           ("int_8","int_16","int_32","int_64")
u_integer           ("uint_8","uint_16","uint_32","uint_64")
float_type          ("float_32","float_64")
bool_type           ("bool")
string_type         ("string")
char_type           ("char")
set_type            ("o_set","u_set")
regex_type          ("regex")
cfg_type            ("cfg")
dfa_type            ("dfa")
nfa_type            ("nfa")
pda_type            ("pda")

ar_ops              ("+","-","*","/","%","@")
bi_lo_ops           ("&&","||")
uni_lo_ops          ("!")
comp_ops            ("==","!=","<",">","<=",">=")
asn_ops             ("=","+=","-=","*=","/=","%=","&=","|=")

reserved_keyword    ("if","elif","else","while")
IO_stmts            ("out","inp")

%%

{reserved_keyword}  {
    // Handling reserved keywords
    fprintf(seq_token,"reserved keyword: %s\n",yytext);
    if(strcmp(yytext,"if")==0) {
        return IF_KW;
    }
    else if(strcmp(yytext,"elif")==0) {
        return ELIF_KW;
    }
    else if(strcmp(yytext,"else")==0) {
        return ELSE_KW;
    }
    else if(strcmp(yytext,"while")==0) {
        return WHILE_KW;
    }
}

{IO_stmts}          {
    // Handling IO statements
    fprintf(seq_token,"reserved keyword: %s\n",yytext);
    if(strcmp(yytext,"out")==0) {
        return OUT_KW;
    }
    else if(strcmp(yytext,"inp")==0) {
        return INP_KW;
    }
}

s_integer           {
    // Handling signed integers
    fprintf(seq_token,"datatype: %s\n",yytext);
    return DATATYPE;
}

u_integer           {
    // Handling unsigned integers
    fprintf(seq_token,"datatype: %s\n",yytext);
    return DATATYPE;
}

float_type          {
    // Handling float type
    fprintf(seq_token,"datatype: %s\n",yytext);
    return DATATYPE;
}

bool_type           {
    // Handling bool type
    fprintf(seq_token,"datatype: %s\n",yytext);
    return DATATYPE;
}

string_type         {
    // Handling string type
    fprintf(seq_token,"datatype: %s\n",yytext);
    return DATATYPE;
}

char_type           {
    // Handling char type
    fprintf(seq_token,"datatype: %s\n",yytext);
    return DATATYPE;
}

set_type            {
    // Handling set type
    fprintf(seq_token,"datatype: %s\n",yytext);
    return SET_TYPE;
}

regex_type          {
    // Handling regex type
    fprintf(seq_token,"datatype: %s\n",yytext);
    return REGEX_TYPE;
}

cfg_type            {
    // Handling cfg type
    fprintf(seq_token,"datatype: %s\n",yytext);
    return CFG_TYPE;
}

dfa_type            {
    // Handling dfa type
    fprintf(seq_token,"datatype: %s\n",yytext);
    return DFA_TYPE;
}

nfa_type            {
    // Handling nfa type
    fprintf(seq_token,"datatype: %s\n",yytext);
    return NFA_TYPE;
}

pda_type            {
    // Handling pda type
    fprintf(seq_token,"datatype: %s\n",yytext);
    return PDA_TYPE;
}

ar_ops              {
    // Handling arithmetic operators
    fprintf(seq_token,"operator: %s\n",yytext);
    return AR_OPS;
}

bi_lo_ops           {
    // Handling binary logical operators
    fprintf(seq_token,"operator: %s\n",yytext);
    return bin_lo_ops;
}

uni_lo_ops          {
    // Handling unary logical operators
    fprintf(seq_token,"operator: %s\n",yytext);
    return unary_lo_ops;
}

comp_ops            {
    // Handling comparison operators
    fprintf(seq_token,"operator: %s\n",yytext);
    return compa_ops;
}

asn_ops             {
    // Handling assignment operators
    fprintf(seq_token,"operator: %s\n",yytext);
    return assign_ops;
}

bool_const          {
    //  Handling boolean constants
    fprintf(seq_token,"boolean constant: %s\n",yytext);
    return bool_const;
}

char_const          {
    // Handling character constants
    fprintf(seq_token,"character constant: %s\n",yytext);
    return char_const;
}

string_const        {
    // Handling string constants
    fprintf(seq_token,"string constant: %s\n",yytext);
    return string_const;
}   

int_const             {
    // Handling integers
    fprintf(seq_token,"integer: %s\n",yytext);
    return int_const;
}

float_const         {
    // Handling floats
    fprintf(seq_token,"float: %s\n",yytext);
    return float_const;
}

id                  {
    // Handling identifiers
    fprintf(seq_token,"identifier: %s\n",yytext);
    return ID;
}

"."                 {
    // Handling dot operator
    fprintf(seq_token,"operator: %s\n",yytext);
    return DOT;
}

"->"                {
    // Handling arrow operator
    fprintf(seq_token,"operator: %s\n",yytext);
    return ARROW;
}

"("                 {
    // Handling left parenthesis
    fprintf(seq_token,"left parenthesis: %s\n",yytext);
    return LBP;
}

")"                 {
    // Handling right parenthesis
    fprintf(seq_token,"right parenthesis: %s\n",yytext);
    return RBP;
}

"["                 {
    // Handling left square parenthesis
    fprintf(seq_token,"left square parenthesis: %s\n",yytext);
    return LSP;
}

"]"                 {
    // Handling right square parenthesis
    fprintf(seq_token,"right square parenthesis: %s\n",yytext);
    return RSP;
}

"{"                 {
    // Handling left curly parenthesis
    fprintf(seq_token,"left curly parenthesis: %s\n",yytext);
    return LCP;
}

"}"                 {
    // Handling right curly parenthesis
    fprintf(seq_token,"right curly parenthesis: %s\n",yytext);
    return RCP;
}


[ ]                 {
    // Handlling empty spaces
}

\n                  {
    // Handling new lines
    line_no++;
}

.                   {
    // Handling Error in lex part
    fprintf(seq_token,"Aborted\n");
    fprintf(seq_token,"Lexical Error at line number : %d : %s\n",yylineno,yytext);
    return 0;
}

%%

int yywrap() {}
int main(int argc,char *argv[]) { 
    extern FILE *yyin, *seq_token;
    if(argc > 1)
        yyin = fopen(argv[1], "r");
    else
        yyin = stdin; 
    seq_token = fopen("../Tests/seq_token.txt", "w");

    yylex();

    if(argc > 1)
        fclose(yyin);
    fclose(seq_token);
    return 0;
}