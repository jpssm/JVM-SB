
#ifndef EXECUTION_ENGINE_C
#define EXECUTION_ENGINE_C

#include <class_loader/bytes.h>
#include "stdint.h"
#include <class_loader/class_file.h>
#include <class_loader/field.h>
#include <runtime_data/runtime_data.h>
#include <execution_engine/jvm.h>
#include <runtime_data/object.h>


#define ipc(n)  frame_stack.top->pc+=n

#define printDados \
     printf("\nFrame stack length: %d\n", frame_stack.stack_length); \
    printf("Method: %s", get_from_cp(runtime_constant_Pool, cf->constant_pool_count,frame_stack.top->method->name_index)->info.Utf8.bytes); \
    printf("\nInstrucao: %s\n", intructions[frame_stack.top->code[frame_stack.top->pc]]); \
    printf("PC: %u\n", frame_stack.top->pc); \
    printf("Code lenght: %u\n", frame_stack.top->code_lenght);\
    if (frame_stack.top->previous != NULL) printf("Code lenght of previous: %u\n", frame_stack.top->previous->code_lenght); \
    printf("Topo pilha: %d\n", frame_stack.top->operand_stack[-1]); \
    print_stack(frame_stack.top); \
    print_locals(frame_stack.top); \
    printf("\n\n");


//Estruturas principais da JVM
Frame_stack frame_stack;
Method_area method_area;
cp_info *runtime_constant_Pool;
ClassFile *cf;
Control_flags control_flags;
Control_flags defalt_control_flags;
Array_heap array_heap;

//Variavies globais
int32_t int_value1;
int32_t int_value2;
int int_return;
int int_arg;
Value_32 value1_32;
Value_32 value2_32;
Value_64 value1_64;
Value_64 value2_64;
int was_a_call = 0;
int was_a_return = 0;


void jvm(ClassFile * class_file){


    runtime_constant_Pool = class_file->constant_pool;
    cf = class_file;
    array_heap.arrays = NULL;
    array_heap.count = 0;

    //Reinicia as flags de controle
    defalt_control_flags.method_info_index = -1;
    defalt_control_flags.return_type = -1;
    defalt_control_flags.was_a_call = 0;
    defalt_control_flags.was_a_return = 0;
    control_flags = defalt_control_flags;

    //Inicia a pilha de frames com o método main
    frame_stack.base = NULL;
    frame_stack.stack_length = 1;
    method_info main = class_file->methods[1];
    Frame *frame = create_frame(&main,1);
    frame_stack.top = frame;
    frame_stack.top->previous = frame_stack.base;

    //printf("Iniciando Execucao!\n\n");
    while (frame_stack.top - frame_stack.base > 0){
        //printDados;
        interpreter[frame_stack.top->code[frame_stack.top->pc]](frame_stack.top->code+frame_stack.top->pc+1);
        if (control_flags.was_a_call){
            method_info *method = get_method_info(cf, cf->constant_pool_count, runtime_constant_Pool, control_flags.method_info_index);
            Frame *new_frame = create_frame(method, control_flags.method_info_index);
            pass_parameters(frame_stack.top, new_frame); 
            new_frame->previous = frame_stack.top;
            frame_stack.top = new_frame;
            control_flags = defalt_control_flags;
            frame_stack.stack_length+=1;
        }
        else if(control_flags.was_a_return){
            switch (control_flags.return_type) {
                case I_RETURN:
                    push(frame_stack.top->previous, pop_stack(frame_stack.top));
                    break;
                case L_RETURN:
                    push(frame_stack.top->previous, pop_stack(frame_stack.top));
                    push(frame_stack.top->previous, pop_stack(frame_stack.top));
                    break;
                case F_RETURN:
                    push(frame_stack.top->previous, pop_stack(frame_stack.top));
                    break;
                case D_RETURN:
                    push(frame_stack.top->previous, pop_stack(frame_stack.top));
                    push(frame_stack.top->previous, pop_stack(frame_stack.top));
                    break;
                case A_RETURN:
                    push(frame_stack.top->previous, pop_stack(frame_stack.top));
                    break;
                case RETURN_:
                    break;
                default:
                    printf("Erro: tipo de retorno invalido!\n");
                    exit(NULL);
            }
            frame_stack.top = frame_stack.top->previous;
            frame_stack.stack_length -=1;
            control_flags = defalt_control_flags;
        }
    };
    //printf("\n\nFim da execucao!");
    printf("\n\nPressione qualquer tecla para voltar");
    getch(); 
    fflush(stdin);
}


void	nop               	(u1* operands){
    //Pass
    ipc(1);

};

