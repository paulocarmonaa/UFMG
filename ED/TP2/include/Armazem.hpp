#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "Pilha.hpp"
#include "Pacote.hpp"
#include "Escalonador.hpp" 
#include "ListaEncadeada.hpp" 

struct Secao{
    int conexaoArmazem; // ID do armazém conectado
    Pilha <Pacote*> pacotes; // Pilha de pacotes nesta seção

    Secao() : conexaoArmazem(-1) {} // Construtor padrão, sem conexão definida
    Secao(int conexaoArmazem) : conexaoArmazem(conexaoArmazem) {} // Construtor para inicializar a seção com o ID do armazém conectado
};

class Armazem {
    private:

        int idArmazem;
        int numSecoes;
        Secao* secoes; // Array de seções, uma para cada seção do armazém

    public:
     // Construtor: Aloca o armazém com um ID e número de seções definidos
    Armazem();
    Armazem(int idArmazem, int numSecoes);
    ~Armazem();

    void armazenaPacote(int idSecao, Pacote* pacote);

    Pacote* retiraPacote(int idSecao);

    bool secaoEstaVazia(int idSecao) const;

    int getnumSecoes() const;
    Secao getSecao(int idSecao) const;
    int getIdArmazem() const;
    
};
#endif // ARMAZEM_HPP