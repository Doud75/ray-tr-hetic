TARGET = raytrhetic
BUILD_DIR = build
DOCKER_EXEC = docker-compose exec raytrhetic

all: build

start:
	@echo "Lancement du conteneur de développement..."
	@docker-compose up -d

stop:
	@echo "Arrêt du conteneur de développement..."
	@docker-compose down

build: start
	@echo "Configuration du projet avec CMake..."
	@$(DOCKER_EXEC) bash -c "mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && cmake .."
	@echo "Compilation du projet..."
	@$(DOCKER_EXEC) cmake --build $(BUILD_DIR)

run:
	@echo "Exécution de l'application..."
	@$(DOCKER_EXEC) ./$(BUILD_DIR)/$(TARGET)

clean:
	@echo "Nettoyage des fichiers de build..."
	@$(DOCKER_EXEC) rm -rf $(BUILD_DIR)

shell: start
	@echo "Ouverture d'un shell dans le conteneur..."
	@$(DOCKER_EXEC) bash

.PHONY: all start stop build run clean shell