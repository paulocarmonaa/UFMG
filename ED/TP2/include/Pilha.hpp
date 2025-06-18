#ifndef PILHA_HPP
#define PILHA_HPP

#include "ListaEncadeada.hpp"

// Implementação de uma Pilha (Stack) genérica, utilizando ListaEncadeada como base.
// Segue a política LIFO (Last-In, First-Out).
// Usada nos Armazens para guardar pacotes nas seções.[1]
template <typename T>
class Pilha {
private:
    ListaEncadeada<T> lista; // A lista encadeada armazena os elementos da pilha.

public:
    Pilha();
    ~Pilha();

    // Empilha um elemento no topo da pilha.
    void empilhar(T valor);

    // Remove e retorna o elemento do topo da pilha.
    // Lança uma exceção se a pilha estiver vazia.
    T desempilhar();

    // Retorna o elemento do topo da pilha sem removê-lo.
    // Lança uma exceção se a pilha estiver vazia.
    T verTopo() const;

    // Verifica se a pilha está vazia.
    bool estaVazia() const;

    // Retorna o número de elementos na pilha.
    int tamanho() const;
};

#endif // PILHA_HPP