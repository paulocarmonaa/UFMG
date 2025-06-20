#include "Pacote.hpp"


Pacote::Pacote() 
    : idPacote(-1), armazemOrigem(-1), armazemDestino(-1),
      tempoTotalArmazenado(0), tempoTotalTransporte(0), rota() {}

Pacote::Pacote(int id, int origem, int destino) 
    : idPacote(id), armazemOrigem(origem), armazemDestino(destino),
      tempoTotalArmazenado(0), tempoTotalTransporte(0), rota() {}

#include "Pacote.hpp" // Não se esqueça de incluir o header da própria classe

void Pacote::setRota(const bool** matrizAdj, int numArmazens) {
    // 1. Alocação dinâmica em vez de VLA (Variable Length Array)
    //    Isso é C++ padrão, mais seguro e evita problemas de estouro de pilha.
    bool* visitado = new bool[numArmazens];
    int* anterior = new int[numArmazens];

    for (int i = 0; i < numArmazens; ++i) {
        visitado[i] = false;
        anterior[i] = -1;
    }

    ListaEncadeada<int> fila; // Fila da BFS
    
    // 2. Usando 'this->' para deixar claro que são membros da classe Pacote
    fila.inserirFim(this->armazemOrigem);
    visitado[this->armazemOrigem] = true;

    // A lógica principal da busca BFS já estava correta.
    while (!fila.estaVazia()) {
        int atual = fila.removerInicio(); // Seu removerInicio() já retorna o valor, correto.

        if (atual == this->armazemDestino) {
            break; // Encontrou o destino, pode parar a busca.
        }

        for (int i = 0; i < numArmazens; ++i) {
            if (matrizAdj[atual][i] && !visitado[i]) {
                fila.inserirFim(i);
                visitado[i] = true;
                anterior[i] = atual;
            }
        }
    }

    // Se encontrou caminho (se o destino foi visitado), reconstrói a rota.
    if (visitado[this->armazemDestino]) {
        // 3. Limpa a rota antiga e constrói a nova diretamente no membro 'rota'
        this->rota.limpar();
        int atual = this->armazemDestino;

        // 4. Reconstrói o caminho parando no armazém de origem (para não incluí-lo)
        while (atual != this->armazemOrigem) {
            this->rota.inserirInicio(atual); // Insere no início para inverter a ordem
            atual = anterior[atual];
        }
    }
    
    // 5. Libera a memória alocada dinamicamente
    delete[] visitado;
    delete[] anterior;
}

int Pacote::getProximoDestino() {
    if (rota.tamanho() > 1) {
        // A rota é [atual, proximo, ...]. Pegamos o segundo elemento.
        // Isso requer um método 'obterElementoEm(int pos)' na sua ListaEncadeada.
        // Se sua lista não tiver, uma forma é clonar e remover o primeiro.
        // Por simplicidade, vamos supor que a rota contém apenas os passos futuros.
        return rota.obterPrimeiro();
        avancarNaRota();

    }
    return -1; // Sem próximo destino
}

void Pacote::avancarNaRota() {
    rota.removerInicio();
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

int Pacote::getArmazemDestino() const {
    return armazemDestino;
}