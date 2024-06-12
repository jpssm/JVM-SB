#include "bytes.c"
#include <class_loader/attribute.h>
#include <class_loader/field.h>
#include <class_loader/method.h>
#include <class_loader/constant_pool.h>
#include <class_loader/class_file.h>

/**
 * Cria uma estrutura ClassFile baseada em um arquivo.
 *
 * Esta função aloca memória para uma estrutura ClassFile e preenche seus campos com base nos dados lidos do arquivo.
* @param file Um ponteiro para o arquivo binário a ser lido.
 * @return Um ponteiro para a estrutura ClassFile preenchida.
 */
ClassFile *create_classfile(FILE *file)
{

    // Aloca memória para a estrutura ClassFile
    ClassFile *cf = (ClassFile *)malloc(sizeof(ClassFile));
    
    // Lê o magic number (cafebabe)
    cf->magic = u4Read(file);
    // Lê a versão menor
    cf->minor_version = u2Read(file);
    // Lê a versão maior
    cf->major_version = u2Read(file);
    // Lê o número de elementos da pool de constantes
    cf->constant_pool_count = u2Read(file);
    
    // Criar a pool de constantes (alocacao de memoria)
    cf->constant_pool = create_constant_pool(file, cf->constant_pool_count);

    // Le proximos atributos
    cf->access_flags = u2Read(file);
    cf->this_class = u2Read(file);
    cf->super_class = u2Read(file);
    cf->interfaces_count = u2Read(file);

    // TODO: Interface methods
    if (cf->interfaces_count > 0)
    {
        cf->interfaces = (u2 *)malloc(sizeof(u2) * cf->interfaces_count);
        u2 *curr_interface;
        int i = 1; 
        for (curr_interface = cf->interfaces; curr_interface < cf->interfaces + cf->interfaces_count; curr_interface++, i++)
        {
            *curr_interface = u2Read(file);
        }

    }
    else
    {
        cf->interfaces = NULL;
    }

    // Criar fields
    cf->fields_count = u2Read(file);
    cf->fields = create_fields(file, cf->fields_count);

    // Criar methods
    cf->methods_count = u2Read(file);
    cf->methods = create_methods(file, cf->methods_count, cf->constant_pool);

    cf->attributes_count = u2Read(file);
    
    return cf;
}