CC := gcc
CFLAGS := -Wall -c -pedantic -std=c99 -g -O0
LFLAGS := -lm
INSTALL_DIR := /usr/sbin # Voy a tener que ser admin para instalar ahi

all: programa

main.o: main.c
	$(CC) $(CFLAGS) $(LFLAGS) main.c

nave.o: nave.c
	$(CC) $(CFLAGS) nave.c

disparos.o: disparos.c
	$(CC) $(CFLAGS) disparos.c

asteroides.o: asteroides.c
	$(CC) $(CFLAGS) asteroides.c

movimiento.o: movimiento.c
	$(CC) $(CFLAGS) movimiento.c $(LFLAGS) 

iterador.o: iterador.c iterador.h lista.h
	$(CC) $(CFLAGS) iterador.c

graficador.o: graficador.c
	$(CC) $(CFLAGS) graficador.c

caracteres.o: caracteres.c
	$(CC) $(CFLAGS) caracteres.c

lista.o: lista.c
	$(CC) $(CFLAGS) lista.c

dibujar.o: dibujar.c 
	$(CC) $(CFLAGS) dibujar.c

diccionario.o: diccionario.c
	$(CC) $(CFLAGS) diccionario.c

vector.o: vector.c
	$(CC) $(CFLAGS) vector.c

programa: main.o graficador.o caracteres.o nave.o movimiento.o lista.o dibujar.o diccionario.o vector.o iterador.o disparos.o asteroides.o
	$(CC) main.o graficador.o caracteres.o nave.o movimiento.o lista.o dibujar.o diccionario.o vector.o iterador.o disparos.o asteroides.o -o Asteroids -lSDL2 $(LFLAGS) 

clean:
	rm *.o