void	aconst_null       	(u1* operands){
    push(frame_stack.top, NULL);
    ipc(1);
};
	
void	iconst_m1         	(u1* operands){
    push(frame_stack.top, -1);
    ipc(1);
};
	
void	iconst_0          	(u1* operands){
    push(frame_stack.top, 0);
    ipc(1);
};
	
void	iconst_1          	(u1* operands){
    push(frame_stack.top, 1);
    ipc(1);
};
	
void	iconst_2          	(u1* operands){
    push(frame_stack.top, 2);
    ipc(1);
};
	
void	iconst_3          	(u1* operands){
    push(frame_stack.top, 3);
    ipc(1);
};
	
void	iconst_4          	(u1* operands){
    push(frame_stack.top, 4);
    ipc(1);
};
	
void	iconst_5          	(u1* operands){
    push(frame_stack.top, 5);
    ipc(1);
};
	
void	lconst_0          	(u1* operands){
    //push_u8(0);
    ipc(1);
};
	
void	lconst_1          	(u1* operands){
    //push_u8(1);
    ipc(1);
};
	
void	fconst_0          	(u1* operands){
    value1_32.f = 0;
    push(frame_stack.top, value1_32.i);
    ipc(1);
};
	
void	fconst_1          	(u1* operands){
    value1_32.f = 1.0;
    push(frame_stack.top, value1_32.i);
    ipc(1);
};
	
void	fconst_2          	(u1* operands){
    value1_32.f = 2.0;
    push(frame_stack.top, value1_32.i);
    ipc(1);
};
	
void	dconst_0          	(u1* operands){
    //value_64.d = 0.0;
    //push_u8(value_64.l);
    ipc(1);
};
	
void	dconst_1          	(u1* operands){
    //value_64.d = 1.0;
    //push_u8(value_64.l);
    ipc(1);
};
	
void	bipush            	(u1* operands){
    push(frame_stack.top, (int8_t)operands[0]);
    ipc(2);
};
	
void	sipush            	(u1* operands){ 
    push(frame_stack.top, (u2)operands[0]<<8 | operands[1]);
    ipc(3);
};
	
void	ldc               	(u1* operands){
    cp_info *item = get_from_cp(runtime_constant_Pool, cf->constant_pool_count, operands[0]);
    if (item->tag == 8) {//Se for uma string
        push(frame_stack.top, item->info.String.string_index);
    }
    if (item->tag == 3) {//Se for um int
        push(frame_stack.top, item->info.Integer.bytes);
    }
    ipc(2);
};
	
void	ldc_w             	(u1* operands){
    //Implementar
};
	
void	ldc2_w            	(u1* operands){
    //Implementar
};
	
void	iload             	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[operands[0]]);
    ipc(2);
};
	
void	lload             	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[operands[0]]);
    push(frame_stack.top, frame_stack.top->locals[operands[0]+1]);
    ipc(2);
};
	
void	fload             	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[operands[0]]);
    ipc(2);
};
	
void	dload             	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[operands[0]]);
    push(frame_stack.top, frame_stack.top->locals[operands[0]+1]);
    ipc(2);
};
	
void	aload             	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[operands[0]]);
    ipc(2);
};
	
void	iload_0           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[0]);
    ipc(1);
};
	
void	iload_1           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[1]);
    ipc(1);
};
	
void	iload_2           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[2]);
    ipc(1);
};
	
void	iload_3           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[3]);
    ipc(1);
};
	
void	lload_0           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[0]);
    push(frame_stack.top, frame_stack.top->locals[1]);
    ipc(1);
};
	
void	lload_1           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[1]);
    push(frame_stack.top, frame_stack.top->locals[2]);
    ipc(1);
};
	
void	lload_2           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[2]);
    push(frame_stack.top, frame_stack.top->locals[3]);
    ipc(1);
};
	
void	lload_3           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[3]);
    push(frame_stack.top, frame_stack.top->locals[4]);
    ipc(1);
};
	
void	fload_0           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[0]);
    ipc(1);
};
	
void	fload_1           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[1]);
    ipc(1);
};
	
void	fload_2           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[2]);
    ipc(1);
};
	
void	fload_3           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[3]);
    ipc(1);
};
	
void	dload_0           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[0]);
    push(frame_stack.top, frame_stack.top->locals[1]);
    ipc(1);
};
	
void	dload_1           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[1]);
    push(frame_stack.top, frame_stack.top->locals[2]);
    ipc(1);
};
	
void	dload_2           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[2]);
    push(frame_stack.top, frame_stack.top->locals[3]);
    ipc(1);
};
	
void	dload_3           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[3]);
    push(frame_stack.top, frame_stack.top->locals[4]);
    ipc(1);
};
	
