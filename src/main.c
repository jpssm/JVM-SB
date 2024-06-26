#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <class_loader/class_file.h>
#include <leitor_exibidor/leitor_exibidor.h>
#include <execution_engine/jvm.h>


/**
 * Ponto de entrada do programa.
 *
 * @param argc Número de argumentos passados na linha de comando.
 * @param argv Argumentos passados na linha de comando - O nome do arquivo.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int main(int argc, char const *argv[]) {

    // Verifica se o nome do arquivo foi passado na linha de comando.
    if (argc != 2) {
        printf("Passe o nome do arquivo na execucao\nUso: %s <filename>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo binário do classfile.
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo.");
        return 1;
    }

    // Cria um objeto ClassFile a partir do arquivo binário.
    ClassFile *cf = create_classfile(file);

    // Loop principal do programa.
    while (1) {
        CLEAR; // Limpa a tela.

        // Menu de opções.
        printf("Exibir .class (1) ou executar na JVM (2) ou sair (3): ");
        char c;
        scanf("%c", &c);

        switch (c) {
            case '1':
                // Exibe o conteúdo do classfile.
                showClass(cf);
                break;

            case '2':
                // Executa o bytecode do classfile na JVM.
                jvm(cf);
                break;

            case '3':
                // Sai do loop principal.
                goto sair;
                break;

            default:
                // Opção inválida.
                printf("Opcao Invalida!\n");
                printf("\nPressione qualquer tecla para voltar");
                getch();
        }
    }

sair:
    // Libera a memória alocada para o ClassFile.
    free(cf);

    // Fecha o arquivo binário.
    fclose(file);

    return 0;
}
