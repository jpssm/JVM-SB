#ifndef RUNTIME_DATA_H
#define RUNTIME_DATA_H

#include <class_loader/class_file.h>
#include <class_loader/method.h>
#include <class_loader/bytes.h>


typedef struct{
    ClassFile *class_list;
    u4 size;
} Method_area;

typedef struct Frame{
    cp_info *cp;
    u4 pc;
    u4 *operand_stack;
    u4 *locals;
    method_info *method;
    u1 *code;
    u4 code_lenght;
    struct Frame *next;
    struct Frame *previous;
} Frame;

typedef struct{
    Frame *base;
    Frame *top;
} Frame_stack;

Frame create_frame(method_info *method, Frame_stack *frame_stack);
void remove_frame(method_info *method);

#endif