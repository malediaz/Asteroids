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


typedef struct {
  float px;
  float py;
  double vx;
  double vy;
  double angulo;
} asteroide_t;

struct asteroides {
  lista_t *l;
};


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



void asteroides_destruir(asteroides_t *ast) {
  lista_destruir(ast->l, NULL);
  free(ast);
}



