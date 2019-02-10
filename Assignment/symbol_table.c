#include"symbol_table.h"

SymTab *init(SymTab *S, SymTab *parent) {
    S = (SymTab *)malloc(sizeof(SymTab));
    S -> parent_scope = parent;
    for (int i = 0; i < HASH_SIZE; i++)
        S -> table[i] = NULL;
    return S;    
} 

int hash(char *name) {
    unsigned int hash = 0;
    while (*name) 
        hash = (hash << 1) + *name++;
    return hash % HASH_SIZE;
}


Sym *sym_found(SymTab *S, char *name, int bit) {
    if(!S)
        return NULL;
    int map_val = hash(name);
    //printf("Map value %d \n", map_val);
    //The bit value indicates whether to do a scope check or just a normal check, good for declaration analysis
    if(S -> table[map_val] == NULL) {
        //printf("JDGHjhGDFJHG \n");
        if(bit)
            return sym_found(S -> parent_scope, name, bit);
        return NULL;
    }
    return S -> table[map_val];
}

int sym_add(SymTab *S, int lineno, char *name, int type) {
    //printf("Belh \n");
    int map_val = hash(name);
    //printf("Map value gffggffg %d \n", map_val);
    S -> table[map_val] = (Sym *)malloc(sizeof(Sym));
    S -> table[map_val] -> name = name;
    S -> table[map_val] -> datatype = type;
    S -> table[map_val] -> line_no = lineno;

    return 1;
}

void check_exp_symbols(SymTab *S, Exp *exp) {
     //printf("Z \n");
    if(!exp)
        return;
    
    switch(exp -> op) {
        case NO_OP: {
            if(exp -> datatype == VAR_DT) {
                Sym *E = sym_found(S, exp -> u.literal, 1);
                //printf("Z \n");
                if(!E) {
                    printf("Identifier %s not defined \n", exp -> u.literal);
                    exit(1);
                }
                int map = hash(exp -> u.literal);
                printf("%s %d \n", exp -> u.literal, map);
                if(E -> datatype == STRING_DT)
                    printf("Ass Dt \n");
                exp -> datatype = E -> datatype;
            }
        }
        break;
        default: {
            check_exp_symbols(S, exp -> u.binary.left);
            check_exp_symbols(S, exp -> u.binary.right);
            
            if(exp -> u.binary.left == NULL) {
                int type = exp -> u.binary.right -> datatype;
                int choice = exp -> op;

                switch(choice) {
                    case MINUS : {
                        if(type == INTEGER || type == FLOATING)
                            exp -> datatype = type;
                        else {
                            printf("Invalid operation for UNARY for given type of expression \n");
                            exit(1);
                        }
                    }
                    break;
                    case COMPL : {
                        printf("Here \n");
                        if(type == BOOL_DT) {
                            //printf("%d \n", type);
                            exp -> datatype = type;
                            //printf("%d \n", exp -> datatype);
                        }
                        else {
                            printf("Invalid type to do a comliment operation \n");
                            exit(1);
                        }
                    }
                    break;
                }
            }
            else  {
                int type_left = exp -> u.binary.left -> datatype;
                int type_right = exp -> u.binary.right -> datatype;
                //Lets evaluate for Binary 
                int choice = exp -> op;
                switch(choice) {
                    case PLUS : case MINUS : case MULT: case DIVIDE: {
                        if(type_left == INTEGER && type_right == INTEGER) 
                            exp -> datatype = INTEGER;
                        else if (type_left == FLOATING && type_right == FLOATING)
                            exp -> datatype = FLOATING;
                        else if ((type_left == FLOATING || type_left == INTEGER ) && (type_right == FLOATING || type_right == INTEGER))
                            exp -> datatype = FLOATING;
                        else if (exp -> op == PLUS && (type_left == STRING_DT && type_right == STRING_DT)) {
                            printf("Im here \n");
                            exp -> datatype = STRING_DT;
                        }
                        else {
                            printf("Incorrect type based operation \n");
                            exit(1);
                        }
                    }
                    break;
                    case ANDAND: case OROR : {
                        if(type_left == BOOL_DT && type_right == BOOL_DT)
                            exp -> datatype = BOOL_DT;
                        else {
                            printf("Invalid Logical operation done :( \n");
                            exit(1);
                        }
                    }
                    break;
                    case EQUAL : case NOT_EQUAL : case GT_EQ : case LT_EQ : case GRT : case LTN : {
                        if(type_left == type_right) {
                            exp -> datatype = BOOL_DT;
                        }
                        else {
                            printf("Invalid relational operation \n ");
                            exit(1);
                        }
                    }
                    break;
                }
            }
        }
    }
} 

