//This header file will define the tree that i want to define to create abstract syntax tree
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"essentials.h"

extern int yylineno;

typedef struct Statements Statements;
typedef struct Stmt Stmt;
typedef struct Exp Exp;
typedef struct Decl Decl;
typedef struct Loop Loop;
typedef struct Cond Cond;

//Node that defines expressions 
struct Exp {
    enum operation op;
    union {
        char *literal; //Identifier
        struct { 
            Exp *left;
            Exp *right;
        } binary;
    }u;
    
    enum type datatype;

};

//Node that defines Declarations
struct Decl {
    char *ident;
    enum type datatype;
    Exp *exp;

};

//Ndoe to define loops
struct Loop {
    Exp *exp;
    Statements *stmts;
};


//Node to define COnditional statements
struct Cond {
    Exp *exp;
    Statements *stmts;
    Stmt *op_else_if;
};

//Ndoe that defines a statment in general
struct Stmt {
    int lineno;
    enum statement_kind stmt_type;
    union {
        Decl *declaration;
        Exp *read_print; //In case it is read / print it will be expression
        Loop loop; 
        Cond cond;
    }body_of_stmt;
};

//Node for set of statements 
struct Statements {
    Statements *stmts;
    Stmt *stmt;
};

//I can define a separate function to define a leaf in the expression 
Exp *create_leaf_exp(int type, char *text_to_val);

//There will be just one function to create expressions 
Exp *create_exp(Exp *left, Exp *right, int op);

//Create a declaration 
Decl *create_decl(char *ident, int datatype, Exp *exp);

//Create a statement 
struct Stmt *create_statement ( int lineno, int type_of_st, Decl *decl, Exp *exp, Statements *stmts, struct Stmt *optional);

//Create statements 
Statements *create_program(Statements *stmts, struct Stmt *stmt);