void	aload_0           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[0]);
    ipc(1);
};
	
void	aload_1           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[1]);
    ipc(1);
};
	
void	aload_2           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[2]);
    ipc(1);
};
	
void	aload_3           	(u1* operands){
    push(frame_stack.top, frame_stack.top->locals[3]);
    ipc(1);
};
	
void	iaload            	(u1* operands){
    u4 index = pop_stack(frame_stack.top); 
    u4 ref = pop_stack(frame_stack.top);
    Array *array = array_heap.arrays[ref];
    int32_t *int_array = array->content;
    if (index >= array->size){
        printf("Excecao: Indice %d fora dos limites para comprimento %d", index, array->size);
        exit(NULL);
    }
    else{
        push(frame_stack.top, int_array[index]);
    }
    
    ipc(1);
};
	
void	laload            	(u1* operands){};
	
void	faload            	(u1* operands){};
	
void	daload            	(u1* operands){};
	
void	aaload            	(u1* operands){};
	
void	baload            	(u1* operands){};
	
void	caload            	(u1* operands){};
	
void	saload            	(u1* operands){};
	
void	istore            	(u1* operands){
    frame_stack.top->locals[operands[0]] = pop_stack(frame_stack.top);
    ipc(2);
};
	
void	lstore            	(u1* operands){
    frame_stack.top->locals[operands[0]+1] = pop_stack(frame_stack.top);
    frame_stack.top->locals[operands[0]] = pop_stack(frame_stack.top);
    ipc(2);

};
	
void	fstore            	(u1* operands){
    value1_32.i = pop_stack(frame_stack.top);
    frame_stack.top->locals[operands[0]] = value1_32.i;
    ipc(2);
};
	
void	dstore            	(u1* operands){};
	
void	astore            	(u1* operands){};
	
void	istore_0          	(u1* operands){
    frame_stack.top->locals[0] = pop_stack(frame_stack.top);
    ipc(1);
};
	
void	istore_1          	(u1* operands){
    frame_stack.top->locals[1] = pop_stack(frame_stack.top);
    ipc(1);
};
	
void	istore_2          	(u1* operands){
    frame_stack.top->locals[2] = pop_stack(frame_stack.top);
    ipc(1);
};
	
void	istore_3          	(u1* operands){
    frame_stack.top->locals[3] = pop_stack(frame_stack.top);
    ipc(1);
};
	
void	lstore_0          	(u1* operands){
    frame_stack.top->locals[0] = pop_stack(frame_stack.top); 
    frame_stack.top->locals[1] = pop_stack(frame_stack.top);
    ipc(1);
};
	
void	lstore_1          	(u1* operands){
    frame_stack.top->locals[1] = pop_stack(frame_stack.top); 
    frame_stack.top->locals[2] = pop_stack(frame_stack.top);
    ipc(1);
};
	
void	lstore_2          	(u1* operands){
    frame_stack.top->locals[2] = pop_stack(frame_stack.top);
    frame_stack.top->locals[3] = pop_stack(frame_stack.top);
    ipc(1);
};
	
void	lstore_3          	(u1* operands){
    frame_stack.top->locals[3] = pop_stack(frame_stack.top); 
    frame_stack.top->locals[4] = pop_stack(frame_stack.top);
    ipc(1);
};
	
void	fstore_0          	(u1* operands){
    value1_32.i = pop_stack(frame_stack.top);
    frame_stack.top->locals[0] = value1_32.i;
    ipc(1);
};
	
void	fstore_1          	(u1* operands){
    value1_32.i = pop_stack(frame_stack.top);
    frame_stack.top->locals[1] = value1_32.i;
    ipc(1);
};
	
void	fstore_2          	(u1* operands){
    value1_32.i = pop_stack(frame_stack.top);
    frame_stack.top->locals[2] = value1_32.i;
    ipc(1);
};
	
void	fstore_3          	(u1* operands){
    value1_32.i = pop_stack(frame_stack.top);
    frame_stack.top->locals[3] = value1_32.i;
    ipc(1);
};
	
void	dstore_0          	(u1* operands){};
	
void	dstore_1          	(u1* operands){};
	
void	dstore_2          	(u1* operands){};
	
void	dstore_3          	(u1* operands){};
	
void	astore_0          	(u1* operands){
    frame_stack.top->locals[0] = pop_stack(frame_stack.top);
    ipc(1);
};
	
void	astore_1          	(u1* operands){
    frame_stack.top->locals[1] = pop_stack(frame_stack.top);
    ipc(1);
};
	
void	astore_2          	(u1* operands){
    frame_stack.top->locals[2] = pop_stack(frame_stack.top);
    ipc(1);
};
	
