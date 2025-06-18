

class Transporte{
    private:
        int idPacote;
        int latenciaTransporte;
        int armazemOrigem;
        int armazemDestino;
        int capacidadeTransporte;
    public:
        Transporte();
        Transporte(int id, int latencia, int origem, int destino, int capacidade);
        ~Transporte();

        int getIdPacote() const;
        int getLatenciaTransporte() const;
        int getArmazemOrigem() const;
        int getArmazemDestino() const;
        int getCapacidadeTransporte() const;

};