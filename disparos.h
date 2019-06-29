#ifndef _DISPAROS_H_
#define _DISPAROS_H_

#include "lista.h"

typedef struct disparo disparo_t;

disparo_t *disparo_crear();

void disparo_inicializar(disparo_t *disp, float px, float py, double angulo);

int disparo_vida(disparo_t *disp);

float disparo_px(disparo_t *disp);

float disparo_py(disparo_t *disp);

/* Le avisa al la nave que pasó un instante dt de tiempo y que debe actualizar su posición
  y su estado */
bool disparo_mover(disparo_t *disp, float dt);

/* Grafica los disparos en pantalla */
bool disparo_dibujar(disparo_t *disp);


#endif // _DISPAROS_H_
