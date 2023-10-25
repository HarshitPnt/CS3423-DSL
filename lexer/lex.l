%option stack

%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>
  #include <string.h>

  // Defining files
  FILE *yyin, *seq_token;
  char comment[10000];
  int comm_len=0;
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
comm_begin         ("<!--")
comm_end           ("--!>")
%x COMMENT

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


{IO_stmts}          {
//This tells us which keyword is matched by comparing the keyword in the input program to given keywords
    fprintf(seq_token,"reserved keyword: %s\n",yytext);
    if(strcmp(yytext,"out")==0) {
        // return OUT_KW;
    }
    else if(strcmp(yytext,"inp")==0) {
        // return INP_KW;
    }
}


{s_integer}         {
    //This tells us whether matched reserved word is out or inp .
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return S_INT_TYPE;
}


{u_integer}         {
    //Here we print the s_integer type (whether its int_8 or int_16 etc)
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return U_INT_TYPE;
}


{float_type}        {
    //Here we print the u_integer type (whether its uint_8 or uint_16 etc)
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return FLOAT_TYPE;
}


{bool_type}         {
    //Here we print the float_type(whether its float_32 or float_64)
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return BOOL_TYPE;
}


{string_type}       {
    //Here we print the bool_type (bool).
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return STRING_TYPE;
}


{char_type}         {
    //Here we print the string_type (string)
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return CHAR_TYPE;
}


{set_type}          {
    //Here we print the char_type (char).
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return SET_TYPE;
}


{regex_type}        {
    //Here we print the set_type (o_set or u_set).
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return REGEX_TYPE;
}


{cfg_type}          {
    //Here we print the regex_type (regex).
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return CFG_TYPE;
}


{dfa_type}          {
    //Here we print the cfg_type (cfg).
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return DFA_TYPE;
}


{nfa_type}          {
    //Here we print the dfa_type (dfa).
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return NFA_TYPE;
}


{pda_type}          {
    //Here we print the nfa_type (nfa).
    fprintf(seq_token,"datatype: %s\n",yytext);
    // return PDA_TYPE;
}


{ar_ops}            {
    //Here we print the pda_type (pda).
    fprintf(seq_token,"operator: %s\n",yytext);
    // return AR_OPS;
}


{bi_lo_ops}         {
    //Here we print the ar_ops used (whether + or - or * or / or % or @)
    fprintf(seq_token,"operator: %s\n",yytext);
    // return bin_lo_ops;
}


{uni_lo_ops}        {
//Here we print the bi_lo_ops used (whether &&or ||)
    fprintf(seq_token,"operator: %s\n",yytext);
    // return UNI_LO_OPS;
}
{comp_ops}          {
    //Here we print the uni_lo_ops used (!)
    fprintf(seq_token,"operator: %s\n",yytext);
    // return COMP_OPS;
}


{asn_ops}           {
    //Here we print the comp_ops used (whether == or != or < or > or <= or>=)
    fprintf(seq_token,"operator: %s\n",yytext);
    // return ASN_OPS;
}


{bool_const}        {
    //Here we print the ASN_ops used (whether = or += or -= or *= or /= or %= or &= or |=)
    fprintf(seq_token,"boolean constant: %s\n",yytext);
    // return BOOL_CONST;
}


{char_const}        {
    //Here we print the bool_const used in the input program.
    fprintf(seq_token,"character constant: %s\n",yytext);
    // return CHAR_CONST;
}


{string_const}      {
    //Here we print the char_const used in the input program.
    fprintf(seq_token,"string constant: %s\n",yytext);
    // return STRING_CONST;
}   


{int_const}         {
    //Here we print the string_const used in the input program.
    fprintf(seq_token,"integer: %s\n",yytext);
    // return INT_CONST;
}


{float_const}       {
    //Here we print the int_const used in the input program.
    fprintf(seq_token,"float: %s\n",yytext);
    // return FLOAT_CONST;
}


{id}                {
    //Here we print the float_const used in the input program.
    fprintf(seq_token,"identifier: %s\n",yytext);
    // return ID;
}


"," {
    //Here we print the identifier used in the input program.
    fprintf(seq_token,"punctuation: %s\n",yytext);
    // return COMMA;  
}


"."                 {
    //Here we print ',' punctuation symbol when we encounter it in the input program.
    fprintf(seq_token,"operator: %s\n",yytext);
    // return DOT;
}


"->"                {
    //Here we print '.' operator when we encounter it in the input program.
    fprintf(seq_token,"operator: %s\n",yytext);
    // return ARROW;
}


"("                 {
    //Here we print '->' operator when we encounter it in the input program.
    fprintf(seq_token,"left parenthesis: %s\n",yytext);
    // return LBP;
}


")"                 {
    //Here we print '(' (left parentheis) when we encounter it in the input program.
    fprintf(seq_token,"right parenthesis: %s\n",yytext);
    // return RBP;
}


"["                 {
    //Here we print ')' (right parentheis) when we encounter it in the input program.
    fprintf(seq_token,"left square parenthesis: %s\n",yytext);
    // return LSP;
}


"]"                 {
    //Here we print '[' (left square parentheis) when we encounter it in the input program.
    fprintf(seq_token,"right square parenthesis: %s\n",yytext);
    // return RSP;
}


"{"                 {
    //Here we print ']' (right square parentheis) when we encounter it in the input program.
    fprintf(seq_token,"left curly parenthesis: %s\n",yytext);
    // return LCP;
}


"}"                 {
    //Here we print '{' (left curly parentheis) when we encounter it in the input program.
    fprintf(seq_token,"right curly parenthesis: %s\n",yytext);
    // return RCP;
}


";"                 {
    //Here we print '}' (right curly parentheis) when we encounter it in the input program.
    fprintf(seq_token,"punctuation: %s\n",yytext);
    // return SEMICOLON;
}
<COMMENT>{comm_begin} {
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

{comm_begin} {
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

[ ]                 {
    //Here we print ';' punctuation symbol when we encounter it in the input program.
    // Handling empty spaces
}

"\n"                  {
    line_no++;
}
.                   {
//everytime we see a newline we increase line_no by 1 .
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
  seq_token = fopen("../test/lexer_tests/easy_tests/tokens/seq_token.txt", "w");

  yylex();

  if(argc > 1)
    fclose(yyin);
  fclose(seq_token);
  return 0;
}