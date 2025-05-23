#include"OrdenadorUniversal.hpp"

int OrdenadorUniversal::getSeed(){
    return this->seed;
}

int OrdenadorUniversal::getLimiarCusto(){
    return this->limiarCusto;
}

int OrdenadorUniversal::getTamanho(){
    return this->tamanho;
}

double OrdenadorUniversal::getA(){
    return this->a;
}

double OrdenadorUniversal::getB(){
    return this->b;
}
double OrdenadorUniversal::getC(){
    return this->b;
}

void OrdenadorUniversal::setSeed(int seed){
     this->seed = seed;
}

void OrdenadorUniversal::setLimiarCusto(int limiarCusto){
     this->limiarCusto = limiarCusto;
}

void OrdenadorUniversal::setTamanho(int tamanho){
     this->tamanho = tamanho;
}

void OrdenadorUniversal::setA(double a){
     this->a = a;
}

void OrdenadorUniversal::setB(double b){
     this->b = b;
}

void OrdenadorUniversal::setC(double c){
     this->c = c;
}


int determinaNumQuebras(int tamanho, int* vetor){
   
    int numQuebras = 0;
    
    for(int i = 0; i< tamanho-1 ; i++){
        if(vetor[i] > vetor[i+1])
            numQuebras++;
    }

    return numQuebras;
}

OrdenadorUniversal* criaOrdenador(int* vetor, int tam, int minTamParticao, int limiarQuebras){

}