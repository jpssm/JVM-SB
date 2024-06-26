#ifndef RUNTIME_DATA_H
#define RUNTIME_DATA_H

#include <class_loader/class_file.h>
#include <class_loader/method.h>
#include <class_loader/bytes.h>
#include <runtime_data/object.h>


typedef struct{
    ClassFile *class_list;
    u4 size;
} Method_area;

typedef struct{
    Array **arrays;
    u4 count;
} Array_heap;



typedef struct Frame{
    cp_info *cp;
    u4 pc;
    u4 *operand_stack;
    u4 *operand_stack_base;
    u4 *locals;
    method_info *method;
    u2 method_info_index;
    u1 *code;
    u4 code_lenght;
    struct Frame *next;
    struct Frame *previous;
} Frame;

typedef struct{
    Frame *base;
    Frame *top;
    u4 stack_length;
} Frame_stack;

Frame *create_frame(method_info *method, u2 method_info_index);
u4 store_array(Array_heap * array_heap, Array *array);

void print_stack(Frame *frame);
void print_locals(Frame *frame);


#endif