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

#define AST_INICIALES 4

typedef struct {
  float px;
  float py;
  double vx;
  double vy;
  double angulo;
  float radio;
} ast_t;

struct asteroides {
  lista_t *l;
};


float rand_float(float p0, float p1) {  
  return ((float)rand() / (float)RAND_MAX) * (p1 - p0) + p0;        
}

asteroides_t *asteroides_crear() {
  asteroides_t *ast = malloc(sizeof(asteroides_t));
  if (ast == NULL)
    return NULL;
    
  ast->l = lista_crear();
  if (ast->l == NULL) {
    free(ast);
    
    return NULL;
  }
  
  return ast;
}

static ast_t *asteroide_crear() {
  ast_t *un_ast = malloc(sizeof(ast_t));
  if (un_ast == NULL)
    return NULL;
    
  return un_ast;
}


void asteroides_destruir(asteroides_t *ast) {
  lista_destruir(ast->l, NULL);
  free(ast);
}

static bool asteroides_primeros_inicializar(asteroides_t *ast) {
  iterador_t *li = iterador_crear(ast->l);
  if (li == NULL)
    return false;
  
  for (/*size_t i = 0, j = 1*/; !iterador_termino(li); iterador_siguiente(li)) {
    ast_t *ast_actual = iterador_actual(li);
    
    ast_actual->radio = ROCK1_R;
    
    double vaux_max = (1000.0 / ast_actual->radio) + 100;
    double vaux_min = (1000.0 / ast_actual->radio) - 100;
    double velocidad = rand_float(vaux_min, vaux_max);
    
    ast_actual->angulo = rand_float(0, 2 * PI);
    ast_actual->px = 1; //i * rand_float(0, VENTANA_ANCHO);
    ast_actual->py = 1; // j * rand_float(0, VENTANA_ALTO);
    ast_actual->vx = velocidad * cos(ast_actual->angulo);
    ast_actual->vy = velocidad * sin(ast_actual->angulo);
    
  }
  
  iterador_destruir(li);
  
  return true;
}


bool asteroides_primeros_insertar(asteroides_t *ast) {
  for (size_t i = 0; i < AST_INICIALES; i++) {
    ast_t *un_ast = asteroide_crear();
    if (un_ast == NULL)
      return false;
    
    if (!lista_insertar_comienzo(ast->l, un_ast))
      return false;;
  }
  asteroides_primeros_inicializar(ast);
  
  return true;
}


static bool asteroide_graficar_por_radio(ast_t *ast_actual) {
  if (ast_actual->radio == ROCK1_R) {
    graficador_dibujar("ROCK1", ast_actual->radio, ast_actual->px, ast_actual->py, ast_actual->angulo);    // En realidad tiene que ser random el asteroide
     
    return true;
  }
  
  return false;
}
  

bool asteroides_graficar(asteroides_t *ast) {
  iterador_t *li = iterador_crear(ast->l);
  if (li == NULL)
    return false;
  
  for ( ; !iterador_termino(li); iterador_siguiente(li)) {
    ast_t *ast_actual = iterador_actual(li);
    
    if (!asteroide_graficar_por_radio(ast_actual)) {
      iterador_destruir(li);
      
      return false;
    }
  }
  
  iterador_destruir(li);
  
  return true;
}

bool asteroides_mover(asteroides_t *ast, float dt) {
  iterador_t *li = iterador_crear(ast->l);
  if (li == NULL)
    return false;
  
  for ( ; !iterador_termino(li); iterador_siguiente(li)) {
    ast_t *ast_actual = iterador_actual(li);
    
    graficador_ajustar_variables(&ast_actual->px, &ast_actual->py);
    
    ast_actual->px = computar_posicion(ast_actual->px, ast_actual->vx, dt);
    ast_actual->py = computar_posicion(ast_actual->py, ast_actual->vy, dt);
    
  }
  
  iterador_destruir(li);
  
  return true;
}
  
  
  
