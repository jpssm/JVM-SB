package banco;

import java.util.Scanner;

public class Banco {

    static private ContaBancaria procurarConta(long cpf, int tipo,  ContaBancaria[] Contas) {
        ContaBancaria contaCliente = null;
        for (ContaBancaria conta : Contas) {
            if (conta != null && conta.getTitular().getCpf() == cpf) {
                if ((conta instanceof ContaCorrente && tipo == 1) ||
                    (conta instanceof ContaPoupanca && tipo == 2) ||
                    (conta instanceof ContaSalario && tipo == 3)) {
                    contaCliente = conta;
                    break;
                }
            }
        }
        return contaCliente;
    }

    public static void main(String[] args) {
        ContaBancaria[] Contas = new ContaBancaria[100];
        int numContas = 0; // Adicionado para controlar o número de contas criadas
        Scanner scanner = new Scanner(System.in);
        String inStr1;
        String inStr2;
        long inInt;
        ContaBancaria conta = null;
        ContaCorrente contaCorrente;
        ContaPoupanca contaPoupanca;
        ContaSalario contaSalario;
        Pessoa usuario = null;
        long cpf;
        int senha;
        int tipoConta = -1;

        while (true) {

            tipoConta = -1; // Reset tipoConta for each iteration
            while (tipoConta > 3 || tipoConta < 1) {
                System.out.print("Seleciona o tipo de conta\n\nCorrente(1) Poupanca(2) Salario(3): ");
                try {
                    inInt = scanner.nextInt();
                } catch (Exception e) {
                    System.out.print("Opcao Invalida!\n\n");
                    scanner.next();  
                    continue;
                }
                if (inInt > 3 || inInt < 1) {
                    System.out.print("Opcao Invalida!\n\n");
                } else {
                    tipoConta = (int) inInt;
                }
            }

            while (true) {
                System.out.print("\nEscolha uma opção: Acessar Conta(1) Abrir Conta(2): ");
                inStr1 = scanner.next();
                scanner.nextLine();  // Consume newline

                if (inStr1.equals("1")) {
                    while (usuario == null) {
                      if (inStr1.equals("1")) {
                        while (usuario == null) {
                            System.out.print("CPF(Somente digitos) ou digite 'cancelar' para sair: ");
                            inStr1 = scanner.nextLine();
                            if (inStr1.equalsIgnoreCase("cancelar")) {
                                System.out.print("\nOperação cancelada. Retornando ao menu principal...");
                                continue;
                            }

                        System.out.print("Senha: ");
                        inStr2 = scanner.nextLine();

                        try {
                            cpf = Long.parseLong(inStr1);
                            senha = Integer.parseInt(inStr2);
                        } catch (Exception e) {
                            System.out.print("\nEscreva somente (Somente digitos) para cpf e senha\n\n");
                            continue;
                        }

                        conta = procurarConta(cpf, tipoConta, Contas);

                        if (conta == null || !conta.verificar(senha)) {
                            System.out.print("Não foi encontrada conta do tipo escolhido para o CPF e senha informados!\n\n");
                        } else {
                            // Acesso à conta foi bem-sucedido
                            usuario = conta.getTitular();
                        }
                    }
                } else if (inStr1.equals("2")) {

                    System.out.println("Insira seus dados pessoais:");

                    System.out.print("Nome Completo: ");
                    String nome = scanner.nextLine();

                    cpf = 0;
                    while (cpf == 0) {
                        try {
                            System.out.print("CPF(Somente digitos): ");
                            cpf = scanner.nextLong();
                            scanner.nextLine();
                        } catch (Exception e) {
                            System.out.print("CPF inválido!\n\n");
                            scanner.next();  
                            cpf = 0;
                        }
                    }

                    System.out.print("Telefone: ");
                    String telefone = scanner.nextLine();

                    System.out.print("Email: ");
                    String email = scanner.nextLine();

                    System.out.println("Insira seu Endereço:");

                    System.out.print("Estado: ");
                    String estado = scanner.nextLine();

                    System.out.print("Municipio: ");
                    String municipio = scanner.nextLine();

                    System.out.print("Rua: ");
                    String rua = scanner.nextLine();

                    int numero = 0;
                    while (numero == 0) {
                        try {
                            System.out.print("Numero: ");
                            numero = scanner.nextInt();
                            scanner.nextLine();
                        } catch (Exception e) {
                            System.out.print("Numero inválido!\n\n");
                            scanner.next();  
                            numero = 0;
                        }
                    }

                    long cep = 0;
                    while (cep == 0) {
                        try {
                            System.out.print("CEP(Somente digitos): ");
                            cep = scanner.nextLong();
                            scanner.nextLine();
                        } catch (Exception e) {
                            System.out.print("CEP inválido!\n\n");
                            scanner.next();  
                            cep = 0;
                        }
                    }

                    Endereco endereco = new Endereco(estado, municipio, rua, numero, cep);
                    Pessoa pessoa = new Pessoa(nome, cpf, telefone, email, endereco);

                    senha = 0;
                    while (senha == 0) {
                        try {
                            System.out.print("Escolha uma senha(somente digitos): ");
                            senha = scanner.nextInt();
                            scanner.nextLine();
                        } catch (Exception e) {
                            System.out.print("Escolha uma senha valida!\n\n");
                            scanner.next();  
                            senha = 0;
                        }
                    }

                    if (tipoConta == 1) {
                        contaCorrente = new ContaCorrente(pessoa, senha);
                        Contas[numContas++] = contaCorrente;
                    } else if (tipoConta == 2) {
                        contaPoupanca = new ContaPoupanca(pessoa, senha);
                        Contas[numContas++] = contaPoupanca;
                    } else if (tipoConta == 3) {
                        contaSalario = new ContaSalario(pessoa, senha);
                        Contas[numContas++] = contaSalario;
                    }
                    conta = Contas[numContas - 1];
                    usuario = pessoa;
                    break;
                } else {
                    System.out.print("Operação Inválida\n\n");
                }
            }

            // Opções de transações especificas para conta
            while (true) {
                System.out.println("\nEscolha uma opção: ");
                System.out.println("1. Ver Saldo");
                System.out.println("2. Depositar");
                System.out.println("3. Sacar");
                System.out.println("4. Transferir");
                System.out.println("5. Atualizar Informações");
                System.out.println("6. Sair");
                System.out.print("Opção: ");
                int opcao = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                switch (opcao) {
                    case 1:
                        System.out.println("Saldo atual: " + conta.getSaldo());
                        break;

                    case 2:
                        System.out.print("Valor para depositar: ");
                        long valorDeposito = scanner.nextLong();
                        conta.depositar(valorDeposito);
                        System.out.println("Depósito realizado com sucesso!");
                        break;

                    case 3:
                        System.out.print("Valor para sacar: ");
                        long valorSaque = scanner.nextLong();
                        System.out.print("Digite sua senha: ");
                        int senhaSaque = scanner.nextInt();
                        double sacado = conta.sacar(valorSaque, senhaSaque);
                        if (sacado > 0) {
                            System.out.println("Saque realizado com sucesso!");
                        } else {
                            System.out.println("Saque falhou! Verifique sua senha ou saldo.");
                        }
                        break;

                    case 4:
                        System.out.print("CPF da conta de destino: ");
                        long cpfDestino = scanner.nextLong();
                        System.out.print("Tipo da conta de destino (1: Corrente, 2: Poupança, 3: Salário): ");
                        int tipoContaDestino = scanner.nextInt();
                        System.out.print("Valor para transferir: ");
                        long valorTransferencia = scanner.nextLong();
                        System.out.print("Digite sua senha: ");
                        int senhaTransferencia = scanner.nextInt();
                        ContaBancaria contaDestino = procurarConta(cpfDestino, tipoContaDestino, Contas);
                        if (contaDestino != null && conta.transferir(contaDestino, valorTransferencia, senhaTransferencia)) {
                            System.out.println("Transferência realizada com sucesso!");
                        } else {
                            System.out.println("Transferência falhou! Verifique os dados e tente novamente.");
                        }
                        break;

                    case 5:
                        System.out.println("Atualizar Informações:");
                        System.out.print("Novo Telefone: ");
                        String novoTelefone = scanner.nextLine();
                        conta.atulizaTelefone(novoTelefone);
                        System.out.print("Novo Email: ");
                        String novoEmail = scanner.nextLine();
                        conta.atulizaEmail(novoEmail);
                        System.out.println("Atualização realizada com sucesso!");
                        break;

                    case 6:
                        System.out.println("Saindo da conta...");
                        usuario = null;
                        conta = null;
                        break;

                    default:
                        System.out.println("Opção inválida!");
                        break;
                }

                if (opcao == 6) {
                    break; // Sair do loop de transações e retornar ao menu principal
                }
            }
        }
    }
}
