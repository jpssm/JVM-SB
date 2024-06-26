/**
 * @file code_attribute.h
 * @brief Declarações de estruturas e funções para manipulação do atributo de código de classes Java.
 */

#ifndef CODE_ATTRIBUTE_H
#define CODE_ATTRIBUTE_H

#include <class_loader/bytes.h>
#include <class_loader/field.h>
#include <class_loader/method.h>
#include <class_loader/constant_pool.h>
#include <class_loader/class_file.h>

/**
 * @struct code_attribute_struct
 * @brief Estrutura para armazenar informações do atributo de código.
 */
typedef struct code_attribute_struct
{
    u2 attribute_name_index;     /**< Índice no pool de constantes que indica o nome do atributo. */
    u4 attribute_length;         /**< Comprimento do atributo em bytes, excluindo este cabeçalho. */
    u2 max_stack;                /**< Tamanho máximo da pilha de operandos do método. */
    u2 max_locals;               /**< Número máximo de variáveis locais do método. */
    u4 code_length;              /**< Comprimento do array de código em bytes. */
    u1 *code;                    /**< Ponteiro para o array de código (bytecode). */
    u2 exception_table_length;   /**< Número de entradas na tabela de exceções. */
    u2 *exception_table;         /**< Ponteiro para a tabela de exceções. */
    u2 attributes_count;         /**< Número de atributos adicionais. */
    u1 *attributes;              /**< Ponteiro para os atributos adicionais. */
} code_attribute;

/**
 * @brief Cria uma estrutura code_attribute a partir de um arquivo.
 * 
 * @param file Ponteiro para o arquivo que contém os dados do atributo de código.
 * @return Ponteiro para a estrutura code_attribute criada.
 */
code_attribute* create_code_attribute(FILE *file);

#endif // CODE_ATTRIBUTE_H
