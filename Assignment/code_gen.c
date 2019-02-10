#include"code_gen.h"

int find(Exp *exp, char *literal) {
    if(!exp) 
        return 0;
    if(exp -> op == NO_OP) {
        if(!strcmp(literal, exp -> u.literal)) {
            switch(exp -> datatype) {
                case INTEGER: return 1;
                case FLOATING: return 2;
                case STRING_DT: return 3;
                case BOOL_DT: return 4;
            }
        }
        else 
            return 0;
    }
    int x1 = find(exp -> u.binary.left, literal);
    int x2 = find(exp -> u.binary.right, literal);

    return x1 > x2 ? x1 : x2;
}



void create_C_exp(Exp *exp, FILE *fp, int tag) {
    if(!exp)
        return;

    if(exp -> op == NO_OP) {
    
        switch(tag) {
            case 0: fprintf(fp, "%s", exp -> u.literal);
            break;
            case 1: fprintf(fp, "*tmpi");
            break;
            case 2: fprintf(fp, "*tmpf");
            break;
            case 3: fprintf(fp, "*tmps");
            break;
            case 4: fprintf(fp, "*tmpb");
            break;
        }
        
        return;
    }

    //I should compare here for things related to string oeprations
    if(exp -> u.binary.left != NULL) {
        if(exp -> u.binary.left -> datatype == STRING_DT && exp -> u.binary.right -> datatype == STRING_DT) {
            switch(exp -> op) {
                case PLUS: {
                    fprintf(fp, "str_add(");
                    create_C_exp(exp -> u.binary.left, fp, tag);
                    fprintf(fp, ", ");
                    create_C_exp(exp -> u.binary.right, fp, tag);
                    fprintf(fp, ")");
                }
                break;
                case EQUAL: case NOT_EQUAL: case GRT :case LTN: case GT_EQ : case LT_EQ : {
                    fprintf(fp, "strcmp(");
                    create_C_exp(exp -> u.binary.left, fp, tag);
                    fprintf(fp, ", ");
                    create_C_exp(exp -> u.binary.right, fp, tag);
                    fprintf(fp, ")");

                    switch(exp -> op) {
                        case EQUAL: fprintf(fp, "==0");
                        break;
                        case NOT_EQUAL: fprintf(fp, "!=0");
                        break;
                        case GRT: fprintf(fp, ">0");
                        break;
                        case LTN: fprintf(fp, "<0");
                        break;
                        case GT_EQ: fprintf(fp, ">=0");
                        break;
                        case LT_EQ: fprintf(fp, "<=0");
                        break;
                    }
                }
            }
        return ;
        }
    }
    fprintf(fp, "(");
    create_C_exp(exp -> u.binary.left, fp, tag);



    switch(exp -> op) {
        case EQUAL: fprintf(fp, "==");
        break;
        case NOT_EQUAL: fprintf(fp, "!=");
        break;
        case OROR: fprintf(fp, "||");
        break;
        case ANDAND: fprintf(fp, "&&");
        break;
        case GT_EQ: fprintf(fp, ">=");
        break;
        case LT_EQ: fprintf(fp, "<=");
        break;
        case GRT: fprintf(fp, ">");
        break;
        case LTN: fprintf(fp, "<");
        break;
        case PLUS: fprintf(fp, "+");
        break;
        case MINUS: fprintf(fp, "-");
        break;
        case MULT: fprintf(fp, "*");
        break;
        case DIVIDE: fprintf(fp, "/");
    }
    create_C_exp(exp -> u.binary.right, fp, tag);
    fprintf(fp, ")");

}



