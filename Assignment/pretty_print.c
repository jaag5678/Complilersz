#include"pretty_print.h"



void print_exp(Exp *exp) {
    if(!exp)
        return;
    if(exp -> op == -1) {
        switch(exp -> datatype) {
            case INTEGER: printf("%d", exp -> u.ival);
        }
        return;
    }
    printf("(");
    print_exp(exp -> u.binary.left);
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
    printf(")");
}


void Print_AST(Statements *AST) {
    if(!AST)
        return;
        
    Print_AST(AST -> stmts);
    //printf("I AM HERE \n");
    switch (AST -> stmt -> stmt_type) {

        case DECLARATION: {
            //printf("HH \n");
            Decl *temp = AST -> stmt -> body_of_stmt.declaration;
            switch(temp -> datatype) {
                case INTEGER: printf("var %s : int ", temp -> ident);
                break;
                case FLOATING: printf("var %s : float ", temp -> ident);
                break;
                case STRING_DT: printf("var %s : string ", temp -> ident);
                break;
                case BOOL_DT: printf("var %s : boolean ", temp -> ident);
                break;
                case UNDEF: printf("%s = ", temp -> ident);
            }
            if(temp -> exp != NULL) 
                print_exp(temp -> exp);
            printf(";\n");
            
        }
        break;
    }
}