void	astore_3          	(u1* operands){
    frame_stack.top->locals[3] = pop_stack(frame_stack.top);
    ipc(1);
};
	
void	iastore           	(u1* operands){
    int32_t value = pop_stack(frame_stack.top);
    u4 index = pop_stack(frame_stack.top); 
    u4 ref = pop_stack(frame_stack.top);
    Array *array = array_heap.arrays[ref];
    int32_t *int_array = array->content;
    if (index >= array->size){
        printf("Excecao: Indice %d fora dos limites para comprimento %d", index, array->size);
        exit(NULL);
    }
    else{
        int_array[index] = value;
    }
    ipc(1);
};
	
void	lastore           	(u1* operands){};
	
void	fastore           	(u1* operands){};
	
void	dastore           	(u1* operands){};
	
void	aastore           	(u1* operands){};
	
void	bastore           	(u1* operands){};
	
void	castore           	(u1* operands){};
	
void	sastore           	(u1* operands){};
	
void	pop               	(u1* operands){};
	
void	pop2              	(u1* operands){};
	
void	dup               	(u1* operands){};
	
void	dup_x1            	(u1* operands){};
	
void	dup_x2            	(u1* operands){};
	
void	dup2              	(u1* operands){};
	
void	dup2_x1           	(u1* operands){};
	
void	dup2_x2           	(u1* operands){};
	
void	swap              	(u1* operands){};
	
void	iadd              	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    push(frame_stack.top, int_value1 + int_value2);
    ipc(1);
};
	
void	ladd              	(u1* operands){
    //push_u8((int64_t)pop_stack_u8() + (int64_t)pop_stack_u8());
    ipc(1);
};
	
void	fadd              	(u1* operands){
    value2_32.i = pop_stack(frame_stack.top);
    value1_32.i = pop_stack(frame_stack.top);
    value1_32.f = value1_32.f + value2_32.f;
    push(frame_stack.top, value1_32.i);
    ipc(1);
};
	
void	dadd              	(u1* operands){};
	
void	isub              	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    push(frame_stack.top, int_value1 - int_value2);
    ipc(1);
};
	
void	lsub              	(u1* operands){};
	
void	fsub              	(u1* operands){
    value2_32.i = pop_stack(frame_stack.top);
    value1_32.i = pop_stack(frame_stack.top);
    value1_32.f = value1_32.f - value2_32.f;
    push(frame_stack.top, value1_32.i);
    ipc(1);
};
	
void	dsub              	(u1* operands){};
	
void	imul              	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    push(frame_stack.top, int_value1 * int_value2);
    ipc(1);
};
	
void	lmul              	(u1* operands){};
	
void	fmul              	(u1* operands){
    value2_32.i = pop_stack(frame_stack.top);
    value1_32.i = pop_stack(frame_stack.top);
    value1_32.f = value1_32.f * value2_32.f;
    push(frame_stack.top, value1_32.i);
    ipc(1);
};
	
void	dmul              	(u1* operands){};
	
void	idiv              	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    push(frame_stack.top, int_value1 / int_value2);
    ipc(1);
};
	
void	ldiv_              	(u1* operands){};
	
void	fdiv              	(u1* operands){
    value2_32.i = pop_stack(frame_stack.top);
    value1_32.i = pop_stack(frame_stack.top);
    value1_32.f = value1_32.f / value2_32.f;
    push(frame_stack.top, value1_32.i);
    ipc(1);
};
	
void	ddiv              	(u1* operands){};
	
void	irem              	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    push(frame_stack.top, int_value1 % int_value2);
    ipc(1);
};
	
void	lrem              	(u1* operands){};
	
void	frem              	(u1* operands){
    value2_32.i = pop_stack(frame_stack.top);
    value1_32.i = pop_stack(frame_stack.top);
    int64_t quotient = (int64_t) (value1_32.f / value2_32.f);
    value1_32.f = value1_32.f - quotient*value2_32.f;
    push(frame_stack.top, value1_32.i);
    ipc(1);
};
	
void	drem              	(u1* operands){};
	
void	ineg              	(u1* operands){
    int_value1 = pop_stack(frame_stack.top);
    push(frame_stack.top, -int_value1);
    ipc(1);
};
	
void	lneg              	(u1* operands){};
	
void	fneg              	(u1* operands){
    value1_32.i = pop_stack(frame_stack.top);
    value1_32.f = -value1_32.f;
    push(frame_stack.top, value1_32.i);
    ipc(1);
};
	
void	dneg              	(u1* operands){};
	
