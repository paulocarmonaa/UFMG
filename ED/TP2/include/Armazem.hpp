#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "Pilha.hpp"
#include "Pacote.hpp"
#include "Escalonador.hpp" 
#include "ListaEncadeada.hpp" 

// Representa um armazém no sistema logístico.
// Cada armazém contém múltiplas seções, uma para cada possível destino conectado.
// Cada seção opera como uma Pilha (LIFO).[1]
class Armazem {
    private:

        int idArmazem;
        int numSecoes;
        Pilha<Pacote*>* secoes; // Array de pilhas, uma para cada seção do armazém

    public:
     // Construtor: Aloca o armazém com um ID e número de seções definidos
    Armazem();
    Armazem(int idArmazem, int numSecoes);

    ~Armazem();

    void armazenaPacote(int idSecao, Pacote* pacote);

    Pacote* retiraPacote(int idSecao);

    bool secaoEstaVazia(int idSecao) const;
    
};

#endif // ARMAZEM_HPP