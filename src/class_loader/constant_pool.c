#include "bytes.c"
#include <class_loader/attribute.h>
#include <class_loader/field.h>
#include <class_loader/method.h>
#include <class_loader/constant_pool.h>
#include <class_loader/class_file.h>

/**
 * Cria uma pool de constantes baseada em um arquivo e um contador.
 *
 * Esta função lê a estrutura da pool de constantes de um arquivo binário e
 * retorna um ponteiro para a pool de constantes criada.
 *
 * @param file Um ponteiro para o arquivo binário a ser lido.
 * @param count O número de elementos na pool de constantes.
 * @return Um ponteiro para a pool de constantes criada.
 */
cp_info *create_constant_pool(FILE *file, u2 count)
{
    // Aloca memória para a pool de constantes
    cp_info *constantPool = (cp_info *)malloc(sizeof(cp_info) * (count - 1));
    cp_info *cp;

    // Itera sobre cada elemento da pool de constantes
    for (cp = constantPool; cp < constantPool + count - 1; cp++)
    {
        // Lê o tipo de tag do elemento
        cp->tag = u1Read(file);

        // Preenche a estrutura com base na tag
        switch (cp->tag)
        {
        case CONSTANT_Class:
            cp->info.Class.name_index = u2Read(file);
            break;
        case CONSTANT_Fieldref:
            cp->info.Fieldref.class_index = u2Read(file);
            cp->info.Fieldref.name_and_type_index = u2Read(file);
            break;
        case CONSTANT_Methodref:
            cp->info.Methodref.class_index = u2Read(file);
            cp->info.Methodref.name_and_type_index = u2Read(file);
            break;
        case CONSTANT_InterfaceMethodref:
            cp->info.InterfaceMethodref.class_index = u2Read(file);
            cp->info.InterfaceMethodref.name_and_type_index = u2Read(file);
            break;
        case CONSTANT_String:
            cp->info.String.string_index = u2Read(file);
            break;
        case CONSTANT_Integer:
            cp->info.Integer.bytes = u4Read(file);
            break;
        case CONSTANT_Float:
            cp->info.Float.bytes = u4Read(file);
            break;
        case CONSTANT_Long:
            cp->info.Long.high_bytes = u4Read(file);
            cp->info.Long.low_bytes = u4Read(file);
            cp++;
            break;
        case CONSTANT_Double:
            cp->info.Double.high_bytes = u4Read(file);
            cp->info.Double.low_bytes = u4Read(file);
            cp++;
            break;
        case CONSTANT_NameAndType:
            cp->info.NameAndType.name_index = u2Read(file);
            cp->info.NameAndType.descriptor_index = u2Read(file);
            break;
        case CONSTANT_Utf8:
            cp->info.Utf8.length = u2Read(file);
            cp->info.Utf8.bytes = (u1 *)malloc(sizeof(u1) * (cp->info.Utf8.length + 1)); // Aloca 1 byte a mais para o '\0'.
            u1 *curr_byte;
            for (curr_byte = cp->info.Utf8.bytes; curr_byte < cp->info.Utf8.bytes + cp->info.Utf8.length; curr_byte++)
            {
                *curr_byte = u1Read(file);
            }
            *curr_byte = '\0'; // Termina a string UTF-8 com '\0'
            break;
        default:
            break;
        }
    }
    return constantPool;
}


cp_info *get_from_cp(cp_info *constantPool, u2 count, u2 index)
{
    // retorna cp_info do pool de constantes de acordo com o index;
    index--;
    if (index > count || index < 0)
    {
        printf("Erro: index da constante pool maior que quantidade de elementos.\n Quantidade de elementos:  %d\n Index: %d\n", count, index);
        exit(1);
    }
    return constantPool + index;
}
