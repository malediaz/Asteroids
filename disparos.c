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


typedef struct balas {
  float px;
  float py;
  float vx;
  float vy;
  double angulo;
  float escala;
  float vida;
} bala_t;

struct disparos {
  lista_t *l;
};


bala_t *bala_crear() {
  bala_t *bala = malloc(sizeof(bala_t));
  if (bala == NULL)
    return NULL;
  
  return bala;
}

static void bala_inicializar(bala_t *bala, float px, float py, double angulo) {
  bala->px = px;
  bala->py = py;
  bala->vx = DISPARO_VELOCIDAD * sin(angulo);
  bala->vy = DISPARO_VELOCIDAD * cos(angulo);
  bala->angulo = angulo;
  bala->escala = 1;
  bala->vida = 0;
}

disparos_t *disparos_crear() {
  disparos_t *disparo = malloc(sizeof(disparos_t));
  if (disparo == NULL)
    return NULL;
  
  disparo->l = lista_crear();
  if (disparo->l == NULL) {
    free(disparo);
    
    return NULL;
  }
  
  return disparo;
}

bool disparo_insertar(disparos_t *disparo, float px, float py, double angulo) {
  bala_t *bala = bala_crear();
  if (bala == NULL)
    return false;
    
  bala_inicializar(bala, px, py, angulo);
  
  if (!lista_insertar_comienzo(disparo->l, bala))
    return false;
  
  return true;
}

bool disparos_es_vacia(disparos_t *disparo) {
  return lista_es_vacia(disparo->l);
}

bool disparo_mover(disparos_t *disparo, float dt) { 
  iterador_t *li = iterador_crear(disparo->l);
  if (li == NULL)
    return false;
  
  for ( ; !iterador_termino(li); iterador_siguiente(li)) {
    bala_t *bala = iterador_actual(li);
      
    bala->px = computar_posicion(bala->px, bala->vx, dt);
    bala->py = computar_posicion(bala->py, bala->vy, dt);
    bala->vida += dt;
    
    if (bala->vida > DISPARO_VIDA) {
      iterador_eliminar(li);
      iterador_destruir(li);
      
      return true;
    }
    
    graficador_ajustar_variables(&bala->px, &bala->py);
  }
  
  iterador_destruir(li);
  
  return true;
}

bool disparos_graficar(disparos_t *disparo) {
  iterador_t *li = iterador_crear(disparo->l);
  if (li == NULL)
    return false;
  
  for ( ; !iterador_termino(li); iterador_siguiente(li)) {
    bala_t *bala = iterador_actual(li);
    
    if (!graficador_dibujar("SHOT", bala->escala, bala->px, bala->py, bala->angulo)) {
      iterador_destruir(li);
      
      return false;
    }
  }
  
  iterador_destruir(li);
  
  return true;
}

void disparos_destruir(disparos_t *disparo) {
  lista_destruir(disparo->l, NULL);
  free(disparo);
}


  
