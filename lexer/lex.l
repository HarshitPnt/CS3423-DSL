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

letter              [a-zA-Z] //This deals with a single character
digit               [0-9]//This deals with a single digit
special_char        ("@"|"#"|"*"|"-"|"+"|"/"|"_"|"\\")
int_const           (({digit}+))//This takes cares of integer nkumbers
float_const         (({digit}+)"."({digit}+))//This takes care of real numbers.It has decimal in it and integers on both side of it.
string_const        ("\""({special_char}|{digit}|{letter}|" "|"'"|"\\\"")*"\"")//This takes care of string .
char_const          ("\'"({letter}|{digit}|{special_char})"\'")
reserved_keyword    ("if"|"elif"|"else"|"while")
IO_stmts            ("out"|"inp") //reserved keywords of input and output
bool_const          ("true"|"false")//Bool values true and false
s_integer           ("int_8"|"int_16"|"int_32"|"int_64") //This takes care of int_64,int_32,int_16,int_8 datatypes.
u_integer           ("uint_8"|"uint_16"|"uint_32"|"uint_64")//This takes care of uint_64,uint_32,uint_16,uint_8 datatypes.
float_type          ("float_32"|"float_64")//This takes care of float_64,float_32 datatypes.
bool_type           ("bool")
string_type         ("string")
char_type           ("char")
set_type            ("o_set"|"u_set")
regex_type          ("regex")
cfg_type            ("cfg")
dfa_type            ("dfa")
nfa_type            ("nfa")
pda_type            ("pda")
id                  (({letter}|"_")({letter}|{digit}|"_")*)//This takes care of identifiers .They start with letter or underscore and can be followed by multiple digits,letter and underscores
ar_ops              ("+"|"-"|"*"|"/"|"%"|"@")
bi_lo_ops           ("&&"|"||")
uni_lo_ops          ("!")
comp_ops            ("=="|"!="|"<"|">"|"<="|">=")
asn_ops             ("="|"+="|"-="|"*="|"/="|"%="|"&="|"|=")

%%

{reserved_keyword}  {
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

 //This tells us which keyword is matched by comparing the keyword in the input program to given keywords

{IO_stmts}          {
    fprintf(seq_token,"reserved keyword: %s\n",yytext);
    if(strcmp(yytext,"out")==0) {
        // return OUT_KW;
    }
    else if(strcmp(yytext,"inp")==0) {
        // return INP_KW;
    }
}

//Thi tells us whether matched reserved word is out or inp .

{s_integer}         {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return S_INT_TYPE;
}

//Here we print the s_integer type (whether its int_8 or int_16 etc)

{u_integer}         {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return U_INT_TYPE;
}

//Here we print the u_integer type (whether its uint_8 or uint_16 etc)

{float_type}        {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return FLOAT_TYPE;
}

//Here we print the float_type(whether its float_32 or float_64)

{bool_type}         {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return BOOL_TYPE;
}

//Here we print the bool_type (bool).

{string_type}       {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return STRING_TYPE;
}

//Here we print the string_type (string)

{char_type}         {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return CHAR_TYPE;
}

//Here we print the char_type (char).

{set_type}          {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return SET_TYPE;
}

//Here we print the set_type (o_set or u_set).

{regex_type}        {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return REGEX_TYPE;
}

//Here we print the regex_type (regex).

{cfg_type}          {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return CFG_TYPE;
}

//Here we print the cfg_type (cfg).

{dfa_type}          {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return DFA_TYPE;
}

//Here we print the dfa_type (dfa).

{nfa_type}          {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return NFA_TYPE;
}

//Here we print the nfa_type (nfa).

{pda_type}          {
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return PDA_TYPE;
}

//Here we print the pda_type (pda).

{ar_ops}            {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return AR_OPS;
}

//Here we print the ar_ops used (whether + or - or * or / or % or @)

{bi_lo_ops}         {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return bin_lo_ops;
}

//Here we print the bi_lo_ops used (whether &&or ||)

{uni_lo_ops}        {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return UNI_LO_OPS;
}
//Here we print the uni_lo_ops used (!)
{comp_ops}          {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return COMP_OPS;
}

//Here we print the comp_ops used (whether == or != or < or > or <= or>=)

{asn_ops}           {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return ASN_OPS;
}

//Here we print the ASN_ops used (whether = or += or -= or *= or /= or %= or &= or |=)

{bool_const}        {
    fprintf(seq_token,"boolean constant: %s\n",yytext);
    // return BOOL_CONST;
}

//Here we print the bool_const used in the input program.

{char_const}        {
    fprintf(seq_token,"character constant: %s\n",yytext);
    // return CHAR_CONST;
}

//Here we print the char_const used in the input program.

{string_const}      {
    fprintf(seq_token,"string constant: %s\n",yytext);
    // return STRING_CONST;
}   

//Here we print the string_const used in the input program.

{int_const}         {
    fprintf(seq_token,"integer: %s\n",yytext);
    // return INT_CONST;
}

//Here we print the int_const used in the input program.

{float_const}       {
    fprintf(seq_token,"float: %s\n",yytext);
    // return FLOAT_CONST;
}

//Here we print the float_const used in the input program.

{id}                {
    fprintf(seq_token,"identifier: %s\n",yytext);
    // return ID;
}

//Here we print the identifier used in the input program.

","                 {
    fprintf(seq_token,"punctuation: %s\n",yytext);
    // return COMMA;  
}

//Here we print ',' punctuation symbol when we encounter it in the input program.

"."                 {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return DOT;
}

//Here we print '.' operator when we encounter it in the input program.

"->"                {
    fprintf(seq_token,"operator: %s\n",yytext);
    // return ARROW;
}

//Here we print '->' operator when we encounter it in the input program.

"("                 {
    fprintf(seq_token,"left parenthesis: %s\n",yytext);
    // return LBP;
}

//Here we print '(' (left parentheis) when we encounter it in the input program.

")"                 {
    fprintf(seq_token,"right parenthesis: %s\n",yytext);
    // return RBP;
}

//Here we print ')' (right parentheis) when we encounter it in the input program.

"["                 {
    fprintf(seq_token,"left square parenthesis: %s\n",yytext);
    // return LSP;
}

//Here we print '[' (left square parentheis) when we encounter it in the input program.

"]"                 {
    fprintf(seq_token,"right square parenthesis: %s\n",yytext);
    // return RSP;
}

//Here we print ']' (right square parentheis) when we encounter it in the input program.

"{"                 {
    fprintf(seq_token,"left curly parenthesis: %s\n",yytext);
    // return LCP;
}

//Here we print '{' (left curly parentheis) when we encounter it in the input program.

"}"                 {
    fprintf(seq_token,"right curly parenthesis: %s\n",yytext);
    // return RCP;
}

//Here we print '}' (right curly parentheis) when we encounter it in the input program.

";"                 {
    fprintf(seq_token,"punctuation: %s\n",yytext);
    // return SEMICOLON;
}

//Here we print ';' punctuation symbol when we encounter it in the input program.

[ ]                 {
    // Handling empty spaces
}

\n                  {
    line_no++;
}
//everytime we see a newline we increase line_no by 1 .
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
      //Taking input file from argv[1]
  else
      yyin = stdin; 
  seq_token = fopen("../test/seq_token.txt", "w");

  yylex();

  if(argc > 1)
    fclose(yyin);
  fclose(seq_token);
  return 0;
}