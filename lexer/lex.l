%option yylineno

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Defining files
FILE *yyin, *seq_token;
char comment[10000];
int comm_len=0;

// Defining functions
void error();
%}

/*Some standard Definitons*/
letter              [a-zA-Z] 
digit               [0-9]
special_char        ("@"|"#"|"*"|"-"|"+"|"/"|"_"|"\\")
whitespace          (" "|"\t"|"\n")

/*Constants*/
const_int           (({digit}+))
const_float         (({digit}+)"."({digit}+))
const_string        ("\""({special_char}|{digit}|{letter}|" "|"'"|"\\\"")*"\"")
const_char          ("\'"({letter}|{digit}|{special_char})"\'")
const_bool          ("true"|"false")

/*Identifiers*/
id                  (({letter}|"_")({letter}|{digit}|"_")*)

/*Opeartors*/
oper_ari            ("+"|"-"|"*"|"/"|"%"|"@")
oper_bi_log         ("&&"|"||")
oper_un_log         ("!")
oper_comp           ("=="|"!="|"<"|">"|"<="|">=")
oper_asn            ("="|"+="|"-="|"*="|"/="|"%="|"&="|"|=")
operator            ({oper_ari}|{oper_bi_log}|{oper_un_log}|{oper_comp}|{oper_asn})

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
keyword_control     ("if"|"elif"|"else"|"while")
stmt_IO             ("out"|"inp") 
comm_beg            ("<!--")
comm_end            ("--!>")

/*Punctuations*/
/* Note that BRACE: {} BRACKETS: [] PARENTHESIS: () */
brackets            ("(" | ")" | "[" | "]" | "{" | "}")
punctuation         ("," | "." | "->" | ";" | ":")

%x COMMENT

%%

{whitespace}        {
    // Ignoring whitespaces
}


{keyword_control}  {
    fprintf(seq_token,"reserved keyword: %s\n",yytext);
    if(strcmp(yytext,"if")==0 ) {
        // return IF_KW;
    }
    else if(strcmp(yytext,"elif")==0) {
        // return ELIF_KW;
    }
    else if(strcmp(yytext,"else")==0) {
        // return ELSE_KW;
    }
    else if(strcmp(yytext,"while")==0) {
        // return WHILE_KW;
    }
}


{stmt_IO}          {
    // Input and Output statements
    fprintf(seq_token,"reserved keyword: %s\n",yytext);
    if(strcmp(yytext,"out")==0) {
        // return OUT_KW;
    }
    else if(strcmp(yytext,"inp")==0) {
        // return INP_KW;
    }
}

{brackets}         {
    fprintf(seq_token,"punctuation: %s\n",yytext);
    if(strcmp(yytext,"(")==0) {
        // return LPAREN;
    }
    else if(strcmp(yytext,")")==0) {
        // return RPAREN;
    }
    else if(strcmp(yytext,"[")==0) {
        // return LBRACK;
    }
    else if(strcmp(yytext,"]")==0) {
        // return RBRACK;
    }
    else if(strcmp(yytext,"{")==0) {
        // return LBRACE;
    }
    else if(strcmp(yytext,"}")==0) {
        // return RBRACE;
    }
}

{type_standard}     {
    fprintf(seq_token,"datatype: %s\n",yytext);
    if(strcmp(yytext,"int_8")==0) {
        // return INT_8;
    }
    else if(strcmp(yytext,"int_16")==0) {
        // return INT_16;
    }
    else if(strcmp(yytext,"int_32")==0) {
        // return INT_32;
    }
    else if(strcmp(yytext,"int_64")==0) {
        // return INT_64;
    }
    else if(strcmp(yytext,"uint_8")==0) {
        // return UINT_8;
    }
    else if(strcmp(yytext,"uint_16")==0) {
        // return UINT_16;
    }
    else if(strcmp(yytext,"uint_32")==0) {
        // return UINT_32;
    }
    else if(strcmp(yytext,"uint_64")==0) {
        // return UINT_64;
    }
    else if(strcmp(yytext,"float_32")==0) {
        // return FLOAT_32;
    }
    else if(strcmp(yytext,"float_64")==0) {
        // return FLOAT_64;
    }
    else if(strcmp(yytext,"bool")==0) {
        // return BOOL;
    }
    else if(strcmp(yytext,"string")==0) {
        // return STRING;
    }
    else if(strcmp(yytext,"char")==0) {
        // return CHAR;
    }
}

