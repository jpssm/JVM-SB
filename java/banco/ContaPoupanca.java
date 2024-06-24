package banco;


public class ContaPoupanca extends ContaBancaria{
    static double juros = 0.5;
    int saques_restantes;
    int transferencias_restantes;


    ContaPoupanca(Pessoa titular,int senha){
        super(titular, senha);
        this.saques_restantes = 2;
        this.transferencias_restantes = 4;
    }

    void render(){
        this.saldo *=juros;
    }

    boolean transferir(ContaBancaria conta, long valor, int senha){
        if (saques_restantes > 0){
            return super.transferir(conta, valor, senha);
        }
        else return false;
    }

    double sacar(long valor, int senha){
        if (saques_restantes > 0){
            return super.sacar(valor, senha);
        }
        else return 0;
    }
}
