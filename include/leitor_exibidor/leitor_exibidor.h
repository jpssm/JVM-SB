#ifndef LEITOR_EXIBIDOR_H
#define LEITOR_EXIBIDOR_H

#include <class_loader/class_file.h>

#ifdef _WIN32 
#define CLEAR system("cls");
#endif

#ifdef __linux__  
#define CLEAR system("clear");
#endif

#ifdef __APPLE__  
#define CLEAR system("clear");
#endif

void showClass(ClassFile *cf);


#endif
