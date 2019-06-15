CC := gcc
CFLAGS := -Wall -c -pedantic -std=c99 -g -O3
LFLAGS := -lm -lSDL2
INSTALL_DIR := /usr/sbin # Voy a tener que ser admin para instalar ahi

all: programa

main.o: main.c
	$(CC) $(CFLAGS) $(LFLAGS) main.c

caracteres.o: caracteres.c 
	$(CC) $(CFLAGS) caracteres.c

vectores_dinamicos.o: vectores_dinamicos.c
	$(CC) $(CFLAGS) vectores_dinamicos.c

generador_terreno.o: generador_terreno.c
	$(CC) $(CFLAGS) generador_terreno.c

fisica_del_juego.o: fisica_del_juego.c 
	$(CC) $(CFLAGS) fisica_del_juego.c

dibujo_en_juego.o: dibujo_en_juego.c 
	$(CC) $(CFLAGS) dibujo_en_juego.c

diccionario.o: diccionario.c
	$(CC) $(CFLAGS) diccionario.c

programa: main.o caracteres.o vectores_dinamicos.o generador_terreno.o fisica_del_juego.o diccionario.o dibujo_en_juego.o
	$(CC) main.o caracteres.o vectores_dinamicos.o generador_terreno.o fisica_del_juego.o diccionario.o dibujo_en_juego.o -o programa $(LFLAGS)

clean:
	rm *.o

