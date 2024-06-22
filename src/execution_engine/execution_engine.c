#include <execution_engine/execution_engine.h>
#include <class_loader/bytes.h>
#include "stdint.h"

Frame_stack frame_stack;
Method_area method_area;
cp_info *cp;
ClassFile cf;

void push(n){
    frame_stack.top->operand_stack = n;
    frame_stack.top->operand_stack ++;
};

void push_u8(u8 n){
    frame_stack.top->operand_stack = n<<32>>32;
    frame_stack.top->operand_stack ++;
    frame_stack.top->operand_stack = n>>32;
    frame_stack.top->operand_stack ++;
};

u4 pop_stack(){
    frame_stack.top->operand_stack --;
    return frame_stack.top->operand_stack[0];\
};

u8 pop_stack_u8(){
    frame_stack.top->operand_stack -=2;
    return  (u4)frame_stack.top->operand_stack[0] <<32 | frame_stack.top->operand_stack[1];
};

void ipc(int n) { //Incrementa pc
    frame_stack.top->pc+=n;
}

struct {
    int32_t i;
    float f;
}value_32;

struct {
    uint64_t l;
    double d;
}value_64;



void	nop               	(u1* operands){
    //Pass
    ipc(1);

};

void	aconst_null       	(u1* operands){
    push(NULL);
    ipc(1);
};
	
void	iconst_m1         	(u1* operands){
    push(-1);
    ipc(1);
};
	
void	iconst_0          	(u1* operands){
    push(0);
    ipc(1);
};
	
void	iconst_1          	(u1* operands){
    push(1);
    ipc(1);
};
	
void	iconst_2          	(u1* operands){
    push(2);
    ipc(1);
};
	
void	iconst_3          	(u1* operands){
    push(3);
    ipc(1);
};
	
void	iconst_4          	(u1* operands){
    push(4);
    ipc(1);
};
	
void	iconst_5          	(u1* operands){
    push(5);
    ipc(1);
};
	
void	lconst_0          	(u1* operands){
    push_u8(0);
    ipc(1);
};
	
void	lconst_1          	(u1* operands){
    push_u8(1);
    ipc(1);
};
	
void	fconst_0          	(u1* operands){
    value_32.f = 0;
    push(value_32.i);
    ipc(1);
};
	
void	fconst_1          	(u1* operands){
    value_32.f = 1.0;
    push(value_32.i);
    ipc(1);
};
	
void	fconst_2          	(u1* operands){
    value_32.f = 2.0;
    push(value_32.i);
    ipc(1);
};
	
void	dconst_0          	(u1* operands){
    value_64.d = 0.0;
    push_u8(value_64.l);
    ipc(1);
};
	
void	dconst_1          	(u1* operands){
    value_64.d = 1.0;
    push_u8(value_64.l);
    ipc(1);
};
	
void	bipush            	(u1* operands){
    push((int8_t)operands[0]);
    ipc(2);
};
	
void	sipush            	(u1* operands){ 
    push((uint16_t)operands[0]<<8 | operands[1]);
    ipc(1);
};
	
