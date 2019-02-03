//This is the header file to define a symbol table for storing the variable records of the program
#include<stdlib.h>
#define HASH_SIZE 100
#include"essentials.h"

typedef struct Sym {
    int line_no;
    char *name;
    enum type datatype;
}Sym;

typedef struct SymTab {
    Sym *table[HASH_SIZE];
    struct SymTab *parent_scope;
}SymTab;


//Initialzie the table with the size given by the user
SymTab *init(SymTab *S, SymTab *parent);

//Hash tp map symbol to a place in table
int hash(char *name);

//To check if symbol found in table
int sym_found(SymTab *S, char *name);

//Add symbol to the table
int sym_add(SymTab *S, int line_no, char *ident, int type);



