CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2
LDLIBS = -lm

.PHONY: all test clean
all: artemis
artemis: main.c artemis.c validaciones.c artemis.h validaciones.h
	$(CC) $(CFLAGS) main.c artemis.c validaciones.c -o $@ $(LDLIBS)

test: pruebas
	./pruebas
