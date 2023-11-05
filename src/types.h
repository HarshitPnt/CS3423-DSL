#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Types of Constants 
typedef enum ConstTYPE {
    CINT,
    CFLOAT,
    CCHAR,
    CSTRING,
    CBOOL,
} CTYPE;

typedef enum VariableTYPE_Standard {
    INT_8,
    INT_16,
    INT_32,
    INT_64,
    FLOAT_32,
    FLOAT_64,
    UINT_8,
    UINT_16,
    UINT_32,
    UINT_64,
    CHAR,
    BOOL,
    STRING
} VTYPE_STANDARD;

typedef enum VariableTYPE_Complex {
    OSET,
    USET,
    REGEX,
    CFG,
    DFA,
    NFA,
    PDA
} VTYPE_COMPLEX;

VTYPE_STANDARD getStandardType(char *type);
VTYPE_COMPLEX getComplexType(char *type);
