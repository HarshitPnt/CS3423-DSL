%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "y.tab.h"
    FILE *seq_token, *copy, *yyout;
    // buffer to store the last line
    char *buffer;
    // maintaining line number for error statement
    int line_no = 0;
%} 

letter              [a-zA-Z]
digit               [0-9]
special_char        ("@"|"#"|"*"|"-"|"+"|"/"|"_"|"\\")

id                  (({letter}|"_")({letter}|{digit}|"_")*)

p_integer           (({digit}+))
integer             (("-"{digit}+)|{digit}+)
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
    fprintf(seq_token,"reserved keyword: %s\n",yytext);
    if(strcmp(yytext,"if")==0) {
        return if_kw;
    }
    else if(strcmp(yytext,"elif")==0) {
        return elif_kw;
    }
    else if(strcmp(yytext,"else")==0) {
        return else_kw;
    }
    else if(strcmp(yytext,"while")==0) {
        return while_kw;
    }
}

{IO_stmts}          {
    fprintf(seq_token,"reserved keyword: %s\n",yytext);
    if(strcmp(yytext,"out")==0) {
        return out_kw;
    }
    else if(strcmp(yytext,"inp")==0) {
        return inp_kw;
    }
}

s_integer           {
    // Handling signed integers
    fprintf(yyout,"%s",yytext);
    fprintf(seq_token,"datatype: %s\n",yytext);
    return s_int_type;
}

u_integer           {
    // Handling unsigned integers
    fprintf(yyout,"%s",yytext);
    fprintf(seq_token,"datatype: %s\n",yytext);
    return u_int_type;
}

float_type          {
    // Handling float type
    fprintf(yyout,"%s",yytext);
    fprintf(seq_token,"datatype: %s\n",yytext);
    return float    _type;
}

bool_type           {
    // Handling bool type
    fprintf(yyout,"%s",yytext);
    fprintf(seq_token,"datatype: %s\n",yytext);
    return datatype;
}

string_type         {
    // Handling string type
    fprintf(yyout,"%s",yytext);
    fprintf(seq_token,"datatype: %s\n",yytext);
    return datatype;
}

char_type           {
    // Handling char type
    fprintf(yyout,"%s",yytext);
    fprintf(seq_token,"datatype: %s\n",yytext);
    return datatype;
}

set_type            {
    // Handling set type
    fprintf(yyout,"%s",yytext);
    fprintf(seq_token,"datatype: %s\n",yytext);
    return datatype;
}

regex_type          {
    // Handling regex type
    fprintf(yyout,"%s",yytext);
    fprintf(seq_token,"datatype: %s\n",yytext);
    return datatype;
}

cfg_type            {
    // Handling cfg type
    fprintf(yyout,"%s",yytext);
    fprintf(seq_token,"datatype: %s\n",yytext);
    return datatype;
}

dfa_type            {
    // Handling dfa type
    fprintf(yyout,"%s",yytext);
    fprintf(seq_token,"datatype: %s\n",yytext);
    return datatype;
}

nfa_type            {
    // Handling nfa type
    fprintf(yyout,"%s",yytext);
    fprintf(seq_token,"datatype: %s\n",yytext);
    return datatype;
}

pda_type            {
    // Handling pda type
    fprintf(yyout,"%s",yytext);
    fprintf(seq_token,"datatype: %s\n",yytext);
    return datatype;
}



[ ]                 {
    // Handlling empty spaces
    fprintf(yyout,"%s",yytext);
}

\n                  {
    // Handling m=new lines
    fprintf(yyout,"%s",yytext);
    line_no++;
    // storing newline in the buffer
    if(fgets(buffer, 255, copy)) {
    }
}

.                   {
    // Handling Error in lex part
    fprintf(seq_token,"Aborted\n");
    fprintf(seq_token,"Lexical Error at line number : %d : %s\n",yylineno,yytext);
    return 0;
}

%%

int yywrap() {}