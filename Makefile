CC=gcc
CFLAGS=-Wall -Wextra -Iinclude

SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,build/%.o,$(SRC))

TARGET=dist/cedit

$(TARGET): $(OBJ)
	mkdir -p dist
	$(CC) $(OBJ) -o $(TARGET)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build dist