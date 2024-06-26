/**
 * @file method.h
 * @brief Declarações de estruturas e funções para manipulação de métodos de classes Java.
 */

#ifndef METHOD_H
#define METHOD_H

#include <class_loader/bytes.h>
#include <class_loader/attribute.h>
#include <class_loader/constant_pool.h>

/**
 * @struct method_info_struct
 * @brief Estrutura para armazenar informações de métodos de uma classe Java.
 */
typedef struct method_info_struct
{
    u2 access_flags;             /**< Flags de acesso do método. */
    u2 name_index;               /**< Índice no pool de constantes que indica o nome do método. */
    u2 descriptor_index;         /**< Índice no pool de constantes que indica o descritor do método. */
    u2 attributes_count;         /**< Número de atributos adicionais deste método. */
    attribute_info *attributes;  /**< Ponteiro para os atributos adicionais deste método. */
    code_attribute *code_attribute; /**< Ponteiro para o atributo de código deste método (se houver). */
} method_info;

/**
 * @brief Cria um array de estruturas method_info a partir de um arquivo.
 * 
 * @param file Ponteiro para o arquivo que contém os dados dos métodos.
 * @param count Número de métodos a serem lidos.
 * @param constant_pool Ponteiro para o pool de constantes da classe.
 * @return Ponteiro para o array de estruturas method_info criado.
 */
method_info *create_methods(FILE *file, u2 count, cp_info *constant_pool);

#endif // METHOD_H
