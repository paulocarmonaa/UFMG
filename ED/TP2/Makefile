# Compilador C++ a ser utilizado
CXX = g++

# Flags de compilação: 
# -std=c++11: Exigido pelo trabalho
# -Wall -Wextra: Mostra todos os avisos (warnings), uma ótima prática
# -g: Inclui informações de debug no executável
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# --- Diretórios do Projeto ---
# Diretório dos arquivos de cabeçalho (.hpp)
IDIR = include

# Diretório dos arquivos de código fonte (.cpp)
SDIR = src

# Diretório onde os arquivos objeto (.o) serão armazenados
ODIR = obj

# Diretório onde o executável final será armazenado
BDIR = bin

# Nome do executável final
EXECUTABLE = tp2.out

# --- Gerenciamento de Arquivos ---
# Encontra automaticamente todos os arquivos .cpp na pasta src
SOURCES = $(wildcard $(SDIR)/*.cpp)

# Gera a lista de arquivos objeto (.o) correspondentes, com o caminho para a pasta obj
OBJECTS = $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SOURCES))


# --- Regras de Compilação ---

# A regra 'all' é a padrão. Será executada quando você digitar apenas 'make'
# Ela depende da criação do executável final.
all: $(BDIR)/$(EXECUTABLE)

# Regra para criar o executável final
# Ela depende de todos os arquivos objeto.
$(BDIR)/$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BDIR) # Cria o diretório bin se ele não existir
	@echo "Linkando os arquivos objeto para criar o executável..."
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra padrão para compilar um arquivo .cpp para um arquivo .o
# Isso transforma qualquer arquivo de 'src/arquivo.cpp' em 'obj/arquivo.o'
$(ODIR)/%.o: $(SDIR)/%.cpp
	@mkdir -p $(ODIR) # Cria o diretório obj se ele não existir
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -I$(IDIR) -c -o $@ $<

# Regra 'clean', exigida pelo trabalho
# Remove todos os arquivos gerados pela compilação
clean:
	@echo "Limpando arquivos de compilacao..."
	rm -rf $(ODIR) $(BDIR)

# .PHONY informa ao 'make' que 'all' e 'clean' não são nomes de arquivos
# Isso garante que as regras sempre executem, mesmo que um arquivo chamado 'clean' exista
.PHONY: all clean