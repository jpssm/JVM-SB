/**
 * @file bytes.h
 * @brief Declarações de tipos e funções para leitura de bytes de arquivos.
 */

#ifndef BYTES_H
#define BYTES_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @typedef uint8_t u1
 * @brief Define um tipo de 1 byte sem sinal.
 */
typedef uint8_t u1;

/**
 * @typedef uint16_t u2
 * @brief Define um tipo de 2 bytes sem sinal.
 */
typedef uint16_t u2;

/**
 * @typedef uint32_t u4
 * @brief Define um tipo de 4 bytes sem sinal.
 */
typedef uint32_t u4;

/**
 * @typedef uint64_t u8
 * @brief Define um tipo de 8 bytes sem sinal.
 */
typedef uint64_t u8;

/**
 * @brief Lê 1 byte de um arquivo.
 * 
 * @param fd Ponteiro para o arquivo de onde o byte será lido.
 * @return O byte lido.
 */
static u1 u1Read(FILE *fd);

/**
 * @brief Lê 2 bytes de um arquivo.
 * 
 * @param fd Ponteiro para o arquivo de onde os bytes serão lidos.
 * @return Os 2 bytes lidos.
 */
static u2 u2Read(FILE *fd);

/**
 * @brief Lê 4 bytes de um arquivo.
 * 
 * @param fd Ponteiro para o arquivo de onde os bytes serão lidos.
 * @return Os 4 bytes lidos.
 */
static u4 u4Read(FILE *fd);

/**
 * @brief Lê 8 bytes de um arquivo.
 * 
 * @param fd Ponteiro para o arquivo de onde os bytes serão lidos.
 * @return Os 8 bytes lidos.
 */
static u8 u8Read(FILE *fd);

#endif
