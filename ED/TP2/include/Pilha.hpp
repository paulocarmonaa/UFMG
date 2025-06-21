#ifndef PILHA_HPP
#define PILHA_HPP

#include "ListaEncadeada.hpp"
#include <stdexcept>

template <typename T>
class Pilha {
private:
    ListaEncadeada<T> lista;

public:
    // Construtor e destrutor
    Pilha();
    ~Pilha();

    // Métodos para empilhar e desempilhar elementos.
    void empilhar(T valor);
    T desempilhar();

    //Metodos de verificação
    T verTopo() const;
    bool estaVazia() const;
    int tamanho() const;
};

//Implementação dos métodos da Pilha

//Construtor
template <typename T>
Pilha<T>::Pilha() {} 

//Destrutor
template <typename T>
Pilha<T>::~Pilha() {} // Destrutor padrão de ListaEncadeada é chamado, limpando a lista

//Método para empilhar o elemento no topo
template <typename T>
void Pilha<T>::empilhar(T valor) { lista.inserirInicio(valor);}

// Método para desempilhar o elemento do topo
template <typename T>
T Pilha<T>::desempilhar() {
    if (estaVazia()) {
        throw std::runtime_error("Erro: Pilha vazia ao tentar desempilhar.");
    }
    return lista.removerInicio();
}

//Método para verificar elemento do topo sem removê-lo
template <typename T>
T Pilha<T>::verTopo() const {
    if (estaVazia()) {
        throw std::runtime_error("Erro: Pilha vazia ao tentar ver o topo.");
    }
    return lista.obterPrimeiro();
}

//Método para verificar se a pilha está vazia
template <typename T>
bool Pilha<T>::estaVazia() const { return lista.estaVazia();}

// Método para obter o tamanho da pilha
template <typename T>
int Pilha<T>::tamanho() const { return lista.getTamanho(); }

#endif