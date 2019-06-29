#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "diccionario.h"
#include "dibujar.h"
#include "config.h"
#include "caracteres.h"

void dibujo_cadena(char cad[], float f, float cx, float cy, SDL_Renderer *renderer){
  for(size_t j = 0; cad[j]; j++){
    if(cad[j] != '-'){
      matrizc_t car = caracter_a_matriz(cad[j]);
      size_t car_tam = caracter_a_tamagno(cad[j]);

      for(size_t i = 0; i < car_tam - 1; i++){
        SDL_RenderDrawLine(
          renderer,
          car[i][0] * f + cx,
          -car[i][1] * f + cy,
          car[i+1][0] * f + cx,
          -car[i+1][1] * f + cy
        );
      }
      cx += CARACTER_ANCHO * f;
    }
  }
}

void dibujo_num(int num, int escala, float cx, float cy, SDL_Renderer *renderer){
  char cad[12];
  sprintf(cad, "%03d", num);

  dibujo_cadena(cad, escala, cx, cy, renderer);
}
