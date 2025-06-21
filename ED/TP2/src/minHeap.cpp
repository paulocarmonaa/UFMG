#include "minHeap.hpp"
#include <stdexcept>

//Método para garantir a propriedade do MinHeap
//Troca um nó pelo seu pai, "subindo-o" na árvore até a condição do filho ser maior que o pai ser atingida
template <typename T>
void MinHeap<T>::heapifyUp(int index) {
    while (index > 0 && *array[index] < *array[getPai(index)]) {
        trocar(index, getPai(index));
        index = getPai(index);
    }
}

//Método para garantir a propriedade do MinHeap
//"Afunda" um elemento na árvore quando o mínimo é retirado para garantir a propriedade do MinHeahp do
// pai ser sempre menor que o filho
template <typename T>
void MinHeap<T>::heapifyDown(int index) {
    int menorIndex;

    while (true) {
        menorIndex = index;
        int esq = getFilhoEsquerda(index);
        int dir = getFilhoDireita(index);

        if (esq < tamanho && *array[esq] < *array[menorIndex]) 
            menorIndex = esq;
        if (dir < tamanho && *array[dir] < *array[menorIndex]) 
            menorIndex = dir;
        if (index == menorIndex) 
            break;

        trocar(index, menorIndex);
        index = menorIndex;
    }
}

//Redimensiona a capacidade do array que armazena o heap quando ele fica cheio
template <typename T>
void MinHeap<T>::redimensionar() {
    capacidade *= 2;
    T* novoArray = new T[capacidade];

    for (int i = 0; i < tamanho; ++i) 
        novoArray[i] = array[i];
    
    delete[] array;
    array = novoArray;
}

//Retorna o pai do nó
template <typename T>
int MinHeap<T>::getPai(int index) {
    return (index - 1) / 2;
}

//Retorna o filho da esquerda do nó
template <typename T>
int MinHeap<T>::getFilhoEsquerda(int index) {
    return 2 * index + 1;
}

//Retorna o filho da direita do nó
template <typename T>
int MinHeap<T>::getFilhoDireita(int index) {
    return 2 * index + 2;
}

//Troca duas posicões do array que armazena o heap
template <typename T>
void MinHeap<T>::trocar(int i, int j) {
    T temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

//Construtor
template <typename T>
MinHeap<T>::MinHeap() : capacidade(10), tamanho(0) {
    array = new T[capacidade];
}

//Destrutor
template <typename T>
MinHeap<T>::~MinHeap() {
    delete[] array;
}

//Insere um item na estrutura do Heap
template <typename T>
void MinHeap<T>::inserir(T item) {
    if (tamanho == capacidade)
        redimensionar();
    
    array[tamanho] = item;
    tamanho++;
    heapifyUp(tamanho - 1);
}

//Remove o elemento mínimo(raiz) do Heap
template <typename T>
T MinHeap<T>::removerMin() {
    if (estaVazio()) 
        throw std::runtime_error("Erro: Heap vazio ao tentar remover o minimo.");
    
    T itemMinimo = array[0];
    array[0] = array[tamanho - 1];
    tamanho--;
    heapifyDown(0);

    return itemMinimo;
}

//Confere se o Heap está vazio
template <typename T>
bool MinHeap<T>::estaVazio() const {
    return tamanho == 0;
}

// Instanciação Explícita
template class MinHeap<Evento*>;
