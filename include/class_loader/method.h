#ifndef METHOD_H
#define METHOD_H


#include <class_loader/bytes.h>
#include <class_loader/attribute.h>
#include <class_loader/constant_pool.h>

typedef struct method_info_struct
{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
    code_attribute *code_attribute;
    

} method_info;

method_info *create_methods(FILE *file, u2 count, cp_info *constant_pool);



#endif