//Will store the essential symbols required 


//Enumerator for type of operation
enum operation{
    OROR,
    ANDAND,
    EQUAL,
    NOT_EQUAL,
    GT_EQ,
    LT_EQ,
    GRT,
    LTN,
    PLUS,
    MINUS,
    MULT,
    DIVIDE,
    COMPL
};

//Enumerator for datatype
enum type {
    INTEGER, 
    FLOATING, 
    STRING_DT, 
    BOOL_DT,
    VAR_DT,
    UNDEF
};

//Enumerator for type of statements
enum statement_kind { 
    DECLARATION,
    PRINT_ST,
    READ_ST,
    WHILE_ST,
    IF_ST,
    ELSE_ST,
    ELSE_IF_ST
};
