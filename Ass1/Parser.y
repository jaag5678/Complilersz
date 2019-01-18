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

program :   
        | decls ";" stmts
;

decls : 
        | decls ";" decl ";"
;
dec :
        | VAR IDENT ":" dtype
        | VAR IDENT ":" dtype "=" exp
;
dtype : D_INT 
        | D_FLOAT
        | D_STRING
        | D_BOOL
;
val :    INT
        | FLOAT
        | STRING
        | BOOL
;

stmts : 
        | stmts ";" stmt ";"
;
stmt : 
        | read
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
extend : 
        | ELSE "{" stmts "}"
        | ELSE IF "(" exp ")" "{" stmts "}" extend
;
exp : e "||" e {$$ = $1 || $3;} 
    | e "&&" e {$$ = $1 && $3;}
    | f 
;
f : f "==" f {$$ = $1 == $3;}
    | f "!=" f ($$ = $1 != $3;)
    | g
;
g : g ">=" g {$$ = $1 >= $3;}
    | g "<=" g {$$ = $1 >= $3;}
    | g ">" g {$$ = $1 > $3;}
    | g "<" g {$$ = $1 < $3;}
    | h
;
h : h "+" h {$$ = $1 + $3;}
    | h "-" h {$$ = $1 + $3;}
    | i
;
i : i "*" i {$$ = $1 * $3;}
    | i "/" i {$$ = $1 / $3;}
    | j
;
j : "-"j {$$ = -$1;}
    | "!"j {$$ = !$1;}
    | "("exp")" {$$ = $2}
    | k
;
k : ID 
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