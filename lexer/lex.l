%option yylineno
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
punctuation         ","|"."|"->"|";"|":"
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
stmt_IO             "out"|"inp"
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

"r"/{single_quote}([^']|"\'")*{single_quote}    {
    fprintf(seq_token,"regex: %s\n",yytext);
    BEGIN REGEX;
    //return REGEX;
}

<REGEX>{single_quote} {
    fprintf(seq_token,"punctuation: %s\n",yytext);
    BEGIN REGEX_START;
    //return SIN_QUOTE;
}


<REGEX_START>{single_quote} {
    fprintf(seq_token,"punctuation: %s\n",yytext);
    BEGIN INITIAL;
    // return SIN_QUOTE;
}

<REGEX_START>{letter}|{whitespace} {
    fprintf(seq_token,"regex_lit: %s\n",yytext);
    // return REGEX_LIT;
}

<REGEX_START>{digit}+ {
    fprintf(seq_token,"regex_num: %s\n",yytext);
    // return REGEX_NUM;
}

<REGEX_START>"|" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_OR;
}

<REGEX_START>"*" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_STAR;
}

<REGEX_START>"+" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_PLUS;
}

<REGEX_START>"?" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_QUE;
}

<REGEX_START>"^" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_CARET;
}

<REGEX_START>"$" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_DOLLAR;
} 

<REGEX_START>"(" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return LPAREN;
}

<REGEX_START>")" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return RPAREN;
}

<REGEX_START>"{"/{digit}+","?({digit}+)?"}" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_LIMIT;
    // return LBRACE;
}

<REGEX_LIMIT>{digit}+ {
    fprintf(seq_token,"regex_num: %s\n",yytext);
    // return REGEX_NUM;
}

<REGEX_LIMIT>"," {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return COMMA;
}

<REGEX_LIMIT>"}" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_START;
    // return RBRACE;
}

<REGEX_START>"["/(("^")?[^\]]|"\\]")+"]" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_SQ;
    // return REGEX_LBRACK;
}
<REGEX_SQ>"^" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_CARET;
}

<REGEX_SQ>{letter}/("-"{letter}|{digit}) {
    fprintf(seq_token,"regex_lit: %s\n",yytext);
    BEGIN REGEX_RANGE;
    // return REGEX_LRANGE;
}

<REGEX_RANGE>"-" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    //return REGEX_HYPHEN;
}

<REGEX_RANGE>{letter}|{digit} {
    fprintf(seq_token,"regex_lit: %s\n",yytext);
    BEGIN REGEX_SQ;
    // return REGEX_RRANGE;
}

<REGEX_SQ>"]" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_START;
    // return REGEX_RBRACK;
}

<REGEX_START,REGEX_SQ>"\\("|"\\)"|"\\{"|"\\}"|"\\["|"\\]"|"\\|"|"\\*"|"\\+"|"\\?"|"\\^"|"\\$"|"\\\\"|{digit}|{letter}|{whitespace}|{special_char}|{brackets} {
    fprintf(seq_token,"regex_lit: %s\n",yytext);
    // return REGEX_LIT;
}

<REGEX_START>(.|"\n") {
    fprintf(seq_token,"regex_lit: %s\n",yytext);
}

<REGEX_START>"$"/"{"{id}"}" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_VAR;
    //return REGEX_DOLLAR;
}

<REGEX_VAR>"{" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return LBRACE;
}

<REGEX_VAR>{id} {
    fprintf(seq_token,"regex_var: %s\n",yytext);
    //return REGEX_ID;
}

<REGEX_VAR>"}" {
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_START;
    // return RBRACE;
}

<REGEX_START,REGEX_LIMIT,REGEX_SQ,REGEX_RANGE,REGEX_VAR>. {
    fprintf(seq_token,"regex pattern error: %s\n",yytext);
    // return REGEX_ERROR;
}

{brackets}  {
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
    fprintf(seq_token,"identifier: %s\n",yytext);
    // return ID;
}

<COMMENT>{comm_beg} {
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

{epsilon} {
    fprintf(seq_token,"epsilon: %s\n",yytext);
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
    yyin = fopen(argv[1],"r");
    char *filename = (char*)malloc(sizeof(char)*strlen(argv[1]));
     //position of last '.' in file name
    char *pos = strrchr(argv[1],'.'); 

    //position of last '/' in file name
    char *x = strrchr(argv[1],'/');

    // file name of the input file after removing .txt at the end
    // This requires the input file to have an extension
    if(x==NULL)
        strncpy(filename,argv[1],pos-argv[1]);
    else
        strncpy(filename,x+1,pos-x-1);

  // path to the folder of test file
  char *path = (char*)malloc(sizeof(char)*strlen(argv[1]));
  strncpy(path,argv[1],x-argv[1]);
  x = strrchr(path,'/');
  path[x-path] = '\0';
  char *seq = (char*)malloc(sizeof(char)*(strlen(path)+50));

  sprintf(seq,"%s/tokens/seq_tokens_%s.tok",path,filename);

  // tokens file path
  seq_token = fopen(seq, "w");
  yylex();

  if(argc > 1)
    fclose(yyin);
  fclose(seq_token);
  return 0;
}
