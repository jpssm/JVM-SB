#ifndef BYTES_C
#define BYTES_C

#include <class_loader/bytes.h>



/**
 * Lê um byte de um arquivo e o retorna como um tipo de dado de 8 bits sem sinal (u1).
 *
 * @param fd Um ponteiro para o arquivo binário de onde o byte será lido.
 * @return O byte lido como um tipo de dado de 8 bits sem sinal (u1).
 */
static u1 u1Read(FILE *fd) {
    u1 toReturn = getc(fd); // Lê o primeiro byte
    return toReturn;
}

/**
 * Lê dois bytes de um arquivo e os retorna como um tipo de dado de 16 bits sem sinal (u2).
 *
 * @param fd Um ponteiro para o arquivo binário de onde os bytes serão lidos.
 * @return Os bytes lidos como um tipo de dado de 16 bits sem sinal (u2).
 */
static u2 u2Read(FILE *fd) {
    u2 toReturn = getc(fd);
    toReturn = (toReturn << 8) | (getc(fd));
    return toReturn;
}

/**
 * Lê quatro bytes de um arquivo e os retorna como um tipo de dado de 32 bits sem sinal (u4).
 *
 * @param fd Um ponteiro para o arquivo binário de onde os bytes serão lidos.
 * @return Os bytes lidos como um tipo de dado de 32 bits sem sinal (u4).
 */
static u4 u4Read(FILE *fd) {
    u4 toReturn = getc(fd);                         // Lê o primeiro byte
    toReturn = (toReturn << 24) | (getc(fd) << 16); // Desloca e lê o segundo byte
    toReturn |= (getc(fd) << 8);                    // Lê o terceiro byte
    toReturn |= getc(fd);                           // Lê o quarto byte
    return toReturn;
}

/**
 * Lê oito bytes de um arquivo e os retorna como um tipo de dado de 64 bits sem sinal (u8).
 *
 * @param fd Um ponteiro para o arquivo binário de onde os bytes serão lidos.
 * @return Os bytes lidos como um tipo de dado de 64 bits sem sinal (u8).
 */
static u8 u8Read(FILE *fd) {
    u8 toReturn = getc(fd); // Lê o primeiro byte
    toReturn = (toReturn << 56) | ((u8) getc(fd) << 48); // Desloca e lê o segundo byte
    toReturn |= ((u8) getc(fd) << 40); // Lê o terceiro byte
    toReturn |= ((u8) getc(fd) << 32); // Lê o quarto byte
    toReturn |= ((u8) getc(fd) << 24); // Lê o quinto byte
    toReturn |= ((u8) getc(fd) << 16); // Lê o sexto byte
    toReturn |= ((u8) getc(fd) << 8); // Lê o sétimo byte
    toReturn |= getc(fd); // Lê o oitavo byte
    return toReturn;
}


#endif
