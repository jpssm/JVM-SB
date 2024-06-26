/**
 * @file class_file.h
 * @brief Módulo responsável pelas estruturas e funções para manipulação do ClassFile.
 */

#ifndef CLASS_FILE_H
#define CLASS_FILE_H

#include <class_loader/bytes.h>
#include <class_loader/attribute.h>
#include <class_loader/field.h>
#include <class_loader/method.h>
#include <class_loader/constant_pool.h>

/**
 * @struct class_file
 * @brief Estrutura que representa um arquivo de classe Java.
 */
typedef struct class_file
{
    u4 magic;                   /**< Número mágico para identificar o arquivo de classe (0xCAFEBABE). */
    u2 minor_version;           /**< Versão menor do compilador que gerou o arquivo de classe. */
    u2 major_version;           /**< Versão maior do compilador que gerou o arquivo de classe. */
    u2 constant_pool_count;     /**< Número de entradas no pool de constantes. */
    cp_info *constant_pool;     /**< Ponteiro para o pool de constantes. */
    u2 access_flags;            /**< Flags de acesso da classe. */
    u2 this_class;              /**< Índice no pool de constantes que aponta para a definição desta classe. */
    u2 super_class;             /**< Índice no pool de constantes que aponta para a superclasse desta classe. */
    u2 interfaces_count;        /**< Número de interfaces implementadas por esta classe. */
    u2 *interfaces;             /**< Ponteiro para os índices no pool de constantes que definem as interfaces. */
    u2 fields_count;            /**< Número de campos (variáveis de instância) declarados nesta classe. */
    field_info *fields;         /**< Ponteiro para os campos declarados nesta classe. */
    u2 methods_count;           /**< Número de métodos declarados nesta classe. */
    method_info *methods;       /**< Ponteiro para os métodos declarados nesta classe. */
    u2 attributes_count;        /**< Número de atributos adicionais desta classe. */
    attribute_info *attributes; /**< Ponteiro para os atributos adicionais desta classe. */
} ClassFile;

/**
 * @brief Cria uma estrutura ClassFile a partir de um arquivo.
 * 
 * @param file Ponteiro para o arquivo que contém os dados do arquivo de classe.
 * @return Ponteiro para a estrutura ClassFile criada.
 */
ClassFile *create_classfile(FILE *file);

/**
 * @brief Obtém o nome de um método a partir do pool de constantes.
 * 
 * @param count Número de entradas no pool de constantes.
 * @param constant_pool Ponteiro para o pool de constantes.
 * @param Methodref_index Índice no pool de constantes que aponta para a referência do método.
 * @return Ponteiro para uma string contendo o nome do método.
 */
char *get_method_name(u2 count, cp_info *constant_pool, u2 Methodref_index);

/**
 * @brief Obtém o descritor de um método a partir do pool de constantes.
 * 
 * @param count Número de entradas no pool de constantes.
 * @param constant_pool Ponteiro para o pool de constantes.
 * @param Methodref_index Índice no pool de constantes que aponta para a referência do método.
 * @return Ponteiro para uma string contendo o descritor do método.
 */
char *get_method_descriptor(u2 count, cp_info *constant_pool, u2 Methodref_index);

/**
 * @brief Obtém as informações de um método específico.
 * 
 * @param class_file Ponteiro para a estrutura ClassFile.
 * @param count Número de entradas no pool de constantes.
 * @param constant_pool Ponteiro para o pool de constantes.
 * @param Methodref_index Índice no pool de constantes que aponta para a referência do método.
 * @return Ponteiro para a estrutura method_info contendo as informações do método.
 */
method_info *get_method_info(ClassFile *class_file, u2 count, cp_info *constant_pool, u2 Methodref_index);

#endif // CLASS_FILE_H
