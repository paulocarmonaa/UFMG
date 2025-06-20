#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <iomanip>   // Para std::setw e std::setfill
#include <sstream>   // Para std::stringstream
#include <string>    // Para std::string e std::stoll

struct Evento {
    long long chavePrioridade;
    
    int tipoEvento;
    int tempo;

    int idPacote;
    int idArmazemAtual;
    int idArmazemOrigem;
    int idArmazemDestino;

    // Construtor padrão
    Evento() : chavePrioridade(0), tipoEvento(0), tempo(0), idPacote(-1), 
               idArmazemAtual(-1), idArmazemOrigem(-1), idArmazemDestino(-1) {}

    // Construtor principal CORRIGIDO E SIMPLIFICADO
    Evento(int tipo, int t, int pac_id, int arm_atual, int arm_org, int arm_dst)
        // 1. Inicializa TODOS os membros com os valores recebidos (boa prática)
        : tipoEvento(tipo),
          tempo(t),
          idPacote(pac_id),
          idArmazemAtual(arm_atual),
          idArmazemOrigem(arm_org),
          idArmazemDestino(arm_dst) 
    {
        // 2. Usa UM ÚNICO stringstream para construir a chave de forma limpa
        std::stringstream ss;

        // Parte 1: Adiciona o TEMPO (6 dígitos)
        ss << std::setw(6) << std::setfill('0') << this->tempo;

        // Parte 2: Adiciona os DADOS do evento (6 dígitos)
        if (this->tipoEvento == 1) { // Chegada de Pacote
            ss << std::setw(6) << std::setfill('0') << this->idPacote;
        } 
        else if (this->tipoEvento == 2) { // Evento de Transporte
            ss << std::setw(3) << std::setfill('0') << this->idArmazemOrigem;
            ss << std::setw(3) << std::setfill('0') << this->idArmazemDestino;
        }

        // Parte 3: Adiciona o TIPO do evento (1 dígito)
        ss << this->tipoEvento;

        // 3. Converte a string final para long long e armazena na chave
        this->chavePrioridade = std::stoll(ss.str());
    }

    // Operador de comparação continua correto
    bool operator<(const Evento& outro) const {
        return this->chavePrioridade < outro.chavePrioridade;
    }
};

#endif // EVENTO_HPP