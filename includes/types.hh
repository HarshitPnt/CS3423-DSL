// Types of Constants
#ifndef TYPES_HH
#define TYPES_HH
typedef enum ConstTYPE
{
    CINT,
    CFLOAT,
    CCHAR,
    CSTRING,
    CBOOL,
} CTYPE;

typedef enum VariableTYPE_Primitive
{
    TYPE_INT_8,
    TYPE_INT_16,
    TYPE_INT_32,
    TYPE_INT_64,
    TYPE_FLOAT_32,
    TYPE_FLOAT_64,
    TYPE_UINT_8,
    TYPE_UINT_16,
    TYPE_UINT_32,
    TYPE_UINT_64,
    TYPE_CHAR,
    TYPE_BOOL,
} VTYPE_PRIMITIVE;

typedef enum VariableTYPE_Automata
{
    TYPE_CFG,
    TYPE_DFA,
    TYPE_NFA,
    TYPE_PDA
} VTYPE_AUTOMATA;

typedef enum VariableTYPE_Set
{
    TYPE_USET,
    TYPE_OSET
} VTYPE_SET;

typedef enum VariableTYPE_SR
{
    TYPE_STR,
    TYPE_REGEX,
    TYPE_STRU
} VTYPE_SR;

VTYPE_PRIMITIVE getPrimitiveType(char *type);
VTYPE_AUTOMATA getAutomataType(char *type);
VTYPE_SET getSetType(char *type);
VTYPE_SR getSRType(char *type);
#endif
