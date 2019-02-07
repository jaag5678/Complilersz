//This is the header file to define a symbol table for storing the variable records of the program
#include<stdio.h>
#include<stdlib.h>
#include"tree.h"

#define HASH_SIZE 317

typedef struct Sym {
    int line_no;
    char *name;
    enum type datatype;
}Sym;

typedef struct SymTab {
    Sym *table[HASH_SIZE];
    struct SymTab *parent_scope;
}SymTab;


//Function to build the entire symbol table
int build_symbol_table(Statements *AST, SymTab *S);

SymTab *init(SymTab *S, SymTab *parent);

//Hash tp map symbol to a place in table
int hash(char *name);

//To check if symbol found in table
Sym *sym_found(SymTab *S, char *name, int bit);

//Add symbol to the table
int sym_add(SymTab *S, int line_no, char *ident, int type);

//Check if identifier exists in valid scopes
int check_valid_scope(SymTab *S, char *name);

//Funnction to verify symbols in expresssions are actually defined before in symbol table
void check_exp_symbols(SymTab *S, Exp *exp);

//Print Symbol
void print_symbol(SymTab *S, char *name);