void	ishl              	(u1* operands){
    int_value2 = pop_stack(frame_stack.top) & 0x1f;
    int_value1 = pop_stack(frame_stack.top) ;
    push(frame_stack.top, int_value1 << int_value2);
    ipc(1);
};
	
void	lshl              	(u1* operands){};
	
void	ishr              	(u1* operands){
    int_value2 = pop_stack(frame_stack.top) & 0x1f;
    int_value1 = pop_stack(frame_stack.top);
    push(frame_stack.top, int_value1 >> int_value2);
    ipc(1);
};
	
void	lshr              	(u1* operands){};
	
void	iushr             	(u1* operands){
    int_value2 = pop_stack(frame_stack.top) & 0x1f;
    u4 value1 = pop_stack(frame_stack.top); //Garante que o deslocamento não tenha extensão de sinal
    push(frame_stack.top, value1 >> int_value2);
    ipc(1);
};
	
void	lushr             	(u1* operands){};
	
void	iand              	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    push(frame_stack.top, int_value1 & int_value2);
    ipc(1);
};
	
void	land              	(u1* operands){};
	
void	ior               	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    push(frame_stack.top, int_value1 | int_value2);
    ipc(1);
};
	
void	lor               	(u1* operands){};
	
void	ixor              	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    push(frame_stack.top, int_value1 ^ int_value2);
    ipc(1);
};
	
void	lxor              	(u1* operands){};
	
void	iinc              	(u1* operands){
    frame_stack.top->locals[operands[0]] += (int8_t) operands[1];
    ipc(3);
};
	
void	i2l               	(u1* operands){};
	
void	i2f               	(u1* operands){};
	
void	i2d               	(u1* operands){};
	
void	l2i               	(u1* operands){};
	
void	l2f               	(u1* operands){};
	
void	l2d               	(u1* operands){};
	
void	f2i               	(u1* operands){
    value1_32.f = pop_stack(frame_stack.top);
    push(frame_stack.top, (int32_t)value1_32.f);
    ipc(1);
};
	
void	f2l               	(u1* operands){
    value1_32.f = pop_stack(frame_stack.top);
    push(frame_stack.top, (int64_t)value1_32.f);
    ipc(1);
};
	
void	f2d               	(u1* operands){
    value1_32.f = pop_stack(frame_stack.top);
    value1_64.d = (double) value1_32.f;
    push_u8(frame_stack.top, value1_64.l);
    ipc(1);
};
	
void	d2i               	(u1* operands){};
	
void	d2l               	(u1* operands){};
	
void	d2f               	(u1* operands){};
	
void	i2b               	(u1* operands){};
	
void	i2c               	(u1* operands){};
	
void	i2s               	(u1* operands){};
	
void	lcmp              	(u1* operands){};
	
void	fcmpl             	(u1* operands){
    value2_32.i = pop_stack(frame_stack.top);
    value1_32.i = pop_stack(frame_stack.top);
    u4 result = value1_32.f < value2_32.f;
    push(frame_stack.top, result);
};
	
void	fcmpg             	(u1* operands){
    value2_32.i = pop_stack(frame_stack.top);
    value1_32.i = pop_stack(frame_stack.top);
    u4 result = value1_32.f > value2_32.f;
    push(frame_stack.top, result);
};
	
void	dcmpl             	(u1* operands){};
	
void	dcmpg             	(u1* operands){};
	
void	ifeq              	(u1* operands){
    int32_t value = pop_stack(frame_stack.top);
    if (value == 0){
        ipc((int16_t)((u2)operands[0]<<8 | operands[1]));
    }
    else{
        ipc(3);
    }
};
	
void	ifne              	(u1* operands){
    int32_t value = pop_stack(frame_stack.top);
    if (value != 0){
        ipc((int16_t)((u2)operands[0]<<8 | operands[1]));
    }
    else{
        ipc(3);
    }
};
	
void	iflt              	(u1* operands){
    int32_t value = pop_stack(frame_stack.top);
    if (value < 0){
        ipc((int16_t)((u2)operands[0]<<8 | operands[1]));
    }
    else{
        ipc(3);
    }
};
	
void	ifge              	(u1* operands){
    int32_t value = pop_stack(frame_stack.top);
    if (value >= 0){
        ipc((int16_t)((u2)operands[0]<<8 | operands[1]));
    }
    else{
        ipc(3);
    }
};
	
void	ifgt              	(u1* operands){
    int32_t value = pop_stack(frame_stack.top);
    if (value > 0){
        ipc((int16_t)((u2)operands[0]<<8 | operands[1]));
    }
    else{
        ipc(3);
    }
};
	
