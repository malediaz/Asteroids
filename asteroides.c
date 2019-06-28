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

typedef struct{
  float px;
  float py;
  double vx;
  double vy;
  double angulo;
  float radio;
} ast_t;

static ast_t *asteroide_crear(){
  ast_t *un_ast = malloc(sizeof(ast_t));
  if (un_ast == NULL)
    return NULL;

  return un_ast;
}

static float rand_float(float p0, float p1){
  return ((float)rand() / (float)RAND_MAX) * (p1 - p0) + p0;
}

static void swap_elementos(size_t *elemento0, size_t *elemento1){
  size_t auxiliar;

  auxiliar = *elemento1;
  *elemento1 = *elemento0;
  *elemento0 = auxiliar;
}

static void asteroide_inicializar(ast_t *ast_actual, float radio, float x, float y){
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


static bool asteroides_inicializar(lista_t *ast, float radio) {
  iterador_t *li = iterador_crear(ast);
  if (li == NULL)
    return false;

  for (size_t i = 0, j = 1; !iterador_termino(li); iterador_siguiente(li)) {
    ast_t *ast_actual = iterador_actual(li);

    ast_actual->radio = radio;

    double vaux_max = (1000.0 / ast_actual->radio) + 100;
    double vaux_min = (1000.0 / ast_actual->radio) - 100;
    double velocidad = rand_float(vaux_min, vaux_max);

    ast_actual->angulo = rand_float(0, 2 * PI);
    ast_actual->px = i * rand_float(0, VENTANA_ANCHO); // Cómo hago para no usar esto
    ast_actual->py = j * rand_float(0, VENTANA_ALTO);
    ast_actual->vx = velocidad * cos(ast_actual->angulo);
    ast_actual->vy = velocidad * sin(ast_actual->angulo);

    swap_elementos(&i, &j);
  }

  iterador_destruir(li);

  return true;
}

bool asteroides_insertar(lista_t *ast, size_t n_ast){
  for(size_t i = 0; i < n_ast; i++){
    ast_t *un_ast = asteroide_crear();
    if(un_ast == NULL)
      return false;

    if(!lista_insertar_comienzo(ast, un_ast))
      return false;
  }
  asteroides_inicializar(ast, ROCK1_R);

  return true;
}


static bool asteroide_graficar_por_radio(ast_t *ast_actual){
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


bool asteroides_graficar(lista_t *ast){
  iterador_t *li = iterador_crear(ast);
  if (li == NULL)
    return false;

  for ( ; !iterador_termino(li); iterador_siguiente(li)){
    ast_t *ast_actual = iterador_actual(li);
    asteroide_graficar_por_radio(ast_actual);
  }

  iterador_destruir(li);

  return true;
}

bool asteroides_mover(lista_t *ast, float dt){
  iterador_t *li = iterador_crear(ast);
  if (li == NULL)
    return false;

  for ( ; !iterador_termino(li); iterador_siguiente(li)){
    ast_t *ast_actual = iterador_actual(li);


    ast_actual->px = computar_posicion(ast_actual->px, ast_actual->vx, dt);
    ast_actual->py = computar_posicion(ast_actual->py, ast_actual->vy, dt);

    graficador_ajustar_variables(&ast_actual->px, &ast_actual->py);

  }

  iterador_destruir(li);

  return true;
}

bool asteroides_destruidos(lista_t *ast, void *disp){
  iterador_t *li = iterador_crear(ast);
  if (li == NULL)
    return false;

  for ( ; !iterador_termino(li); iterador_siguiente(li)){
    ast_t *ast_actual = iterador_actual(li);

    if(disparos_estan_adentro(disp, ast_actual->px, ast_actual->py, ast_actual->radio)){
      iterador_eliminar(li);

      for (size_t i = 0; ast_actual->radio >= ROCK1_R / 4 && i < 2; i++){
        ast_t *un_ast = asteroide_crear();
        if (un_ast == NULL)
          return false;

        asteroide_inicializar(un_ast, ast_actual->radio / 2, ast_actual->px, ast_actual->py);
        iterador_insertar(li, un_ast);
      }

      iterador_destruir(li);

      return true;
    }
  }

  iterador_destruir(li);

  return false;
}
