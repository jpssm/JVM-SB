
#include <class_loader/class_file.h>
#include <class_loader/bytes.h>
#include <class_loader/field.h>
#include <leitor_exibidor/leitor_exibidor.h>

void showClass(ClassFile *cf)
{
    fflush(stdin);

    char in;
    while (1)
    {
        CLEAR
        print_general_information(cf);
        printf("\n\n1) Pool de Constantes\n2) Interfaces\n3) Fields\n4) Metodos\n5) Atributos\n6) sair\n\nSelecione uma opcao: ");
        scanf(" %c", &in);

        CLEAR
        switch (in)
        {
        case '1':
            print_constant_pool(cf);
            break;
        case '2':
            print_interfaces(cf);
            break;
        case '3':
            print_fields(cf);
            break;
        case '4':
            print_methods(cf);
            break;
        case '5':
            printf("\n--- ATTRIBUTES ---\n");
            printf("\n%i Entradas\n", cf->attributes_count);
            break;
        case '6':
            fflush(stdin);
            goto fim;
            break;
        default:
            fflush(stdin);
            printf("Opcao Invalida!\n");
            getch();
            continue;
        }
        printf("\n\nPressione qualquer tecla para voltar");
        getch();
    }

    fim:
}

void print_general_information(ClassFile *cf){
    printf("General Information\n\n");
    printf("Minor version:       %i \n", cf->minor_version);
    printf("Major version:       %i\n", cf->major_version);
    printf("Constant pool count: %i\n", cf->constant_pool_count);
    printf("Acess flags:         0x%x\n" , cf->access_flags);
    cp_info *cp_utf8, *cp_class;
    
    cp_class = get_from_cp(cf->constant_pool, cf->constant_pool_count, cf->this_class);
    cp_class->info.Class.name_index;
    cp_utf8 = get_from_cp(cf->constant_pool, cf->constant_pool_count, cp_class->info.Class.name_index);
    printf("This class:          cp_info #%i <%s>\n", cf->this_class, cp_utf8->info.Utf8.bytes);

    cp_class = get_from_cp(cf->constant_pool, cf->constant_pool_count, cf->super_class);
    cp_utf8 = get_from_cp(cf->constant_pool, cf->constant_pool_count, cp_class->info.Class.name_index);
    printf("Super class:         cp_info #%i <%s>\n" , cf->super_class, cp_utf8->info.Utf8.bytes);

    printf("Interface count:     %i\n" , cf->interfaces_count);
    printf("Fileds count:        %i\n" , cf->fields_count);
    printf("Methods count:       %i\n" , cf->methods_count);
    printf("Attributes count:    %i\n" , cf->attributes_count);

}

void print_fields(ClassFile *cf)
{
    cp_info *constantPool = cf->constant_pool ;  
    u2 cp_count = cf->constant_pool_count; 
    field_info *fields = cf->fields; 
    u2 fields_count = cf->fields_count;

    field_info *curr_field; // curr_field in loop
    cp_info *cp_utf8;       // constant pool to print
    int i = 0;

    printf("\n--- FIELDS ---\n");
    printf("\n%i Entradas\n", cf->fields_count);
    for (curr_field = fields; curr_field < fields + fields_count; curr_field++, i++)
    {

        cp_utf8 = get_from_cp(constantPool, cp_count, curr_field->name_index);
        printf("\n\n[%d] %s\n", i, cp_utf8->info.Utf8.bytes);
        printf("Name:         cp_info_#%d   <%s>\n", curr_field->name_index, cp_utf8->info.Utf8.bytes);
        cp_utf8 = get_from_cp(constantPool, cp_count, curr_field->descriptor_index);
        printf("Descriptor:   cp_info_#%d   <%s>\n", curr_field->descriptor_index, cp_utf8->info.Utf8.bytes);
        printf("Access flags: 0x000%X\b", curr_field->access_flags);
    }
}

void print_interfaces(ClassFile *cf)
{
    cp_info *constantPool = cf->constant_pool ;  
    u2 cp_count = cf->constant_pool_count; 
    field_info *fields = cf->fields; 
    u2 fields_count = cf->fields_count;
    u2 *interfaces = cf->interfaces;
    u2 interface_count = cf->interfaces_count;

    printf("\n--- INTERFACES ---\n");
    printf("\n%i Entradas\n\n", cf->interfaces_count);
    u2 *curr_interface;          // curr_field in loop
    cp_info *cp_utf8, *cp_class; // constant pool to print
    int i = 0;
    for (curr_interface = interfaces; curr_interface < interfaces + interface_count; curr_interface++, i++)
    {

        printf("Interface %d\n", i);
        cp_class = get_from_cp(constantPool, cp_count, *curr_interface);
        cp_utf8 = get_from_cp(constantPool, cp_count, cp_class->info.Class.name_index);

        printf("Interface: cp_info_#%d   <%s>\n", *curr_interface, cp_utf8->info.Utf8.bytes);
    }
}

