#include <iostream>
#include <fstream>
#include <stdexcept> 
#include <iomanip> 
#include <string>

#include "Simulador.hpp"

//Construtor
Simulador::Simulador(Escalonador& escalonador)
    :escalonador(escalonador),Configuracao(),Estatisticas() { }

//Destrutor
Simulador::~Simulador(){}

//Carrega todas as informações de pacotes e armazens
//Inicializa os eventos de postagem de pacote e de transporte entre armazens
void Simulador::carregarConfiguracao(const std::string& arquivoConfig){

    std::ifstream arquivo(arquivoConfig);

    //Carrega as informacoes inicias do arquivo
    arquivo >> this->Configuracao.capacidadeTransporte;
    arquivo >> this->Configuracao.latenciaTransporte;
    arquivo >> this->Configuracao.intervaloTransporte;
    arquivo >> this->Configuracao.custoRemocao;
    arquivo >> this->Configuracao.numArmazens;

    //Carrega a Matriz de adjacência 
    this->Configuracao.matrizAdjacencia = new bool*[Configuracao.numArmazens];

    for(int i = 0; i < Configuracao.numArmazens; i++) {
        this->Configuracao.matrizAdjacencia[i] = new bool[Configuracao.numArmazens];

        for(int j = 0; j < Configuracao.numArmazens; j++) {
            arquivo >> Configuracao.matrizAdjacencia[i][j];
        }
    }

    //Cria os armazens a partir das informacoes de entrada
    Configuracao.armazens = new Armazem*[Configuracao.numArmazens];

    for(int i = 0; i < Configuracao.numArmazens; i++) {
        int numSecoes = 0;

        for(int j = 0; j < Configuracao.numArmazens; j++) {
            if (Configuracao.matrizAdjacencia[i][j]) 
                numSecoes++;
        }
        Configuracao.armazens[i] = new Armazem(i, numSecoes, Configuracao.numArmazens, Configuracao.matrizAdjacencia);
    }
    
    //Cria os pacotes a partir das iformacoes de entrada
    //Agenda os eventos de postagem de pacotes
    arquivo >> Configuracao.numPacotes;
    Configuracao.pacotes = new Pacote*[Configuracao.numPacotes];

    for(int i = 0; i < Configuracao.numPacotes; i++) {
        int tempo, id, origem, destino;
        std::string lixo;

        arquivo >> tempo >> lixo >> id >> lixo >> origem >> lixo >> destino;

        if(i == 0){
            escalonador.setTempoSimulacao(tempo);
        }

        Configuracao.pacotes[i] = new Pacote(i, origem, destino);

        Configuracao.pacotes[i]->setRota(Configuracao.matrizAdjacencia, Configuracao.numArmazens);
        escalonador.agendarEvento(new Evento(1, tempo, i, origem , -1, -1));
    }

    // Criação de eventos de transporte entre armazéns
    for(int i = 0; i < Configuracao.numArmazens; i++){
        for(int j = 0; j < Configuracao.numArmazens; j++){
            if (Configuracao.matrizAdjacencia[i][j]) {
                // Criação de eventos de transporte entre armazéns
                Evento* evento = new Evento(2, Configuracao.intervaloTransporte + escalonador.getTempoAtual(),-1,-1,i,j);
                escalonador.agendarEvento(evento);
            }
        }
    }

    arquivo.close();
}