void	ifle              	(u1* operands){
    int_value1 = pop_stack(frame_stack.top);
    if (int_value1 <= 0){
        ipc((int16_t)((u2)operands[0]<<8 | operands[1]));
    }
    else{
        ipc(3);
    }
};

void	if_icmpeq         	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    if (int_value1 == int_value2){
        ipc((int16_t)((u2)operands[0]<<8 | operands[1]));
    }
    else ipc(3);
};
	
void	if_icmpne         	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    if (int_value1 != int_value2){
        ipc((int16_t)((u2)operands[0]<<8 | operands[1]));
    }
    else ipc(3);
};
	
void	if_icmplt         	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    if (int_value1 < int_value2){
        ipc((int16_t)((u2)operands[0]<<8 | operands[1]));
    }
    else ipc(3);
};
	
void	if_icmpge         	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    if (int_value1 >= int_value2){
        ipc((int16_t)((u2)operands[0]<<8 | operands[1]));
    }
    else ipc(3);
};
	
void	if_icmpgt         	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    if (int_value1 > int_value2){
        ipc((int16_t)((u2)operands[0]<<8 | operands[1]));
    }
    else ipc(3);
};
	
void	if_icmple         	(u1* operands){
    int_value2 = pop_stack(frame_stack.top);
    int_value1 = pop_stack(frame_stack.top);
    if (int_value1 <= int_value2){
        ipc((int16_t)((u2)operands[0]<<8 | operands[1]));
    }
    else ipc(3);
};
	
void	if_acmpeq         	(u1* operands){};
	
void	if_acmpne         	(u1* operands){

};
	
void	goto_              	(u1* operands){
    ipc((int16_t)((u2)operands[0]<<8 | operands[1]));
};
	
void	jsr               	(u1* operands){};
	
void	ret               	(u1* operands){};
	
void	tableswitch       	(u1* operands){};
	
void	lookupswitch      	(u1* operands){};
	
void	ireturn           	(u1* operands){
    control_flags.was_a_return = 1;
    control_flags.return_type = I_RETURN;
};
	
void	lreturn           	(u1* operands){};
	
void	freturn           	(u1* operands){};
	
void	dreturn           	(u1* operands){};
	
void	areturn           	(u1* operands){};
	
void	return_            	(u1* operands){
    frame_stack.top = frame_stack.top->previous;
};
	
void	getstatic         	(u1* operands){
    //Implementar
    ipc(3);
};
	
void	putstatic         	(u1* operands){};
	
void	getfield          	(u1* operands){};
	
void	putfield          	(u1* operands){};
	
void	invokevirtual     	(u1* operands){
    u2 index = (u2)operands[0] << 8 | operands[1];
    ipc(3);
    char *method_name = get_method_name(cf->constant_pool_count, runtime_constant_Pool, index);
    char *method_descriptor = get_method_descriptor(cf->constant_pool_count, runtime_constant_Pool, index);

    if (strcmp(method_name, "print") == 0 | strcmp(method_name, "println") == 0){ //Simulacao de print

        if (strcmp(method_descriptor, "(I)V") == 0){
            int32_t i = pop_stack(frame_stack.top);
            printf("%d", i);
        }
        if (strcmp(method_descriptor, "(F)V") == 0){
            value1_32.i = pop_stack(frame_stack.top);
            printf("%f", value1_32.f);
        }
        else if (strcmp(method_descriptor, "(Ljava/lang/String;)V") == 0){
            index = pop_stack(frame_stack.top);
            cp_info *cp_utf8 = get_from_cp(runtime_constant_Pool, cf->constant_pool_count, index);
            printf("%s", cp_utf8->info.Utf8.bytes);
        }
        else if (strcmp(method_descriptor, "(C)V") == 0){
            char c = (char)pop_stack(frame_stack.top);
            printf("%c", c);
        }
        if (strcmp(method_name, "println") == 0){
            printf("\n");
        }
    }

    else{

    }

};
	
void	invokespecial     	(u1* operands){};
	
void	invokestatic      	(u1* operands){
    u2 index = (u2)operands[0] << 8 | operands[1];
    ipc(3);
    control_flags.was_a_call = 1;
    control_flags.method_info_index = index;
};
	
void	invokeinterface   	(u1* operands){};
	
void	invokedynamic     	(u1* operands){};
	
void	new               	(u1* operands){};
	
void	newarray          	(u1* operands){
    u4 size = pop_stack(frame_stack.top);
    u4 ref = store_array(&array_heap, create_array(size, operands[0]));
    push(frame_stack.top, ref);
    ipc(2);
};
	
void	anewarray         	(u1* operands){};
	
void	arraylength       	(u1* operands){};
	
void	athrow            	(u1* operands){};
	
