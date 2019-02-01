#include"tree.h"


Exp *create_leaf_exp(int type, char *text_to_val) {
    Exp *Leaf = (Exp*)malloc(sizeof(Exp));

    if(type == INTEGER)
        Leaf -> u.ival = atoi(text_to_val);
    else if(type == FLOATING)
        Leaf -> u.fval = atof(text_to_val);
    else if (type == STRING_DT) 
        Leaf -> u.sval = text_to_val;
    else if (type == BOOL_DT) 
        Leaf -> u.bval = text_to_val;   
    else 
        Leaf -> u.ident = text_to_val;
    Leaf -> datatype = type; //IF it is an identifier, we must obtain the type ffrom the symbol table. Check this later

    return Leaf;
}


//There will be just one function to create expressions 
Exp * create_exp(char *text, Exp *left, Exp *right, char op) {

    Exp *NewExp = (Exp *)malloc(sizeof(Exp));
    NewExp -> op = op;
   
    if(left -> datatype == right -> datatype) 
        NewExp -> datatype = left -> datatype;
    else 
        NewExp -> datatype = UNDEF; //To say its undefined as the subexpressions are of differnet types. THis will help us in analysys further
    
    NewExp -> u.binary.left = left;
    NewExp -> u.binary.right = right;

    return NewExp;
}

//Create a declaration 
Decl *create_decl(char *ident, int datatype, Exp *exp) {

    Decl *NewDec = (Decl*)malloc(sizeof(Decl));
    NewDec -> ident = ident;
    NewDec -> datatype = datatype;
    NewDec -> exp = exp;

    return NewDec;
}

struct Stmt *create_statement ( int type_of_st, Decl *decl, Exp *exp, Statements *stmts, struct Stmt *optional) {

    printf("STatement Creation \t");
    struct Stmt *statement = (struct Stmt*)malloc(sizeof(struct Stmt));
    statement -> stmt_type = type_of_st;
    switch (statement -> stmt_type) {
        case DECLARATION:   {
             statement -> body_of_stmt.declaration = decl;
        }
        break;
        case PRINT_ST | PRINT_ST: {
            statement -> body_of_stmt.exp = exp;
        }
        break;
        case WHILE_ST: {
            statement -> body_of_stmt.loop.exp = exp;
            statement -> body_of_stmt.loop.stmts = stmts;
        }
        break;
        case IF_ST | ELSE_ST | ELSE_IF_ST: {
            statement -> body_of_stmt.cond.exp = exp;
            statement -> body_of_stmt.cond.stmts = stmts;
            statement -> body_of_stmt.cond.op_else_if = optional;
        }
    }
    printf("STatemnt created \n");
    return statement;
}

Statements *create_program(Statements *stmts, struct Stmt *stmt) {
    Statements *program = (Statements*)malloc(sizeof(Statements));
    program -> stmts = stmts;
    program -> stmt = stmt;
    printf("UHIUHIUHUIH\n");
    return program;
}

void Print_AST(Statements *AST) {
    
}