//Roda a simulação do sistema de escalonamento, adotando os procedimentos corretos para cada tipo de evento
//Agenda os próximos eventos necessário para transportar todos os pacotes até o armazém final
void Simulador::rodarSimulacao(){

    while (escalonador.temEventos()) {

        Evento* eventoAtual = escalonador.proximoEvento();
        escalonador.setTempoSimulacao(eventoAtual->tempo);

        //Switch do tipo de evento para tratar cada evento corretamente
        //1 : Evento de Pacote ; 2 : Evento de Transporte
        switch(eventoAtual->tipoEvento){
            //Evento de Pacote
            case 1: {
                
                Pacote* pacoteAtual = Configuracao.pacotes[eventoAtual->idPacote];
                int idArmazemAtual = eventoAtual->idArmazemAtual;

                //Confere se o pacote chegou ao destino final
                if(idArmazemAtual == Configuracao.pacotes[eventoAtual->idPacote]->getArmazemDestino()){
                   
                    this->imprimirPacoteEntregue(*eventoAtual, *pacoteAtual);
                    Estatisticas.numPacotesEntregues++;
                    break;
                }

                //Armazena o pacote no armazem intermediário caso o mesmo não tenha chegado no armazém final
                Configuracao.armazens[idArmazemAtual]->armazenaPacote(pacoteAtual->getProximoDestino(), pacoteAtual);
                this->imprimirPacoteArmazenado(*eventoAtual, *pacoteAtual);

                pacoteAtual->avancarNaRota();

                break;
            }
            //Evento de Transporte
            case 2:{

                Armazem* armazemAtual = Configuracao.armazens[eventoAtual->idArmazemOrigem];
                Secao* secaoAtual;

                //Obtem a seção do armazém atual com os pacotes que serão enviados para o destino do evento atual
                for(int i = 0; i < armazemAtual->getnumSecoes(); i++){
                    if(armazemAtual->getSecao(i).conexaoArmazem == eventoAtual->idArmazemDestino){
                        secaoAtual = &armazemAtual->getSecao(i);
                        break;
                    }
                }
                
                //Agenda mais eventos de transporte caso ainda faltem pacotes para entregar
                if(Estatisticas.numPacotesEntregues < Configuracao.numPacotes)
                    escalonador.agendarEvento(new Evento(2, escalonador.getTempoAtual() + Configuracao.intervaloTransporte
                                                ,-1, -1, eventoAtual->idArmazemOrigem, eventoAtual->idArmazemDestino));
                
                
                Pilha<Pacote*> pilhaAuxiliar;

                //Desimpilha a secao atual considerando o custo de remoção por pacote
                while(!secaoAtual->pacotes.estaVazia()){

                    pilhaAuxiliar.empilhar(secaoAtual->pacotes.desempilhar());
                    escalonador.setTempoSimulacao(escalonador.getTempoAtual() + Configuracao.custoRemocao);
                    
                    this->imprimirPacoteRemovido(pilhaAuxiliar,*armazemAtual,*secaoAtual);
                }
                
                //Realiza o transporte dos pacotes para o próximo armazém, agendando o evento de chegada
                for(int i = 0; i < Configuracao.capacidadeTransporte && !pilhaAuxiliar.estaVazia(); i++){
                    
                    escalonador.agendarEvento(new Evento(1, escalonador.getTempoAtual() + Configuracao.latenciaTransporte
                                                ,pilhaAuxiliar.verTopo()->getId(), eventoAtual->idArmazemDestino, -1, -1));
                    this->imprimirPacoteTransito(pilhaAuxiliar,*eventoAtual);
                    pilhaAuxiliar.desempilhar();
                }

                //Rearmazena os pacotes que sobraram de volta na seção
                while(!pilhaAuxiliar.estaVazia()){

                    this->imprimirPacoteRearmazenado(pilhaAuxiliar,*eventoAtual,*secaoAtual);
                    armazemAtual->armazenaPacote(secaoAtual->conexaoArmazem, pilhaAuxiliar.desempilhar());
                }
                
            }
        
        }

    }

}

//Realiza a impressão no formato adequado de um pacote que chega no seu armazém final
void Simulador::imprimirPacoteEntregue(Evento& eventoAtual, Pacote& pacoteAtual){

    std::cout << std::setw(7) << std::setfill('0') << this->escalonador.getTempoAtual()
    << " pacote " << std::setw(3) << std::setfill('0') << eventoAtual.idPacote
    << " entregue em " << std::setw(3) << std::setfill('0') << pacoteAtual.getArmazemDestino() << std::endl;
}

//Realiza a impressão no formato adequado de um pacote que é armazenado em um armazém em uma seção específica
void Simulador::imprimirPacoteArmazenado(Evento& eventoAtual, Pacote& pacoteAtual){

    std::cout << std::setw(7) << std::setfill('0') << escalonador.getTempoAtual()
    << " pacote " << std::setw(3) << std::setfill('0') << eventoAtual.idPacote
    << " armazenado em " << std::setw(3) << std::setfill('0') << eventoAtual.idArmazemAtual 
    << " na secao " << std::setw(3) << std::setfill('0') << pacoteAtual.getProximoDestino() << std::endl;
}

//Realiza a impressão no formato adequado de um pacote que é removido de uma seção em determinado armazém
void Simulador::imprimirPacoteRemovido(Pilha<Pacote*>& pilhaAuxiliar,Armazem& armazemAtual, Secao& secaoAtual){

    std::cout << std::setw(7) << std::setfill('0') << escalonador.getTempoAtual() 
    << " pacote " << std::setw(3) << std::setfill('0') <<pilhaAuxiliar.verTopo()->getId() 
    << " removido de " << std::setw(3) << std::setfill('0') << armazemAtual.getIdArmazem() 
    << " na secao " << std::setw(3) << std::setfill('0') << secaoAtual.conexaoArmazem << std::endl;
}

//Realiza a impressão no formato adequado de um pacote que entra em transito de um armazém para o próximo
void Simulador::imprimirPacoteTransito(Pilha<Pacote*>& pilhaAuxiliar,Evento& eventoAtual){

    std::cout << std::setw(7) << std::setfill('0') << escalonador.getTempoAtual() 
    << " pacote " << std::setw(3) << std::setfill('0') << pilhaAuxiliar.verTopo()->getId() 
    << " em transito de " << std::setw(3) << std::setfill('0') << eventoAtual.idArmazemOrigem << 
    " para " << std::setw(3) << std::setfill('0') << eventoAtual.idArmazemDestino << std::endl;
}

//Realiza a impressão no formato adequado de um pacote que é rearmazenado na mesma seção
void Simulador::imprimirPacoteRearmazenado(Pilha<Pacote*>& pilhaAuxiliar,Evento& eventoAtual,Secao& secaoAtual){

    std::cout << std::setw(7) << std::setfill('0') << escalonador.getTempoAtual() 
    << " pacote " << std::setw(3) << std::setfill('0') << pilhaAuxiliar.verTopo()->getId() 
    << " rearmazenado em " << std::setw(3) << std::setfill('0') << eventoAtual.idArmazemOrigem << 
    " na secao " << std::setw(3) << std::setfill('0') << secaoAtual.conexaoArmazem << std::endl;
}