void	checkcast         	(u1* operands){};
	
void	instanceof        	(u1* operands){};
	
void	monitorenter      	(u1* operands){};
	
void	monitorexit       	(u1* operands){};
	
void	wide              	(u1* operands){};
	
void	multianewarray    	(u1* operands){};
	
void	ifnull            	(u1* operands){};
	
void	ifnonnull         	(u1* operands){};
	
void	goto_w            	(u1* operands){};
	
void	jsr_w             	(u1* operands){};
	
void	breakpoint        	(u1* operands){};
	
void	impdep1           	(u1* operands){};
	
void	impdep2           	(u1* operands){};
	
void (*interpreter[256]) (u1*) = {nop, aconst_null, iconst_m1, iconst_0, iconst_1, iconst_2, iconst_3, iconst_4, iconst_5, lconst_0, lconst_1, fconst_0, fconst_1, fconst_2, dconst_0, dconst_1, bipush, sipush, ldc, ldc_w, ldc2_w, iload, lload, fload, dload, aload, iload_0, iload_1, iload_2, iload_3, lload_0, lload_1, lload_2, lload_3, fload_0, fload_1, fload_2, fload_3, dload_0, dload_1, dload_2, dload_3, aload_0, aload_1, aload_2, aload_3, iaload, laload, faload, daload, aaload, baload, caload, saload, istore, lstore, fstore, dstore, astore, istore_0, istore_1, istore_2, istore_3, lstore_0, lstore_1, lstore_2, lstore_3, fstore_0, fstore_1, fstore_2, fstore_3, dstore_0, dstore_1, dstore_2, dstore_3, astore_0, astore_1, astore_2, astore_3, iastore, lastore, fastore, dastore, aastore, bastore, castore, sastore, pop, pop2, dup, dup_x1, dup_x2, dup2, dup2_x1, dup2_x2, swap, iadd, ladd, fadd, dadd, isub, lsub, fsub, dsub, imul, lmul, fmul, dmul, idiv, ldiv, fdiv, ddiv, irem, lrem, frem, drem, ineg, lneg, fneg, dneg, ishl, lshl, ishr, lshr, iushr, lushr, iand, land, ior, lor, ixor, lxor, iinc, i2l, i2f, i2d, l2i, l2f, l2d, f2i, f2l, f2d, d2i, d2l, d2f, i2b, i2c, i2s, lcmp, fcmpl, fcmpg, dcmpl, dcmpg, ifeq, ifne, iflt, ifge, ifgt, ifle, if_icmpeq, if_icmpne, if_icmplt, if_icmpge, if_icmpgt, if_icmple, if_acmpeq, if_acmpne, goto_, jsr, ret, tableswitch, lookupswitch, ireturn, lreturn, freturn, dreturn, areturn, return_, getstatic, putstatic, getfield, putfield, invokevirtual, invokespecial, invokestatic, invokeinterface, invokedynamic, new, newarray, anewarray, arraylength, athrow, checkcast, instanceof, monitorenter, monitorexit, wide, multianewarray, ifnull, ifnonnull, goto_w, jsr_w, breakpoint, impdep1, impdep2};
char *intructions[256] = {"nop", "aconst_null", "iconst_m1", "iconst_0", "iconst_1", "iconst_2", "iconst_3", "iconst_4", "iconst_5", "lconst_0", "lconst_1", "fconst_0", "fconst_1", "fconst_2", "dconst_0", "dconst_1", "bipush", "sipush", "ldc", "ldc_w", "ldc2_w", "iload", "lload", "fload", "dload", "aload", "iload_0", "iload_1", "iload_2", "iload_3", "lload_0", "lload_1", "lload_2", "lload_3", "fload_0", "fload_1", "fload_2", "fload_3", "dload_0", "dload_1", "dload_2", "dload_3", "aload_0", "aload_1", "aload_2", "aload_3", "iaload", "laload", "faload", "daload", "aaload", "baload", "caload", "saload", "istore", "lstore", "fstore", "dstore", "astore", "istore_0", "istore_1", "istore_2", "istore_3", "lstore_0", "lstore_1", "lstore_2", "lstore_3", "fstore_0", "fstore_1", "fstore_2", "fstore_3", "dstore_0", "dstore_1", "dstore_2", "dstore_3", "astore_0", "astore_1", "astore_2", "astore_3", "iastore", "lastore", "fastore", "dastore", "aastore", "bastore", "castore", "sastore", "pop", "pop2", "dup", "dup_x1", "dup_x2", "dup2", "dup2_x1", "dup2_x2", "swap", "iadd", "ladd", "fadd", "dadd", "isub", "lsub", "fsub", "dsub", "imul", "lmul", "fmul", "dmul", "idiv", "ldiv", "fdiv", "ddiv", "irem", "lrem", "frem", "drem", "ineg", "lneg", "fneg", "dneg", "ishl", "lshl", "ishr", "lshr", "iushr", "lushr", "iand", "land", "ior", "lor", "ixor", "lxor", "iinc", "i2l", "i2f", "i2d", "l2i", "l2f", "l2d", "f2i", "f2l", "f2d", "d2i", "d2l", "d2f", "i2b", "i2c", "i2s", "lcmp", "fcmpl", "fcmpg", "dcmpl", "dcmpg", "ifeq", "ifne", "iflt", "ifge", "ifgt", "ifle", "if_icmpeq", "if_icmpne", "if_icmplt", "if_icmpge", "if_icmpgt", "if_icmple", "if_acmpeq", "if_acmpne", "goto_", "jsr", "ret", "tableswitch", "lookupswitch", "ireturn", "lreturn", "freturn", "dreturn", "areturn", "return_", "getstatic", "putstatic", "getfield", "putfield", "invokevirtual", "invokespecial", "invokestatic", "invokeinterface", "invokedynamic", "new", "newarray", "anewarray", "arraylength", "athrow", "checkcast", "instanceof", "monitorenter", "monitorexit", "wide", "multianewarray", "ifnull", "ifnonnull", "goto_w", "jsr_w", "breakpoint", "impdep1", "impdep2"};


