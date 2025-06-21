#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP

#include <stdexcept>

// Estrutura do nó
template <typename T>
struct No {
    T valor;
    No<T>* proximo;
    No<T>* anterior;

    // Construtor do nó
    No(T val) : valor(val), proximo(nullptr), anterior(nullptr) {}
};

template <typename T>
class ListaEncadeada {
    private:
        No<T>* cabeca;
        No<T>* cauda;
        int tamanho;

    public:
        // Construtor e destrutor
        ListaEncadeada();
        ~ListaEncadeada();

        //Métodos de Inserção e Remoção
        void inserirInicio(T valor);
        void inserirFim(T valor);
        T removerInicio();
        T removerFim();
        
        // Métodos de Acesso
        T obterPrimeiro() const;
        T obterUltimo() const;

        // Métodos de Verificação
        bool estaVazia() const;
        int getTamanho() const;
        void limpar();
};

//Implementação dos métodos da Lista Encadeada

//Construtor
template <typename T>
ListaEncadeada<T>::ListaEncadeada() : cabeca(nullptr), cauda(nullptr), tamanho(0) {}

//Destrutor
template <typename T>
ListaEncadeada<T>::~ListaEncadeada() { limpar(); }

//Insercao no Inicio da Lista
template <typename T>
void ListaEncadeada<T>::inserirInicio(T valor) {
    No<T>* novo = new No<T>(valor);
    novo->proximo = cabeca;

    if (cabeca != nullptr)
        cabeca->anterior = novo;
    cabeca = novo;
    if (cauda == nullptr)
        cauda = novo;

    tamanho++;
}

//Insercao no Fim da Lista
template <typename T>
void ListaEncadeada<T>::inserirFim(T valor) {
    No<T>* novo = new No<T>(valor);
    novo->anterior = cauda;

    if (cauda != nullptr)
        cauda->proximo = novo;
    cauda = novo;
    if (cabeca == nullptr)
        cabeca = novo;

    tamanho++;
}

//Remocao no Inicio da Lista
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
    tamanho--;
    return val;
}

//Remocao no Fim da Lista
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
    tamanho--;
    return val;
}

//Retorna o primeiro elemento da lista
template <typename T>
T ListaEncadeada<T>::obterPrimeiro() const {
    if (estaVazia())
        throw std::runtime_error("Lista vazia");

    return cabeca->valor;
}

//Retorna o ultimo elemento da lista
template <typename T>
T ListaEncadeada<T>::obterUltimo() const {
    if (estaVazia())
        throw std::runtime_error("Lista vazia");

    return cauda->valor;
}

// Verifica se a lista está vazia
template <typename T>
bool ListaEncadeada<T>::estaVazia() const {
    return tamanho == 0;
}

// Retorna o tamanho da lista
template <typename T>
int ListaEncadeada<T>::getTamanho() const {
    return tamanho;
}

//Remove todos os elementos da lista
template <typename T>
void ListaEncadeada<T>::limpar() {
    while (!estaVazia())
        removerInicio();
}

#endif
