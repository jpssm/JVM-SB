#include <class_loader/class_file.h>
#include <class_loader/bytes.h>
#include <class_loader/field.h>
#include <leitor_exibidor/leitor_exibidor.h>
#include <runtime_data/runtime_data.h>
#include "execution_engine/execution_engine.c"

void jvm(ClassFile * class){

    cf = *class;
    frame_stack;
    method_area;
    cp = cf.constant_pool;
    cf;
    frame_stack.base = NULL;
    frame_stack.top = NULL;

    method_info main = cf.methods[1];
    create_frame(&main, frame_stack);

    u1* code = frame_stack.top->code;
    while (frame_stack.top - frame_stack.base > 0){
        interpreter[frame_stack.top->code[frame_stack.top->pc]](frame_stack.top->code[frame_stack.top->pc]+1);
    };

}