void push(Frame *frame, u4 n){
    frame->operand_stack[0] = n;
    frame->operand_stack ++;
};

void push_u8(Frame *frame, u8 n){
    frame->operand_stack = n<<32>>32;
    frame->operand_stack ++;
    frame->operand_stack = n>>32;
    frame->operand_stack ++;
};

u4 pop_stack(Frame *frame){
    frame->operand_stack --;
    return frame_stack.top->operand_stack[0];\
};

u8 pop_stack_u8(){
    frame_stack.top->operand_stack -=2;
    return  (u4)frame_stack.top->operand_stack[0] <<32 | frame_stack.top->operand_stack[1];
};

void pass_parameters(Frame *caller_frame, Frame *called_frame){
    
    cp_info *method_info = get_from_cp(runtime_constant_Pool, cf->constant_pool_count, called_frame->method_info_index);
    cp_info *name_and_type = get_from_cp(runtime_constant_Pool, cf->constant_pool_count, method_info->info.Methodref.name_and_type_index);
    char *descriptor = get_from_cp(runtime_constant_Pool, cf->constant_pool_count, name_and_type->info.NameAndType.descriptor_index)->info.Utf8.bytes;
    descriptor++; //Pula o '(' do inicio do descritor

    //Conta numero de slots para passar parâmetros
    int number_of_parameters_slots = 0;
    for (char *type_char= descriptor; *type_char != ')'; type_char++){
        switch (*type_char)
        {
        case 'B':
            number_of_parameters_slots+=1;
            break;
        case 'C':
            number_of_parameters_slots+=1;
            break;
        case 'D':
            number_of_parameters_slots+=2;
            break;
        case 'F':
            number_of_parameters_slots+=1;
            break;
        case 'I':
            number_of_parameters_slots+=1;
            break;
        case 'J':
            number_of_parameters_slots+=2;
            break;
        case 'S':
            number_of_parameters_slots+=1;
            break;
        case 'Z':
            number_of_parameters_slots+=1;
            break;
        default:
            break;
        }
    }

    //Passa parâmetros
    int i = number_of_parameters_slots - 1; //Vai até o indice 0
    for (char *type_char= descriptor; *type_char != ')'; type_char++, i--){
        switch (*type_char)
        {
        case 'B':
            called_frame->locals[i] = pop_stack(caller_frame);
            break;
        case 'C':
            called_frame->locals[i] = pop_stack(caller_frame);
            break;
        case 'D':
            called_frame->locals[i] = pop_stack(caller_frame); i--;
            called_frame->locals[i] = pop_stack(caller_frame);
            break;
        case 'F':
            called_frame->locals[i] = pop_stack(caller_frame);
            break;
        case 'I':
            called_frame->locals[i] = pop_stack(caller_frame);
            break;
        case 'J':
            called_frame->locals[i] = pop_stack(caller_frame); i--;
            called_frame->locals[i] = pop_stack(caller_frame);
            break;
        case 'S':
            called_frame->locals[i] = pop_stack(caller_frame);
            break;
        case 'Z':
            called_frame->locals[i] = pop_stack(caller_frame);
            break;
        default:
            break;
        }
    }
    
}


#endif