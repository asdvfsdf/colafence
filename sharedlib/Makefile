# Makefile for compiling colafence.c into a shared library

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -fPIC

# Source file
SRC = colafence.c

# Shared library name
LIBNAME = libcolafence.so

all: $(LIBNAME)

# Compile colafence.c into shared library
$(LIBNAME): $(SRC)
	$(CC) $(CFLAGS) -shared $(SRC) -o $(LIBNAME)

clean:
	rm -f $(LIBNAME)

lib:
	sudo cp libcolafence.so /lib
	sudo cp libcolafence.so /usr/lib

