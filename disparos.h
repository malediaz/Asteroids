#ifndef _DISPAROS_H_
#define _DISPAROS_H_

#include "lista.h"

typedef struct disparos disparos_t;

/* Inserta un nuevo disparo que comienza en las posiciones (px, py) con 
  su respectivo ángulo */
bool disparo_insertar(lista_t *disparo, float px, float py, double angulo);

/* Le avisa al la nave que pasó un instante dt de tiempo y que debe actualizar su posición
  y su estado */
bool disparo_mover(lista_t *disparo, float dt);

/* Retorna true si hay disparos y false en caso contrario */
bool disparos_es_vacia(lista_t *disparo);

/* Grafica los disparos en pantalla */
bool disparos_graficar(lista_t *disparo);

/* Devuelve true si alguno de los disparos actuales se encuentra dentro del
  rango dado y false en caso contrario */
bool disparos_estan_adentro(lista_t *disparo, float x, float y, float radio);


#endif // _DISPAROS_H_
