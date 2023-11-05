#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "st.h" 

VTYPE_PRIMITIVE getPrimitiveType(char *type){
    if(strcmp(type, "bool") == 0){
        return TYPE_BOOL;
    } else if(strcmp(type, "char") == 0){
        return TYPE_CHAR;
    } else if(strcmp(type, "int_8") == 0){
        return TYPE_INT_8;
    } else if(strcmp(type, "int_16") == 0){
        return TYPE_INT_16;
    } else if(strcmp(type, "int_32") == 0){
        return TYPE_INT_32;
    } else if(strcmp(type, "int_64") == 0){
        return TYPE_INT_64;
    } else if(strcmp(type, "uint_8") == 0){
        return TYPE_UINT_8;
    } else if(strcmp(type, "uint_16") == 0){
        return TYPE_UINT_16;
    } else if(strcmp(type, "uint_32") == 0){
        return TYPE_UINT_32;
    } else if(strcmp(type, "uint_64") == 0){
        return TYPE_UINT_64;
    } else if(strcmp(type, "float_32") == 0){
        return TYPE_FLOAT_32;
    } else if(strcmp(type, "float_64") == 0){
        return TYPE_FLOAT_64;
    }
    exit(1);
}
