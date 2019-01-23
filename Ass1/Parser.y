/* A Sample parser */

%{
    #include<stdio.h>
    #include<string.h>

    extern int g;
%}

%define parse.error verbose

%token IDENT
%token INT 
%token FLOAT
%token STRING
%token BOOL

/*Keywords*/
%token D_INT
%token D_FLOAT
%token D_STRING
%token D_BOOL
%token VAR
%token PRINT
%token READ
%token IF
%token ELSE
%token WHILE

/* ASsignemnt and other operators (unary) */

%token ASS
%token NOT



/*Arithmetic Operators */
%token ADD
%token SUB
%token MUL
%token DIV



/*Relational Tokens */

%token EQ
%token NEQ
%token GEQ
%token LEQ
%token GT
%token LT

/*Logical Tokens */
%token OR
%token AND

/* FORMAL STRUCTURE TOKENS */
%token CO
%token CC
%token FO
%token FC
%token COLON
%token SCOLON

%token ERR

%%

stmts : %empty
        | stmts stmt 
;
stmt :  decl
        | read
        | print
        | cond
        | loop
;

decl :   VAR IDENT COLON dtype SCOLON
        | VAR IDENT COLON dtype ASS exp SCOLON
        | IDENT ASS exp SCOLON
;
dtype : D_INT 
        | D_FLOAT
        | D_STRING
        | D_BOOL
;

read : READ CO IDENT CC SCOLON
;       
print : PRINT CO exp CC SCOLON
;

loop : WHILE CO exp CC FO stmts FC
;
cond : IF CO exp CC FO stmts FC extend
;
extend : %empty
        | ELSE FO stmts FC
        | ELSE IF CO exp CC FO stmts FC extend
;
exp : exp OR f 
    | exp AND f 
    | f 
;
f : f EQ g   
    | f NEQ g 
    | g
;
g : g GEQ h 
    | g LEQ h 
    | g GT h
    | g LT h 
    | h
;
h : h ADD i 
    | h SUB i 
    | i
;
i : i MUL j 
    | i DIV j 
    | j
;
j : SUB j 
    | NOT j 
    | CO exp CC 
    | k
;
k : IDENT 
    | INT
    | FLOAT
    | STRING
    | BOOL 
;

%%

int main (int argc, char *argv[]) {


    if(argc < 2) 
        printf("Invalid for of running lex / parser. Give type \n");    
    else if(!strcmp(argv[1], "scan")) {
        int x;
        while(x = yylex() ) {
            if(x == ERR) {
                return 1;
            }
        }
        if(x == 0) {
                printf("OK\n");
                return 0;
        }

    }
    else if(!strcmp(argv[1], "token")) {
        g = 1;
        while(yylex());
    }
    else if(!strcmp(argv[1], "parse")) {
        yyparse();
        printf("OK\n");
    }

        

    return 0;
}

/* we must supply our error function yyerror */

