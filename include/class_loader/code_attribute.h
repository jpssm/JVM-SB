#ifndef CODE_ATTRIBUTE_H
#define CODE_ATTRIBUTE_H


#include <class_loader/bytes.h>
#include <class_loader/field.h>
#include <class_loader/method.h>
#include <class_loader/constant_pool.h>
#include <class_loader/class_file.h>

typedef struct code_attribute_struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_lenght;
    u1 *code;
    u2 exception_table_length;
    u2 *exception_table;
    u2 attributes_count;
    u1 *attributes; 
} code_attribute;



code_attribute* create_code_attribute(FILE *file);
#endif