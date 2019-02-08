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

int yyerror (char const *s) {

    fprintf(stderr,"Error: %s --> check line %d \n", s, yylineno);
    exit(1);
}
%}


%option yylineno

%%

"//".*                {if(g) printf("tCOMMENT "); }
[ \t]+                  { }
[\n]                    {if(g) printf("tEOL \n");}

"var"       {if(g) printf("tVAR_DEC\n");
                return VAR;}
"string"    {if(g) printf("tDTYPE_S\n ");
                return D_STRING;}
"float"     {if(g) printf("tDTYPE_F \n");
                return D_FLOAT;}
"int"       {if(g) printf("tDTYPE_I \n");
                return D_INT;}
"boolean"   {if(g) printf("tDTYPE_B \n");
                return D_BOOL;}

"if"        {if(g) printf("tIF \n");
                return IF;}
"else"      {if(g) printf("tELSE\n ");
                return ELSE;}

"while"     {if(g) printf("tWHILE \n");
                return WHILE;}

"print"     {if(g) printf("tPRINT \n");
                return PRINT;}
"read"      {if(g) printf("tREAD \n");
                return READ;}

"!"         {if(g) printf("tNOT\n");
                return NOT;}
"="         {if(g) printf("tASS\n");
                return ASS;}

"+"         {if(g) printf("tADD\n");
                return ADD;}
"-"         {if(g) printf("tMINUS\n");
                return SUB;}
"*"         {if(g) printf("tMUL\n ");
                return MUL;}
"/"         {if(g) printf("tDIV\n ");
                return DIV;}

">="        {if(g) printf("tGEQ\n ");
                return GEQ;}
"<="        {if(g) printf("tLEQ\n ");
                return LEQ;}
">"         {if(g) printf("tGT\n ");
                return GT;}
"<"         {if(g) printf("tLT \n");
                return LT;}

"=="        {if(g) printf("tEQ\n ");
                return EQ;}
"!="        {if(g) printf("tNEQ\n ");
                return NEQ;}

"&&"        {if(g) printf("tAND \n");
                return AND;}
"||"        {if(g) printf("tOR \n");
                return OR;}

"("         {if(g) printf("tOPEN_P\n ");
                return CO;}
")"         {if(g) printf("tCLOSE_P\n ");
                return CC;}

"{"         {if(g) printf("tOPEN_C \n");
                return FO;}
"}"         {if(g) printf("tCLOSE_C \n");
                return FC;}

":"         {if(g) printf("tCOLON \n");
                return COLON;}

";"         {if(g) printf("SEMCOLON \n");
                return SCOLON;}



0|[1-9][0-9]*               {if(g) printf("tINT(%s) \n", yytext);
                                yylval.str = strdup(yytext);
                                return INT;}
[0-9]*                      {   yyerror("Invalid Integer ");
                                printf("tERR_INT \n");
                                return ERR;}

0"."[0-9]*|[1-9]+[0-9]*"."[0-9]*  {if(g) printf("tFLOAT(%s) \n", yytext);
                                yylval.str = strdup(yytext);
                                return FLOAT;}
[0-9]*"."[0-9]*             {   yyerror("Invalid Floating point number ");
                                printf("tERR_FLOAT \n");
                                return ERR;}

"true"|"false"              {if(g) printf("tBOOL \n");
                                yylval.str = strdup(yytext);
                                return BOOL;}

\"([a-zA-Z+-/*0-9`~!@#$%^&\(\)_={} \[\];':,.<>?|]|"\\a"|"\\b"|"\\f"|"\\n"|"\\r"|"\\t"|"\\v"|"\\\\"|"\\\"")*\" {if(g) printf("STRING(%s)\n", yytext);
                                                                                                                        yylval.str = strdup(yytext);                                                                                      
                                                                                                                        return STRING;}         

[a-zA-Z_][a-zA-Z0-9_]*  {if(g) printf("tIDENT(%s) \n", yytext);
                            yylval.str = strdup(yytext);
                            return IDENT;}

.         { yyerror("Invalid INput :(");
                printf("tERR \n");
                return ERR;}

%%

