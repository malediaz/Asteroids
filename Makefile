CC := gcc
CFLAGS := -Wall -c -pedantic -std=c99 -g -O0
LFLAGS := -lm
INSTALL_DIR := /usr/sbin # Voy a tener que ser admin para instalar ahi

all: programa

main.o: main.c config.h nave.h graficador.h disparos.h asteroides.h
	$(CC) $(CFLAGS) $(LFLAGS) main.c

nave.o: nave.c nave.h config.h movimiento.h graficador.h
	$(CC) $(CFLAGS) nave.c

disparos.o: disparos.c disparos.h config.h movimiento.h graficador.h lista.h iterador.h
	$(CC) $(CFLAGS) disparos.c

asteroides.o: asteroides.c asteroides.h config.h movimiento.h graficador.h lista.h iterador.h
	$(CC) $(CFLAGS) asteroides.c

movimiento.o: movimiento.c movimiento.h config.h
	$(CC) $(CFLAGS) movimiento.c $(LFLAGS) 

iterador.o: iterador.c iterador.h lista.h
	$(CC) $(CFLAGS) iterador.c

graficador.o: graficador.c graficador.h config.h diccionario.h lista.h iterador.h
	$(CC) $(CFLAGS) graficador.c

caracteres.o: caracteres.c caracteres.h
	$(CC) $(CFLAGS) caracteres.c

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) lista.c
	
dibujar.o: dibujar.c dibujar.h config.h movimiento.h vector.h
	$(CC) $(CFLAGS) dibujar.c

diccionario.o: diccionario.c diccionario.h caracteres.h
	$(CC) $(CFLAGS) diccionario.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) vector.c

programa: main.o graficador.o caracteres.o nave.o movimiento.o lista.o dibujar.o diccionario.o vector.o iterador.o disparos.o asteroides.o
	$(CC) main.o graficador.o caracteres.o nave.o movimiento.o lista.o dibujar.o diccionario.o vector.o iterador.o disparos.o asteroides.o -o Asteroids -lSDL2 $(LFLAGS) 

clean:
	rm *.o
