/**
 * @file constant_pool.h
 * @brief Definições relacionadas à pool de constantes.
 */

#ifndef CONSTANT_POOL_H
#define CONSTANT_POOL_H

#include <class_loader/bytes.h>

// Constantes de tag da pool de constantes
#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1

/**
 * @struct cp_info_struct
 * @brief Estrutura que representa um item da pool de constantes.
 */
typedef struct cp_info_struct {
    u1 tag; /**< Tag que indica o tipo do item da pool de constantes. */
    union {
        struct {
            u2 name_index; /**< Índice para o nome da classe. */
        } Class;
        struct {
            u2 class_index; /**< Índice para a classe. */
            u2 name_and_type_index; /**< Índice para o nome e tipo. */
        } Fieldref;
        struct {
            u2 class_index; /**< Índice para a classe. */
            u2 name_and_type_index; /**< Índice para o nome e tipo. */
        } Methodref;
        struct {
            u2 class_index; /**< Índice para a classe. */
            u2 name_and_type_index; /**< Índice para o nome e tipo. */
        } InterfaceMethodref;
        struct {
            u2 string_index; /**< Índice para a string. */
        } String;
        struct {
            u4 bytes; /**< Valor inteiro de 32 bits. */
        } Integer;
        struct {
            u4 bytes; /**< Valor de ponto flutuante de 32 bits. */
        } Float;
        struct {
            u4 high_bytes; /**< Bytes mais significativos do valor inteiro de 64 bits. */
            u4 low_bytes; /**< Bytes menos significativos do valor inteiro de 64 bits. */
        } Long;
        struct {
            u4 high_bytes; /**< Bytes mais significativos do valor de ponto flutuante de 64 bits. */
            u4 low_bytes; /**< Bytes menos significativos do valor de ponto flutuante de 64 bits. */
        } Double;
        struct {
            u2 name_index; /**< Índice para o nome. */
            u2 descriptor_index; /**< Índice para o descritor. */
        } NameAndType;
        struct {
            u2 length; /**< Comprimento da string UTF-8. */
            u1 *bytes; /**< Ponteiro para os bytes da string UTF-8. */
        } Utf8;
    } info;
} cp_info;

/**
 * @brief Cria uma pool de constantes baseada em um arquivo e um contador.
 *
 * Esta função lê a estrutura da pool de constantes de um arquivo binário e
 * retorna um ponteiro para a pool de constantes criada.
 *
 * @param file Um ponteiro para o arquivo binário a ser lido.
 * @param count O número de elementos na pool de constantes.
 * @return Um ponteiro para a pool de constantes criada.
 */
cp_info *create_constant_pool(FILE *file, u2 count);


/**
 * @brief Libera memória do Pool de constantes.
 *
 *
 * @param cp Um ponteiro para estrutura Constant Pool.
 * @param count O número de elementos na pool de constantes.
 */
void destroy_cp(cp_info* cp, u2 count);


/**
 * @brief Imprime os itens da pool de constantes.
 *
 * Esta função imprime os itens da pool de constantes na saída padrão.
 *
 * @param cp Um ponteiro para a pool de constantes.
 * @param count O número de itens na pool de constantes.
 */


cp_info *get_from_cp(cp_info *constantPool, u2 count, u2 index);

#endif
