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

"var"       {printf("VAR_DEC ");
                return VAR;}
"string"    {printf("DTYPE_S ");
                return D_STRING;}
"float"     {printf("DTYPE_F ");
                return D_FLOAT;}
"int"       {printf("DTYPE_I ");
                return D_INT;}
"boolean"   {printf("DTYPE_B ");
                return D_BOOL;}

"if"        {printf("IF ");
                return IF;}
"else"      {printf("ELSE ");
                return ELSE;}

"while"     {printf("WHILE ");
                return WHILE;}

"print"     {printf("PRINT ");
                return PRINT;}
"read"      {printf("READ ");
                return READ;}

"!"         {printf("! ");
                return "!"}
"="         {printf("= ");
                return "=";}

"+"         {printf("+ ");
                return "+";}
"-"         {printf("- ");
                return "-";}
"*"         {printf("* ");
                return "*";}
"/"         {printf("/ ");
                reutrn "/";}

">="        {printf(">= ");
                return ">=";}
"<="        {printf("<= ");
                return "<=";}
">"         {printf("> ");
                return ">";}
"<"         {printf("< ");
                return "<";}

"=="        {printf("== ");
                return "==";}
"!="        {printf("!= ");
                return "!=";}

"&&"        {printf("&& ");
                return "&&";}
"||"        {printf("|| ");
                retrun "||";}

"("         {printf("OPEN_P ");
                return "(";}
")"         {printf("CLOSE_P ");
                return ")";}

"{"         {printf("OPEN_C ");
                return "{";}
"}"         {printf("CLOSE_C ");
                return "}";}

":"         {printf(": ");
                return ":";}

";"         {printf("CE ## ");
                return ";";}



0|[1-9][0-9]*               {printf("INT ");
                                return INT;}
[0-9]*                      {printf("ERR_INT ");
                                return ERR;}

0"."[0-9]*|[1-9]+"."[0-9]*  {printf("FLOAT ");
                                return FLOAT;}
[0-9]*"."[0-9]*             {printf("ERR_FLOAT ");
                                return ERR;}

"true"|"false"              {printf("BOOL ");
                                return BOOL;}

\"([a-zA-Z+-/*0-9`~!@#$%^&\(\)_={} \[\];':,.<>?]|"\\a"|"\\b"|"\\f"|"\\n"|"\\n"|"\\r"|"\\t"|"\\v"|"\\\\"|"\\\"")*\" {printf("STRING ");
                                                                                                                        return STRING;}         

[a-zA-Z_][a-zA-Z0-9_]*  {printf("IDENT ");
                            return IDENT;}

.         {printf("ERR ");
                    return ERR;}

%%

int main () {

    yylex();

    return 0;
}
