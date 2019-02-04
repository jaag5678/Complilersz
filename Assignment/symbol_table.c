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

int sym_found(SymTab *S, char *name) {
    if(!S)
        return -1;
    int map_val = hash(name);
    if(S -> table[map_val] == NULL)
        return -1;
    return map_val;
}

int sym_add(SymTab *S, int lineno, char *name, int type) {
    int map_val = sym_found(S, name);
    if(map_val != -1) {
        return 0;
    }
    map_val = hash(name);
    //printf("Map value %d \n", map_val);
    S -> table[map_val] = (Sym *)malloc(sizeof(Sym));
    S -> table[map_val] -> name = name;
    S -> table[map_val] -> datatype = type;
    S -> table[map_val] -> line_no = lineno;

    return 1;
}

void print_symbol(SymTab *S, char *name) {
    int x = hash(name);

    printf("Symbol name : %s", name);

    printf(" At line %d \n", S -> table[x] ->line_no);

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
                case UNDEF: {
                    if(sym_found(S,dec -> ident) == -1) {
                        printf("Identifier  %s not defined \n", dec -> ident);
                        exit(1);
                    }
                    dec -> datatype = S -> table[sym_found(S, dec -> ident)] -> datatype; 
                }
                break;
                default : {
                    if(sym_found(S, dec -> ident) != -1) {
                        printf("Redefinition of Identifier %s that already exists\n", dec -> ident);
                        exit(1);
                    }
                    sym_add(S, stmt -> lineno, dec -> ident, dec -> datatype);
                    print_symbol(S, dec -> ident);
                }
            }
        }
        break;

    }

    return 0;    
}