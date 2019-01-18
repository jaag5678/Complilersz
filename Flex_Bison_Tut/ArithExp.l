/* Simple arithmetic Expressions denoted using their names */

%{
    #include<stdlib.h>

    char* add() {
        return "HAHAH";
    }
    enum yytokentype {
     NUMBER = 0,
     ADD = 1,
     SUB = 2,
     MUL = 3,
     DIV = 4,
     MOD = 5,
     ABS = 6,
     EOL = 7
   };
    int x = 0;
    int y = 0;
    int z = 0;
%}


%%

"+"     {printf("PLUS ");
            return ADD;}
"-"     {printf("MINUs ");
            return SUB;}
"*"     {printf("MULTIPLY ");
            return MUL;}
"/"     {printf("DIVIDE ");
            return DIV;}
"%"     {printf("MOD ");
            return MOD;}
[0-9]+  {x = atoi(yytext);
            printf("NUMBER %s ", yytext);
            return NUMBER;}
\n      {printf("NEWLINE\n");
            return EOL;}
[ \t]   { }
.       {printf("SOME RANDOM CHAR\n");}

%%

int main () {
    yylex();
    printf("%s\n", add());
    return 0;
}