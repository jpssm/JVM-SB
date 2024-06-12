#ifndef FIELD_H
#define FIELD_H

#include <class_loader/bytes.h>
#include <class_loader/attribute.h>

typedef struct field_info_struct
{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
} field_info;

field_info *create_fields(FILE *file, u2 count);

#endif