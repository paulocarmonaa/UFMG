#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "Pilha.hpp"
#include "Pacote.hpp"
#include "Escalonador.hpp" 
#include "ListaEncadeada.hpp" 

//Estrutura para armazenar as seções do armazém
struct Secao{
    int conexaoArmazem; 
    Pilha <Pacote*> pacotes; 

    //Construtores
    Secao() : conexaoArmazem(-1) {} 
    Secao(int conexaoArmazem) : conexaoArmazem(conexaoArmazem) {} 
};

class Armazem {
    private:

        int idArmazem;
        int numSecoes;
        Secao* secoes;

    public:

    //Construtores e destrutor
    Armazem();
    Armazem(int idArmazem, int numSecoes,int numArmazens, bool** matrizdeAdjacencia);
    ~Armazem();

    //Getters do Armazém
    int getIdArmazem() const;
    
    // Métodos para gerenciar pacotes
    void armazenaPacote(int idSecao, Pacote* pacote);
    Pacote* retiraPacote(int idSecao);

    //Metodos para gerenciar seções
    int getnumSecoes() const;
    int getSecaoConexao(int idSecao) const;
    Secao& getSecao(int idSecao); 
    bool secaoEstaVazia(int idSecao) const;
    
};
#endif 