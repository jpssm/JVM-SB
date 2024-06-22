#include <runtime_data/runtime_data.h>

void create_frame(method_info *method, Frame_stack frame_stack){
    Frame new_frame;
    new_frame.locals = (u4*) malloc(sizeof(u4)*method->code_attribute->max_locals);
    new_frame.operand_stack = (u4*) malloc(sizeof(u4)*method->code_attribute->max_stack);
    new_frame.code = method->code_attribute->code;
    new_frame.code_lenght = method->code_attribute->code_length;
    new_frame.pc = 0;
    if (frame_stack.base  != NULL){
        frame_stack.top->next = &new_frame;
        new_frame.previous = frame_stack.top;
        frame_stack.top = &new_frame;
        new_frame.next = NULL;
    }
    else{
        frame_stack.base = &new_frame;
        frame_stack.top = &new_frame;
        new_frame.previous = NULL;
        new_frame.next = NULL;
    } 
}