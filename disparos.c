#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "config.h"
#include "movimiento.h"
#include "disparos.h"
#include "graficador.h"


struct disparo{
  float px;
  float py;
  float vx;
  float vy;
  double angulo;
  float escala;
  float vida;
};

disparo_t *disparo_crear() {
  disparo_t *disp = malloc(sizeof(disparo_t));
  if (disp == NULL)
    return NULL;

  return disp;
}

void disparo_inicializar(disparo_t *disp, float px, float py, double angulo) {
  disp->px = px;
  disp->py = py;
  disp->vx = DISPARO_VELOCIDAD * cos(angulo);
  disp->vy = -DISPARO_VELOCIDAD * sin(angulo);
  disp->angulo = angulo;
  disp->escala = 1;
  disp->vida = 0;
}


bool disparo_mover(disparo_t *disp, float dt){
  disp->px = computar_posicion(disp->px, disp->vx, dt);
  disp->py = computar_posicion(disp->py, disp->vy, dt);
  disp->vida += dt;

  graficador_ajustar_variables(&disp->px, &disp->py);

  return true;
}

float disparo_vida(disparo_t *disp) {
  return disp->vida;
}

float disparo_px(disparo_t *disp) {
  return disp->px;
}

float disparo_py(disparo_t *disp) {
  return disp->py;
}

float disparo_angulo(disparo_t *disp) {
  return disp->angulo;
}

bool disparo_dibujar(disparo_t *disp) {
  return graficador_dibujar("SHOT", disp->escala, disp->px, disp->py, disp->angulo);
}


bool disparo_esta_adentro(disparo_t *disp, float x, float y, float radio){
  return sqrt(pow(disp->px - x, 2) + pow(disp->py - y, 2)) < radio;
}

