#include "Escalonador.hpp"

//Construtor
Escalonador::Escalonador() : tempoSimulacao(0) {}

//Destrutor
Escalonador::~Escalonador() {
    while (!filaEventos.estaVazio()) {
        delete filaEventos.removerMin();
    }
}

//Checa se ainda tem eventos no minHeap
bool Escalonador::temEventos() const {
    return !filaEventos.estaVazio();
}

//Retorna o tempo atual da simulação
int Escalonador::getTempoAtual() const {
    return tempoSimulacao;
}

//Seta o tempo da simulação para o tempo fornecido
void Escalonador::setTempoSimulacao(int tempo){
    this->tempoSimulacao = tempo;
}

//Agenda um evento inserindo o mesmo no minHeap
void Escalonador::agendarEvento(Evento* evento) {
    filaEventos.inserir(evento);
}

//Retorna o proximo evento da simulacao
//Atualiza o tempo da simulação para o tempo do proximo evento
Evento* Escalonador::proximoEvento() {
    if (filaEventos.estaVazio()) return nullptr;
    
    Evento* proxEvento = filaEventos.removerMin();
    this->tempoSimulacao = proxEvento->tempo;
    
    return proxEvento;
}