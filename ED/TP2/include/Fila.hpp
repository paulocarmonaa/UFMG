#ifndef FILA_HPP
#define FILA_HPP

#include"ListaEncadeada.hpp"


template <typename T>
class Fila{
    private:
        ListaEncadeada<T> lista;
    public:
        //Construto e destrutor
        Fila();
        ~Fila();

        //Métodos de Inserção e Remoção
        void enfileirar(T valor);
        T desenfileirar();

        //Métodos de Acesso
        int getTamanho() const;
        T getFrente() const;
        bool estaVazia() const;

};

//Construtor
template <typename T>
Fila<T>::Fila() : lista() {}

//Destrutor
template <typename T>
Fila<T>::~Fila() {}

//Insere um elemento na fila
template <typename T>
void Fila<T>::enfileirar(T valor) { lista.inserirFim(valor); }

//Remove o primeiro elemento da fila
template <typename T>
T Fila<T>::desenfileirar() { return lista.removerInicio(); }

//Retorna o tamanho da fila
template <typename T>
int Fila<T>::getTamanho() const { return lista.getTamanho(); }

//Retorna o primeiro elemento da fila sem removê-lo
template <typename T>
T Fila<T>::getFrente() const { return lista.obterPrimeiro(); }

//Verifica se a fila está vazia
template <typename T>
bool Fila<T>::estaVazia() const { return lista.estaVazia(); }

#endif