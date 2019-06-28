#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "config.h"
#include "movimiento.h"
#include "disparos.h"
#include "lista.h"
#include "iterador.h"
#include "graficador.h"

typedef struct disparo{
  float px;
  float py;
  float vx;
  float vy;
  double angulo;
  float escala;
  float vida;
}disparo_t;

disparo_t *disparo_crear() {
  disparo_t *bala = malloc(sizeof(disparo_t));
  if (bala == NULL)
    return NULL;

  return bala;
}


static void disparo_inicializar(disparo_t *bala, float px, float py, double angulo){
  bala->px = px;
  bala->py = py;
  bala->vx = DISPARO_VELOCIDAD * cos(angulo);
  bala->vy = -DISPARO_VELOCIDAD * sin(angulo);
  bala->angulo = angulo;
  bala->escala = 1;
  bala->vida = 0;
}

bool disparo_insertar(lista_t *disparo, float px, float py, double angulo){
  disparo_t *bala = disparo_crear();
  if (bala == NULL)
    return false;

  disparo_inicializar(bala, px, py, angulo);

  if(!lista_insertar_comienzo(disparo, bala))
    return false;

  return true;
}

bool disparo_mover(lista_t *disparo, float dt){
  iterador_t *li = iterador_crear(disparo);
  if (li == NULL)
    return false;

  for ( ; !iterador_termino(li); iterador_siguiente(li)){
    disparo_t *bala = iterador_actual(li);

    bala->px = computar_posicion(bala->px, bala->vx, dt);
    bala->py = computar_posicion(bala->py, bala->vy, dt);
    bala->vida += dt;

    if(bala->vida > DISPARO_VIDA){
      iterador_eliminar(li);
      iterador_destruir(li);

      return true;
    }

    graficador_ajustar_variables(&bala->px, &bala->py);
  }

  iterador_destruir(li);

  return true;
}

bool disparos_graficar(lista_t *disparo){
  iterador_t *li = iterador_crear(disparo);
  if (li == NULL)
    return false;

  for ( ; !iterador_termino(li); iterador_siguiente(li)){
    disparo_t *bala = iterador_actual(li);

    if (!graficador_dibujar("SHOT", bala->escala, bala->px, bala->py, bala->angulo)){
      iterador_destruir(li);

      return false;
    }
  }

  iterador_destruir(li);

  return true;
}

bool disparos_estan_adentro(lista_t *disparo, float x, float y, float radio){
  iterador_t *li = iterador_crear(disparo);
  if(li == NULL)
    return false;

  for( ; !iterador_termino(li); iterador_siguiente(li)){
    disparo_t *bala = iterador_actual(li);
    float coordenada = sqrt(pow(bala->px - x, 2) + pow(bala->py - y, 2));

    if(coordenada < radio){
      iterador_eliminar(li);
      iterador_destruir(li);

      return true;
    }
  }

  iterador_destruir(li);

  return false;
}
