#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "dibujar.h"
#include "caracteres.h"
#include "diccionario.h"
#include "config.h"


#define MARGEN_SUP 30
#define MAX_CADENA 9999
#define MSJ_ALTO 20


void dibujar_cadena(char *cadena, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y) {

  for (size_t j = 0; cadena[j] != '\0'; j++) {
    vectores_t letra_vector = conversion_a_vector(cadena[j]);
    size_t letra_longitud = conversion_a_longitud(cadena[j]);

    for (size_t i = 1; i < letra_longitud; i++) {
      SDL_RenderDrawLine(
        renderer,
        (letra_vector[i - 1][0] + posicion_x) * escala,
       (-letra_vector[i - 1][1] + posicion_y) * escala,
        (letra_vector[i][0] + posicion_x) * escala,
       (-letra_vector[i][1] + posicion_y) * escala
      );

      posicion_x += CARACTER_ANCHO;
    }
  }
}


void valores_dibujar(float valor, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y) {
  char aux[MAX_CADENA];
  sprintf(aux, "%04f", valor);

  dibujar_cadena(aux, escala, renderer, posicion_x, posicion_y);
}
