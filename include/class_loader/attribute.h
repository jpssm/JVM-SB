/**
 * @file attribute.h
 * @brief Declarações de estruturas e funções para manipulação de atributos de classes Java.
 */

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <class_loader/bytes.h>
#include <class_loader/constant_pool.h>

/**
 * @struct attribute_info_struct
 * @brief Estrutura para armazenar informações de atributos genéricos.
 */
struct attribute_info_struct
{
    u2 attribute_name_index; /**< Índice no pool de constantes que indica o nome do atributo. */
    u4 attribute_length;     /**< Comprimento do atributo em bytes, excluindo este cabeçalho. */
    u1 *info;                /**< Ponteiro para os dados do atributo. */
} typedef attribute_info;

/**
 * @struct exception_table_struct
 * @brief Estrutura para armazenar informações da tabela de exceções.
 */
struct exception_table_struct{
    u2 start_pc;   /**< Ponto de início do bloco de código a ser protegido. */
    u2 end_pc;     /**< Ponto de término do bloco de código a ser protegido. */
    u2 handler_pc; /**< Ponto de início do manipulador de exceções. */
    u2 catch_type; /**< Índice no pool de constantes que indica o tipo de exceção a ser capturada. */
} typedef exception_table;

/**
 * @struct code_attribute_struct
 * @brief Estrutura para armazenar informações de atributos de código.
 */
struct code_attribute_struct{
    u2 attribute_name_index;      /**< Índice no pool de constantes que indica o nome do atributo. */ 
    u4 attribute_length;          /**< Comprimento do atributo em bytes, excluindo este cabeçalho. */
    u2 max_stack;                 /**< Tamanho máximo da pilha de operandos do método. */
    u2 max_locals;                /**< Número máximo de variáveis locais do método. */
    u4 code_length;               /**< Comprimento do array de código em bytes. */
    u1 *code;                     /**< Ponteiro para o array de código (bytecode). */
    u2 exception_table_length;    /**< Número de entradas na tabela de exceções. */
    exception_table *exeption;    /**< Ponteiro para a tabela de exceções. */
    u2 attributes_count;          /**< Número de atributos adicionais. */
    attribute_info *attributes;   /**< Ponteiro para os atributos adicionais. */
} typedef code_attribute;

/**
 * @brief Cria um array de atributos a partir de um arquivo.
 * 
 * @param file Ponteiro para o arquivo que contém os dados dos atributos.
 * @param count Número de atributos a serem lidos.
 * @return Ponteiro para o array de atributos criado.
 */
attribute_info* create_attributes(FILE *file, u2 count);

/**
 * @brief Obtém um atributo de código a partir de um array de atributos.
 * 
 * @param attribute Ponteiro para o array de atributos.
 * @param count Número de atributos no array.
 * @param constant_pool Ponteiro para o pool de constantes.
 * @return Ponteiro para o atributo de código encontrado, ou NULL se não for encontrado.
 */
code_attribute* get_code_attribute(attribute_info* attribute, u2 count, cp_info *constant_pool);

#endif
