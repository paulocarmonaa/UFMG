#ifndef EVENTO_HPP
#define EVENTO_HPP

// Representa um evento na simulação.
// A prioridade é determinada pela 'chavePrioridade', garantindo uma ordem total.
struct Evento {
    long int chavePrioridade;
    int tipoEvento;

    int tempo; // Chave única (ex: tempo, tipo, etc. combinados)
    
    int idPacote;
    int idArmazemAtual;

    int idArmazemOrigem; // ID do armazém de origem (se aplicável)
    int idArmazemDestino; // ID do armazém de destino (se aplic

    Evento()
        : chavePrioridade(0),tipoEvento(0), tempo(0), idPacote(-1), idArmazemAtual(-1), idArmazemOrigem(-1), idArmazemDestino(-1) {}

    Evento( int tipoEvento, int tempo, int idPacote, int idarmazemAtual, int idArmazemOrigem, int idArmazemDestino)
        : chavePrioridade(0), tipoEvento(tipoEvento), tempo(tempo), idPacote(idPacote), idArmazemAtual(idarmazemAtual), idArmazemOrigem(idArmazemOrigem), idArmazemDestino(idArmazemDestino) {

            if (tipoEvento == 1) // Evento de transporte
                chavePrioridade = tempo + idPacote + tipoEvento; // Prioridade é o tempo do evento + ID do pacote
            else if (tipoEvento == 2)  // Evento de remoção
                chavePrioridade = tempo + idArmazemOrigem + idArmazemDestino + idPacote; // Prioridade é o tempo + ID do pacote
    }

    // Sobrecarga do operador '<' para que o MinHeap possa comparar dois Eventos.
    // O MinHeap armazena Evento*, então precisamos desreferenciar para comparar.
        bool operator<(const Evento& outro) const {
            return this->chavePrioridade < outro.chavePrioridade;
        }

    
};

#endif // EVENTO_HPP