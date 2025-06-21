#include "Armazem.hpp"
#include "Pilha.hpp"
#include "Pacote.hpp"

#include <stdexcept> // Biblioteca para usar exceções em caso de erro


Armazem::Armazem() : idArmazem(0), numSecoes(0), secoes(nullptr) {}
    // Construtor padrão, inicializa o armazém com ID 0 e sem seções.
    // O array de Pilhas é inicializado como nullpt}
// Implementação do Construtor
Armazem::Armazem(int id, int numSecoes,int numArmazens, bool** matrizdeAdjacencia) : 
idArmazem(id), numSecoes(numSecoes), secoes(nullptr) {
    // Aloca dinamicamente um array do seu objeto Pilha<Pacote*>.
    // O construtor padrão de Pilha() será chamado para cada uma das 'numSecoes'.
    this->secoes = new Secao[this->numSecoes];

    // --- Lógica Corrigida para Mapear Seções aos Vizinhos ---

    // 3. Cria um contador para o índice do nosso array 'secoes'.
    // Este contador irá de 0 até numSecoes-1.
    int indiceDaSecao = 0; 

    // 4. Itera por TODOS os possíveis armazéns para encontrar os que são vizinhos.
    for (int idVizinho = 0; idVizinho < numArmazens; ++idVizinho) {
        
        // Verifica na matriz se o 'idVizinho' é realmente um vizinho do armazém atual.
        if (matrizdeAdjacencia[this->idArmazem][idVizinho]) {
            
            // Se for um vizinho, configura a próxima seção disponível.
            if (indiceDaSecao < this->numSecoes) {
                
                // 5. Atribui o ID do vizinho à 'conexaoArmazem' da seção correta.
                this->secoes[indiceDaSecao].conexaoArmazem = idVizinho;

                // Passa para a próxima seção a ser configurada.
                indiceDaSecao++;
            }
        }
    }
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

// DEPOIS
Secao& Armazem::getSecao(int idSecao) { // Mesma alteração aqui
    if (idSecao < 0 || idSecao >= numSecoes) {
        throw std::out_of_range("Erro: Indice de secao invalido.");
    }
    return secoes[idSecao];
}
int Armazem::getIdArmazem() const {
        return idArmazem;
    }
    

int Armazem::getSecaoConexao(int idSecao) const{

    for(int i = 0; i < numSecoes; i++) {
        if (secoes[i].conexaoArmazem == idSecao) {
            return i;
        }
    }
    return -1; // Retorna -1 se não encontrar a seção com o ID especificado
}