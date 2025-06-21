#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <iomanip>   
#include <sstream>   
#include <string>    

struct Evento {
    //Chave de Prioridade para ordenação de eventos
    long long chavePrioridade;
    
    //Informacoes basicas do evento
    int tipoEvento; // 1: Evento de Pacote ; 2: Evento de Transporte
    int tempo; 

    //Informacoes para eventos de pacote
    int idPacote;  
    int idArmazemAtual; //ID do Armazém onde esse pacote está chegando
    
    //Informacoes para eventos de transporte
    int idArmazemOrigem; 
    int idArmazemDestino; 

    // Construtor padrão
    Evento() : chavePrioridade(0), tipoEvento(0), tempo(0), idPacote(-1), 
               idArmazemAtual(-1), idArmazemOrigem(-1), idArmazemDestino(-1) {} 

    // Construtor com parãmetros 
    Evento(int tipoEvento, int tempo, int idPac, int armAtual, int armOrg, int armDst)
        : tipoEvento(tipoEvento),
          tempo(tempo),
          idPacote(idPac),
          idArmazemAtual(armAtual),
          idArmazemOrigem(armOrg),
          idArmazemDestino(armDst) 
    {
        std::stringstream ss;
        
        //Montagem da chave da prioridade a partir das informações de entrada
        ss << std::setw(6) << std::setfill('0') << this->tempo;

        if (this->tipoEvento == 1) {
            ss << std::setw(6) << std::setfill('0') << this->idPacote;
        }
        else if (this->tipoEvento == 2) { 
            ss << std::setw(3) << std::setfill('0') << this->idArmazemOrigem;
            ss << std::setw(3) << std::setfill('0') << this->idArmazemDestino;
        }

        ss << this->tipoEvento;

        this->chavePrioridade = std::stoll(ss.str());
    }

    //Compara dois eventos com base na chave de prioridade
    bool operator<(const Evento& outro) const {
        return this->chavePrioridade < outro.chavePrioridade;
    }
};

#endif