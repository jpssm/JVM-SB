package banco;

public class ContaSalario extends ContaBancaria{

    ContaSalario(Pessoa titular,int senha){
        super(titular, senha);
    }

    boolean transferir(ContaBancaria conta, long valor, int senha){
        if (conta.titular.equals(this.titular)){
            return super.transferir(conta, valor, senha);
        }
        else return false;
    }
}