void print_constant_pool(ClassFile *cf)
{
    cp_info *constantPool = cf->constant_pool ;  
    u2 count = cf->constant_pool_count; 

    cp_info *cp, *cp_class, *cp_utf8, *cp_name_and_type;
    long long l;

    int i = 1;
    printf("\n--- CONSTANT POOL ---\n");
    printf("\n%i Entradas\n\n", cf->constant_pool_count);

    for (cp = constantPool; (cp < constantPool + count - 1); cp++, i++)
    {
        printf("\n[%d] ", i);
        switch (cp->tag)
        {
        case CONSTANT_Class:
            printf(" CONSTANT_Class_info\n");
            cp_utf8 = get_from_cp(constantPool, count, cp->info.Class.name_index);
            printf("Class Name:    cp_info_#%d       <%s>\n", cp->info.Class.name_index, cp_utf8->info.Utf8.bytes);
            break;
        case CONSTANT_Fieldref:
            printf(" CONSTANT_Fieldref_info\n");
            cp_class = get_from_cp(constantPool, count, cp->info.Fieldref.class_index);
            cp_utf8 = get_from_cp(constantPool, count, cp_class->info.Class.name_index);
            printf("Class Name:    cp_info_#%d       <%s>\n", cp->info.Fieldref.class_index, cp_utf8->info.Utf8.bytes);
            cp_name_and_type = get_from_cp(constantPool, count, cp->info.Fieldref.name_and_type_index);
            cp_utf8 = get_from_cp(constantPool, count, cp_name_and_type->info.NameAndType.name_index);
            printf("Name and Type: cp_info_#%d       <%s", cp->info.Fieldref.name_and_type_index, cp_utf8->info.Utf8.bytes);
            cp_utf8 = get_from_cp(constantPool, count, cp_name_and_type->info.NameAndType.descriptor_index);
            printf("%s> \n", cp_utf8->info.Utf8.bytes);
            break;
        case CONSTANT_Methodref:
            printf("CONSTANT_Methodref_info\n");
            cp_class = get_from_cp(constantPool, count, cp->info.Methodref.class_index);
            cp_utf8 = get_from_cp(constantPool, count, cp_class->info.Class.name_index);
            printf("Class Name:    cp_info_#%d       <%s>\n", cp->info.Methodref.class_index, cp_utf8->info.Utf8.bytes);
            cp_name_and_type = get_from_cp(constantPool, count, cp->info.Methodref.name_and_type_index);
            cp_utf8 = get_from_cp(constantPool, count, cp_name_and_type->info.NameAndType.name_index);
            printf("Name and Type: cp_info_#%d       <%s ", cp->info.Methodref.name_and_type_index, cp_utf8->info.Utf8.bytes);
            cp_utf8 = get_from_cp(constantPool, count, cp_name_and_type->info.NameAndType.descriptor_index);
            printf("%s> \n", cp_utf8->info.Utf8.bytes);

            break;
        case CONSTANT_InterfaceMethodref:
            printf(" CONSTANT_InterfaceMethodref_info\n");
            cp_class = get_from_cp(constantPool, count, cp->info.InterfaceMethodref.class_index);
            cp_utf8 = get_from_cp(constantPool, count, cp_class->info.Class.name_index);
            printf("Class Name:    cp_info_#%d       <%s>\n", cp->info.InterfaceMethodref.class_index, cp_utf8->info.Utf8.bytes);
            cp_name_and_type = get_from_cp(constantPool, count, cp->info.InterfaceMethodref.name_and_type_index);
            cp_utf8 = get_from_cp(constantPool, count, cp_name_and_type->info.NameAndType.name_index);
            printf("Name and Type: cp_info_#%d       <%s ", cp->info.InterfaceMethodref.name_and_type_index, cp_utf8->info.Utf8.bytes);
            cp_utf8 = get_from_cp(constantPool, count, cp_name_and_type->info.NameAndType.descriptor_index);
            printf("%s> \n", cp_utf8->info.Utf8.bytes);
            break;
        case CONSTANT_String:
            printf(" CONSTANT_String_info\n");
            printf("String Index:  #%d\n", cp->info.String.string_index);
            break;
        case CONSTANT_Integer:
            printf(" CONSTANT_Integer_info\n");
            printf("Bytes:   0x%x\n", cp->info.Integer.bytes);
            printf("Integer: %d\n", cp->info.Integer.bytes);
            break;
        case CONSTANT_Float:
            printf(" CONSTANT_Float_info\n");
            printf("Bytes: 0x%x\n", cp->info.Float.bytes);
            union{
                float flt;
                int i;
                } f; //Avoid conversion error
            f.i = cp->info.Float.bytes;
            printf("Float: %f\n", f.flt);
            break;
        case CONSTANT_Long:
            l = cp->info.Long.high_bytes;
            l<<= 32;
            l+= cp->info.Long.low_bytes;
            printf(" CONSTANT_Long_info\n");
            printf("Hight bytes: 0x%x\n", cp->info.Long.high_bytes);
            printf("Low bytes:   0x%x\n", cp->info.Long.low_bytes);
            printf("Long:        %lli\n", l);
            i++; cp++;
            printf("\n[%d] (large numeric continued)\n", i);
            break;
        case CONSTANT_Double:
            l = cp->info.Double.high_bytes;
            l<<= 32;
            l+= cp->info.Double.low_bytes;
            printf(" CONSTANT_Long_info\n");
            printf("Hight bytes: 0x%x\n", cp->info.Double.high_bytes);
            printf("Low bytes:   0x%x\n", cp->info.Double.low_bytes);
            printf("Double:      %lf\n", l);
            i++; cp++;
            printf("\n[%d] (large numeric continued)\n", i);
            break;
        case CONSTANT_NameAndType:
            printf("CONSTANT_NameAndType_info\n");
            cp_utf8 = get_from_cp(constantPool, count, cp->info.NameAndType.name_index);
            printf("Name:          cp_info_#%d       <%s>\n", cp->info.NameAndType.name_index, cp_utf8->info.Utf8.bytes);
            cp_utf8 = get_from_cp(constantPool, count, cp->info.NameAndType.descriptor_index);
            printf("Descriptor:    cp_info_#%d       <%s>\n", cp->info.NameAndType.descriptor_index, cp_utf8->info.Utf8.bytes);

            break;
        case CONSTANT_Utf8:
            printf(" CONSTANT_Utf8_info\n");
            printf("Length of byte array:  %d\n", cp->info.Utf8.length);
            printf("Lenght of String:      %d\n", cp->info.Utf8.length);
            printf("String:                \"%s\"\n", cp->info.Utf8.bytes);
            break;
        }
    }
}

