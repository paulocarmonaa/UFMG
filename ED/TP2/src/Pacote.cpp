#include "Pacote.hpp"

//Construtor padrão
Pacote::Pacote() 
    : idPacote(-1), armazemOrigem(-1), armazemDestino(-1), 
    rota(),tempoTotalArmazenado(0), tempoTotalTransporte(0) {}

//Construtor com parâmetros
Pacote::Pacote(int id, int origem, int destino) 
    : idPacote(id), armazemOrigem(origem), armazemDestino(destino),
        rota(), tempoTotalArmazenado(0), tempoTotalTransporte(0) {}

//Destrutor
Pacote::~Pacote(){}

//Retorna o ID do pacote
int Pacote::getId() const {
    return idPacote;
}

//Retorna o armazém de destino do pacote
int Pacote::getArmazemDestino() const {
    return armazemDestino;
}

//Define a rota do pacote usando a matriz de adjacência fornecida na entrada
void Pacote::setRota(bool** matrizAdj, int numArmazens) {
    
    bool* visitado = new bool[numArmazens];
    int* anterior = new int[numArmazens];

    for (int i = 0; i < numArmazens; ++i) {
        visitado[i] = false;
        anterior[i] = -1;
    }

    Fila<int> fila;
    fila.enfileirar(this->armazemOrigem);
    visitado[this->armazemOrigem] = true;

    while (!fila.estaVazia()) {
        int atual = fila.desenfileirar();

        if(atual == this->armazemDestino)
            break; 
        
        for(int i = 0; i < numArmazens; ++i) {
            if (matrizAdj[atual][i] && !visitado[i]) {
                fila.enfileirar(i);
                visitado[i] = true;
                anterior[i] = atual;
            }
        }
    }

    if (visitado[this->armazemDestino]) {
        this->rota.limpar();
        int atual = this->armazemDestino;

        while (atual != this->armazemOrigem) {
            this->rota.inserirInicio(atual);
        }
    }
    
    delete[] visitado;
    delete[] anterior;
}

//Avança o pacote para o próximo destino na rota, removendo o primeiro elemento da lista de destinos
void Pacote::avancarNaRota() {
    rota.removerInicio();
}

//Retorna o próximo destino do pacote, que é o primeiro elemento da lista de destinos
int Pacote::getProximoDestino() {
    if (!rota.estaVazia()) {
        return rota.obterPrimeiro();
    }
    return -1;
}

//Confere se o pacote chegou ao destino final, verificando se a rota tem apenas um elemento
bool Pacote::chegouAoDestinoFinal() const {
    if(rota.getTamanho() == 1)
        return true;
    else 
        return false; 
}

//Adiciona um valor inteiro ao tempo total armazenado do pacote
void Pacote::adicionaTempoArmazenado(int tempo) {
    this->tempoTotalArmazenado += tempo;
}

//Adiciona um valor inteiro ao tempo total em transpote do pacote
void Pacote::adicionaTempoTransporte(int tempo) {
    if (tempo > 0) this->tempoTotalTransporte += tempo;
}