void create_C_code(Statements *AST, FILE *fp) {

    if(!AST)
        return;
    
    create_C_code(AST -> stmts, fp);

    Stmt *stmt = AST -> stmt;

    int statement = stmt -> stmt_type;

    switch(statement) {

        case DECLARATION : {
            Decl *dec = stmt -> body_of_stmt.declaration;

            //Hey you need to check if initialization is done before hand or not 
            //We just need to see if the name of the variable resides in the expression 
            //Once we know it does, we need to just tag it, and sedn the tag status to the print expression function
            //This tag depends on if it is int, float , strong , boolean or nothing
            //Based on that we can use the tag to verify our claims.
            //We also need to send the var name itself as only those variables need to be replaced which are equal to that .
            int tag = 0;
            if(dec -> datatype == INTEGER || dec ->datatype == FLOATING || dec -> datatype == STRING_DT || dec -> datatype == BOOL_DT) {
                tag = find(dec-> exp, dec -> ident);
                switch(tag) {
                    case 1 : fprintf(fp, "tmpi = &%s;\n", dec -> ident);
                    break;
                    case 2 : fprintf(fp, "tmpf = &%s;\n", dec -> ident);
                    break;
                    case 3 : fprintf(fp, "tmps = &%s;\n", dec -> ident);
                    break;
                    case 4 : fprintf(fp, "tmpb = &%s;\n", dec -> ident);
                    break;
                }
            }
            int type = dec -> datatype;
            switch(type) {
                case INTEGER: fprintf(fp, "int %s ", dec -> ident);
                break;
                case FLOATING: fprintf(fp, "float %s", dec -> ident);
                break;
                case STRING_DT: fprintf(fp, "char *%s", dec -> ident);
                break;
                case BOOL_DT: fprintf(fp, "bool %s", dec -> ident);
                break;
                default: fprintf(fp, "%s", dec -> ident);
            }
            fprintf(fp, "=");
            if(dec -> exp != NULL) {
                create_C_exp(dec -> exp, fp, tag);
            }
            else {
                switch(type) {
                    case INTEGER : fprintf(fp, "0");
                    break;
                    case FLOATING : fprintf(fp, "0.0");
                    break;
                    case STRING_DT : fprintf(fp, "\"\"");
                    break;
                    case BOOL_DT : fprintf(fp, "false");
                    break;
                }
            }
            fprintf(fp, ";\n");
        }
        break;
        
        case PRINT_ST: case READ_ST: {
            int type = stmt -> body_of_stmt.read_print -> datatype;
            
            if(type != BOOL_DT) {

                if(statement == PRINT_ST)
                    fprintf(fp, "printf(\"");
                else
                    fprintf(fp, "scanf(\"");
                switch(type) {
                    case INTEGER: fprintf(fp, "%%d\", ");
                    break;
                    case FLOATING: fprintf(fp, "%%f\", ");
                    break;
                    case STRING_DT: fprintf(fp, "%%s\", ");
                    break;
                }
                if(statement == READ_ST)
                    fprintf(fp, "&");
                //Print the expression here by calling print expression function
                create_C_exp(stmt -> body_of_stmt.read_print, fp, 0);
                fprintf(fp, ");\n");
            }
            else {
                if(statement == PRINT_ST) {
                    fprintf(fp, "if (");
                    create_C_exp(stmt -> body_of_stmt.read_print, fp, 0);
                    fprintf(fp, ")");
                    fprintf(fp, "printf(\"true\"); \n");
                    fprintf(fp, "else printf(\"false\");\n");
                    
                }
                else {
                    //Wrtie a fucntion to take input boolean value as "true" or "false"
                    create_C_exp(stmt -> body_of_stmt.read_print, fp, 0); 
                    fprintf(fp, "= bool_inp(); \n");
                }
            }
            
        }
        break;

        case WHILE_ST: {
            fprintf(fp, "while (");
            //Print the expression
            create_C_exp(stmt -> body_of_stmt.loop.exp, fp, 0);
            fprintf(fp, ") { \n");
            create_C_code(stmt -> body_of_stmt.loop.stmts, fp);
            fprintf(fp, "}\n");
        }
        break;

        case IF_ST : case ELSE_IF_ST : case ELSE_ST: {
            while(1) {
                switch(statement) {
                    case IF_ST: fprintf(fp, "if (");
                    break;
                    case ELSE_IF_ST: fprintf(fp, "else if (");
                    break;
                    case ELSE_ST: fprintf(fp, "else ");
                    break;
                }
                if(stmt -> body_of_stmt.cond.exp != NULL) {
                    //Print the expression 
                    create_C_exp(stmt -> body_of_stmt.cond.exp, fp, 0);
                    fprintf(fp, ") ");
                }
                fprintf(fp, "{ \n");
                create_C_code(stmt -> body_of_stmt.cond.stmts, fp);
                fprintf(fp, "}\n");
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

void code_gen(Statements *AST, char *filename) {

    //Later remember to put all this in a file 
   

    //Create a file pointer
    FILE *c_file;

    c_file = fopen(filename, "w+");

    fprintf(c_file,"#include<stdio.h>\n#include<stdbool.h>\n#include<string.h>\n#include<stdlib.h>\n");
    
    //Need to add helper functions 

    FILE *fp; 
    fp = fopen("helper_func.c", "r+");

    char *c = (char *)malloc(sizeof(char) * 100);

    while(fgets(c, 100, fp) != NULL) 
        fprintf(c_file, "%s", c);
    
    fclose(fp);
    
    fprintf(c_file, "\n\nint main() {\n");

    create_C_code(AST, c_file);
    fprintf(c_file, "return 0; \n } \n");
    fclose(c_file);
}