#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <class_loader/bytes.h>
#include <class_loader/bytes.h>
#include <class_loader/constant_pool.h>

struct attribute_info_struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u1 *info;
} typedef attribute_info;

struct exception_table_struct{
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} typedef exception_table;


struct code_attribute_struct{
    u2 attribute_name_index; 
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    exception_table *exeption;
    u2 attributes_count;
    attribute_info *attributes;
} typedef code_attribute;


attribute_info* create_attributes(FILE *file, u2 count);
code_attribute* get_code_attribute(attribute_info* attribute, u2 count, cp_info *constant_pool);
#endif