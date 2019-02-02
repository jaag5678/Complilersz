/* A Sample parser */

%{
    #include<stdio.h>
    #include<string.h>
   
    extern char *yytext;
    extern int g;
    int yylex();
%}


%code requires {
    #include"pretty_print.h"
    Statements *AST;
}



%error-verbose

%union {
    int int_val;
    float float_val;
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
%type <stmts> stmts program
%type <stmt> stmt read print loop cond extend

%token <str> IDENT
%token <int_val> INT 
%token <float_val> FLOAT
%token <str>STRING
%token <str>BOOL

/*Keywords*/
%token D_INT
%token D_FLOAT
%token D_STRING
%token D_BOOL
%token <str> VAR
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

program :  stmts {AST = $1;}
;

stmts : %empty  {$$ = NULL;}
        | stmts stmt {$$ = create_program ($1, $2);}
;
stmt :  decl    {$$ = create_statement(DECLARATION, $1, NULL, NULL, NULL);}
        | read  {$$ = $1;}
        | print {$$ = $1;}
        | cond  {$$ = $1;}
        | loop  {$$ = $1;}
;

decl :   VAR IDENT COLON dtype SCOLON {$$ = create_decl($2, $4, NULL);}
        | VAR IDENT COLON dtype ASS exp SCOLON  {$$ = create_decl($2, $4, $6);}
        | IDENT ASS exp SCOLON  {$$ = create_decl($1, UNDEF, $3);}
;
dtype : D_INT   {$$ = INTEGER;}
        | D_FLOAT   {$$ = FLOATING;}
        | D_STRING  {$$ = STRING_DT;}
        | D_BOOL    {$$ = BOOL_DT;}
;

read : READ CO IDENT CC SCOLON  {   Exp *exp = malloc(sizeof(Exp));
                                    exp -> datatype = VAR_DT;
                                    exp -> u.ident = $3;
                                    exp -> op = -1;
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
exp : exp OR f  {$$ = create_exp(NULL, $1, $3, OROR);}
    | exp AND f  {$$ = create_exp(NULL, $1, $3, ANDAND);}
    | f         {$$ = $1;}
;
f : f EQ g    {$$ = create_exp(NULL, $1, $3, EQUAL);}
    | f NEQ g  {$$ = create_exp(NULL, $1, $3, NOT_EQUAL);}
    | g         {$$ = $1;}
;
g : g GEQ h  {$$ = create_exp(NULL, $1, $3, GT_EQ);}
    | g LEQ h  {$$ = create_exp(NULL, $1, $3, LT_EQ);}
    | g GT h  {$$ = create_exp(NULL, $1, $3, GRT);}
    | g LT h  {$$ = create_exp(NULL, $1, $3, LTN);}
    | h         {$$ = $1;}
;
h : h ADD i      {$$ = create_exp(NULL, $1, $3, PLUS);}
    | h SUB i  {$$ = create_exp(NULL, $1, $3, MINUS);}
    | i         {$$ = $1;}
;
i : i MUL j      {$$ = create_exp(NULL, $1, $3, MULT);}
    | i DIV j {$$ = create_exp(NULL, $1, $3, DIVIDE);}
    | j     {$$ = $1;}
;
j : SUB j {$$ = create_exp(NULL, NULL, $2, MINUS);}
    | NOT j {$$ = create_exp(NULL, NULL, $2, COMPL);}
    | CO exp CC {$$ = $2;}
    | k   {$$ = $1;}
;
k : IDENT   {$$ = create_leaf_exp(VAR_DT, $1);}
    | INT   {$$ = create_leaf_exp(INTEGER, yytext);}
    | FLOAT {$$ = create_leaf_exp(FLOATING, yytext);}
    | STRING    {$$ = create_leaf_exp(STRING_DT, $1);}
    | BOOL  {$$ = create_leaf_exp(BOOL_DT, $1);}
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
        
        Print_AST(AST);
    }

        

    return 0;
}



