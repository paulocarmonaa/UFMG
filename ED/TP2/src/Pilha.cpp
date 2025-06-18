#include "Pilha.hpp"
#include <stdexcept> // Para std::runtime_error

template <typename T>
Pilha<T>::Pilha() {} // Construtor padrão de ListaEncadeada é chamado

template <typename T>
Pilha<T>::~Pilha() {} // Destrutor padrão de ListaEncadeada é chamado, limpando a lista

template <typename T>
void Pilha<T>::empilhar(T valor) {
    // Empilhar é equivalente a inserir no início da lista para LIFO eficiente.
    lista.inserirInicio(valor);
}

template <typename T>
T Pilha<T>::desempilhar() {
    if (estaVazia()) {
        throw std::runtime_error("Erro: Pilha vazia ao tentar desempilhar.");
    }
    // Desempilhar é equivalente a remover do início da lista.
    return lista.removerInicio();
}

template <typename T>
T Pilha<T>::verTopo() const {
    if (estaVazia()) {
        throw std::runtime_error("Erro: Pilha vazia ao tentar ver o topo.");
    }
    // Ver o topo é equivalente a obter o primeiro elemento da lista.
    return lista.obterPrimeiro();
}

template <typename T>
bool Pilha<T>::estaVazia() const {
    return lista.estaVazia();
}

template <typename T>
int Pilha<T>::tamanho() const {
    return lista.tamanho();
}

// Explicit template instantiations
class Pacote; // Forward declaration
template class Pilha<Pacote*>;