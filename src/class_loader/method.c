#include "bytes.c"
#include <class_loader/attribute.h>
#include <class_loader/field.h>
#include <class_loader/method.h>
#include <class_loader/constant_pool.h>
#include <class_loader/class_file.h>
#include <string.h>

method_info *create_methods(FILE *file, u2 count, cp_info *constant_pool)
{
    if (count <= 0)
    {
        return NULL;
    }
    method_info *methods, *method;
    methods = (method_info *)malloc(sizeof(method_info) * count);
    for (method = methods; method < methods + count; method++)
    {
        method->access_flags = u2Read(file);
        method->name_index = u2Read(file);
        method->descriptor_index = u2Read(file);
        method->attributes_count = u2Read(file);
        method->attributes = create_attributes(file, method->attributes_count);
        method->code_attribute = get_code_attribute(method->attributes, method->attributes_count, constant_pool);
        
    }
    return methods;
}