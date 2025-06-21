#ifndef PACOTE_HPP
#define PACOTE_HPP

#include "ListaEncadeada.hpp" // Supondo que ListaEncadeada.hpp esteja correta

class Pacote {
private:
    int idPacote;
    int armazemOrigem;
    int armazemDestino;
    

    // Estatísticas de tempo
    int tempoTotalArmazenado;
    int tempoTotalTransporte;

    ListaEncadeada<int> rota;
    //int estadoPacote;

public:
    Pacote(); // Construtor padrão
    Pacote(int id, int origem, int destino);
    
    // Métodos para gerenciar a rota
    void setRota(bool** matrizAdj, int numArmazens);
    int getProximoDestino();
    void avancarNaRota();
    bool chegouAoDestinoFinal() const;

    // Métodos para estatísticas de tempo (sua sugestão!)
    void adicionaTempoArmazenado(double tempo);
    void adicionaTempoTransporte(double tempo);

    // Getters para informações básicas
    int getId() const;
    int getArmazemDestino() const;
};

#endif // PACOTE_HPP