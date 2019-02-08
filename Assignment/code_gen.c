#include"code_gen.h"

void create_C_exp(Exp *exp) {
    if(!exp)
        return;

    if(exp -> op == NO_OP) {
        printf("%s", exp -> u.literal);
        return;
    }

    printf("(");
    create_C_exp(exp -> u.binary.left);

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
    create_C_exp(exp -> u.binary.right);
    printf(")");

}



void create_C_code(Statements *AST) {

    if(!AST)
        return;
    
    create_C_code(AST -> stmts);

    Stmt *stmt = AST -> stmt;

    int statement = stmt -> stmt_type;

    switch(statement) {

        case DECLARATION : {
            Decl *dec = stmt -> body_of_stmt.declaration;

            int type = dec -> datatype;
            switch(type) {
                case INTEGER: printf("int %s ", dec -> ident);
                break;
                case FLOATING: printf("float %s", dec -> ident);
                break;
                case STRING_DT: printf("char *%s", dec -> ident);
                break;
                case BOOL_DT: printf("bool %s", dec -> ident);
                break;
                default: printf("%s", dec -> ident);
            }
            if(dec -> exp != NULL) {
                printf("=");
                create_C_exp(dec -> exp);
            }
            printf(";\n");
        }
        break;
        
        case PRINT_ST: case READ_ST: {
            int type = stmt -> body_of_stmt.read_print -> datatype;
            if(statement == PRINT_ST)
                printf("printf(\"");
            else
                printf("scanf(\"");
            switch(type) {
                case INTEGER: printf("%%d");
                break;
                case FLOATING: printf("%%f");
                break;
                case STRING_DT: printf("%%s");
                break;
                case BOOL_DT: printf("%%d");
                break; 
            }
            printf("\", ");
            if(statement == READ_ST)
                printf("&");
            //Print the expression here by calling print expression function
            create_C_exp(stmt -> body_of_stmt.read_print);
            printf(");\n");
        }
        break;

        case WHILE_ST: {
            printf("while (");
            //Print the expression
            create_C_exp(stmt -> body_of_stmt.loop.exp);
            printf(") { \n");
            create_C_code(stmt -> body_of_stmt.loop.stmts);
            printf("}\n");
        }
        break;

        case IF_ST : case ELSE_IF_ST : case ELSE_ST: {
            while(1) {
                switch(statement) {
                    case IF_ST: printf("if (");
                    break;
                    case ELSE_IF_ST: printf("else if (");
                    break;
                    case ELSE_ST: printf("else ");
                    break;
                }
                if(stmt -> body_of_stmt.cond.exp != NULL) {
                    //Print the expression 
                    create_C_exp(stmt -> body_of_stmt.cond.exp);
                    printf(") ");
                }
                printf("{ \n");
                create_C_code(stmt -> body_of_stmt.cond.stmts);
                printf("}\n");
                if(stmt -> body_of_stmt.cond.op_else_if != NULL) {
                    statement = stmt -> body_of_stmt.cond.op_else_if -> stmt_type;
                    stmt = stmt -> body_of_stmt.cond.op_else_if;
                }
                else
                    break;
            }
        }
        break;
    }
}