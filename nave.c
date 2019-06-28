#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "config.h"
#include "nave.h"
#include "movimiento.h"
#include "graficador.h"

struct mi_nave{
  float px;
  float py;
  double vx;
  double vy;
  double angulo;
  float potencia;
  float escala;
};

nave_t *nave_crear(){
  nave_t *nave = malloc(sizeof(nave_t));

  if (nave == NULL)
    return NULL;

  return nave;
}

void nave_destruir(nave_t *nave){
  free(nave);
}

void nave_inicializar(nave_t *nave){
  nave->px = NAVE_X_INICIAL;
  nave->py = NAVE_Y_INICIAL;
  nave->vx = NAVE_VX_INICIAL;
  nave->vy = NAVE_VY_INICIAL;
  nave->angulo = NAVE_ANGULO_INICIAL;
  nave->potencia = NAVE_POTENCIA_INICIAL;
  nave->escala = NAVE_ESCALA;
}

void nave_vidas_dibujar(size_t vidas){

  for(size_t i = 0, j = 0; i < vidas; i++, j += 20)
  	graficador_dibujar("SHIP", NAVE_ESCALA, 180 + j, 80, PI / 2);
}

void nave_potencia_incrementar(nave_t *nave){
  nave->potencia += 1000;
}

void nave_rotar_derecha(nave_t *nave){
  nave->angulo -= NAVE_ROTACION_PASO;
}

void nave_rotar_izquierda(nave_t *nave){
  nave->angulo += NAVE_ROTACION_PASO;
}

static void velocidad_decrementar(nave_t *nave, float dt){
  nave->vx -= nave->vx * dt;
  nave->vy -= nave->vy * dt;
}

double nave_angulo(nave_t *nave){
  return nave->angulo;
}

float nave_px(nave_t *nave){
  return nave->px;
}

float nave_py(nave_t *nave){
  return nave->py;
}

void nave_mover(nave_t *nave, float dt){
  if(nave->potencia > 0)
    nave->potencia -= nave->potencia * 0.1;

  nave->vx = computar_velocidad(nave->vx, nave->potencia * cos(nave->angulo), dt);
  nave->vy = computar_velocidad(nave->vy, -nave->potencia * sin(nave->angulo), dt);
  nave->px = computar_posicion(nave->px, nave->vx, dt);
  nave->py = computar_posicion(nave->py, nave->vy, dt);

  velocidad_decrementar(nave, dt);

  graficador_ajustar_variables(&nave->px, &nave->py);
}

bool nave_dibujar(const nave_t *nave){
  if(!graficador_dibujar("SHIP", nave->escala, nave->px, nave->py, nave->angulo))
    return false;

  if(nave->potencia > 1){
    if(!graficador_dibujar("THURST", nave->escala, nave->px, nave->py, nave->angulo))
      return false;
  }

  return true;
}
