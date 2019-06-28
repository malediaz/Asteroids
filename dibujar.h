#ifndef _DIBUJAR_H_
#define _DIBUJAR_H_

#include"dibujar.h"
#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"diccionario.h"
#include"config.h"


void dibujo_objetos(float **v, size_t n, float cx, float cy, SDL_Renderer *renderer);

/*La voy a utilizar para poder dibujar las palabras del juego*/
void dibujo_cadena(char cad[], float f, float cx, float cy, SDL_Renderer *renderer);

/*Esta funcion la voy a utilizar para dibujar las variables que dependen del 
comportamiento del juego*/
void dibujo_num(int num, int escala, float cx, float cy, SDL_Renderer *renderer);

#endif // _DIBUJAR_H_

