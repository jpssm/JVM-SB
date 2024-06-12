#include "bytes.c"
#include <class_loader/attribute.h>
#include <class_loader/field.h>
#include <class_loader/method.h>
#include <class_loader/constant_pool.h>
#include <class_loader/class_file.h>

field_info *create_fields(FILE *file, u2 count)
{

    if (count <= 0)
    {
        return NULL;
    }
    field_info *fields, *field;
    fields = (field_info *) malloc(sizeof(field_info) * count);
    for (field = fields; field < fields + count; field++)
    {
        // reading main data
        field->access_flags = u2Read(file);

        field->name_index = u2Read(file);
        field->descriptor_index = u2Read(file);
        field->attributes_count = u2Read(file);
        
        // reading attributes
       field->attributes = create_attributes(file, field->attributes_count);
    }
    return fields;
}
