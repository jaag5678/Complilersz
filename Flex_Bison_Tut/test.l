/* This is a test code to try out different features of FLex itself */

%{
   // #include "tokens.h" //I can store all my token labels as macros in anohter file and link it later (good programming practice)
   
   typedef struct stats {
      int length;
      char *bla;
   }stats;

%}

NUMBERS [0-9]+
ALPHABETS [a-zA-Z]+
CURVE_BRACKETS ["(" | ")"]
OPERATORS [+*-/]

%%

("\\a"|[a-z])*  {printf("OKAU ");}

%%

int main() {
    
   yylex();

    return 0;
}