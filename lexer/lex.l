%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>
  #include <string.h>

  // Defining files
  FILE *yyin, *seq_token;

  // maintaining line number for error statement
  int line_no = 0;
%} 

letter              [a-zA-Z]
digit               [0-9]
special_char        ("@"|"#"|"*"|"-"|"+"|"/"|"_"|"\\")
int_const           (({digit}+))
float_const         (({digit}+)"."({digit}+))
string_const        ("\""({special_char}|{digit}|{letter}|" "|"'"|"\\\"")*"\"")
char_const          ("\'"({letter}|{digit}|{special_char})"\'")
reserved_keyword    ("if"|"elif"|"else"|"while")
IO_stmts            ("out"|"inp")
bool_const          ("true"|"false")
s_integer           ("int_8"|"int_16"|"int_32"|"int_64")
u_integer           ("uint_8"|"uint_16"|"uint_32"|"uint_64")
float_type          ("float_32"|"float_64")
bool_type           ("bool")
string_type         ("string")
char_type           ("char")
set_type            ("o_set"|"u_set")
regex_type          ("regex")
cfg_type            ("cfg")
dfa_type            ("dfa")
nfa_type            ("nfa")
pda_type            ("pda")
id                  (({letter}|"_")({letter}|{digit}|"_")*)
ar_ops              ("+"|"-"|"*"|"/"|"%"|"@")
bi_lo_ops           ("&&"|"||")
uni_lo_ops          ("!")
comp_ops            ("=="|"!="|"<"|">"|"<="|">=")
asn_ops             ("="|"+="|"-="|"*="|"/="|"%="|"&="|"|=")

%%

{reserved_keyword}  {
    fprintf(seq_token,"reserved keyword: %s\n",yytext);
    if(strcmp(yytext,"if")==0) {
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

{IO_stmts}          {
    fprintf(seq_token,"reserved keyword: %s\n",yytext);
    if(strcmp(yytext,"out")==0) {
        // return OUT_KW;
    }
    else if(strcmp(yytext,"inp")==0) {
        // return INP_KW;
    }
}

{s_integer}         {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return S_INT_TYPE;
}

{u_integer}         {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return U_INT_TYPE;
}

{float_type}        {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return FLOAT_TYPE;
}

{bool_type}         {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return BOOL_TYPE;
}

{string_type}       {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return STRING_TYPE;
}

{char_type}         {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return CHAR_TYPE;
}

{set_type}          {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return SET_TYPE;
}

{regex_type}        {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return REGEX_TYPE;
}

{cfg_type}          {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return CFG_TYPE;
}

{dfa_type}          {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return DFA_TYPE;
}

{nfa_type}          {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return NFA_TYPE;
}

{pda_type}          {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return PDA_TYPE;
}

{ar_ops}            {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return AR_OPS;
}

{bi_lo_ops}         {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return bin_lo_ops;
}

{uni_lo_ops}        {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return UNI_LO_OPS;
}

{comp_ops}          {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return COMP_OPS;
}

{asn_ops}           {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return ASN_OPS;
}

{bool_const}        {
    fprintf(seq_token,"boolean constant: %s\n",yytext);
    // return BOOL_CONST;
}

{char_const}        {
    fprintf(seq_token,"character constant: %s\n",yytext);
    // return CHAR_CONST;
}

{string_const}      {
    fprintf(seq_token,"string constant: %s\n",yytext);
    // return STRING_CONST;
}   

{int_const}         {
    fprintf(seq_token,"integer: %s\n",yytext);
    // return INT_CONST;
}

{float_const}       {
    fprintf(seq_token,"float: %s\n",yytext);
    // return FLOAT_CONST;
}

{id}                {
    fprintf(seq_token,"identifier: %s\n",yytext);
    // return ID;
}

","                 {
    fprintf(seq_token,"punctuation: %s\n",yytext);
    // return COMMA;  
}

"."                 {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return DOT;
}

"->"                {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return ARROW;
}

"("                 {
    fprintf(seq_token,"left parenthesis: %s\n",yytext);
    // return LBP;
}

")"                 {
    fprintf(seq_token,"right parenthesis: %s\n",yytext);
    // return RBP;
}

"["                 {
    fprintf(seq_token,"left square parenthesis: %s\n",yytext);
    // return LSP;
}

"]"                 {
    fprintf(seq_token,"right square parenthesis: %s\n",yytext);
    // return RSP;
}

"{"                 {
    fprintf(seq_token,"left curly parenthesis: %s\n",yytext);
    // return LCP;
}

"}"                 {
    fprintf(seq_token,"right curly parenthesis: %s\n",yytext);
    // return RCP;
}

";"                 {
    fprintf(seq_token,"punctuation: %s\n",yytext);
    // return SEMICOLON;
}

[ ]                 {
    // Handling empty spaces
}

\n                  {
    line_no++;
}

.                   {
    fprintf(seq_token,"Aborted\n");
    fprintf(seq_token,"Lexical Error at line number : %d : %s\n",yylineno,yytext);
    return 0;
}

%%

int yywrap() {}
int main(int argc,char *argv[]) { 
  if(argc > 1)
      yyin = fopen(argv[1], "r");
  else
      yyin = stdin; 
  seq_token = fopen("../test/seq_token.txt", "w");

  yylex();

  if(argc > 1)
    fclose(yyin);
  fclose(seq_token);
  return 0;
}