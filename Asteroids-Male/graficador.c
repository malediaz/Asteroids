#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "diccionario.h"

bool graficador_inicializar(const char *fn, SDL_Renderer *r) {
  FILE *sprites;
  if (( sprites = fopen(fn, "rb")) == NULL)
    return false;  

  return true;
}                   // Y el renderer dónde me lo meto?

void graficador_finalizar(/* ??? el graficador_inicializar no me devuelve un puntero a file, qué le paso? */) {
  fclose();
}

bool graficador_dibujar(const char *nombre, float escala, float x, float y, float angulo) {
}