void print_methods(ClassFile *cf)
{
    cp_info *constantPool = cf->constant_pool ;  
    u2 cp_count = cf->constant_pool_count; 
    method_info *methods = cf->methods;
    u2 methods_count = cf->methods_count;
    method_info *method; // method in loop
    cp_info *cp_utf8;    // constant pool to print
    int i = 0;

    printf("\n--- METHODS ---\n");
    printf("\n%i Entradas\n\n", cf->methods_count);
    for (method = methods; method < methods + methods_count; method++, i++)
    {   
        cp_utf8 = get_from_cp(constantPool, cp_count, method->name_index);
        printf("\n\n\n[%d] %s\n", i, cp_utf8->info.Utf8.bytes);
        printf("Name:   cp_info_#%d   <%s>\n", method->name_index, cp_utf8->info.Utf8.bytes);
        cp_utf8 = get_from_cp(constantPool, cp_count, method->descriptor_index);
        printf("Descriptor:   cp_info_#%d   <%s>\n", method->descriptor_index, cp_utf8->info.Utf8.bytes);
        printf("Access flags: 0x000%X\n", method->access_flags);
        printf("Name index = %d\n", method->name_index);
        printf("Attributes count = %d\n", method->attributes_count);
        if (method->attributes_count> 0){
            printf("\nCode attributes:\n");
            printf("Attribute name index = %u\n", method->code_attribute->attribute_name_index);
            printf("Attribute lenght = %u\n", method->code_attribute->attribute_length);
            printf("Max stack = %u\n", method->code_attribute->max_stack); //u2 max_stack
            printf("Max locals =  %u\n",  method->code_attribute->max_locals); //u2 max_locals
            printf("Code lenght = %u\n", method->code_attribute->code_length);  
            printf("Exeption table lenght = %u\n", method->code_attribute->exception_table_length);  
            print_bytecode(method->code_attribute->code, method->code_attribute->code_length);
        }
    }
}

