# Compilador e flags
CC = gcc
CFLAGS = -g -c -Iinclude -Wno-unused-variable -std=c99

#CFLAGS = -c -Iinclude -Wall -Wextra -std=c99
LDFLAGS = 

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# Arquivos fontes e objetos
SRCS = $(wildcard $(SRC_DIR)/class_loader/*.c $(SRC_DIR)/execution_engine/*.c $(SRC_DIR)/leitor_exibidor/*.c $(SRC_DIR)/runtime_data/*.c $(SRC_DIR)/main.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executável final
TARGET = main

# Regra default
all: $(TARGET)

# Linkagem do executável final
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compilação dos arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos objeto e executável
clean:
	rm -rf $(OBJ_DIR) $(TARGET) *.exe

# Regra para debug
debug: CFLAGS += -g
debug: $(TARGET)


.PHONY: all clean debug test
