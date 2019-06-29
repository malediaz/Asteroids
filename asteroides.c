#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "asteroides.h"
#include "config.h"
#include "movimiento.h"
#include "lista.h"
#include "iterador.h"
#include "graficador.h"
#include "disparos.h"

struct asteroide {
  float px;
  float py;
  double vx;
  double vy;
  double angulo;
  float radio;
};


ast_t *asteroide_crear() {
  ast_t *un_ast = malloc(sizeof(ast_t));
  if (un_ast == NULL)
    return NULL;

  return un_ast;
}

static float rand_float(float p0, float p1) {
  return ((float)rand() / (float)RAND_MAX) * (p1 - p0) + p0;
}


void asteroide_inicializar(ast_t *ast_actual, float radio, float x, float y) {
  ast_actual->radio = radio;

  double vaux_max = (1000.0 / ast_actual->radio) + 100;
  double vaux_min = (1000.0 / ast_actual->radio) - 100;
  double velocidad = rand_float(vaux_min, vaux_max);

  ast_actual->angulo = rand_float(0, 2 * PI);
  ast_actual->px = x;
  ast_actual->py = y;
  ast_actual->vx = velocidad * cos(ast_actual->angulo);
  ast_actual->vy = velocidad * sin(ast_actual->angulo);
}


bool asteroide_ejes_inicializar(ast_t *ast_actual, float eje_x, float eje_y) {
  ast_actual->radio = ROCK1_R;

  double vaux_max = (1000.0 / ast_actual->radio) + 100;
  double vaux_min = (1000.0 / ast_actual->radio) - 100;
  double velocidad = rand_float(vaux_min, vaux_max);

  ast_actual->angulo = rand_float(0, 2 * PI);
  ast_actual->px = eje_x * rand_float(0, VENTANA_ANCHO); 
  ast_actual->py = eje_y * rand_float(0, VENTANA_ALTO);
  ast_actual->vx = velocidad * cos(ast_actual->angulo);
  ast_actual->vy = velocidad * sin(ast_actual->angulo);

  return true;
}

float asteroide_px(ast_t *ast) {
  return ast->px;
}

float asteroide_py(ast_t *ast) {
  return ast->py;
}

float asteroide_radio(ast_t *ast) {
  return ast->radio;
}

bool asteroide_graficar(ast_t *ast_actual){
  if (ast_actual->radio == ROCK1_R){
    graficador_dibujar("ROCK1", ast_actual->radio, ast_actual->px, ast_actual->py, ast_actual->angulo);

    return true;
  }

  if (ast_actual->radio == ROCK1_R / 2){
    graficador_dibujar("ROCK2", ast_actual->radio, ast_actual->px, ast_actual->py, ast_actual->angulo);

    return true;
  }

  if (ast_actual->radio == ROCK1_R / 4){
    graficador_dibujar("ROCK3", ast_actual->radio, ast_actual->px, ast_actual->py, ast_actual->angulo);

    return true;
  }

  return false;
}

bool asteroide_mover(ast_t *ast_actual, float dt) {
  ast_actual->px = computar_posicion(ast_actual->px, ast_actual->vx, dt);
  ast_actual->py = computar_posicion(ast_actual->py, ast_actual->vy, dt);

  graficador_ajustar_variables(&ast_actual->px, &ast_actual->py);
  
  return true;
}

bool asteroide_colisiona(ast_t *ast_actual, float x, float y){
  return sqrt(pow(ast_actual->px - x, 2) + pow(ast_actual->py - y, 2)) < ast_actual->radio;
}

