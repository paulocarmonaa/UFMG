#ifndef SIMULADOR_HPP
#define SIMULADOR_HPP

#include "Evento.hpp"
#include "Escalonador.hpp"
#include "Armazem.hpp"
#include "Pacote.hpp"


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

class Simulador{
    private:
        Escalonador& escalonador;
        config Configuracao;
        stats Estatisticas;
    public:
        //Construtor
        Simulador(Escalonador& escalonador);
        ~Simulador();

        //Leitura do arquivo e das configuracoes iniciais
        void carregarConfiguracao(const std::string& arquivoConfig);

        //Roda a lógica de simulação
        void rodarSimulacao();

        //Métodos de impressão
        void imprimirPacoteEntregue(Evento& eventoAtual, Pacote& pacoteAtual);
        void imprimirPacoteArmazenado(Evento& eventoAtual, Pacote& pacoteAtual);
        void imprimirPacoteRemovido(Pilha<Pacote*>& pilhaAuxiliar,Armazem& armazemAtual, Secao& secaoAtual);
        void imprimirPacoteTransito(Pilha<Pacote*>& pilhaAuxiliar,Evento& eventoAtual);
        void imprimirPacoteRearmazenado(Pilha<Pacote*>& pilhaAuxiliar,Evento& eventoAtual,Secao& secaoAtual);
};

#endif