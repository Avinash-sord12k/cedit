CC=gcc
CFLAGS=-Wall -Wextra -Iinclude
PLATFORM=linux-x86_64
VERSION := $(shell grep CEDIT_VERSION include/version.h | cut -d '"' -f2)

TARGET=dist/cedit
RELEASE_BIN=dist/cedit-v$(VERSION)-$(PLATFORM)

SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,build/%.o,$(SRC))


$(TARGET): $(OBJ)
	mkdir -p dist
	$(CC) $(OBJ) -o $(TARGET)

release: $(TARGET)
	cp $(TARGET) $(RELEASE_BIN)
	@echo "Release ready: $(RELEASE_BIN)"

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build dist