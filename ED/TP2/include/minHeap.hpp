#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include "Evento.hpp" // Certifique-se de que este arquivo exista e defina a struct Evento

// Classe template para o Min-Heap, que funcionará como uma fila de prioridade.
// O tipo 'T' será 'Evento*' para o escalonador do seu trabalho.
template <typename T>
class MinHeap {
private:
    T* array;
    int capacidade;
    int tamanho;

    // Métodos auxiliares privados para as operações do heap.
    void heapifyUp(int index);
    void heapifyDown(int index);
    void redimensionar();
    int getPai(int index);
    int getFilhoEsquerda(int index);
    int getFilhoDireita(int index);
    void trocar(int i, int j);

public:
    // Construtor e Destrutor.
    MinHeap();
    ~MinHeap();

    // Métodos públicos da interface.
    void inserir(T item);
    T removerMin();
    bool estaVazio() const;
};

#endif // MINHEAP_HPP