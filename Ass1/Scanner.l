/* This attempt is to create a scanner for a simple language 
/* First job is to detect all keywords and tag them aptly 
/* Next comes Identifiers which would be use to define varaible names acting as alias for a datatype 
/* Next comes for each datatype the kind of values it can accept. (Note that string is gonna be hard to do so beware) 
/* Next comes operations that need to be detected. Note the priority of the operators and order them in that fashion 
/* Next comes language mandatory stuff like braces and all 
/* Lastly we will deal with spaces and other characters not in the language */

%{
#include<stdio.h>
#include<stdlib.h>
%}

%%

"//".*                {printf("COMMENT "); }
[ \t]+                  { }
[\n]                    {printf("EOL \n");}

"var"       {printf("VAR_DEC ");}
"string"    {printf("DTYPE_S ");}
"float"     {printf("DTYPE_F ");}
"int"       {printf("DTYPE_I ");}
"boolean"   {printf("DTYPE_B ");}

"if"        {printf("IF ");}
"else"      {printf("ELSE ");}

"while"     {printf("WHILE ");}

"print"     {printf("PRINT ");}
"read"      {printf("READ ");}

"!"         {printf("! ");}
"="         {printf("= ");}

"+"         {printf("+ ");}
"-"         {printf("- ");}
"*"         {printf("* ");}
"/"         {printf("/ ");}

">="        {printf(">= ");}
"<="        {printf("<= ");}
">"         {printf("> ");}
"<"         {printf("< ");}

"=="        {printf("== ");}
"!="        {printf("!= ");}

"&&"        {printf("&& ");}
"||"        {printf("|| ");}

"("         {printf("OPEN_P ");}
")"         {printf("CLOSE_P ");}

"{"         {printf("OPEN_C ");}
"}"         {printf("CLOSE_C ");}

":"         {printf(": ");}

";"         {printf("CE ## ");}



0|[1-9][0-9]*               {printf("INT ");}
[0-9]*                      {printf("ERR_INT ");}

0"."[0-9]*|[1-9]+"."[0-9]*  {printf("FLOAT ");}
[0-9]*"."[0-9]*             {printf("ERR_FLOAT ");}

"true"|"false"              {printf("BOOL ");}

\"([a-zA-Z+-/*0-9`~!@#$%^&\(\)_={} \[\];':,.<>?]|"\\a"|"\\b"|"\\f"|"\\n"|"\\n"|"\\r"|"\\t"|"\\v"|"\\\\"|"\\\"")*\" {printf("STRING ");}         

[a-zA-Z_][a-zA-Z0-9_]*  {printf("IDENT ");}

.         {printf("ERR ");}

%%

int main () {

    yylex();

    return 0;
}
