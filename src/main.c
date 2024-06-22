
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <class_loader/class_file.h>
#include <leitor_exibidor/leitor_exibidor.h>
#include "jvm.c"


int main(int argc, char const *argv[])
{

    // Nome do arquivo passado na execucao
    if (argc != 2)
    {
        printf("Passe o nome do arquivo na execucao\nUso: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "rb"); // abrindo arquivo

    if (file == NULL)
    {
        printf("Erro ao abrir arquivo.");
        return 1;
    }


    ClassFile *cf = create_classfile(file);



    while (1)
    {
        CLEAR;
        printf("Exibir .class (1) ou executar na JVM (2) ou sair (3): ");
        char c;
        scanf("%c", &c);
        switch (c)
        {
            case '1':
                showClass(cf);
                break;
            case '2':
                jvm(cf);
                break;
            case '3':
                goto sair;
                break;
            default:
                printf("Opcao Invalida!\n");
                printf("\nPressione qualquer tecla para voltar");
                getch(); 
        }

    }
    sair:
    free(cf);
    fclose(file);

    return 0;
}
