// ListaEncadeada.cpp
#include "ListaEncadeada.hpp"
#include "Pacote.hpp"

template <typename T>
ListaEncadeada<T>::ListaEncadeada() : cabeca(nullptr), cauda(nullptr), _tamanho(0) {}

template <typename T>
ListaEncadeada<T>::~ListaEncadeada() {
    limpar();
}

template <typename T>
void ListaEncadeada<T>::inserirInicio(T valor) {
    No<T>* novo = new No<T>(valor);
    novo->proximo = cabeca;
    if (cabeca != nullptr)
        cabeca->anterior = novo;
    cabeca = novo;
    if (cauda == nullptr)
        cauda = novo;
    _tamanho++;
}

template <typename T>
void ListaEncadeada<T>::inserirFim(T valor) {
    No<T>* novo = new No<T>(valor);
    novo->anterior = cauda;
    if (cauda != nullptr)
        cauda->proximo = novo;
    cauda = novo;
    if (cabeca == nullptr)
        cabeca = novo;
    _tamanho++;
}

template <typename T>
T ListaEncadeada<T>::removerInicio() {
    if (estaVazia())
        throw std::runtime_error("Lista vazia");
    No<T>* temp = cabeca;
    T val = temp->valor;
    cabeca = cabeca->proximo;
    if (cabeca != nullptr)
        cabeca->anterior = nullptr;
    else
        cauda = nullptr;
    delete temp;
    _tamanho--;
    return val;
}

template <typename T>
T ListaEncadeada<T>::removerFim() {
    if (estaVazia())
        throw std::runtime_error("Lista vazia");
    No<T>* temp = cauda;
    T val = temp->valor;
    cauda = cauda->anterior;
    if (cauda != nullptr)
        cauda->proximo = nullptr;
    else
        cabeca = nullptr;
    delete temp;
    _tamanho--;
    return val;
}

template <typename T>
T ListaEncadeada<T>::obterPrimeiro() const {
    if (estaVazia())
        throw std::runtime_error("Lista vazia");
    return cabeca->valor;
}

template <typename T>
T ListaEncadeada<T>::obterUltimo() const {
    if (estaVazia())
        throw std::runtime_error("Lista vazia");
    return cauda->valor;
}

template <typename T>
bool ListaEncadeada<T>::estaVazia() const {
    return _tamanho == 0;
}

template <typename T>
int ListaEncadeada<T>::tamanho() const {
    return _tamanho;
}

template <typename T>
void ListaEncadeada<T>::limpar() {
    while (!estaVazia())
        removerInicio();
}

// Instanciações explícitas para int
template class ListaEncadeada<int>;
template class ListaEncadeada<Pacote*>;
