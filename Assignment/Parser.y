/* A Sample parser */

%{
    #include<stdio.h>
    #include<string.h>
   
    extern char *yytext;
    extern int g;
    int yylex();
%}


%code requires {
    #include"tree.h"
}

%error-verbose

%union {
    Exp *exp;
    Decl *dec; 
    char *str;
    char dt;
}

%type <exp> exp f g h i j k
%type <dec> decl
%type <dt> dtype
%type <str> IDENT VAR

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

decl :   VAR IDENT COLON dtype SCOLON {$$ = create_decl($1, $2, $4, NULL);}
        | VAR IDENT COLON dtype ASS exp SCOLON  {$$ = create_decl($1, $2, $4, $6);}
        | IDENT ASS exp SCOLON  {$$ = create_decl(NULL, $1, NULL, $3);}
;
dtype : D_INT   {$$ = 'i';}
        | D_FLOAT   {$$ = 'f';}
        | D_STRING  {$$ = 's';}
        | D_BOOL    {$$ = 'b';}
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
h : h ADD i      {$$ = create_exp(NULL, $1, $3, '+');}
    | h SUB i  {$$ = create_exp(NULL, $1, $3, '-');}
    | i
;
i : i MUL j      {$$ = create_exp(NULL, $1, $3, '*');}
    | i DIV j {$$ = create_exp(NULL, $1, $3, '/');}
    | j
;
j : SUB j {$$ = create_exp(NULL, NULL, $2, '-');}
    | NOT j {$$ = create_exp(NULL, NULL, $2, '!');}
    | CO exp CC {$$ = $2;}
    | k   {$$ = $1;}
;
k : IDENT   {$$ = create_leaf_exp('v', yytext);}
    | INT   {$$ = create_leaf_exp('i', yytext);}
    | FLOAT {$$ = create_leaf_exp('f', yytext);}
    | STRING    {$$ = create_leaf_exp('s', yytext);}
    | BOOL  {$$ = create_leaf_exp('b', yytext);}
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
        int x;
        x = yyparse();

        if(!x)
            printf("OK\n");
        
    }

        

    return 0;
}



