#include "minHeap.hpp"
#include <stdexcept> // Necessário para std::runtime_error

// --- Implementação do Construtor ---
template <typename T>
MinHeap<T>::MinHeap() : capacidade(10), tamanho(0) {
    array = new T[capacidade];
}

// --- Implementação do Destrutor ---
template <typename T>
MinHeap<T>::~MinHeap() {
    delete[] array;
}

// --- Implementação dos Métodos Públicos ---
template <typename T>
void MinHeap<T>::inserir(T item) {
    if (tamanho == capacidade) {
        redimensionar();
    }
    array[tamanho] = item;
    tamanho++;
    heapifyUp(tamanho - 1);
}

template <typename T>
T MinHeap<T>::removerMin() {
    if (estaVazio()) {
        throw std::runtime_error("Erro: Heap vazio ao tentar remover o minimo.");
    }
    T itemMinimo = array[0];
    array[0] = array[tamanho - 1];
    tamanho--;
    heapifyDown(0);
    return itemMinimo;
}

template <typename T>
bool MinHeap<T>::estaVazio() const {
    return tamanho == 0;
}

// --- Implementação dos Métodos Auxiliares ---
template <typename T>
int MinHeap<T>::getPai(int index) {
    return (index - 1) / 2;
}

template <typename T>
int MinHeap<T>::getFilhoEsquerda(int index) {
    return 2 * index + 1;
}

template <typename T>
int MinHeap<T>::getFilhoDireita(int index) {
    return 2 * index + 2;
}

template <typename T>
void MinHeap<T>::trocar(int i, int j) {
    T temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

template <typename T>
void MinHeap<T>::heapifyUp(int index) {
    // Compara os objetos (*ponteiro) para ordenar pela prioridade do evento,
    // e não pelo endereço de memória do ponteiro.
    while (index > 0 && *array[index] < *array[getPai(index)]) {
        trocar(index, getPai(index));
        index = getPai(index);
    }
}

template <typename T>
void MinHeap<T>::heapifyDown(int index) {
    int menorIndex;
    while (true) {
        menorIndex = index;
        int esq = getFilhoEsquerda(index);
        int dir = getFilhoDireita(index);

        // Compara os objetos (*ponteiro) para encontrar o menor.
        if (esq < tamanho && *array[esq] < *array[menorIndex]) {
            menorIndex = esq;
        }
        if (dir < tamanho && *array[dir] < *array[menorIndex]) {
            menorIndex = dir;
        }

        if (index == menorIndex) {
            break; // A propriedade do heap foi restaurada.
        }
        trocar(index, menorIndex);
        index = menorIndex;
    }
}

template <typename T>
void MinHeap<T>::redimensionar() {
    capacidade *= 2;
    T* novoArray = new T[capacidade];
    for (int i = 0; i < tamanho; ++i) {
        novoArray[i] = array[i];
    }
    delete[] array;
    array = novoArray;
}

// --- Instanciação Explícita ---
// Esta linha é OBRIGATÓRIA para que o linker encontre a implementação
// de MinHeap para o tipo Evento*. Sem ela, você terá um erro de
// "undefined reference" ao compilar o projeto com arquivos separados.
template class MinHeap<Evento*>;
