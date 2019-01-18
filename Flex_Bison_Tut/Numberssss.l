/* Simple program to test for valuid integeres and floating point numbers */

/* Declare an alias for any digit */

%{

#define ERR -1
#define NUM 0
#define OPEN_P 1
#define CLOSE_P 2
#define ADD 3
#define SUB 4
#define MUL 5
#define DIV 6
#define MOD 7

%}


DIGIT [0-9]


%% 


0|[1-9]{DIGIT}*                 {printf("INT ");
                                    return NUM;}
                                
{DIGIT}*                        {printf("INT INVALID ");
                                    return ERR;}

0"."{DIGIT}*|[1-9]+"."{DIGIT}*  {printf("FLOAT ");
                                    return NUM;} 
{DIGIT}*"."{DIGIT}*             {printf("FLOAT INVALID ");
                                    return ERR;} 

"("                             {printf("BRAC OPEN ");
                                    return OPEN_P;}
")"                             {printf("BRAC CLOSE ");
                                    return CLOSE_P;}

"+"                             {printf("ADD ");
                                    return ADD;}
"-"                             {printf("SUB ");
                                    return SUB;}
"*"                             {printf("MUL ");
                                    return MUL;}
"/"                             {printf("DIV ");
                                    return DIV;}
"%"                             {printf("MOD ");
                                    return MOD;}

%%

int main () {

    int ret_type;
    while(ret_type = yylex()) {
        
    }
}