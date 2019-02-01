//This header file will define the tree that i want to define to create abstract syntax tree
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Node that defines expressions 
typedef struct Exp {
    enum {
        OROR,
        ANDAND,
        EQUAL,
        NOT_EQUAL,
        GT_EQ,
        LT_EQ,
        GRT,
        LTN,
        PLUS,
        MINUS,
        MULT,
        DIVIDE,
        COMPL

    }op; //Define the operator that is working on the expression. A '\0' would imply no operation and the expression is going to be converted to a value
    union {
        int ival; //Integer value
        float fval; //Float value
        char *sval; //String value
        char *bval; //Binary valure
        char *ident; //Identifier
        struct { 
            struct Exp *left;
            struct Exp *right;
        } binary;
    }u;
    //char datatype; //Could be int (i) or float (f)
    enum type {
        INTEGER, 
        FLOATING, 
        STRING_DT, 
        BOOL_DT,
        VAR_DT,
        UNDEF
    }datatype;

}Exp;

//Node that defines Declarations
typedef struct Decl {
    char *ident;
    enum type datatype;
    Exp *exp;

}Decl;

//Node for set of statements 
typedef struct Statments {
    struct Statements *stmts;
    struct Stmt {
        enum {
            DECLARATION,
            PRINT_ST,
            READ_ST,
            WHILE_ST,
            IF_ST,
            ELSE_ST,
            ELSE_IF_ST
        }stmt_type;
        union {
            Decl *declaration;
            Exp *read_print; //In case it is read / print it will be expression
            struct Loop {
                Exp *exp;
                struct Statements *stmts;
            }loop; 
            struct Cond {
                Exp *exp;
                struct Statements *stmts;
                struct Stmt *op_else_if;
            }cond;
        }body_of_stmt;
    }*stmt;
}Statements;

//I can define a separate function to define a leaf in the expression 
Exp *create_leaf_exp(int type, char *text_to_val);

//There will be just one function to create expressions 
Exp *create_exp(char *text, Exp *left, Exp *right, int op);

//Create a declaration 
Decl *create_decl( char *ident, int datatype, Exp *exp);

//Create a statement 
struct Stmt *create_statement ( int type_of_st, Decl *decl, Exp *exp, Statements *stmts, struct Stmt *optional);

//Create statements 
Statements *create_program(Statements *stmts, struct Stmt *stmt);


