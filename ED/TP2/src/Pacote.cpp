#include "Pacote.hpp"


Pacote::Pacote() 
    : idPacote(-1), armazemOrigem(-1), armazemDestino(-1),
      tempoTotalArmazenado(0), tempoTotalTransporte(0), rota() {}

Pacote::Pacote(int id, int origem, int destino) 
    : idPacote(id), armazemOrigem(origem), armazemDestino(destino),
      tempoTotalArmazenado(0), tempoTotalTransporte(0), rota() {}

void Pacote::setRota(const ListaEncadeada<int>& rotaCalculada) {
    this->rota = rotaCalculada;
}

int Pacote::getProximoDestino() const {
    if (rota.tamanho() > 1) {
        // A rota é [atual, proximo, ...]. Pegamos o segundo elemento.
        // Isso requer um método 'obterElementoEm(int pos)' na sua ListaEncadeada.
        // Se sua lista não tiver, uma forma é clonar e remover o primeiro.
        // Por simplicidade, vamos supor que a rota contém apenas os passos futuros.
        return rota.obterPrimeiro();
    }
    return -1; // Sem próximo destino
}

void Pacote::avancarNaRota() {
    if (!rota.estaVazia()) {
        rota.removerInicio();
    }
}

bool Pacote::chegouAoDestinoFinal() const {
    // Chegou se a rota de próximos passos está vazia.
    return rota.estaVazia();
}

void Pacote::adicionaTempoArmazenado(double tempo) {
    if (tempo > 0) this->tempoTotalArmazenado += tempo;
}

void Pacote::adicionaTempoTransporte(double tempo) {
    if (tempo > 0) this->tempoTotalTransporte += tempo;
}

int Pacote::getId() const {
    return idPacote;
}

// Implementação da função auxiliar de cálculo de rota
ListaEncadeada<int> calcularRotaBFS(int origem, int destino, const bool** matrizAdj, int numArmazens) {
    // ... sua lógica de BFS que já estava correta vai aqui ...
    // Ela retorna um objeto ListaEncadeada<int> com a rota.
    // Lembre-se que a rota deve conter os passos A PARTIR da origem.
    // Ex: Origem 0, Destino 3, Rota: [1, 2, 3]
    // ... preencher com BFS ...

}