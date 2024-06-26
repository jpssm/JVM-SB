# README - JVM


### Integrantes
    Felipe N Rocha - 17/0050084

    Solano Dias Pereira	- 17/0114392

    João Pedro de Sousa Soares Martins - 20/0020692

    Saulo Oliveira de Freitas - 21/1000176


## Documentação

É posssível acessar a documentação e descrição das estruturas e funções do projeto no arquivo index.html dentro da pasta docs/html, onde é encontrada a documentação Doxygen do projeto.

## Requisitos do Sistema

Para compilar e executar o projeto, você precisará dos seguintes componentes instalados no seu sistema:

1. **GCC (GNU Compiler Collection)**
   - Para instalar o GCC no seu sistema:
     - **Ubuntu/Debian**:
       ```sh
       sudo apt update
       sudo apt install build-essential
       ```
     - **Fedora**:
       ```sh
       sudo dnf group install "Development Tools"
       ```
     - **macOS**:
       ```sh
       brew install gcc
       ```
     - **Windows**:
       - Baixe e instale o [MinGW-w64](http://mingw-w64.org/doku.php) ou utilize o [WSL (Windows Subsystem for Linux)](https://docs.microsoft.com/en-us/windows/wsl/install).

2. **Make**
   - Para instalar o Make no seu sistema:
     - **Ubuntu/Debian**:
       ```sh
       sudo apt update
       sudo apt install make
       ```
     - **Fedora**:
       ```sh
       sudo dnf install make
       ```
     - **macOS**:
        ```sh
       brew install make
       ```
    
     - **Windows**:
       - Make geralmente está incluído no pacote do MinGW-w64. Alternativamente, pode-se utilizar o [GnuWin](http://gnuwin32.sourceforge.net/packages/make.htm).


## Compilação do projeto
Para executar o projeto é preciso compilar o programa, utilizando o seguinte comando no diretório raiz:
```
make

```

## Como usar 
Basta chamar o executável junto com o caminho para o arquivo .class que se deseja analizar.

```
    main.exe <caminho-do-arquivo .class>

    ./main <caminho-do-arquivo .class>
```





## Estrutura do projeto

Este projeto está dividido em duas partes:


A primeira visa a implementação de um leitor exibidor capaz de ler uma arquivo ponto class e apresentar as estruturas nele contidas, de forma similar ao visualizador jclasslib (Opção 1 do menu ao exectuar o código). Para isto Foram aplicados os conceitos estudados em sala de aula para desenvolver usa uma estrutura de dados chamada ClassFile para armazenar as informações lidas do arquivo de bytecode.

A segunda é a implementação de uma JVM que irá executar os Bytecode Java gerados pela leitura do ClassFile.



## Diagrama de Comunicação Entre módulos:
