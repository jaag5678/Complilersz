//Header file for containing stuff to generate code of minilang to C

#include"symbol_table.h"

void code_gen(Statements *AST); //Just an extra function to write to file (.c file) along with adding a few header files required by Minilang code 
void create_C_exp(Exp *exp);
void create_C_code(Statements *AST);