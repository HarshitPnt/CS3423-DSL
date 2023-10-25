%{
 #include <stdio.h>
 #include <string.h>
 #include<math.h>
#include <stdlib.h>


%}



%%


 
 "const"      {printf("Keyword ") ; }
 "struct"     {printf("Keyword ") ; }
 "o_set"      {printf("Keyword ") ; }
 "u_set"      {printf("Keyword ") ; }
 "string"     {printf("Keyword ") ; }
 "regex"      {printf("Keyword ") ; }
  "dfa"       {printf("Keyword ") ; }
  "nfa"       {printf("Keyword ") ; }
  "pda"       {printf("Keyword ") ; }
  "cfg"       {printf("Keyword ") ; }
   "if"       {printf("Keyword ") ; }
  "elif"      {printf("Keyword ") ; }
  "else"      {printf("Keyword ") ; }
 "while"      {printf("Keyword ") ; }
 "break"      {printf("Keyword ") ; }
"continue"    {printf("Keyword ") ; }
 "return"     {printf("Keyword ") ; }
  "true"      {printf("Keyword ") ; }
 "false"      {printf("Keyword ") ; }
  "<!--"      {printf("Keyword ") ; }
  "--!>"      {printf("Keyword ") ; }





"("      {printf("Misc operator") ;}       
")"      {printf("Misc operator") ;}
"["      {printf("Misc operator") ;}
"]"      {printf("Misc operator") ;}

 "*"     {printf("Arithmetic") ; }       
 "!"     {printf("Arithmetic") ; }                
 "+"     {printf("Arithmetic") ; }       
 "-"     {printf("Arithmetic") ; }       
 "\\"    {printf("Arithmetic") ; }        
 "%"     {printf("Arithmetic") ; }


 "@"         {printf("concatination")}
 "^2"        {printf("Powerset")}



 "+="    {printf("Assignment operator") ; }     
 "-="    {printf("Assignment operator") ; }     
 "*="    {printf("Assignment operator") ; }     
 "/="    {printf("Assignment operator") ; }     
 "%="    {printf("Assignment operator") ; }     
 "&="    {printf("Assignment operator") ; }     
 "\|="    {printf("Assignment operator");}      



">"       {printf("comparison");}           
"<"      {printf("comparison");}
">="      {printf("comparison");}          
"<="      {printf("comparison");}          

"=="          
"!="          
"\|\|"          {printf("Logical");}
"&&"          {printf("Logical");}
"->"        {printf("Arrow"); }

","    {printf("Punctuation"); }
";"    {printf("Punctuation"); }



"int_2"   {printf("Datatype")  ;}
"int_4"   {printf("Datatype")  ;}
"int_8"   {printf("Datatype")  ;}
"int_16"   {printf("Datatype") ;}
"int_32"   {printf("Datatype") ;}
"int_64"   {printf("Datatype") ;}

"char"   {printf("Datatype");}

"float_32" {printf("Datatype");}
"float_64" {printf("Datatype");}

"bool"     {printf("Datatype");}

"string"     {printf("Datatype");}



[a-zA-Z_][a-zA-Z0-9_]*  {printf("ID");}
[0-9]+                  {printf("num");}


%%


yywrap(){
}

main(int argc ,char *argv[]){


yylex();

}