#include "Armazem.hpp"
#include "Pilha.hpp"
#include "Pacote.hpp"

#include <stdexcept> 

//Construtor Padrão
Armazem::Armazem() : idArmazem(0), numSecoes(0), secoes(nullptr) {}

//Construtor com parâmetros
Armazem::Armazem(int idArmazem, int numSecoes,int numArmazens, bool** matrizdeAdjacencia) : 
    idArmazem(idArmazem), numSecoes(numSecoes), secoes(nullptr) 
{
    int indiceSecao = 0; 
    this->secoes = new Secao[this->numSecoes];
    
    //Inicializa as seções do armazém
    for (int i = 0; i < numArmazens; ++i) {
        
        if (matrizdeAdjacencia[idArmazem][i]) {

            if (indiceSecao < numSecoes) {
                this->secoes[indiceSecao].conexaoArmazem = i;
                indiceSecao++;
            }
        }
    }
}

// Implementação do Destrutor
Armazem::~Armazem() {

    delete[] secoes;
}

//Getter ID Armazém
int Armazem::getIdArmazem() const {
        return idArmazem;
}
    
// Método para armazenar um pacote em uma seção específica do armazém
void Armazem::armazenaPacote(int proxArmazem, Pacote* pacote) {

    for(int i = 0; i < this->numSecoes; i++) {
        if (this->secoes[i].conexaoArmazem == proxArmazem) {
            
            this->secoes[i].pacotes.empilhar(pacote);
            return;
        }
    }
    throw std::out_of_range("Erro: Indice de secao invalido.");
}

// Método para retirar um pacote de uma seção específica do armazém
Pacote* Armazem::retiraPacote(int idSecao) {

    if (idSecao < 0 || idSecao >= this->numSecoes){
        throw std::out_of_range("Erro: Indice da secao invalido.");
    }
    else if (!this->secaoEstaVazia(idSecao)) {
        return this->secoes[idSecao].pacotes.desempilhar();
    }
    else{
        return nullptr;
    }
}

// Getter para o número de seções do armazém
 int Armazem::getnumSecoes() const {
    return numSecoes;
 }

// Método para obter o índice da seção de conexão com base no ID da seção
int Armazem::getSecaoConexao(int idSecao) const{

    for(int i = 0; i < numSecoes; i++) {
        if (secoes[i].conexaoArmazem == idSecao) {
            return i;
        }
    }
    return -1;
}
  
// Método para obter uma referência à seção com base no ID da seção
Secao& Armazem::getSecao(int idSecao) { 
    
    if (idSecao < 0 || idSecao >= this->numSecoes) {
        throw std::out_of_range("Erro: Indice de secao invalido.");
    }
    return secoes[idSecao];
}

// Método para verificar se uma seção específica do armazém está vazia
bool Armazem::secaoEstaVazia(int idSecao) const {

    if (idSecao < 0 || idSecao >= this->numSecoes) {
        throw std::out_of_range("Erro: Indice de secao invalido.");
    }

    return this->secoes[idSecao].pacotes.estaVazia();
}



