# Nombre del compilador
CC = gcc

# Flags de compilación con optimización -O3
CFLAGS = -Wall -Wextra -pedantic -O3

# Librerías necesarias
LDFLAGS = -lncurses

# Nombre del archivo fuente y del ejecutable
SRC = main.c
TARGET = CursedType

# Regla principal
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET)

# Regla para limpiar objetos si los hubiera
clean_all: clean
	rm -f *.o
