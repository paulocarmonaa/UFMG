#ifndef PACOTE_HPP
#define PACOTE_HPP

#include "Fila.hpp" 

class Pacote {
    private:
        int idPacote;
        int armazemOrigem;
        int armazemDestino;
        
        ListaEncadeada<int> rota;

        // Estatísticas de tempo
        int tempoTotalArmazenado;
        int tempoTotalTransporte;
    public:

        //Construtores e destrutor
        Pacote(); 
        Pacote(int id, int origem, int destino);
        ~Pacote(); 
        
        //Getters
        int getId() const;
        int getArmazemDestino() const;

        // Métodos para gerenciar a rota
        void setRota(bool** matrizAdj, int numArmazens);
        void avancarNaRota();
        int getProximoDestino();
        bool chegouAoDestinoFinal() const;

        // Métodos para estatísticas de tempo 
        void adicionaTempoArmazenado(int tempo);
        void adicionaTempoTransporte(int tempo);
};

#endif // PACOTE_HPP