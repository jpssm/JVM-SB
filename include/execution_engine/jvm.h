#ifndef EXECUTION_ENGINE_H
#define EXECUTION_ENGINE_H

#include <class_loader/bytes.h>
#include <runtime_data/runtime_data.h>

void jvm(ClassFile * class);

//Instruction                  Hex  Operand Type
void nop             (u1* operands); // 0x00    None
void aconst_null     (u1* operands);// 0x01    None
void iconst_m1       (u1* operands);// 0x02    None
void iconst_0        (u1* operands);// 0x03    None
void iconst_1        (u1* operands);// 0x04    None
void iconst_2        (u1* operands);// 0x05    None
void iconst_3        (u1* operands);// 0x06    None
void iconst_4        (u1* operands);// 0x07    None
void iconst_5        (u1* operands);// 0x08    None
void lconst_0        (u1* operands);// 0x09    None
void lconst_1        (u1* operands);// 0x0a    None
void fconst_0        (u1* operands);// 0x0b    None
void fconst_1        (u1* operands);// 0x0c    None
void fconst_2        (u1* operands);// 0x0d    None
void dconst_0        (u1* operands);// 0x0e    None
void dconst_1        (u1* operands);// 0x0f    None
void bipush          (u1* operands);// 0x10    Byte
void sipush          (u1* operands);// 0x11    Short
void ldc             (u1* operands);// 0x12    Byte (index to constant pool)
void ldc_w           (u1* operands);// 0x13    Short (index to constant pool)
void ldc2_w          (u1* operands);// 0x14    Short (index to constant pool)
void iload           (u1* operands);// 0x15    Byte (local variable index)
void lload           (u1* operands);// 0x16    Byte (local variable index)
void fload           (u1* operands);// 0x17    Byte (local variable index)
void dload           (u1* operands);// 0x18    Byte (local variable index)
void aload           (u1* operands);// 0x19    Byte (local variable index)
void iload_0         (u1* operands);// 0x1a    None
void iload_1         (u1* operands);// 0x1b    None
void iload_2         (u1* operands);// 0x1c    None
void iload_3         (u1* operands);// 0x1d    None
void lload_0         (u1* operands);// 0x1e    None
void lload_1         (u1* operands);// 0x1f    None
void lload_2         (u1* operands);// 0x20    None
void lload_3         (u1* operands);// 0x21    None
void fload_0         (u1* operands);// 0x22    None
void fload_1         (u1* operands);// 0x23    None
void fload_2         (u1* operands);// 0x24    None
void fload_3         (u1* operands);// 0x25    None
void dload_0         (u1* operands);// 0x26    None
void dload_1         (u1* operands);// 0x27    None
void dload_2         (u1* operands);// 0x28    None
void dload_3         (u1* operands);// 0x29    None
void aload_0         (u1* operands);// 0x2a    None
void aload_1         (u1* operands);// 0x2b    None
void aload_2         (u1* operands);// 0x2c    None
void aload_3         (u1* operands);// 0x2d    None
void iaload          (u1* operands);// 0x2e    None
void laload          (u1* operands);// 0x2f    None
void faload          (u1* operands);// 0x30    None
void daload          (u1* operands);// 0x31    None
void aaload          (u1* operands);// 0x32    None
void baload          (u1* operands);// 0x33    None
void caload          (u1* operands);// 0x34    None
void saload          (u1* operands);// 0x35    None
void istore          (u1* operands);// 0x36    Byte (local variable index)
void lstore          (u1* operands);// 0x37    Byte (local variable index)
void fstore          (u1* operands);// 0x38    Byte (local variable index)
void dstore          (u1* operands);// 0x39    Byte (local variable index)
void astore          (u1* operands);// 0x3a    Byte (local variable index)
void istore_0        (u1* operands);// 0x3b    None
void istore_1        (u1* operands);// 0x3c    None
void istore_2        (u1* operands);// 0x3d    None
void istore_3        (u1* operands);// 0x3e    None
void lstore_0        (u1* operands);// 0x3f    None
void lstore_1        (u1* operands);// 0x40    None
void lstore_2        (u1* operands);// 0x41    None
void lstore_3        (u1* operands);// 0x42    None
void fstore_0        (u1* operands);// 0x43    None
void fstore_1        (u1* operands);// 0x44    None
void fstore_2        (u1* operands);// 0x45    None
void fstore_3        (u1* operands);// 0x46    None
void dstore_0        (u1* operands);// 0x47    None
void dstore_1        (u1* operands);// 0x48    None
void dstore_2        (u1* operands);// 0x49    None
void dstore_3        (u1* operands);// 0x4a    None
void astore_0        (u1* operands);// 0x4b    None
void astore_1        (u1* operands);// 0x4c    None
void astore_2        (u1* operands);// 0x4d    None
void astore_3        (u1* operands);// 0x4e    None
void iastore         (u1* operands);// 0x4f    None
void lastore         (u1* operands);// 0x50    None
void fastore         (u1* operands);// 0x51    None
void dastore         (u1* operands);// 0x52    None
void aastore         (u1* operands);// 0x53    None
void bastore         (u1* operands);// 0x54    None
void castore         (u1* operands);// 0x55    None
void sastore         (u1* operands);// 0x56    None
void pop             (u1* operands);// 0x57    None
void pop2            (u1* operands);// 0x58    None
void dup             (u1* operands);// 0x59    None
void dup_x1          (u1* operands);// 0x5a    None
void dup_x2          (u1* operands);// 0x5b    None
void dup2            (u1* operands);// 0x5c    None
void dup2_x1         (u1* operands);// 0x5d    None
void dup2_x2         (u1* operands);// 0x5e    None
void swap            (u1* operands);// 0x5f    None
void iadd            (u1* operands);// 0x60    None
void ladd            (u1* operands);// 0x61    None
void fadd            (u1* operands);// 0x62    None
void dadd            (u1* operands);// 0x63    None
void isub            (u1* operands);// 0x64    None
void lsub            (u1* operands);// 0x65    None
void fsub            (u1* operands);// 0x66    None
void dsub            (u1* operands);// 0x67    None
void imul            (u1* operands);// 0x68    None
void lmul            (u1* operands);// 0x69    None
void fmul            (u1* operands);// 0x6a    None
void dmul            (u1* operands);// 0x6b    None
void idiv            (u1* operands);// 0x6c    None
void ldiv_            (u1* operands);// 0x6d    None
void fdiv            (u1* operands);// 0x6e    None
void ddiv            (u1* operands);// 0x6f    None
void irem            (u1* operands);// 0x70    None
void lrem            (u1* operands);// 0x71    None
void frem            (u1* operands);// 0x72    None
void drem            (u1* operands);// 0x73    None
void ineg            (u1* operands);// 0x74    None
void lneg            (u1* operands);// 0x75    None
void fneg            (u1* operands);// 0x76    None
void dneg            (u1* operands);// 0x77    None
void ishl            (u1* operands);// 0x78    None
void lshl            (u1* operands);// 0x79    None
void ishr            (u1* operands);// 0x7a    None
void lshr            (u1* operands);// 0x7b    None
void iushr           (u1* operands);// 0x7c    None
void lushr           (u1* operands);// 0x7d    None
void iand            (u1* operands);// 0x7e    None
void land            (u1* operands);// 0x7f    None
void ior             (u1* operands);// 0x80    None
void lor             (u1* operands);// 0x81    None
void ixor            (u1* operands);// 0x82    None
void lxor            (u1* operands);// 0x83    None
void iinc            (u1* operands);// 0x84    Byte (index), Byte (constant)
void i2l             (u1* operands);// 0x85    None
void i2f             (u1* operands);// 0x86    None
void i2d             (u1* operands);// 0x87    None
void l2i             (u1* operands);// 0x88    None
void l2f             (u1* operands);// 0x89    None
void l2d             (u1* operands);// 0x8a    None
void f2i             (u1* operands);// 0x8b    None
void f2l             (u1* operands);// 0x8c    None
void f2d             (u1* operands);// 0x8d    None
void d2i             (u1* operands);// 0x8e    None
void d2l             (u1* operands);// 0x8f    None
void d2f             (u1* operands);// 0x90    None
void i2b             (u1* operands);// 0x91    None
void i2c             (u1* operands);// 0x92    None
void i2s             (u1* operands);// 0x93    None
void lcmp            (u1* operands);// 0x94    None
void fcmpl           (u1* operands);// 0x95    None
void fcmpg           (u1* operands);// 0x96    None
void dcmpl           (u1* operands);// 0x97    None
void dcmpg           (u1* operands);// 0x98    None
void ifeq            (u1* operands);// 0x99    Short (branch offset)
void ifne            (u1* operands);// 0x9a    Short (branch offset)
void iflt            (u1* operands);// 0x9b    Short (branch offset)
void ifge            (u1* operands);// 0x9c    Short (branch offset)
void ifgt            (u1* operands);// 0x9d    Short (branch offset)
void ifle            (u1* operands);// 0x9e    Short (branch offset)
void if_icmpeq       (u1* operands);// 0x9f    Short (branch offset)
void if_icmpne       (u1* operands);// 0xa0    Short (branch offset)
void if_icmplt       (u1* operands);// 0xa1    Short (branch offset)
void if_icmpge       (u1* operands);// 0xa2    Short (branch offset)
void if_icmpgt       (u1* operands);// 0xa3    Short (branch offset)
void if_icmple       (u1* operands);// 0xa4    Short (branch offset)
void if_acmpeq       (u1* operands);// 0xa5    Short (branch offset)
void if_acmpne       (u1* operands);// 0xa6    Short (branch offset)
void goto_            (u1* operands);// 0xa7    Short (branch offset)
void jsr             (u1* operands);// 0xa8    Short (branch offset)
void ret             (u1* operands);// 0xa9    Byte (local variable index)
void tableswitch     (u1* operands);// 0xaa    Padding, int (default offset), int (low), int (high), int[] (jump offsets)
void lookupswitch    (u1* operands);// 0xab    Padding, int (default offset), int (npairs), {int, int}[] (match-offset pairs)
void ireturn         (u1* operands);// 0xac    None
void lreturn         (u1* operands);// 0xad    None
void freturn         (u1* operands);// 0xae    None
void dreturn         (u1* operands);// 0xaf    None
void areturn         (u1* operands);// 0xb0    None
void return_          (u1* operands);// 0xb1    None
void getstatic       (u1* operands);// 0xb2    Short (index to constant pool)
void putstatic       (u1* operands);// 0xb3    Short (index to constant pool)
void getfield        (u1* operands);// 0xb4    Short (index to constant pool)
void putfield        (u1* operands);// 0xb5    Short (index to constant pool)
void invokevirtual   (u1* operands);// 0xb6    Short (index to constant pool)
void invokespecial   (u1* operands);// 0xb7    Short (index to constant pool)
void invokestatic    (u1* operands);// 0xb8    Short (index to constant pool)
void invokeinterface (u1* operands);// 0xb9    Short (index to constant pool), Byte (count), Byte (0)
void invokedynamic   (u1* operands);// 0xba    Short (index to constant pool), Byte (0), Byte (0)
void new             (u1* operands);// 0xbb    Short (index to constant pool)
void newarray        (u1* operands);// 0xbc    Byte (atype)
void anewarray       (u1* operands);// 0xbd    Short (index to constant pool)
void arraylength     (u1* operands);// 0xbe    None
void athrow          (u1* operands);// 0xbf    None
void checkcast       (u1* operands);// 0xc0    Short (index to constant pool)
void instanceof      (u1* operands);// 0xc1    Short (index to constant pool)
void monitorenter    (u1* operands);// 0xc2    None
void monitorexit     (u1* operands);// 0xc3    None
void wide            (u1* operands);// 0xc4    Byte (opcode), additional bytes depending on opcode
void multianewarray  (u1* operands);// 0xc5    Short (index to constant pool), Byte (dimensions)
void ifnull          (u1* operands);// 0xc6    Short (branch offset)
void ifnonnull       (u1* operands);// 0xc7    Short (branch offset)
void goto_w          (u1* operands);// 0xc8    Int (branch offset)
void jsr_w           (u1* operands);// 0xc9    Int (branch offset)
void breakpoint      (u1* operands);// 0xca    None (reserved for debuggers)
void impdep1         (u1* operands);// 0xfe    None (reserved for implementation-dependent operations)
void impdep2         (u1* operands);// 0xff    None (reserved for implementation-dependent operations)



#endif

