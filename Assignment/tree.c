#include"tree.h"


Exp *create_leaf_exp(int type, char *text_to_val) {
    Exp *Leaf = (Exp*)malloc(sizeof(Exp));
    Leaf -> u.literal = text_to_val;
    Leaf -> datatype = type; //IF it is an identifier, we must obtain the type ffrom the symbol table. Check this later

    Leaf -> op = NO_OP;

    //printf("LEaf done \n");
    return Leaf;
}


//There will be just one function to create expressions 
Exp * create_exp(Exp *left, Exp *right, int op) {

    Exp *NewExp = (Exp *)malloc(sizeof(Exp));
    NewExp -> op = op;
    
    //if(left -> datatype == right -> datatype) 
      //  NewExp -> datatype = left -> datatype;
    //else 
        //NewExp -> datatype = UNDEF; //To say its undefined as the subexpressions are of differnet types. THis will help us in analysys further
    
    //printf("Left %s Right %s\n", left->u.literal, right->u.literal);
    NewExp -> u.binary.left = left;
    NewExp -> u.binary.right = right;

    return NewExp;
}

//Create a declaration 
Decl *create_decl(char *ident, int datatype, Exp *exp) {

    //printf(" %s \n", ident);
    //printf(" %d \n", datatype);
    //printf(" %d \n", exp -> op);
    Decl *NewDec = (Decl*)malloc(sizeof(Decl));
    NewDec -> ident = ident;
   
    NewDec -> exp = exp;

    NewDec -> datatype = datatype;

    return NewDec;
}

struct Stmt *create_statement (int lineno, int type_of_st, Decl *decl, Exp *exp, Statements *stmts, struct Stmt *optional) {

    //printf("STatement Creation \t");
    Statements *s = (Statements *)malloc(sizeof(Statements));
    s -> stmts = NULL;
    s -> stmt = (Stmt*)malloc(sizeof(Stmt));
    Stmt *statement = s -> stmt;
    statement -> lineno = lineno;
    statement -> stmt_type = type_of_st;
    switch (statement -> stmt_type) {
        case DECLARATION:   {
            //printf("HID \n");
             statement -> body_of_stmt.declaration = decl;
        }
        break;
        case PRINT_ST: case READ_ST: {
            //printf("%s ", exp -> u.ident);
            statement -> body_of_stmt.read_print = exp;
        }
        break;
        case WHILE_ST: {
            statement -> body_of_stmt.loop.exp = exp;
            statement -> body_of_stmt.loop.stmts = stmts;
        }
        break;
        case IF_ST: case ELSE_ST: case ELSE_IF_ST: {
            statement -> body_of_stmt.cond.exp = exp;
            statement -> body_of_stmt.cond.stmts = stmts;
            statement -> body_of_stmt.cond.op_else_if = optional;
        }
        break;
    }
    //printf("STatemnt created \n");
    return statement;
}

Statements *create_program(Statements *stmts, struct Stmt *stmt) {
    Statements *program = (Statements*)malloc(sizeof(Statements));
    program -> stmts = stmts;
    program -> stmt = stmt;
    //printf("UHIUHIUHUIH\n");
    return program;
}

