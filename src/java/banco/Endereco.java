package banco;

public class Endereco {
    public String estado;
    public String municipio;
    public String rua;
    public int numero;
    public long cep;

    Endereco(String estado, String municipio, String rua, int numero, long cep){
        this.estado = estado;
        this.municipio = municipio;
        this.rua = rua;
        this.numero = numero;
        this.cep = cep;
    }
}
