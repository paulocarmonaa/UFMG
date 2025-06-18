#include "Armazem.hpp"
#include "Pilha.hpp"
#include "Pacote.hpp"

#include <stdexcept> // Biblioteca para usar exceções em caso de erro


Armazem::Armazem() : idArmazem(0), numSecoes(0), secoes(nullptr) {}
    // Construtor padrão, inicializa o armazém com ID 0 e sem seções.
    // O array de Pilhas é inicializado como nullpt}
// Implementação do Construtor
Armazem::Armazem(int id, int num) : idArmazem(id), numSecoes(num) {
    // Aloca dinamicamente um array do seu objeto Pilha<Pacote*>.
    // O construtor padrão de Pilha() será chamado para cada uma das 'numSecoes'.
    secoes = new Pilha<Pacote*>[numSecoes];
}

// Implementação do Destrutor
Armazem::~Armazem() {
    // Libera a memória do array de Pilhas alocado com 'new[]'.
    // O destrutor ~Pilha() será chamado para cada elemento do array.
    delete[] secoes;
}

// Implementação de armazenaPacote
void Armazem::armazenaPacote(int idSecao, Pacote* pacote) {
    // Validação para garantir que o índice da seção é seguro
    if (idSecao < 0 || idSecao >= this->numSecoes) {
        throw std::out_of_range("Erro: Indice de secao invalido.");
    }

    // Chama o método 'empilhar' do seu TAD Pilha
    this->secoes[idSecao].empilhar(pacote);
}

// Implementação de retiraPacote
Pacote* Armazem::retiraPacote(int idSecao) {
    // Validação do índice da seção
    if (idSecao < 0 || idSecao >= this->numSecoes) {
        throw std::out_of_range("Erro: Indice de secao invalido.");
    }
    
    // Verifica se a seção tem pacotes antes de tentar remover
    if (!this->secaoEstaVazia(idSecao)) {
        // Chama o método 'desempilhar' do seu TAD Pilha
        return this->secoes[idSecao].desempilhar();
    }

    // Se a seção estiver vazia, retorna um ponteiro nulo
    return nullptr;
}

// Implementação de secaoEstaVazia
bool Armazem::secaoEstaVazia(int idSecao) const {
    // Validação do índice da seção
    if (idSecao < 0 || idSecao >= this->numSecoes) {
        throw std::out_of_range("Erro: Indice de secao invalido.");
    }

    // Chama o método 'estaVazia' do seu TAD Pilha
    return this->secoes[idSecao].estaVazia();
}