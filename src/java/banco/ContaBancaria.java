package banco;

abstract class ContaBancaria{
    protected double saldo = 0;
    protected Pessoa titular;
    private int senha;

    
    public ContaBancaria(Pessoa titular,int senha) {
        this.titular = titular;
        this.senha = senha;
    }
    
    void atulizaEndereco(Endereco novoEndereco){
        this.titular.endereco = novoEndereco;
    }

    void atulizaTelefone(String novoTelefone){
        this.titular.setTelefone(novoTelefone);
    }

    void atulizaEmail(String novoEmail){
        this.titular.setEmail(novoEmail);
    }


    public double getSaldo() {
        return saldo;
    }

    public Pessoa getTitular() {
        return titular;
    }

    public double saldo() {
        return saldo;
    }

    void depositar(long valor){
        this.saldo += valor;
    }
    
    boolean transferir(ContaBancaria conta, long valor, int senha){
        if(valor > 0 && this.senha == senha){
            conta.depositar(valor);
            return true;
        }
        else return false;
    }

    double sacar(long valor, int senha){
        if(valor > 0 && this.senha == senha){
            this.saldo -=valor;
            return valor;
        }
        else return 0;
    }

    boolean verificar(int senha){
        return this.senha == senha;
    }
    
}