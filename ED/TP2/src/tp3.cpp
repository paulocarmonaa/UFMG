#include <iostream>
#include <fstream>
#include <stdexcept> 
#include <string>
#include <iomanip> 

#include "ListaEncadeada.hpp"
#include "Pacote.hpp"
#include "Armazem.hpp"
#include "Escalonador.hpp"
#include "Evento.hpp"

struct stats{
    int numPacotesEntregues = 0;
}; 

struct config{
    int capacidadeTransporte;
    int latenciaTransporte;
    int intervaloTransporte;
    int custoRemocao;
    int numArmazens;
    bool** matrizAdjacencia;
    int numPacotes;
    Armazem** armazens;
    Pacote** pacotes;
};

int main(){

    config Configuracao;
    stats Estatisticas;
    Escalonador Escalonador;

    // Leitura do arquivo de configuração
    std::ifstream arquivo("entrada.txt");

    arquivo >> Configuracao.capacidadeTransporte;
    arquivo >> Configuracao.latenciaTransporte;
    arquivo >> Configuracao.intervaloTransporte;
    arquivo >> Configuracao.custoRemocao;
    arquivo >> Configuracao.numArmazens;

    //Matriz de adjacência
    Configuracao.matrizAdjacencia = new bool*[Configuracao.numArmazens];
    for(int i = 0; i < Configuracao.numArmazens; i++) {
        Configuracao.matrizAdjacencia[i] = new bool[Configuracao.numArmazens];
        for(int j = 0; j < Configuracao.numArmazens; j++) {
            arquivo >> Configuracao.matrizAdjacencia[i][j];
        }
    }

    // Criação dos armazéns
    Configuracao.armazens = new Armazem*[Configuracao.numArmazens];

    for(int i = 0; i < Configuracao.numArmazens; i++) {
        int numSecoes = 0;
        for(int j = 0; j < Configuracao.numArmazens; j++) {
            if (Configuracao.matrizAdjacencia[i][j]) {
                numSecoes++;
            }
        }
        Configuracao.armazens[i] = new Armazem(i, numSecoes, Configuracao.numArmazens, Configuracao.matrizAdjacencia);
    }

    
    arquivo >> Configuracao.numPacotes;
    Configuracao.pacotes = new Pacote*[Configuracao.numPacotes];
    
    for(int i = 0; i < Configuracao.numPacotes; i++) {
        int tempo, id, origem, destino;
        std::string lixo;

        arquivo >> tempo >> lixo >> id >> lixo >> origem >> lixo >> destino;

        if(i == 0){
            Escalonador.setTempoSimulacao(tempo);
        }

        Configuracao.pacotes[i] = new Pacote(i, origem, destino);
        Configuracao.pacotes[i]->setRota(Configuracao.matrizAdjacencia, Configuracao.numArmazens);

        Escalonador.agendarEvento(new Evento(1, tempo, i, origem , -1, -1));
    }

    // Criação de eventos de transporte entre armazéns
    for(int i = 0; i < Configuracao.numArmazens; i++){
        for(int j = 0; j < Configuracao.numArmazens; j++){
            if (Configuracao.matrizAdjacencia[i][j]) {
                // Criação de eventos de transporte entre armazéns
                Evento* evento = new Evento(2, Configuracao.intervaloTransporte + Escalonador.getTempoAtual(),-1,-1,i,j);
                Escalonador.agendarEvento(evento);
            }
        }
    }

    arquivo.close();
    

    // Processamento dos eventos
    while (Escalonador.temEventos()) {

        Evento* eventoAtual = Escalonador.proximoEvento();
        Escalonador.setTempoSimulacao(eventoAtual->tempo);

        switch(eventoAtual->tipoEvento){
            case 1: {

                Pacote* pacoteAtual = Configuracao.pacotes[eventoAtual->idPacote];

                if(eventoAtual->idArmazemAtual == Configuracao.pacotes[eventoAtual->idPacote]->getArmazemDestino()){
                   
                    std::cout << std::setw(7) << std::setfill('0') << Escalonador.getTempoAtual()
                    << " pacote " << std::setw(3) << std::setfill('0') << eventoAtual->idPacote
                    << " entregue em " << std::setw(3) << std::setfill('0') << pacoteAtual->getArmazemDestino() << std::endl;

                    Estatisticas.numPacotesEntregues++;

                    break;
                }
                
                // Armazena o pacote    no armazém atual
                //int secaoDestino = pacoteAtual->getProximoDestino();

                Configuracao.armazens[eventoAtual->idArmazemAtual]->armazenaPacote(pacoteAtual->getProximoDestino(), pacoteAtual);

                std::cout << std::setw(7) << std::setfill('0') << Escalonador.getTempoAtual()
                << " pacote " << std::setw(3) << std::setfill('0') << eventoAtual->idPacote
                << " armazenado em " << std::setw(3) << std::setfill('0') << eventoAtual->idArmazemAtual 
                << " na secao " << std::setw(3) << std::setfill('0') << pacoteAtual->getProximoDestino() << std::endl;

                pacoteAtual->avancarNaRota();

                break;
            }
            case 2:{

                Armazem* ArmazemAtual = Configuracao.armazens[eventoAtual->idArmazemOrigem];
                Secao* secaoAtual;

                for(int i = 0; i < ArmazemAtual->getnumSecoes(); i++){
                    if(ArmazemAtual->getSecao(i).conexaoArmazem == eventoAtual->idArmazemDestino){
                        secaoAtual = &ArmazemAtual->getSecao(i);
                        break;
                    }
                }
                
                //!secaoAtual->pacotes.estaVazia()
                if(Estatisticas.numPacotesEntregues < Configuracao.numPacotes){
                    Escalonador.agendarEvento(new Evento(2, Escalonador.getTempoAtual() + Configuracao.intervaloTransporte, -1, -1, eventoAtual->idArmazemOrigem, eventoAtual->idArmazemDestino));
                }
                
                Pilha<Pacote*> pilhaAuxiliar;

                while(!secaoAtual->pacotes.estaVazia()){

                    pilhaAuxiliar.empilhar(secaoAtual->pacotes.desempilhar());
                    Escalonador.setTempoSimulacao(Escalonador.getTempoAtual() + Configuracao.custoRemocao);
                    
                    std::cout << std::setw(7) << std::setfill('0') << Escalonador.getTempoAtual() 
                    << " pacote " << std::setw(3) << std::setfill('0') <<pilhaAuxiliar.verTopo()->getId() 
                    << " removido de " << std::setw(3) << std::setfill('0') << ArmazemAtual->getIdArmazem() 
                    << " na secao " << std::setw(3) << std::setfill('0') << secaoAtual->conexaoArmazem << std::endl;
                }
                
                for(int i = 0; i < Configuracao.capacidadeTransporte && !pilhaAuxiliar.estaVazia(); i++){
                   
                    std::cout << std::setw(7) << std::setfill('0') << Escalonador.getTempoAtual() 
                    << " pacote " << std::setw(3) << std::setfill('0') << pilhaAuxiliar.verTopo()->getId() 
                    << " em transito de " << std::setw(3) << std::setfill('0') << eventoAtual->idArmazemOrigem << 
                    " para " << std::setw(3) << std::setfill('0') << eventoAtual->idArmazemDestino << std::endl;

                    Escalonador.agendarEvento(new Evento(1, Escalonador.getTempoAtual() + Configuracao.latenciaTransporte, pilhaAuxiliar.verTopo()->getId(), eventoAtual->idArmazemDestino, -1, -1));
                    pilhaAuxiliar.desempilhar();
                }
                

                //Rearmazenamento tem que conferir a ordem
                while(!pilhaAuxiliar.estaVazia()){

                    std::cout << std::setw(7) << std::setfill('0') << Escalonador.getTempoAtual() 
                    << " pacote " << std::setw(3) << std::setfill('0') << pilhaAuxiliar.verTopo()->getId() 
                    << " rearmazenado em " << std::setw(3) << std::setfill('0') << eventoAtual->idArmazemOrigem << 
                    " na secao " << std::setw(3) << std::setfill('0') << secaoAtual->conexaoArmazem << std::endl;

                    ArmazemAtual->armazenaPacote(secaoAtual->conexaoArmazem, pilhaAuxiliar.desempilhar());
                }
                
        }
        
    }

    }

    return 0;
}