#include <runtime_data/runtime_data.h>

Frame *create_frame(method_info *method, u2 method_info_index){
    Frame *new_frame = malloc(sizeof(Frame));
    new_frame->locals = (u4*) malloc(method->code_attribute->max_locals*sizeof(u4));
    new_frame->operand_stack = (u4*) malloc(method->code_attribute->max_stack*sizeof(u4));
    new_frame->operand_stack_base = new_frame->operand_stack;
    new_frame->code = method->code_attribute->code;
    new_frame->code_lenght = method->code_attribute->code_length;
    new_frame->method = method;
    new_frame->method_info_index = method_info_index;
    new_frame->pc = 0;
    return new_frame;
}

u4 store_array(Array_heap * array_heap, Array *array){
    array_heap->arrays = realloc(array_heap->arrays, sizeof(Array*)*array_heap->count + 1);
    array_heap->arrays[array_heap->count] = array;
    array_heap->count++;
    return(array_heap->count-1);
}



void print_stack(Frame *frame){
    printf("Stack: ");
    for (int c = 0; c < frame->method->code_attribute->max_stack; c++){
        printf("%d, ", frame->operand_stack_base[c]);
    }
    printf("\n");
}

void print_locals(Frame *frame){
    printf("Locals: ");
    for (int c = 0; c < frame->method->code_attribute->max_locals; c++){
        printf("c%d: %d, ", c, frame->locals[c]);
    }
    printf("\n");
}