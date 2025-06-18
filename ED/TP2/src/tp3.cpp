#include <iostream>
#include <fstream>
#include <stdexcept> 
#include <string>

#include "ListaEncadeada.hpp"
#include "Pacote.hpp"
#include "Armazem.hpp"
#include "Escalonador.hpp"
#include "Evento.hpp"

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
        Configuracao.armazens[i] = new Armazem(i+1, numSecoes);
    }

    // Criação de eventos de transporte entre armazéns
    for(int i = 0; i < Configuracao.numArmazens; i++){
        for(int j = 0; j < Configuracao.numArmazens; j++){
            if (Configuracao.matrizAdjacencia[i][j]) {
                // Criação de eventos de transporte entre armazéns
                Evento* evento = new Evento(2, Configuracao.intervaloTransporte,-1,-1,i+1,j+1);
                Escalonador.agendarEvento(evento);
            }
        }
    }


    arquivo >> Configuracao.numPacotes;
    Configuracao.pacotes = new Pacote*[Configuracao.numPacotes];
    
    for(int i = 0; i < Configuracao.numPacotes; i++) {
        int tempo, id, origem, destino;
        std::string lixo;

        arquivo >> tempo >> lixo >> id >> lixo >> origem >> lixo >> destino;
        Configuracao.pacotes[i] = new Pacote(id, origem, destino);

        Escalonador.agendarEvento(new Evento(1, tempo, Configuracao.pacotes[i]->getId(), origem, origem, destino));
    }

    arquivo.close();
    
    // Processamento dos eventos
    while (Escalonador.temEventos()) {
        
        

    }

    return 0;
}