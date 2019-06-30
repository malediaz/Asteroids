#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "diccionario.h"
#include "dibujar.h"
#include "config.h"
#include "caracteres.h"

static void dibujo_cadena(char cad[], float f, float cx, float cy, SDL_Renderer *renderer){
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

static void dibujo_num(int num, int escala, float cx, float cy, SDL_Renderer *renderer){
  char cad[12];
  sprintf(cad, "%03d", num);

  dibujo_cadena(cad, escala, cx, cy, renderer);
}

void dibujo_mensajes_inicio_juego(SDL_Renderer *renderer) {
  dibujo_cadena("ASTEROIDS", 11, 210, 350, renderer);
  dibujo_cadena("PRESS SPACE TO START GAME", 3, 260, 550, renderer);
}

void dibujo_mensajes_fin_juego(unsigned int score, unsigned int high_score, SDL_Renderer *renderer) {
  dibujo_cadena("GAME OVER", 10, 230, 350, renderer);
  dibujo_cadena("SCORE ", 4, 380, 400, renderer);
  dibujo_cadena("HIGH SCORE ", 2.5, 380, 430, renderer);
  dibujo_num(score, 4, 530, 400 , renderer);
  dibujo_num(high_score, 3, 550, 430 , renderer);
  dibujo_cadena("PRESS SPACE TO START A NEW GAME", 3, 210, 550, renderer);
}

void dibujo_mensajes_en_juego(unsigned int score, unsigned int high_score, SDL_Renderer *renderer) {
  dibujo_num(high_score, 2, VENTANA_ANCHO / 2, 50, renderer);
  dibujo_num(score, 4, 180, 60, renderer);
}

void dibujo_fiuba_inc(SDL_Renderer *renderer) {
  dibujo_cadena("2019 FIUBA INC", 2, VENTANA_ANCHO / 2 - VENTANA_ANCHO / 10, 650, renderer);
}
