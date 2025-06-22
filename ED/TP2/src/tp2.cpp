#include "Simulador.hpp"
#include "Escalonador.hpp"
#include <stdexcept>

int main(int argc, char *argv[]){

    //Confere se o arquivo de entrada foi fornecido de maneira correta
    //Lança uma exceção caso não tenha sido fornecido
    if (argc < 2)
        throw std::invalid_argument("Erro: argumento de entrada ausente.");

    //Cria os objetos do escalonador de eventos e o simulador do Sistema de Escalonamento Logístico
    Escalonador escalonador;
    Simulador simulador(escalonador);

    //Configura a simulacao a partir da entrada e roda a mesma
    simulador.carregarConfiguracao(argv[1]);
    simulador.rodarSimulacao();
    
    return 0;
}