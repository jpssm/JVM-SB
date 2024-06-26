/**
 * @file leitor_exibidor.h
 * @brief Define funções para exibição de informações de um arquivo de classe Java.
 */

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

/**
 * @brief Exibe informações detalhadas de um arquivo de classe Java.
 * 
 * @param cf Ponteiro para a estrutura ClassFile que representa o arquivo de classe Java.
 */
void showClass(ClassFile *cf);

#endif