void print_symbol(SymTab *S, char *name) {
    int x = hash(name);
    //printf("%d \n", x);
    printf("Symbol name : %s ", name);

    printf(" At line %d \n", S -> table[x] ->line_no);

    //DO ADD THE TYPE OF SYMBOL ADDED HERE
}


int build_symbol_table(Statements *AST, SymTab *S) {

    if(!AST)
        return 0;

    build_symbol_table(AST -> stmts, S);

    Stmt *stmt = AST -> stmt;
    switch(stmt -> stmt_type) {
        case DECLARATION: {
            Decl *dec = stmt -> body_of_stmt.declaration;
            int type = dec -> datatype;
            switch(type) {
                case BOOL_DT: case INTEGER: case FLOATING: case STRING_DT: {
                    if(sym_found(S, dec -> ident, 0)) {
                        printf("Redefinition of Identifier %s that already exists\n", dec -> ident);
                        exit(1);
                    }
                    //printf("I'm here \n");
                    sym_add(S, stmt -> lineno, dec -> ident, dec -> datatype);
                    //printf("I'm here b \n");
                    check_exp_symbols(S, dec -> exp);
                    //printf("Z \n");

                    print_symbol(S, dec -> ident);

                    Sym *E = sym_found(S,dec -> ident, 1);
                    if(dec -> exp != NULL) {
                        if(E -> datatype == FLOATING  && (dec -> exp -> datatype == INTEGER || dec -> exp -> datatype == FLOATING)) {

                        }
                        else if(dec -> exp -> datatype != E -> datatype) {
                            printf("Assignment error: Conflicting types \n");
                            exit(1);
                        }
                    }
                }
                break;
                default: {
                    Sym *E = sym_found(S,dec -> ident, 1);
                    if(!E) {
                        printf("Identifier  %s not defined \n", dec -> ident);
                        exit(1);
                    }
                    //dec -> datatype = E -> datatype; 
                    dec -> datatype = VAR_DT;
                    if(E -> datatype == STRING_DT)
                        printf("AssGGG Dt \n");
                    //printf("H %d \n", dec -> exp -> datatype);
                    check_exp_symbols(S, dec -> exp);
                    //printf("N %d \n", dec -> exp -> datatype);

                    if(E -> datatype == FLOATING  && (dec -> exp -> datatype == INTEGER || dec -> exp -> datatype == FLOATING)) {

                    }
                    else if(dec -> exp -> datatype != E -> datatype) {
                        printf("Assignment error: Conflicting types \n");
                        exit(1);
                    }

                    //printf("%s \n", dec -> ident);
                   
                }
                break;
            }
        }
        break;

        case PRINT_ST:  {
            printf("In print eval of exp \n");
            check_exp_symbols(S, stmt -> body_of_stmt.read_print);
        }
        break;
        case READ_ST: {
            printf("In read eval of exp \n");
            check_exp_symbols(S, stmt -> body_of_stmt.read_print);
        }
        break;
        case WHILE_ST: {
            check_exp_symbols(S, stmt -> body_of_stmt.loop.exp);
            //Now I need to ensure that the expression type is boolean otherwise I will quitt
            if(stmt -> body_of_stmt.loop.exp -> datatype != BOOL_DT) {
                printf("Invalid expreesion as a loop condition \n");
                exit(1);
            }

            //Now to create a new table and link it to the parent table
            SymTab *New = init(New, S);
            build_symbol_table(stmt -> body_of_stmt.loop.stmts, New);
            //printf("I am out ! \n");
        }
        break;

        case IF_ST: case ELSE_IF_ST: case ELSE_ST: { 
            while(1) {
                int c = stmt -> stmt_type;

                switch(c) {
                    case IF_ST : case ELSE_IF_ST: {
                        check_exp_symbols(S, stmt -> body_of_stmt.cond.exp);
                    }
                    break;
                }

                SymTab *New = (SymTab *)malloc(sizeof(SymTab));
                New = init(New, S);
                build_symbol_table(stmt -> body_of_stmt.cond.stmts, New);

                if(stmt -> body_of_stmt.cond.op_else_if != NULL) {
                    stmt = stmt -> body_of_stmt.cond.op_else_if;
                    c = stmt -> stmt_type;
                }
                else
                    break;
            }
        }
        break;

    }

    return 0;    
}