#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "minHeap.hpp"
#include "Evento.hpp"

class Escalonador {
private:
    MinHeap<Evento*> filaEventos;
    int tempoSimulacao;

public:
    Escalonador();
    ~Escalonador();

    void setTempoSimulacao(int tempo);
    void agendarEvento(Evento* evento);
    Evento* proximoEvento();
    bool temEventos() const;
    int getTempoAtual() const;
};

#endif // ESCALONADOR_HPP