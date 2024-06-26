/**
 * @file runtime_data.h
 * @brief Define estruturas e funções para gerenciar os dados de execução de uma Máquina Virtual Java (JVM).
 */

#ifndef RUNTIME_DATA_H
#define RUNTIME_DATA_H

#include <class_loader/class_file.h>
#include <class_loader/method.h>
#include <class_loader/bytes.h>
#include <runtime_data/object.h>

/**
 * @brief Representa a área de métodos da JVM.
 */
typedef struct {
    ClassFile *class_list; /**< Lista de classes carregadas. */
    u4 size; /**< Número de classes carregadas. */
} Method_area;

/**
 * @brief Representa o heap de arrays da JVM.
 */
typedef struct {
    Array **arrays; /**< Lista de arrays alocados. */
    u4 count; /**< Número de arrays alocados. */
} Array_heap;

/**
 * @brief Representa um frame de pilha na JVM.
 */
typedef struct Frame {
    cp_info *cp; /**< Ponteiro para a pool de constantes. */
    u4 pc; /**< Contador de programa. */
    u4 *operand_stack; /**< Ponteiro para a pilha de operandos. */
    u4 *operand_stack_base; /**< Ponteiro base para a pilha de operandos. */
    u4 *locals; /**< Array de variáveis locais. */
    method_info *method; /**< Ponteiro para a informação do método. */
    u2 method_info_index; /**< Índice para a informação do método. */
    u1 *code; /**< Ponteiro para o bytecode do método. */
    u4 code_lenght; /**< Comprimento do bytecode. */
    struct Frame *next; /**< Ponteiro para o próximo frame na pilha. */
    struct Frame *previous; /**< Ponteiro para o frame anterior na pilha. */
} Frame;

/**
 * @brief Representa a pilha de frames na JVM.
 */
typedef struct {
    Frame *base; /**< Ponteiro para o frame base. */
    Frame *top; /**< Ponteiro para o frame do topo. */
    u4 stack_length; /**< Comprimento da pilha. */
} Frame_stack;

/**
 * @brief Cria e inicializa um novo frame para um dado método.
 * 
 * @param method Ponteiro para a informação do método.
 * @param method_info_index Índice para a informação do método.
 * @return Ponteiro para o frame criado.
 */
Frame *create_frame(method_info *method, u2 method_info_index);

/**
 * @brief Armazena um novo array no heap de arrays e retorna seu identificador.
 * 
 * @param array_heap Ponteiro para o heap de arrays.
 * @param array Ponteiro para o array a ser armazenado.
 * @return Identificador do array armazenado.
 */
u4 store_array(Array_heap *array_heap, Array *array);

/**
 * @brief Imprime a pilha de operandos de um frame para fins de depuração.
 * 
 * @param frame Ponteiro para o frame cuja pilha de operandos será impressa.
 */
void print_stack(Frame *frame);

/**
 * @brief Imprime as variáveis locais de um frame para fins de depuração.
 * 
 * @param frame Ponteiro para o frame cujas variáveis locais serão impressas.
 */
void print_locals(Frame *frame);

#endif
