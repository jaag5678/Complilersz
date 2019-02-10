//Header file for containing stuff to generate code of minilang to C

#include"symbol_table.h"


int find(Exp *exp, char *literal);
void code_gen(Statements *AST, char *filename); //Just an extra function to write to file (.c file) along with adding a few header files required by Minilang code 
void create_C_exp(Exp *exp, FILE *fp, int tag);
void create_C_code(Statements *AST, FILE *fp);