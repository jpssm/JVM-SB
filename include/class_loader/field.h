/**
 * @file field.h
 * @brief Declarações de estruturas e funções para manipulação de campos de classes Java.
 */

#ifndef FIELD_H
#define FIELD_H

#include <class_loader/bytes.h>
#include <class_loader/attribute.h>

/**
 * @struct field_info_struct
 * @brief Estrutura para armazenar informações de campos (variáveis de instância) de uma classe Java.
 */
typedef struct field_info_struct
{
    u2 access_flags;         /**< Flags de acesso do campo. */
    u2 name_index;           /**< Índice no pool de constantes que indica o nome do campo. */
    u2 descriptor_index;     /**< Índice no pool de constantes que indica o descritor do campo. */
    u2 attributes_count;     /**< Número de atributos adicionais deste campo. */
    attribute_info *attributes; /**< Ponteiro para os atributos adicionais deste campo. */
} field_info;

/**
 * @brief Cria um array de estruturas field_info a partir de um arquivo.
 * 
 * @param file Ponteiro para o arquivo que contém os dados dos campos.
 * @param count Número de campos a serem lidos.
 * @return Ponteiro para o array de estruturas field_info criado.
 */
field_info *create_fields(FILE *file, u2 count);

#endif // FIELD_H
