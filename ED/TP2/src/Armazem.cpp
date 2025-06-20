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
    secoes = new Secao[numSecoes];
}

// Implementação do Destrutor
Armazem::~Armazem() {
    // Libera a memória do array de Pilhas alocado com 'new[]'.
    // O destrutor ~Pilha() será chamado para cada elemento do array.
    delete[] secoes;
}

// Implementação de armazenaPacote
void Armazem::armazenaPacote(int proxArmazem, Pacote* pacote) {
    // Validação para garantir que o índice da seção é seguro
    for(int i = 0; i < this->numSecoes; i++) {
        if (this->secoes[i].conexaoArmazem == proxArmazem) {
            // Se a seção já está conectada ao armazém de destino, armazena o pacote
            this->secoes[i].pacotes.empilhar(pacote);
            return;
        }
    }
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
        return this->secoes[idSecao].pacotes.desempilhar();
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
    return this->secoes[idSecao].pacotes.estaVazia();
}

 int Armazem::getnumSecoes() const {
    return numSecoes;
 }

 Secao Armazem::getSecao(int idSecao) const {
        if (idSecao < 0 || idSecao >= numSecoes) {
            throw std::out_of_range("Erro: Indice de secao invalido.");
        }
        return secoes[idSecao]; // Retorna a seção especificada
    }

int Armazem::getIdArmazem() const {
        return idArmazem;
    }
    