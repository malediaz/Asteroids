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
#define FLECHAS_ESPACIO 230
#define VALORES_ESPACIO 210
#define VALORES_MARGEN_IZQ (MSJ_INFO_MARGEN_IZQ + VALORES_ESPACIO / 2)
#define VALORES_MARGEN_DER (MSJ_INFO_MARGEN_DER + VALORES_ESPACIO)
#define FIGURA_ESCALA 1
#define MSJ_ALTO 20


void dibujar_cadena(char *cadena, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y) {  
  for (size_t j = 0; cadena[j] != '\0'; j++) {
    vectores_t letra_vector = conversion_a_vector(cadena[j]);
    size_t letra_longitud = conversion_a_longitud(cadena[j]);
      
    for (size_t i = 1; i < letra_longitud; i++) {
      SDL_RenderDrawLine(
        renderer,
        (letra_vector[i - 1][0] + posicion_x) * escala,
       (-letra_vector[i - 1][1] + posicion_y) * escala + MARGEN_SUP,     
        (letra_vector[i][0] + posicion_x) * escala, 
       (-letra_vector[i][1] + posicion_y) * escala + MARGEN_SUP
      );
      
      posicion_x += CARACTER_ANCHO;
    }
  }
}

/*
void figura_dibujar(float **figura, float escala, SDL_Renderer *renderer, size_t figura_tam, int posicion_x, int posicion_y) {
  for(int i = 1; i < nave_tam; i++) 
    SDL_RenderDrawLine(
			renderer,
			figura[i - 1][0] * escala + posicion_x,
     -figura[i - 1][1] * escala - posicion_y + VENTANA_ALTO, 
			figura[i][0] * escala + posicion_x,
     -figura[i][1] * escala - posicion_y + VENTANA_ALTO
		);
} */


void valores_dibujar(float valor, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y) {
  char aux[MAX_CADENA];
  sprintf(aux, "%04f", valor);

  dibujar_cadena(aux, escala, renderer, posicion_x, posicion_y);
}


