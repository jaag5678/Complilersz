/* A Sample parser */

%{
    #include<stdio.h>
%}

%token IDENT
%token INT 
%token FLOAT
%token STRING
%token BOOL
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

%%

program : %empty
        | decls ";" stmts
;

decls : %empty
        | decls ";" decl ";"
;
decl :   VAR IDENT ":" dtype
        | VAR IDENT ":" dtype "=" exp
;
dtype : D_INT 
        | D_FLOAT
        | D_STRING
        | D_BOOL
;

stmts : %empty
        | stmts ";" stmt ";"
;
stmt :   read
        | print
        | cond
        | loop
;
read : READ "(" VAR ")"
;
print : PRINT "(" exp ")"
;
loop : WHILE "(" exp ")" "{" stmts "}"
;
cond : IF "(" exp ")" "{" stmts "}" extend
;
extend : %empty
        | ELSE "{" stmts "}"
        | ELSE IF "(" exp ")" "{" stmts "}" extend
;
exp : exp "||" f 
    | exp "&&" f 
    | f 
;
f : f "==" g 
    | f "!=" g 
    | g
;
g : g ">=" h 
    | g "<=" h 
    | g ">" h
    | g "<" h 
    | h
;
h : h "+" i 
    | h "-" i 
    | i
;
i : i "*" j 
    | i "/" j 
    | j
;
j : "-"j 
    | "!"j 
    | "("exp")" 
    | k
;
k : IDENT 
    | INT
    | FLOAT
    | STRING
    | BOOL 
;

%%

int main () {

    yyparse();

    return 0;
}