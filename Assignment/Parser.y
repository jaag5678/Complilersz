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
    Statements *AST;
}



%error-verbose

%union {
    Statements *stmts;
    struct Stmt *stmt;
    Exp *exp;
    Decl *dec; 
    char *str;
    char dt;
    int type;
}

%type <exp> exp f g h i j k
%type <dec> decl
%type <type> dtype
%type <str> IDENT VAR
%type <stmts> stmts
%type <stmt> stmt read print loop cond extend

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

stmts : %empty  {$$ = NULL;}
        | stmts stmt {$$ = create_program ($1, $2);
                        AST = $$;}
;
stmt :  decl    {$$ = create_statement(DECLARATION, $1, NULL, NULL, NULL);}
        | read  {$$ = $1;}
        | print {$$ = $1;}
        | cond  {$$ = $1;}
        | loop  {$$ = $1;}
;

decl :   VAR IDENT COLON dtype SCOLON {$$ = create_decl($2, $4, NULL);}
        | VAR IDENT COLON dtype ASS exp SCOLON  {$$ = create_decl($2, $4, $6);}
        | IDENT ASS exp SCOLON  {$$ = create_decl($1, NULL, $3);}
;
dtype : D_INT   {$$ = INT;}
        | D_FLOAT   {$$ = FLOAT;}
        | D_STRING  {$$ = STRING;}
        | D_BOOL    {$$ = BOOL;}
;

read : READ CO IDENT CC SCOLON  {   Exp *exp = malloc(sizeof(Exp));
                                    exp -> datatype = VAR;
                                    exp -> u.ident = $3;
                                    $$ = create_statement(READ_ST, NULL, exp, NULL, NULL);}
;       
print : PRINT CO exp CC SCOLON  {$$ = create_statement(PRINT_ST, NULL, $3, NULL, NULL);}
;

loop : WHILE CO exp CC FO stmts FC {$$ = create_statement(WHILE_ST, NULL, $3, $6, NULL);}
;
cond : IF CO exp CC FO stmts FC extend  {$$ = create_statement(IF_ST, NULL, $3, $6, $8);}
;
extend : %empty         {$$ = NULL;}
        | ELSE FO stmts FC   {$$ = create_statement(ELSE_ST, NULL, NULL, $3, NULL);}
        | ELSE IF CO exp CC FO stmts FC extend  {$$ = create_statement(ELSE_IF_ST, NULL, $4, $7, $9);}
;
exp : exp OR f  {$$ = create_exp(NULL, $1, $3, '|');}
    | exp AND f  {$$ = create_exp(NULL, $1, $3, '&');}
    | f 
;
f : f EQ g    {$$ = create_exp(NULL, $1, $3, '+');}
    | f NEQ g  {$$ = create_exp(NULL, $1, $3, '+');}
    | g
;
g : g GEQ h  {$$ = create_exp(NULL, $1, $3, '+');}
    | g LEQ h  {$$ = create_exp(NULL, $1, $3, '+');}
    | g GT h  {$$ = create_exp(NULL, $1, $3, '+');}
    | g LT h  {$$ = create_exp(NULL, $1, $3, '+');}
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



