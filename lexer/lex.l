%option yylineno
%option stack

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

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
oper_ari            ("/"|"%")
oper_auto           ("@")
oper_set            ("^2")
oper_ovr_auto_set_ari ("+"|"*")
oper_ovr_set_ari    ("-")
oper_ovr_log_auto   ("!")
oper_bi_log         ("&&"|"||")
oper_comp           ("=="|"!="|"<"|">"|"<="|">=")
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
keyword_control     ("if"|"elif"|"else"|"while"|"break")
keyword_return      ("return")
keyword_struct      ("struct")
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
    else if(strcmp(yytext,"break")==0) {
        // return BREAK_KW;
    }
}

{keyword_struct} {

    /*
      When keyword struct is present ,struct keyword is returned .
    */
    fprintf(seq_token,"reserved keyword: %s\n",yytext);
    // return STRUCT_KW;
}


{keyword_return} {
    fprintf(seq_token,"reserved keyword: %s\n",yytext);
    // return RETURN_KW;
}


"r"/{single_quote}([^']|"\'")*{single_quote} {

    /*
    If the character r is present , check whether there is a string in 
    single quote is present ahead of it ,if so it is a reject string .
    */ 

    fprintf(seq_token,"regex: %s\n",yytext);
    BEGIN REGEX;
    //return REGEX_R;
}


<REGEX>{single_quote} {

    /*
    If the character "'" is present ,
    then we  start we start with regex_start state .
    */

    fprintf(seq_token,"punctuation: %s\n",yytext);
    BEGIN REGEX_START;
    //return SIN_QUOTE;
}


<REGEX_START>{single_quote} {

    /*
    If the character "'" is present ,
    then we begin initial state .
    */

    fprintf(seq_token,"punctuation: %s\n",yytext);
    BEGIN INITIAL;
    // return SIN_QUOTE;
}

<REGEX_START>{letter}|{whitespace} {

    /*
    If any letter is present followed by a white space ,
    then we return REGEX_LIT.
    */

    fprintf(seq_token,"regex_lit: %s\n",yytext);
    // return REGEX_LIT;
}

<REGEX_START>{digit}+ {

    /*
    If any integer is present then
    we return REGEX_LIT.
    */

    fprintf(seq_token,"regex_num: %s\n",yytext);
    // return REGEX_LIT;
}

<REGEX_START>"|" {
    
    /*
    if the symbol "|" is present then
    we return REGEX_OR.
    */

    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_OR;
}

<REGEX_START>"*" {

    /*
    If the symbol "*" is present then 
    we return REGEX_STAR .
    */

    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_STAR;
}

<REGEX_START>"+" {

    /*
    If the symbol "+" is present then
    we return REGEX_PLUS.
    */

    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_PLUS;
}

<REGEX_START>"?" {

    /*
    If the symbol "?" is present then
    we retun REGEX_QUE. 
    */

    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_QUE;
}

<REGEX_START>"^" {

    /*
    IF symbol "^" is present ,
    then we return REGEX_CARET.
    */

    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_CARET;
}

<REGEX_START>"(" {
    
    /*
    If symbol "(" is present ,
    then we return LPAREN
    */

    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return LPAREN;
}

<REGEX_START>")" {
    
    /*
    If symbol ")" is present 
    then we return RPAREN
    */

    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return RPAREN;
}

<REGEX_START>"{"/{digit}+","?({digit}+)?"}" {
    
    /*
    If symbol "{" is followed by integer , ... }
    then we return LBRACE
    */
    
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_LIMIT;
    // return LBRACE;
}

<REGEX_LIMIT>{digit}+ {
    
    /*
    If integer is present then
    we return REGEX_NUM .
    */
    
    fprintf(seq_token,"regex_num: %s\n",yytext);
    // return REGEX_NUM;
}

<REGEX_LIMIT>"," {
    
    /*
    If symbol "," is present 
    then we return COMMA.
    */
    
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return COMMA;
}

<REGEX_LIMIT>"}" {
    
    /*
    If symbol "{" is present 
    then we begin regex_start.
    */
    
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_START;
    // return RBRACE;
}

<REGEX_START>"["/(("^")?[^\]']|"\\]")+"]" {
    
    /*
    checks for regex class expression [abc] or [^abc]
    and then begins regex_sq.
    */
    
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_SQ;
    // return LBRACK;
}

<REGEX_START>"[" {
    
    /*
    If the symbol "[" is present in situations 
    otherthan those in above condition ,then it is 
    an error.
    */
    
    printf("Error at line no: %d\n",yylineno);
    exit(1);
}

<REGEX_SQ>"^" {
    
    /*
    If symbol "^" is present 
    inside regex_sq expression
    then we return REGEX_CARET.
    */
    
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_CARET;
}

<REGEX_SQ>{letter}|{digit}/("-"{letter}|{digit}) {
    
    /* 
    check is any letter or digit is followed by "- letter or digit"
    then we begin regex_range
    */
    
    fprintf(seq_token,"regex_lit: %s\n",yytext);
    BEGIN REGEX_RANGE;
    // return REGEX_LRANGE;
}

<REGEX_RANGE>"-" {
    
    /*
    If symbol "-" is present 
    inside regex_range expression
    then we return regex_hyphen
    */
    
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    //return REGEX_HYPHEN;
}

<REGEX_RANGE>{letter}|{digit} {
    
    /*
    If letter or digit is present 
    in regex_range expression then 
    we begin regex_sq.
    */
    
    fprintf(seq_token,"regex_lit: %s\n",yytext);
    BEGIN REGEX_SQ;
    // return REGEX_RRANGE;
}

<REGEX_SQ>"]" {
    
    /*
    If the symbol "]" is present
    in the reger_sq expression then
    we begin regex_start .
    */
    
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_START;
    // return RBRACK;
}

<REGEX_START,REGEX_SQ>"\\("|"\\)"|"\\{"|"\\}"|"\\["|"\\]"|"\\|"|"\\*"|"\\+"|"\\?"|"\\^"|"\\$"|"\\\\"|{digit}|{letter}|{whitespace}|{special_char}|{brackets} {
    
    /*
    check for all possible REGEX_LIT
    */
    
    fprintf(seq_token,"regex_lit: %s\n",yytext);
    // return REGEX_LIT;
}

<REGEX_START>"$"/"{"{id}"}" {
    
    /*
    Check if dollar symbol is followed by {id}
    in regex_start expression then 
    we begin regex_var .
    */
    
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_VAR;
    //return REGEX_DOLLAR;
}
<REGEX_START>"$"/"'" {
    
    /*
     Check if dollar symbol is followed by '
    in regex_start expression then 
    we begin regex_dollar.
    */
    
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return REGEX_DOLLAR;
}

<REGEX_START>"$" {
    
    /*
    Check if dollar symbol is present (without following 
    any of the above 2 conditions) ,in regex_start expression then 
    we give an error.
    */
    
    printf("Error at line no: %d\n",yylineno);
    exit(1);
}

<REGEX_VAR>"{" {

    /*
    Check if "{" is present
    in regex_var expression then 
    we return lbrace .
    */
    
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    // return LBRACE;
}

<REGEX_VAR>{id} {

    /*
    Check if identifier is present
    in regex_var expression then 
    we return ID .
    */
    
    fprintf(seq_token,"regex_var: %s\n",yytext);
    //return ID;
}

<REGEX_VAR>"}" {

    /*
    Check if symbol "}" is present
    in regex_var expression then 
    we begin regex_start.
    */
    
    fprintf(seq_token,"regex_punct: %s\n",yytext);
    BEGIN REGEX_START;
    // return RBRACE;
}

<REGEX_START,REGEX_LIMIT,REGEX_SQ,REGEX_RANGE,REGEX_VAR>. {

    /*
    Pattern errors detected by lexer are 
    highlighted here .
    */
    
    fprintf(seq_token,"regex pattern error: %s\n",yytext);
    printf(RED "Error at line number: %d\n" RESET, yylineno);
    exit(1);
}

{brackets}  {

    /*
    In this we detect brackets 
    and return corresponding tokens.
    */
    
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

{type_standard} {

    /*
    In this we detect primitive datatype
    and return corresponding token.
    */
    
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

    /*
     In this we detect non-standard datatype
    and return corresponding token.
    */
    
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
    // detecting '/' and '%' which are exclusively arithmetic operators
    fprintf(seq_token,"operator: %s\n",yytext);
    if(strcmp(yytext,"/")==0){
        // return OPER_DIV;
    }
    else if(strcmp(yytext,"%")==0){
        // return OPER_MOD;
    }
}

{oper_auto}         {
    // detecting '@' which is exclusively an automata operator
    fprintf(seq_token,"operator: %s\n",yytext);
        // return AT_THE_RATE;
}

{oper_set}          {
    // detecting '^2' which is exclusively a set operator
    fprintf(seq_token,"operator: %s\n",yytext);
     // return OPER_POWER;
}
{oper_ovr_auto_set_ari}         {
    // detecting '+' and '*' operator which are overloaded for all sets, arithmetic and automata expressions
    fprintf(seq_token,"operator: %s\n",yytext);
    if(strcmp(yytext,"+")==0){
        // return OPER_PLUS;
    }
    else if(strcmp(yytext,"*")==0){
        // return OPER_MUL;
    }
}

{oper_ovr_set_ari} {
    // detecting '-' which is an overloaded operator for sets and arithmetic expressions
    fprintf(seq_token,"operator: %s\n",yytext);
    // return OPER_MINUS;
}

{oper_bi_log}      {
    // detecting binary logical operators
    fprintf(seq_token,"operator: %s\n",yytext);
    if(strcmp(yytext,"&&")==0){
        // return OPER_AND;
    }
    else if(strcmp(yytext,"||")==0) {
        // return OPER_OR;
    }
}

{oper_ovr_log_auto}      {
    // detecting unary logical operator '!'which is overloaded for logical and automata expressions
    fprintf(seq_token,"operator: %s\n",yytext);
    // return OPER_NOT;
}

{oper_comp}      {
    // detecting comparision operators
    fprintf(seq_token,"operator: %s\n",yytext);
    if(strcmp(yytext,"<")==0){
        // return COMP_LT;
    }
    else if(strcmp(yytext,">")==0){
        // return COMP_GT;
    }
    // return OPER_COMP;
}

{oper_asn_simple} {
    // detecting '=' operator
    fprintf(seq_token,"operator: %s\n",yytext);
    // return OPER_ASN_SIMPLE;
}

{oper_asn}      {
    // detecting other assignment operators
    fprintf(seq_token,"operator: %s\n",yytext);
    // return OPER_ASN;
}
{punctuation} {
    
    /*
        punctuation characters 
        ';',',','.','->',':'
    */
    
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

{const_int} {
    
    /*
        detecting positive integer constants
        (negative integers handled by parser)
    */
    
    fprintf(seq_token,"int_const: %s\n",yytext);
    // return INT_CONST;
}

{const_float} {
    
    /*
        detecting positive float constants
        (negative floats handled by parser)
    */
    
    fprintf(seq_token,"float_const: %s\n",yytext);
    // return FLOAT_CONST;
}

{const_string} {
    
    /*
        detecting string constants
        "Test_1213#!@$!\"This is a string constant"
    */
    
    fprintf(seq_token,"string_const: %s\n",yytext);
    // return STRING_CONST;
}

{const_char} {
    
    /*
        Detecting character constants
        'a'
        '\''
    */
    
    fprintf(seq_token,"char_const: %s\n",yytext);
    // return CHAR_CONST;
}

{const_bool} {
    
    /*
        detecting bool constants
        true and false
    */
    
    fprintf(seq_token,"bool_const: %s\n",yytext);
    // return BOOL_CONST;
}

{id} {
    
    /*
        detecting identifiers
    */
    
    fprintf(seq_token,"identifier: %s\n",yytext);
    // return ID;
}

<COMMENT>{comm_beg} {
    
    /*
        Detecting start of comment '<!--' inside a comment
    */
    
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
    
    /*
        Detecting the first '<!--' for comments
    */
    
    yy_push_state(YYSTATE);
    BEGIN COMMENT;
    fprintf(seq_token,"punctuation: %s\n",yytext);
}

<COMMENT>{comm_end} {
    
    /*
        Detecting end punctuator of comments '--!>'
    */
    
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
    
    /*
        Detecting comment body
    */
    
    comment[comm_len] = yytext[0];
    comment[comm_len+1] = '\0';
    comm_len=comm_len+1;
}

<COMMENT><<EOF>> {
    
    /*
        If end of file detected inside a comment body
    */
    
    fprintf(seq_token,"comment: %s\n",comment);
    BEGIN INITIAL;
}


{epsilon} {
    
    /*
        Epsilon token
    */
    
    fprintf(seq_token,"epsilon: %s\n",yytext);
    // return EPSILON;
}


. {
    // everything else that is undetected by above patterns
    error();
}

%%

// Function to quit program
void error(){
        char *toprint = "Error at line number: ";
        printf(RED "%s%d\n" RESET, toprint, yylineno);
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
