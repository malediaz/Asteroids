#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "config.h"
#include "movimiento.h"
#include "disparos.h"

struct balas {
  float px;
  float py;
  float vx;
  float vy;
  float angulo;

  struct balas *sig;
};

struct disparos {
  bala_t *prim;
};

bala_t *bala_crear() {
  bala_t *bala = malloc(sizeof(bala_t));
  if (bala == NULL)
    return NULL;
  
  return bala;
}

disparos_t *disparo_crear() {
  disparos_t *disparo = malloc(sizeof(disparos_t));
  if (disparo == NULL)
    return NULL;
    
  disparo->prim = NULL;
  
  return disparo;
}

void disparo_mover(disparos_t *disparo, float dt) {
  SDL_Event event;
  
  if(SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
		  return;
    
    if (event.type == SDL_KEYDOWN) {
      switch(event.key.keysym.sym) {
        case SDLK_SPACE:
          
          
          break;
      }
    }
  }
    
  disparo->prim->vx = DISPARO_VELOCIDAD * sin(disparo->prim->angulo);
  disparo->prim->vy = DISPARO_VELOCIDAD * cos(disparo->prim->angulo);
  disparo->prim->px = computar_posicion(disparo->prim->px, disparo->prim->vx, dt);
  disparo->prim->py = computar_posicion(disparo->prim->py, disparo->prim->vy, dt);
  
  dt += DT;
}
