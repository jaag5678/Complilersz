//This header file will define the tree that i want to define to create abstract syntax tree
#include<stdlib.h>
#include<string.h>

//Node that defines expressions 
typedef struct Exp {
    
    union {
        int ival;
        float fval;
        char *sval;
        int bval;
        char *ident;
        char op; //Define the operator that is working on the expression. A '\0' would imply no operation and the expression is going to be converted to a value
    }u;
    char datatype; //Could be int (i) or float (f)
    struct Exp *left;
    struct Exp *right;
}Exp;

//Node that defines Declarations
typedef struct Decl {
    char *keyword;
    char *ident;
    char datatype;
    Exp *exp;

}Decl;

//Node that defines a statement 


//I can define a separate function to define a leaf in the expression 
Exp *create_leaf_exp(char type, char *text_to_val);

//There will be just one function to create expressions 
Exp *create_exp(char *text, Exp *left, Exp *right, char op);

//Create a declaration 
Decl *create_decl(char *keyword, char *ident, char datatype, Exp *exp);

