#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP

#include <stdexcept>

// Nó genérico da lista
template <typename T>
struct No {
    T valor;
    No<T>* proximo;
    No<T>* anterior;

    No(T val) : valor(val), proximo(nullptr), anterior(nullptr) {}
};

// Lista duplamente encadeada
template <typename T>
class ListaEncadeada {
private:
    No<T>* cabeca;
    No<T>* cauda;
    int _tamanho;

public:
    ListaEncadeada();
    ~ListaEncadeada();

    void inserirInicio(T valor);
    void inserirFim(T valor);
    T removerInicio();
    T removerFim();
    T obterPrimeiro() const;
    T obterUltimo() const;
    bool estaVazia() const;
    int tamanho() const;
    void limpar();

    // Métodos extras para funcionar como fila
    void push_back(T valor) { inserirFim(valor); }
    void pop_front() { removerInicio(); }
    T front() const { return obterPrimeiro(); }
    bool empty() const { return estaVazia(); }
};

#endif // LISTAENCADEADA_HPP
