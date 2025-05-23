#ifndef ORDENADOR_H
#define ORDENADOR_H

class OrdenadorUniversal{
    private:
        int seed;
        int limiarCusto;
        int tamanho;
        double a,b,c;
    public:
        OrdenadorUniversal(int seed, int limiarCusto, int tamanho, double a, double b, double c) :
            seed(seed) , limiarCusto(limiarCusto), tamanho(tamanho), a(a), b(b), c(c) {}

        int getSeed();
        int getLimiarCusto();
        int getTamanho();
        double getA();
        double getB();
        double getC();

        void setSeed(int seed);
        void setLimiarCusto(int limiarCusto);
        void setTamanho(int tamanho);
        void setA(double a);
        void setB(double b);
        void setC(double c);
};

int determinaNumQuebras(int tamanho, int* vet);
OrdenadorUniversal* criaOrdenador(int* vetor, int tam, int minTamParticao, int limiarQuebras);

#endif