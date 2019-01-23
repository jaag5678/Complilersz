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
#include "Parser.tab.h"

int g = 0;
%}


%option yylineno
%option verbose

%%

"//".*                {if(g) printf("tCOMMENT "); }
[ \t]+                  { }
[\n]                    {if(g) printf("tEOL \n");}

"var"       {if(g) printf("tVAR_DEC\n");
                return VAR;}
"string"    {if(g) printf("tDTYPE_S ");
                return D_STRING;}
"float"     {if(g) printf("tDTYPE_F ");
                return D_FLOAT;}
"int"       {if(g) printf("tDTYPE_I ");
                return D_INT;}
"boolean"   {if(g) printf("tDTYPE_B ");
                return D_BOOL;}

"if"        {if(g) printf("tIF ");
                return IF;}
"else"      {if(g) printf("tELSE ");
                return ELSE;}

"while"     {if(g) printf("tWHILE ");
                return WHILE;}

"print"     {if(g) printf("tPRINT ");
                return PRINT;}
"read"      {if(g) printf("tREAD ");
                return READ;}

"!"         {if(g) printf("tNOT");
                return NOT;}
"="         {if(g) printf("tASS");
                return ASS;}

"+"         {if(g) printf("tADD");
                return ADD;}
"-"         {if(g) printf("tMINUS");
                return SUB;}
"*"         {if(g) printf("tMUL ");
                return MUL;}
"/"         {if(g) printf("tDIV ");
                return DIV;}

">="        {if(g) printf("tGEQ ");
                return GEQ;}
"<="        {if(g) printf("tLEQ ");
                return LEQ;}
">"         {if(g) printf("tGT ");
                return GT;}
"<"         {if(g) printf("tLT ");
                return LT;}

"=="        {if(g) printf("tEQ ");
                return EQ;}
"!="        {if(g) printf("tNEQ ");
                return NEQ;}

"&&"        {if(g) printf("tAND ");
                return AND;}
"||"        {if(g) printf("tOR ");
                return OR;}

"("         {if(g) printf("tOPEN_P ");
                return CO;}
")"         {if(g) printf("tCLOSE_P ");
                return CC;}

"{"         {if(g) printf("tOPEN_C ");
                return FO;}
"}"         {if(g) printf("tCLOSE_C ");
                return FC;}

":"         {if(g) printf("tCOLON ");
                return COLON;}

";"         {if(g) printf("CE ## ");
                return SCOLON;}



0|[1-9][0-9]*               {if(g) printf("tINT(%s) ", yytext);
                                return INT;}
[0-9]*                      {   yyerror("Invalid Integer ");
                                printf("tERR_INT ");
                                return ERR;}

0"."[0-9]*|[1-9]+"."[0-9]*  {if(g) printf("tFLOAT(%s)", yytext);
                                return FLOAT;}
[0-9]*"."[0-9]*             {   yyerror("Invalid Floating point number ");
                                printf("tERR_FLOAT ");
                                return ERR;}

"true"|"false"              {if(g) printf("tBOOL ");
                                return BOOL;}

\"([a-zA-Z+-/*0-9`~!@#$%^&\(\)_={} \[\];':,.<>?|]|"\\a"|"\\b"|"\\f"|"\\n"|"\\r"|"\\t"|"\\v"|"\\\\"|"\\\"")*\" {if(g) printf("STRING(%s)", yytext);
                                                                                                                        return STRING;}         

[a-zA-Z_][a-zA-Z0-9_]*  {if(g) printf("tIDENT(%s) ", yytext);
                            return IDENT;}

.         { yyerror("Invalid INput :(");
                printf("tERR ");
                return ERR;}

%%

int yyerror (char const *s) {

    printf("Error in line %d :", yylineno);
    fprintf (stderr, "%s\n", s);

    return 1;
}