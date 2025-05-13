# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude -IC:/raylib/include

# Carpetas
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Archivos fuente y objetos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
EXECUTABLE = $(BIN_DIR)/juego.exe

# Librerías Raylib
LDLIBS = -LC:/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm

# Regla principal
all: $(EXECUTABLE)

# Enlazado final
$(EXECUTABLE): $(OBJECTS)
	if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

# Compilación
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar
clean:
	del /Q $(OBJ_DIR)\*.o 2>nul || exit 0
	del /Q $(BIN_DIR)\*.exe 2>nul || exit 0

.PHONY: all clean
