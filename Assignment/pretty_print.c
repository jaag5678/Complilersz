#include"pretty_print.h"



void print_exp(Exp *exp) {
    if(!exp)
        return;
    if(exp -> op == -1) {
        printf("%s", exp -> u.literal);

        return;
    }
    printf("(");
    print_exp(exp -> u.binary.left);
    //printf(" x ");
    switch(exp -> op) {
        case EQUAL: printf("==");
        break;
        case NOT_EQUAL: printf("!=");
        break;
        case OROR: printf("||");
        break;
        case ANDAND: printf("&&");
        break;
        case GT_EQ: printf(">=");
        break;
        case LT_EQ: printf("<=");
        break;
        case GRT: printf(">");
        break;
        case LTN: printf("<");
        break;
        case PLUS: printf("+");
        break;
        case MINUS: printf("-");
        break;
        case MULT: printf("*");
        break;
        case DIVIDE: printf("/");
    }
    //printf(" ");
    print_exp(exp ->u.binary.right);
    //printf(" x ");
    printf(")");
}


void Print_AST(Statements *AST) {
    if(!AST)
        return;
        
    Print_AST(AST -> stmts);
    //printf("I AM HERE \n");
    struct Stmt *stmt = AST -> stmt;
    int c = AST -> stmt -> stmt_type;
    switch (c) {

        case DECLARATION: {
            //printf("HH \n");
            Decl *temp = stmt -> body_of_stmt.declaration;
            switch(temp -> datatype) {
                case INTEGER: printf("var %s : int", temp -> ident);
                break;
                case FLOATING: printf("var %s : float", temp -> ident);
                break;
                case STRING_DT: printf("var %s : string", temp -> ident);
                break;
                case BOOL_DT: printf("var %s : boolean", temp -> ident);
                break;
                default: printf("%s", temp -> ident);
            }
            if(temp -> exp != NULL) {
                printf(" = ");
                print_exp(temp -> exp);
            }
            printf(";\n");
        }
        break;
        case PRINT_ST : {
            printf("print (");
            print_exp(stmt->body_of_stmt.read_print);
            printf(");\n");
        }
        break;
        case READ_ST: {
            printf("read (");
            print_exp(stmt->body_of_stmt.read_print);
            printf(");\n");
        }
        break;
        case WHILE_ST: {
            printf("while (");
            print_exp(stmt -> body_of_stmt.loop.exp);
            printf(") {\n \t");
            Print_AST(stmt -> body_of_stmt.loop.stmts);
            printf("}\n");
        }
        break;

        case IF_ST: case ELSE_IF_ST : case ELSE_ST: {
            while(1) {
                switch(c) {
                    case IF_ST: printf("if (");
                    break;
                    case ELSE_IF_ST: printf("else if (");
                    break;
                    case ELSE_ST: printf("else ");
                    break;
                }
                if(stmt -> body_of_stmt.cond.exp != NULL) {
                    print_exp(stmt -> body_of_stmt.cond.exp);
                    printf(") ");
                }
                printf("{ \n");
                Print_AST(stmt -> body_of_stmt.cond.stmts);
                printf("} \n");
                if(stmt -> body_of_stmt.cond.op_else_if != NULL) {
                    c = stmt -> body_of_stmt.cond.op_else_if -> stmt_type;
                    stmt = stmt -> body_of_stmt.cond.op_else_if;
                }
                else 
                    break;
            }
        }
        break;
            
    }
}