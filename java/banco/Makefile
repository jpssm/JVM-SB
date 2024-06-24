# Nome do compilador
JAVAC = javac

# Diretório de origem dos arquivos Java
SRC_DIR = banco

# Diretório de saída para os arquivos .class
OUT_DIR = out

# Lista de arquivos .java
SOURCES = $(wildcard $(SRC_DIR)/*.java)

# Lista de arquivos .class
CLASSES = $(SOURCES:$(SRC_DIR)/%.java=$(OUT_DIR)/%.class)

# Regra padrão para compilar todas as classes
#all: $(CLASSES)

# Regra para compilar arquivos .java em arquivos .class
$(OUT_DIR)/%.class: $(SRC_DIR)/%.java
	@mkdir -p $(OUT_DIR)
	$(JAVAC) -d $(OUT_DIR) $<

# Limpar os arquivos compilados
clean:
	rm -rf $(OUT_DIR)

# Criar um arquivo JAR
jar: all
	jar cf $(OUT_DIR)/banco.jar -C $(OUT_DIR) .

# Limpar e compilar novamente
rebuild: clean all

.PHONY: all clean jar rebuild
