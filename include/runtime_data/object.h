/**
 * @file object.h
 * @brief Define estruturas e funções para manipulação de objetos e arrays na Máquina Virtual Java (JVM).
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <class_loader/class_file.h>
#include <class_loader/method.h>
#include <class_loader/bytes.h>

/**
 * @def T_BOOLEAN
 * @brief Macro que representa o tipo booleano em arrays na JVM.
 */
#define T_BOOLEAN 4

/**
 * @def T_CHAR
 * @brief Macro que representa o tipo char em arrays na JVM.
 */
#define T_CHAR 5

/**
 * @def T_FLOAT
 * @brief Macro que representa o tipo float em arrays na JVM.
 */
#define T_FLOAT 6

/**
 * @def T_DOUBLE
 * @brief Macro que representa o tipo double em arrays na JVM.
 */
#define T_DOUBLE 7

/**
 * @def T_BYTE
 * @brief Macro que representa o tipo byte em arrays na JVM.
 */
#define T_BYTE 8

/**
 * @def T_SHORT
 * @brief Macro que representa o tipo short em arrays na JVM.
 */
#define T_SHORT 9

/**
 * @def T_INT
 * @brief Macro que representa o tipo int em arrays na JVM.
 */
#define T_INT 10

/**
 * @def T_LONG
 * @brief Macro que representa o tipo long em arrays na JVM.
 */
#define T_LONG 11

/**
 * @struct Array
 * @brief Estrutura que representa um array na JVM.
 */
typedef struct {
    void *content; /**< Ponteiro para o conteúdo do array. */
    u4 size;       /**< Tamanho do array. */
    u1 atype;      /**< Tipo do array conforme definido pelas macros T_* (T_BOOLEAN, T_CHAR, etc.). */
} Array;

/**
 * @brief Cria um novo array com o tamanho especificado e tipo.
 * 
 * @param size Tamanho do array.
 * @param type Tipo do array conforme definido pelas macros T_*.
 * @return Array* Ponteiro para a estrutura Array criada.
 */
Array *create_array(u4 size, u1 type);

#endif
