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
    int map_val = hash(name);
    if(S -> table[map_val] == NULL)
        return -1;
    return map_val;
}

int sym_add(SymTab *S, int lineno, char *name, int type) {
    int map_val = sym_found(S, name);
    if(map_val == -1) {
        return 0;
    }

    S -> table[map_val] = (Sym *)malloc(sizeof(Sym));
    S -> table[map_val] -> name = name;
    S -> table[map_val] -> datatype = type;
    S -> table[map_val] -> line_no = lineno;

    return 1;
}