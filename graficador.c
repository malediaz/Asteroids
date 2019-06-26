#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "config.h"
#include "diccionario.h"
#include "lista.h"
#include "iterador.h"
#include "graficador.h"
#include "movimiento.h"

#define BLOQUE 20
#define LONGCADENA 10

static SDL_Renderer *graficador;
static lista_t *l;

typedef struct sprite {

  char nombre[10];
  uint16_t n;
  float **coords;

} sprites_t;


bool graficador_inicializar(const char *fn, SDL_Renderer *r) {
  FILE *binario;
  if ((binario = fopen(fn, "rb")) == NULL){ 
    return false;
  }

  l = lista_crear();

  while (1) {
    sprites_t *sprites = malloc(sizeof(sprites_t));
    if(sprites == NULL){
      fclose(binario);
      
      return false;
    }

    if(fread(&sprites->nombre, sizeof(char) * LONGCADENA, 1, binario) != 1) 
      break;

    if(fread(&sprites->n, sizeof(uint16_t), 1, binario) != 1){
      fclose(binario);
      
      return false;
    }

    sprites->coords = malloc(sprites->n * sizeof(float *));

    if(sprites->coords == NULL){
      fclose(binario);
      
      return false;
    }

    for(size_t i = 0; i < sprites->n; i++){
      sprites->coords[i] = malloc(2 * sizeof(float));

      if(sprites->coords[i] == NULL){
        for(size_t j = 0; j < i; j++)
          free(sprites->coords[j]);
          
        free(sprites->coords);
        
        return false;
      }
      
      if(fread(sprites->coords[i], sizeof(float), 2, binario) != 2){
        fclose(binario);
        
        return false;
      }
    }

    lista_insertar_comienzo(l, sprites);
  }

  fclose(binario);
  graficador = r;

  return true;
}

void graficador_finalizar() {
  lista_destruir(l, NULL);
}

void graficador_ajustar_variables(float *x, float *y) {
  if (*x < 0)
    *x = VENTANA_ANCHO;

  if (*x > VENTANA_ANCHO)
    *x = 0;

  if (*y < 0)
    *y = VENTANA_ALTO;

  if (*y > VENTANA_ALTO)
    *y = 0;
}

bool graficador_dibujar(const char *nombre, float escala, float x, float y, double angulo) {  
  iterador_t *li = iterador_crear(l);

  for (; !iterador_termino(li); iterador_siguiente(li)) {
    sprites_t *dato = iterador_actual(li);
    
    if (strcmp(nombre, dato->nombre) == 0) {
      vector_rotar(dato->coords, dato->n, angulo);
      vector_trasladar(dato->coords, dato->n, x, -y);
      
      for(size_t i = 1; i < dato->n; i++)
        SDL_RenderDrawLine(
          graficador,
          dato->coords[i - 1][0] * escala,
         -dato->coords[i - 1][1] * escala,
          dato->coords[i][0] * escala,
         -dato->coords[i][1] * escala
      );
      
      vector_trasladar(dato->coords, dato->n, -x, y);
      vector_rotar(dato->coords, dato->n, -angulo);

      iterador_destruir(li);

      return true;
    }
  }

  iterador_destruir(li);

  return false;
}
