# Makefile pour le projet Polynômes - DIC2
# Utilisation: make [target]

CC = gcc
CFLAGS = -Wall -Wextra -I include -g
LDFLAGS = -lm

# Répertoires
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BUILD_DIR = build
BIN_DIR = bin

# Fichiers source
SRC = $(SRC_DIR)/polynome.c

# Fichiers objets
OBJ = $(BUILD_DIR)/polynome.o

# Cibles
.PHONY: all clean test dirs

all: dirs polynome

# Créer les répertoires nécessaires
dirs:
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)

# Compilation de la bibliothèque principale
$(BUILD_DIR)/polynome.o: $(SRC_DIR)/polynome.c $(INC_DIR)/polynome.h
	$(CC) $(CFLAGS) -c $< -o $@

# Exécutable principal
polynome: dirs $(SRC_DIR)/main.c $(OBJ)
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c $(OBJ) -o $(BIN_DIR)/$@ $(LDFLAGS)

# Compilation des tests individuels
test-q4: dirs $(TEST_DIR)/test_q4.c $(OBJ)
	$(CC) $(CFLAGS) $(TEST_DIR)/test_q4.c $(OBJ) -o $(BIN_DIR)/test_q4 $(LDFLAGS)

test-q5: dirs $(TEST_DIR)/test_q5.c $(OBJ)
	$(CC) $(CFLAGS) $(TEST_DIR)/test_q5.c $(OBJ) -o $(BIN_DIR)/test_q5 $(LDFLAGS)

test-q6: dirs $(TEST_DIR)/test_q6.c $(OBJ)
	$(CC) $(CFLAGS) $(TEST_DIR)/test_q6.c $(OBJ) -o $(BIN_DIR)/test_q6 $(LDFLAGS)

test-q7: dirs $(TEST_DIR)/test_q7.c $(OBJ)
	$(CC) $(CFLAGS) $(TEST_DIR)/test_q7.c $(OBJ) -o $(BIN_DIR)/test_q7 $(LDFLAGS)

# Tous les tests
test: test-q4 test-q5 test-q6 test-q7

# Nettoyage
clean:
	@if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
	@if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)

# Recompilation complète
rebuild: clean all

# Aide
help:
	@echo "Usage: make [cible]"
	@echo ""
	@echo "Cibles disponibles:"
	@echo "  all       - Compile tout (par defaut)"
	@echo "  polynome  - Compile l'executable principal"
	@echo "  test      - Compile tous les tests"
	@echo "  test-q4   - Compile le test Q4"
	@echo "  test-q5   - Compile le test Q5"
	@echo "  test-q6   - Compile le test Q6"
	@echo "  test-q7   - Compile le test Q7"
	@echo "  clean     - Supprime les fichiers compiles"
	@echo "  rebuild   - Recompile tout"
	@echo "  help      - Affiche cette aide"