void	ldc               	(u1* operands){
    cp_info *item = get_from_cp(cp, operands[0]+1, operands[0]);
    if (item->tag == 8) {//Se for uma string
        push(item->info.String.string_index);
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
    push(frame_stack.top->locals[operands[0]]);
    ipc(2);
};
	
void	lload             	(u1* operands){
    push(frame_stack.top->locals[operands[0]]);
    push(frame_stack.top->locals[operands[0]+1]);
    ipc(2);
};
	
void	fload             	(u1* operands){
    push(frame_stack.top->locals[operands[0]]);
    ipc(2);
};
	
void	dload             	(u1* operands){
    push(frame_stack.top->locals[operands[0]]);
    push(frame_stack.top->locals[operands[0]+1]);
    ipc(2);
};
	
void	aload             	(u1* operands){
    push(frame_stack.top->locals[operands[0]]);
    ipc(2);
};
	
void	iload_0           	(u1* operands){
    push(frame_stack.top->locals[0]);
    ipc(1);
};
	
void	iload_1           	(u1* operands){
    push(frame_stack.top->locals[1]);
    ipc(1);
};
	
void	iload_2           	(u1* operands){
    push(frame_stack.top->locals[2]);
    ipc(1);
};
	
void	iload_3           	(u1* operands){
    push(frame_stack.top->locals[3]);
    ipc(1);
};
	
void	lload_0           	(u1* operands){
    push(frame_stack.top->locals[0]);
    push(frame_stack.top->locals[1]);
    ipc(1);
};
	
void	lload_1           	(u1* operands){
    push(frame_stack.top->locals[1]);
    push(frame_stack.top->locals[2]);
    ipc(1);
};
	
void	lload_2           	(u1* operands){
    push(frame_stack.top->locals[2]);
    push(frame_stack.top->locals[3]);
    ipc(1);
};
	
void	lload_3           	(u1* operands){
    push(frame_stack.top->locals[3]);
    push(frame_stack.top->locals[4]);
    ipc(1);
};
	
void	fload_0           	(u1* operands){
    push(frame_stack.top->locals[0]);
    ipc(1);
};
	
void	fload_1           	(u1* operands){
    push(frame_stack.top->locals[1]);
    ipc(1);
};
	
void	fload_2           	(u1* operands){
    push(frame_stack.top->locals[2]);
    ipc(1);
};
	
void	fload_3           	(u1* operands){
    push(frame_stack.top->locals[3]);
    ipc(1);
};
	
void	dload_0           	(u1* operands){
    push(frame_stack.top->locals[0]);
    push(frame_stack.top->locals[1]);
    ipc(1);
};
	
void	dload_1           	(u1* operands){
    push(frame_stack.top->locals[1]);
    push(frame_stack.top->locals[2]);
    ipc(1);
};
	
void	dload_2           	(u1* operands){
    push(frame_stack.top->locals[2]);
    push(frame_stack.top->locals[3]);
    ipc(1);
};
	
void	dload_3           	(u1* operands){
    push(frame_stack.top->locals[3]);
    push(frame_stack.top->locals[4]);
    ipc(1);
};
	
void	aload_0           	(u1* operands){
    push(frame_stack.top->locals[0]);
    ipc(1);
};
	
void	aload_1           	(u1* operands){
    push(frame_stack.top->locals[1]);
    ipc(1);
};
	
void	aload_2           	(u1* operands){
    push(frame_stack.top->locals[2]);
    ipc(1);
};
	
void	aload_3           	(u1* operands){
    push(frame_stack.top->locals[3]);
    ipc(1);
};
	
void	iaload            	(u1* operands){};
	
void	laload            	(u1* operands){};
	
void	faload            	(u1* operands){};
	
void	daload            	(u1* operands){};
	
void	aaload            	(u1* operands){};
	
void	baload            	(u1* operands){};
	
void	caload            	(u1* operands){};
	
void	saload            	(u1* operands){};
	
void	istore            	(u1* operands){
    frame_stack.top->locals[operands[0]] = pop_stack();
    ipc(2);
};
	
void	lstore            	(u1* operands){
    frame_stack.top->locals[operands[0]+1] = pop_stack();
    frame_stack.top->locals[operands[0]] = pop_stack();
    ipc(2);

};
	
void	fstore            	(u1* operands){};
	
void	dstore            	(u1* operands){};
	
void	astore            	(u1* operands){};
	
void	istore_0          	(u1* operands){
    frame_stack.top->locals[0] = pop_stack();
    ipc(1);
};
	
void	istore_1          	(u1* operands){
    frame_stack.top->locals[1] = pop_stack();
    ipc(1);
};
	
void	istore_2          	(u1* operands){
    frame_stack.top->locals[2] = pop_stack();
    ipc(1);
};
	
void	istore_3          	(u1* operands){
    frame_stack.top->locals[3] = pop_stack();
    ipc(1);
};
	
void	lstore_0          	(u1* operands){
    frame_stack.top->locals[0] = pop_stack(); 
    frame_stack.top->locals[1] = pop_stack();
    ipc(1);
};
	
void	lstore_1          	(u1* operands){
    frame_stack.top->locals[1] = pop_stack(); 
    frame_stack.top->locals[2] = pop_stack();
    ipc(1);
};
	
void	lstore_2          	(u1* operands){
    frame_stack.top->locals[2] = pop_stack();
    frame_stack.top->locals[3] = pop_stack();
    ipc(1);
};
	
void	lstore_3          	(u1* operands){
    frame_stack.top->locals[3] = pop_stack(); 
    frame_stack.top->locals[4] = pop_stack();
    ipc(1);
};
	
void	fstore_0          	(u1* operands){};
	
void	fstore_1          	(u1* operands){};
	
void	fstore_2          	(u1* operands){};
	
void	fstore_3          	(u1* operands){};
	
void	dstore_0          	(u1* operands){};
	
void	dstore_1          	(u1* operands){};
	
void	dstore_2          	(u1* operands){};
	
void	dstore_3          	(u1* operands){};
	
void	astore_0          	(u1* operands){};
	
void	astore_1          	(u1* operands){};
	
void	astore_2          	(u1* operands){};
	
void	astore_3          	(u1* operands){};
	
void	iastore           	(u1* operands){};
	
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
    push(pop_stack() + pop_stack());
};
	
void	ladd              	(u1* operands){
    push_u8((int64_t)pop_stack_u8() + (int64_t)pop_stack_u8());
};
	
void	fadd              	(u1* operands){};
	
void	dadd              	(u1* operands){};
	
void	isub              	(u1* operands){
    push((int32_t)pop_stack_u8() + (int32_t)pop_stack_u8());
};
	
void	lsub              	(u1* operands){};
	
void	fsub              	(u1* operands){};
	