void print_bytecode(u1* code, u4 code_length) {
    printf("\nBytecode:\n\n");
    for (int i = 0; i < code_length; i++){
        printf("%d ", i);
        switch((u1)code[i]) {
            case (u1) 0x00: printf("nop\n"); break;
            case (u1) 0x01: printf("aconst_null\n"); break;
            case (u1) 0x02: printf("iconst_m1\n"); break;
            case (u1) 0x03: printf("iconst_0\n"); break;
            case (u1) 0x04: printf("iconst_1\n"); break;
            case (u1) 0x05: printf("iconst_2\n"); break;
            case (u1) 0x06: printf("iconst_3\n"); break;
            case (u1) 0x07: printf("iconst_4\n"); break;
            case (u1) 0x08: printf("iconst_5\n"); break;
            case (u1) 0x09: printf("lconst_0\n"); break;
            case (u1) 0x0a: printf("lconst_1\n"); break;
            case (u1) 0x0b: printf("fconst_0\n"); break;
            case (u1) 0x0c: printf("fconst_1\n"); break;
            case (u1) 0x0d: printf("fconst_2\n"); break;
            case (u1) 0x0e: printf("dconst_0\n"); break;
            case (u1) 0x0f: printf("dconst_1\n"); break;
            case (u1) 0x10: printf("bipush %d\n", (int8_t) code[i+1]); i++; break;
            case (u1) 0x11: printf("sipush %d\n", (int16_t) (code[i+1]<<8 | code[i+2])); i+=2; break;
            case (u1) 0x12: printf("ldc %d\n", code[i+1]); i++;  break;
            case (u1) 0x13: printf("ldc_w %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0x14: printf("ldc2_w %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0x15: printf("iload %d\n", code[i+1]); i++;  break;
            case (u1) 0x16: printf("lload %d\n", code[i+1]); i++;  break;
            case (u1) 0x17: printf("fload %d\n", code[i+1]); i++;  break;
            case (u1) 0x18: printf("dload %d\n", code[i+1]); i++;  break;
            case (u1) 0x19: printf("aload %d\n", code[i+1]); i++;  break;
            case (u1) 0x1a: printf("iload_0\n"); break;
            case (u1) 0x1b: printf("iload_1\n"); break;
            case (u1) 0x1c: printf("iload_2\n"); break;
            case (u1) 0x1d: printf("iload_3\n"); break;
            case (u1) 0x1e: printf("lload_0\n"); break;
            case (u1) 0x1f: printf("lload_1\n"); break;
            case (u1) 0x20: printf("lload_2\n"); break;
            case (u1) 0x21: printf("lload_3\n"); break;
            case (u1) 0x22: printf("fload_0\n"); break;
            case (u1) 0x23: printf("fload_1\n"); break;
            case (u1) 0x24: printf("fload_2\n"); break;
            case (u1) 0x25: printf("fload_3\n"); break;
            case (u1) 0x26: printf("dload_0\n"); break;
            case (u1) 0x27: printf("dload_1\n"); break;
            case (u1) 0x28: printf("dload_2\n"); break;
            case (u1) 0x29: printf("dload_3\n"); break;
            case (u1) 0x2a: printf("aload_0\n"); break;
            case (u1) 0x2b: printf("aload_1\n"); break;
            case (u1) 0x2c: printf("aload_2\n"); break;
            case (u1) 0x2d: printf("aload_3\n"); break;
            case (u1) 0x2e: printf("iaload\n"); break;
            case (u1) 0x2f: printf("laload\n"); break;
            case (u1) 0x30: printf("faload\n"); break;
            case (u1) 0x31: printf("daload\n"); break;
            case (u1) 0x32: printf("aaload\n"); break;
            case (u1) 0x33: printf("baload\n"); break;
            case (u1) 0x34: printf("caload\n"); break;
            case (u1) 0x35: printf("saload\n"); break;
            case (u1) 0x36: printf("istore %d\n", code[i+1]); i++;  break;
            case (u1) 0x37: printf("lstore %d\n", code[i+1]); i++;  break;
            case (u1) 0x38: printf("fstore %d\n", code[i+1]); i++;  break;
            case (u1) 0x39: printf("dstore %d\n", code[i+1]); i++;  break;
            case (u1) 0x3a: printf("astore %d\n", code[i+1]); i++;  break;
            case (u1) 0x3b: printf("istore_0\n"); break;
            case (u1) 0x3c: printf("istore_1\n"); break;
            case (u1) 0x3d: printf("istore_2\n"); break;
            case (u1) 0x3e: printf("istore_3\n"); break;
            case (u1) 0x3f: printf("lstore_0\n"); break;
            case (u1) 0x40: printf("lstore_1\n"); break;
            case (u1) 0x41: printf("lstore_2\n"); break;
            case (u1) 0x42: printf("lstore_3\n"); break;
            case (u1) 0x43: printf("fstore_0\n"); break;
            case (u1) 0x44: printf("fstore_1\n"); break;
            case (u1) 0x45: printf("fstore_2\n"); break;
            case (u1) 0x46: printf("fstore_3\n"); break;
            case (u1) 0x47: printf("dstore_0\n"); break;
            case (u1) 0x48: printf("dstore_1\n"); break;
            case (u1) 0x49: printf("dstore_2\n"); break;
            case (u1) 0x4a: printf("dstore_3\n"); break;
            case (u1) 0x4b: printf("astore_0\n"); break;
            case (u1) 0x4c: printf("astore_1\n"); break;
            case (u1) 0x4d: printf("astore_2\n"); break;
            case (u1) 0x4e: printf("astore_3\n"); break;
            case (u1) 0x4f: printf("iastore\n"); break;
            case (u1) 0x50: printf("lastore\n"); break;
            case (u1) 0x51: printf("fastore\n"); break;
            case (u1) 0x52: printf("dastore\n"); break;
            case (u1) 0x53: printf("aastore\n"); break;
            case (u1) 0x54: printf("bastore\n"); break;
            case (u1) 0x55: printf("castore\n"); break;
            case (u1) 0x56: printf("sastore\n"); break;
            case (u1) 0x57: printf("pop\n"); break;
            case (u1) 0x58: printf("pop2\n"); break;
            case (u1) 0x59: printf("dup\n"); break;
            case (u1) 0x5a: printf("dup_x1\n"); break;
            case (u1) 0x5b: printf("dup_x2\n"); break;
            case (u1) 0x5c: printf("dup2\n"); break;
            case (u1) 0x5d: printf("dup2_x1\n"); break;
            case (u1) 0x5e: printf("dup2_x2\n"); break;
            case (u1) 0x5f: printf("swap\n"); break;
            case (u1) 0x60: printf("iadd\n"); break;
            case (u1) 0x61: printf("ladd\n"); break;
            case (u1) 0x62: printf("fadd\n"); break;
            case (u1) 0x63: printf("dadd\n"); break;
            case (u1) 0x64: printf("isub\n"); break;
            case (u1) 0x65: printf("lsub\n"); break;
            case (u1) 0x66: printf("fsub\n"); break;
            case (u1) 0x67: printf("dsub\n"); break;
            case (u1) 0x68: printf("imul\n"); break;
            case (u1) 0x69: printf("lmul\n"); break;
            case (u1) 0x6a: printf("fmul\n"); break;
            case (u1) 0x6b: printf("dmul\n"); break;
            case (u1) 0x6c: printf("idiv\n"); break;
            case (u1) 0x6d: printf("ldiv\n"); break;
            case (u1) 0x6e: printf("fdiv\n"); break;
            case (u1) 0x6f: printf("ddiv\n"); break;
            case (u1) 0x70: printf("irem\n"); break;
            case (u1) 0x71: printf("lrem\n"); break;
            case (u1) 0x72: printf("frem\n"); break;
            case (u1) 0x73: printf("drem\n"); break;
            case (u1) 0x74: printf("ineg\n"); break;
            case (u1) 0x75: printf("lneg\n"); break;
            case (u1) 0x76: printf("fneg\n"); break;
            case (u1) 0x77: printf("dneg\n"); break;
            case (u1) 0x78: printf("ishl\n"); break;
            case (u1) 0x79: printf("lshl\n"); break;
            case (u1) 0x7a: printf("ishr\n"); break;
            case (u1) 0x7b: printf("lshr\n"); break;
            case (u1) 0x7c: printf("iushr\n"); break;
            case (u1) 0x7d: printf("lushr\n"); break;
            case (u1) 0x7e: printf("iand\n"); break;
            case (u1) 0x7f: printf("land\n"); break;
            case (u1) 0x80: printf("ior\n"); break;
            case (u1) 0x81: printf("lor\n"); break;
            case (u1) 0x82: printf("ixor\n"); break;
            case (u1) 0x83: printf("lxor\n"); break;
            case (u1) 0x84: printf("iinc %d by %d\n", code[i+1], code[i+2]); i+=2; break;
            case (u1) 0x85: printf("i2l\n"); break;
            case (u1) 0x86: printf("i2f\n"); break;
            case (u1) 0x87: printf("i2d\n"); break;
            case (u1) 0x88: printf("l2i\n"); break;
            case (u1) 0x89: printf("l2f\n"); break;
            case (u1) 0x8a: printf("l2d\n"); break;
            case (u1) 0x8b: printf("f2i\n"); break;
            case (u1) 0x8c: printf("f2l\n"); break;
            case (u1) 0x8d: printf("f2d\n"); break;
            case (u1) 0x8e: printf("d2i\n"); break;
            case (u1) 0x8f: printf("d2l\n"); break;
            case (u1) 0x90: printf("d2f\n"); break;
            case (u1) 0x91: printf("i2b\n"); break;
            case (u1) 0x92: printf("i2c\n"); break;
            case (u1) 0x93: printf("i2s\n"); break;
            case (u1) 0x94: printf("lcmp\n"); break;
            case (u1) 0x95: printf("fcmpl\n"); break;
            case (u1) 0x96: printf("fcmpg\n"); break;
            case (u1) 0x97: printf("dcmpl\n"); break;
            case (u1) 0x98: printf("dcmpg\n"); break;
            case (u1) 0x99: printf("ifeq %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0x9a: printf("ifne %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0x9b: printf("iflt %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0x9c: printf("ifge %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0x9d: printf("ifgt %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0x9e: printf("ifle %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0x9f: printf("if_icmpeq %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xa0: printf("if_icmpne %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xa1: printf("if_icmplt %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xa2: printf("if_icmpge %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xa3: printf("if_icmpgt %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xa4: printf("if_icmple %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xa5: printf("if_acmpeq %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xa6: printf("if_acmpne %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xa7: printf("goto %d\n", (int16_t)(code[i+1]<<8 | code[i+2]));  i+=2; break;
            case (u1) 0xa8: printf("jsr %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xa9: printf("ret %d\n", code[i+1]); i++;  break;
            case (u1) 0xaa: printf("tableswitch\n"); break;
            case (u1) 0xab: printf("lookupswitch\n"); break;
            case (u1) 0xac: printf("ireturn\n"); break;
            case (u1) 0xad: printf("lreturn\n"); break;
            case (u1) 0xae: printf("freturn\n"); break;
            case (u1) 0xaf: printf("dreturn\n"); break;
            case (u1) 0xb0: printf("areturn\n"); break;
            case (u1) 0xb1: printf("return\n"); break;
            case (u1) 0xb2: printf("getstatic %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xb3: printf("putstatic %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xb4: printf("getfield %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xb5: printf("putfield %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xb6: printf("invokevirtual %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xb7: printf("invokespecial %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xb8: printf("invokestatic %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xb9: printf("invokeinterface %d %d %d\n", code[i+1]<<8 | code[i+2], code[i+3], code[i+4]); i+=4; break;
            case (u1) 0xba: printf("invokedynamic %d %d %d\n", code[i+1]<<8 | code[i+2], code[i+3], code[i+4]); i+=4; break;
            case (u1) 0xbb: printf("new %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xbc: printf("newarray %d\n", code[i+1]); i++;  break;
            case (u1) 0xbd: printf("anewarray %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xbe: printf("arraylength\n"); break;
            case (u1) 0xbf: printf("athrow\n"); break;
            case (u1) 0xc0: printf("checkcast %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xc1: printf("instanceof %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xc2: printf("monitorenter\n"); break;
            case (u1) 0xc3: printf("monitorexit\n"); break;
            case (u1) 0xc4: printf("wide\n"); break;
            case (u1) 0xc5: printf("multianewarray %d %d\n", code[i+1]<<8 | code[i+2], code[i+3]); i+=3; break;
            case (u1) 0xc6: printf("ifnull %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xc7: printf("ifnonnull %d\n", code[i+1]<<8 | code[i+2]); i+=2; break;
            case (u1) 0xc8: printf("goto_w %d\n", (int32_t)(code[i+1] << 24 | code[i+2] << 16 | code[i+3] << 8 | code[i+4])); i+=4; break;
            case (u1) 0xc9: printf("jsr_w %d\n", (code[i+1] << 24 | code[i+2] << 16 | code[i+3] << 8 | code[i+4])); i+=4; break;
            default: printf("unknown: %u\n", code[i]); break;
        }
    }
}
