#include"tree.h"


Exp *create_leaf_exp(char type, char *text_to_val) {
    Exp *Leaf = (Exp*)malloc(sizeof(Exp));

    if(type == 'i')
        Leaf -> u.ival = atoi(text_to_val);
    else if(type == 'f')
        Leaf -> u.fval = atof(text_to_val);
    
    Leaf -> datatype = type;

    return Leaf;
}


//There will be just one function to create expressions 
Exp * create_exp(char *text, Exp *left, Exp *right, char op) {

    Exp *NewExp = (Exp *)malloc(sizeof(Exp));
    //NewExp -> u = (Exp_opt *)malloc(sizeof(Exp_opt));
    //NewExp -> datatype = op;
    if(op == 'v')
         NewExp -> u.ident = text;
    else if(op == 'f') 
        NewExp -> u.fval = atof(text);
    else if(op == 'i') 
        NewExp -> u.ival = atoi(text);
    else if (op == 's')
        NewExp -> u.sval = text;
    else if (op == 'b')
        NewExp -> u.bval = *text;
    else 
        NewExp -> u.op = op;
    
    if(!left && !right) {
        NewExp -> datatype = op; //THis will be set to 'v' whcih means we do not know the identifier yet
    }
    else if(left -> datatype == right -> datatype) 
        NewExp -> datatype = left -> datatype;
    else 
        NewExp -> datatype = 'z'; //To say its undefined as the subexpressions are of differnet types. THis will help us in analysys further
    
    NewExp -> left = left;
    NewExp -> right = right;

    return NewExp;
}

//Create a declaration 
Decl *create_decl(char *keyword, char *ident, char datatype, Exp *exp) {

    Decl *NewDec = (Decl*)malloc(sizeof(Decl));

    NewDec -> keyword = keyword;
    NewDec -> ident = ident;
    NewDec -> datatype = datatype;
    NewDec -> exp = exp;

    return NewDec;
}