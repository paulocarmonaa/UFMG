#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "minHeap.hpp"
#include "Evento.hpp"

class Escalonador {
    private:
        MinHeap<Evento*> filaEventos;
        int tempoSimulacao;

    public:
        //Construtor e Destrutor
        Escalonador();
        ~Escalonador();

        //Métodos para checar o estado da simulação
        int getTempoAtual() const;
        bool temEventos() const;
        
        //Métodos para gerenciar a simulação
        void setTempoSimulacao(int tempo);
        void agendarEvento(Evento* evento);
        Evento* proximoEvento();
};

#endif // ESCALONADOR_HPP