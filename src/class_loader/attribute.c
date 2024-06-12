#include "bytes.c"
#include <class_loader/bytes.h>
#include <class_loader/attribute.h>
#include <class_loader/field.h>
#include <class_loader/method.h>
#include <class_loader/constant_pool.h>
#include <class_loader/class_file.h>

attribute_info *create_attributes(FILE *file, u2 count)
{
    if (count <= 0) return NULL;
    attribute_info* attributes = (attribute_info *) malloc(sizeof(attribute_info) * count);
    attribute_info *att;
    for (att = attributes; att < attributes + count; att++)
    {
        att->attribute_name_index = u2Read(file);
        att->attribute_length = u4Read(file);
        att->info = (u1*) malloc(sizeof(u1) * att->attribute_length);
        u1* curr_info;
        for (curr_info = att->info; curr_info < att->info + att->attribute_length; curr_info++)
        {
            *curr_info = u1Read(file);
        }
        
    }
    return attributes;
}


code_attribute* get_code_attribute(attribute_info* attributes, u2 count, cp_info *constant_pool)
{
    code_attribute *code_att = (code_attribute*) malloc(sizeof(code_attribute));
    attribute_info *att;
    for (att = attributes; att < attributes + count; att++){ 
        if(strcmp(constant_pool[att->attribute_name_index].info.Utf8.bytes, "Code")){
            code_att->attribute_name_index = att->attribute_name_index;
            code_att->attribute_length = att->attribute_length;
            u1 *info = att->info;
            code_att->max_stack =  info[0]<<8 | info[1]; info+=2;
            code_att->max_locals = info[0]<<8 | info[1]; info+=2;
            code_att->code_length = info[0]<<24 | info[1]<<16 | info[2]<<8 | info[3]; info+=4;
            code_att->code = info; info += code_att->code_length;
            code_att->exception_table_length = info[0]<<8 | info[1]; info+=2;
            

        }
    }
    return code_att;
}