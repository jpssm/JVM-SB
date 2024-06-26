// Modulo responsavel pelas Struct e funções para manipular o ClassFile
#ifndef CLASS_FILE_H
#define CLASS_FILE_H


#include <class_loader/bytes.h>
#include <class_loader/attribute.h>
#include <class_loader/field.h>
#include <class_loader/method.h>
#include <class_loader/constant_pool.h>

typedef struct class_file
{
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info *constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces;
    u2 fields_count;
    field_info *fields;
    
    u2 methods_count;
    method_info *methods;
    u2 attributes_count;
    attribute_info *attributes;
} ClassFile;

ClassFile *create_classfile(FILE *file);

char *get_method_name(u2 count, cp_info *constant_pool, u2 Methodref_index);
char *get_method_descriptor(u2 count, cp_info *constant_pool, u2 Methodref_index);

method_info *get_method_info(ClassFile *class_file, u2 count, cp_info *constant_pool, u2 Methodref_index);

#endif // !1