void	dsub              	(u1* operands){};
	
void	imul              	(u1* operands){};
	
void	lmul              	(u1* operands){};
	
void	fmul              	(u1* operands){};
	
void	dmul              	(u1* operands){};
	
void	idiv              	(u1* operands){};
	
void	ldiv_              	(u1* operands){};
	
void	fdiv              	(u1* operands){};
	
void	ddiv              	(u1* operands){};
	
void	irem              	(u1* operands){};
	
void	lrem              	(u1* operands){};
	
void	frem              	(u1* operands){};
	
void	drem              	(u1* operands){};
	
void	ineg              	(u1* operands){};
	
void	lneg              	(u1* operands){};
	
void	fneg              	(u1* operands){};
	
void	dneg              	(u1* operands){};
	
void	ishl              	(u1* operands){};
	
void	lshl              	(u1* operands){};
	
void	ishr              	(u1* operands){};
	
void	lshr              	(u1* operands){};
	
void	iushr             	(u1* operands){};
	
void	lushr             	(u1* operands){};
	
void	iand              	(u1* operands){};
	
void	land              	(u1* operands){};
	
void	ior               	(u1* operands){};
	
void	lor               	(u1* operands){};
	
void	ixor              	(u1* operands){};
	
void	lxor              	(u1* operands){};
	
void	iinc              	(u1* operands){
    frame_stack.top->locals[operands[0]] += (int32_t) operands[1];
};
	
void	i2l               	(u1* operands){};
	
void	i2f               	(u1* operands){};
	
void	i2d               	(u1* operands){};
	
void	l2i               	(u1* operands){};
	
void	l2f               	(u1* operands){};
	
void	l2d               	(u1* operands){};
	
void	f2i               	(u1* operands){};
	
void	f2l               	(u1* operands){};
	
void	f2d               	(u1* operands){};
	
void	d2i               	(u1* operands){};
	
void	d2l               	(u1* operands){};
	
void	d2f               	(u1* operands){};
	
void	i2b               	(u1* operands){};
	
void	i2c               	(u1* operands){};
	
void	i2s               	(u1* operands){};
	
void	lcmp              	(u1* operands){};
	
void	fcmpl             	(u1* operands){};
	
void	fcmpg             	(u1* operands){};
	
void	dcmpl             	(u1* operands){};
	
void	dcmpg             	(u1* operands){};
	
void	ifeq              	(u1* operands){};
	
void	ifne              	(u1* operands){};
	
void	iflt              	(u1* operands){};
	
void	ifge              	(u1* operands){};
	
void	ifgt              	(u1* operands){};
	
void	ifle              	(u1* operands){
    int v = pop_stack();
    if (v<=0){
        ipc(operands[0]<<8 | operands[1]);
    }
    else{
        ipc(3);
    }

};

void	if_icmpeq         	(u1* operands){};
	
void	if_icmpne         	(u1* operands){};
	
void	if_icmplt         	(u1* operands){};
	
void	if_icmpge         	(u1* operands){};
	
void	if_icmpgt         	(u1* operands){};
	
void	if_icmple         	(u1* operands){};
	
void	if_acmpeq         	(u1* operands){};
	
void	if_acmpne         	(u1* operands){};
	
void	goto_              	(u1* operands){};
	
void	jsr               	(u1* operands){};
	
void	ret               	(u1* operands){};
	
void	tableswitch       	(u1* operands){};
	
void	lookupswitch      	(u1* operands){};
	
void	ireturn           	(u1* operands){};
	
void	lreturn           	(u1* operands){};
	
void	freturn           	(u1* operands){};
	
void	dreturn           	(u1* operands){};
	
void	areturn           	(u1* operands){};
	
void	return_            	(u1* operands){
    ipc(1);
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
    u2 index = (u2) operands[0]<<8 | operands[1] + 1;
    cp_info *item =  get_from_cp(cp, cf.constant_pool_count, index) ;
    item = get_from_cp(cp, cf.constant_pool_count, item->info.Methodref.name_and_type_index);
    item = get_from_cp(cp, cf.constant_pool_count, item->info.Methodref.name_and_type_index)->info.NameAndType.name_index;
    if (strcmp(item->info.Utf8.bytes, "print")){
        item =  get_from_cp(cp, cf.constant_pool_count, pop_stack()) ;
        printf("%s",item->info.Utf8.bytes);
    }
    if (strcmp(item->info.Utf8.bytes, "println")){
        item =  get_from_cp(cp, cf.constant_pool_count, pop_stack()) ;
        printf("%s\n",item->info.Utf8.bytes);
    }
    ipc(3);
};
	
void	invokespecial     	(u1* operands){};
	
void	invokestatic      	(u1* operands){};
	
void	invokeinterface   	(u1* operands){};
	
void	invokedynamic     	(u1* operands){};
	
void	new               	(u1* operands){};
	
void	newarray          	(u1* operands){};
	
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
 
