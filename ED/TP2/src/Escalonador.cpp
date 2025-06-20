#include "Escalonador.hpp"

Escalonador::Escalonador() : tempoSimulacao(0) {}

Escalonador::~Escalonador() {
    while (!filaEventos.estaVazio()) {
        delete filaEventos.removerMin();
    }
}

void Escalonador::agendarEvento(Evento* evento) {
    filaEventos.inserir(evento);
}


void Escalonador::setTempoSimulacao(int tempo){
    this->tempoSimulacao = tempo;
}

Evento* Escalonador::proximoEvento() {
    if (filaEventos.estaVazio()) return nullptr;
    
    Evento* proxEvento = filaEventos.removerMin();
    // O relógio da simulação SALTA para o tempo do próximo evento.
    this->tempoSimulacao = proxEvento->tempo;
    
    return proxEvento;
}

bool Escalonador::temEventos() const {
    return !filaEventos.estaVazio();
}

int Escalonador::getTempoAtual() const {
    return tempoSimulacao;
}