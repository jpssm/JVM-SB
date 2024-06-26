#ifndef OBJECT_C
#define OBJECT_C


#include <runtime_data/object.h>

Array *create_array(u4 size, u1 type){
    Array *new_array = malloc(sizeof(Array));
    new_array->atype = type;
    new_array->size = size;
    switch (type)
    {
    case T_BOOLEAN:
        new_array->content = malloc(sizeof(uint8_t)*size);
        break;
    case T_CHAR:
        new_array->content = malloc(sizeof(uint8_t)*size);
        break;
    case T_FLOAT:
        new_array->content = malloc(sizeof(float)*size);
        break;
    case T_DOUBLE:
        new_array->content = malloc(sizeof(double)*size);
        break;
    case T_BYTE:
        new_array->content = malloc(sizeof(int8_t)*size);
        break;
    case T_INT:
        new_array->content = malloc(sizeof(int32_t)*size);
        break;    
    case T_LONG:
        new_array->content = malloc(sizeof(int64_t)*size);
        break; 
    default:
        printf("\nErro: Tipo de array invalido!\n");
        exit(NULL);
        break;
    }
    return new_array;
};



#endif