{type_non_standard} {
    fprintf(seq_token,"datatype: %s\n",yytext);
    if(strcmp(yytext,"o_set")==0) {
        // return O_SET;
    }
    else if(strcmp(yytext,"u_set")==0) {
        // return U_SET;
    }
    else if(strcmp(yytext,"regex")==0) {
        // return REGEX;
    }
    else if(strcmp(yytext,"cfg")==0) {
        // return CFG;
    }
    else if(strcmp(yytext,"dfa")==0) {
        // return DFA;
    }
    else if(strcmp(yytext,"nfa")==0) {
        // return NFA;
    }
    else if(strcmp(yytext,"pda")==0) {
        // return PDA;
    }
}

{oper_ari}         {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return OPER_ARI;
}

{oper_bi_log}      {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return OPER_BI_LOG;
}

{oper_un_log}      {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return OPER_UN_LOG;
}

{oper_comp}      {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return OPER_COMP;
}

{oper_asn}      {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return OPER_ASN;
}

{punctuation}      {
    fprintf(seq_token,"punctuation: %s\n",yytext);
    if(strcmp(yytext,";")==0) {
        // return SEMICOLON;
    }
    else if(strcmp(yytext,",")==0) {
        // return COMMA;
    }
    else if(strcmp(yytext,".")==0) {
        // return DOT;
    }
    else if(strcmp(yytext,"->")==0) {
        // return ARROW;
    }
    else if(strcmp(yytext,":")==0) {
        // return COLON;
    }
}

{const_int}         {
    fprintf(seq_token,"int_const: %s\n",yytext);
    // return INT_CONST;
}

{const_float}       {
    fprintf(seq_token,"float_const: %s\n",yytext);
    // return FLOAT_CONST;
}

{const_string}      {
    fprintf(seq_token,"string_const: %s\n",yytext);
    // return STRING_CONST;
}

{const_char}        {
    fprintf(seq_token,"char_const: %s\n",yytext);
    // return CHAR_CONST;
}

{const_bool}        {
    fprintf(seq_token,"bool_const: %s\n",yytext);
    // return BOOL_CONST;
}

{id}                {
    //Here we print the float_const used in the input program.
    fprintf(seq_token,"identifier: %s\n",yytext);
    // return ID;
}

<COMMENT>{comm_beg} {
    yy_push_state(YYSTATE);
    BEGIN COMMENT;
    printf("comment: %s\n",comment);
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
    printf("comment: %s\n",comment);
    comment[comm_len] = yytext[0];
    comment[comm_len+1] = '\0';
    comm_len=comm_len+1;
}

<COMMENT><<EOF>> {
    fprintf(seq_token,"comment: %s\n",comment);
    BEGIN INITIAL;
}


. { error();}

%%

// Function to quit program
void error(){
        char *toprint = "Error at line number: ";
        printf("%s%d\n", toprint, yylineno);
        exit(1);
}

int yywrap() {}
int main(int argc,char *argv[]) { 
  if(argc > 1)
      yyin = fopen(argv[1], "r"); 
      //Taking input file from argv[1]
  else
      yyin = stdin; 
  seq_token = fopen("../test/lexer_tests/easy_tests/tokens/seq_token.txt", "w");

  yylex();

  if(argc > 1)
    fclose(yyin);
  fclose(seq_token);
  return 0;
}