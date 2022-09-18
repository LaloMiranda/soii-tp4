CC=gcc
CFLAGS= -O2 -g -Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11 -fopenmp

all: clean reconocimiento

reconocimiento: funciones
	$(CC) $(CFLAGS) ./obj/funciones.obj ./src/main.c -o ./bin/main.out

funciones:
	$(CC) $(CFLAGS) -c ./src/funciones.c -o ./obj/funciones.obj

clean:
	rm -f ./bin/*
	rm -f ./obj/*