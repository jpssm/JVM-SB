
#ifndef BYTES_H
#define BYTES_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;


static u1 u1Read(FILE *fd);
static u2 u2Read(FILE *fd);
static u4 u4Read(FILE *fd);
static u8 u8Read(FILE *fd);

#endif
