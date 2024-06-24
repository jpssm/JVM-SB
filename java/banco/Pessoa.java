package banco;

public class Pessoa{

    private String nome;
    private long cpf; 
    private String telefone;
    private String email;
    public Endereco endereco;

    public Pessoa(String nome, long cpf, String telefone, String email, Endereco endereco) {
        this.nome = nome;
        this.cpf = cpf;
        this.telefone = telefone;
        this.email = email;
        this.endereco = endereco;
    }

    public boolean equals(Pessoa pessoa2){
        if (pessoa2.getCpf() == this.cpf){
            return true;
        }
        else return false;
    }

    public String getNome() {
        return nome;
    }
    public String getEmail() {
        return email;
    }
    public String getTelefone() {
        return telefone;
    }
    public long getCpf() {
        return cpf;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setTelefone(String telefone) {
        this.telefone = telefone;
    }




    
}