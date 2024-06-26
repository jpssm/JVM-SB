#ifndef OBJECT_H
#define OBJECT_H

#include <class_loader/class_file.h>
#include <class_loader/method.h>
#include <class_loader/bytes.h>


#define T_BOOLEAN 4
#define T_CHAR 5
#define T_FLOAT 6
#define T_DOUBLE 7
#define T_BYTE 8
#define T_SHORT 9
#define T_INT 10
#define T_LONG 11


typedef struct{
    void *content;
    u4 size;
    u1 atype;
} Array;


Array *create_array(u4 size, u1 type);

#endif