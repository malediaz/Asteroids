#ifndef _ASTEROIDES_H_
#define _ASTEROIDES_H_

#include "lista.h"

#define AST_INICIALES 4

/* Inicializa los asteroides correspondientes al inicio de la partida */
bool asteroides_insertar(lista_t *ast, size_t n_ast);

/* Grafica todos los asteroides activos en el momento */
bool asteroides_graficar(lista_t *ast);

/* Mueve los asteroides la posición correspondiente dado un dt de tiempo */
bool asteroides_mover(lista_t *ast, float dt);

/* Verifica si algún asteroide fue destruido por los disparos y en caso de que 
  corresponda, crea nuevos */
bool asteroides_destruidos(lista_t *ast, void *disp);


#endif // _ASTEROIDES_H_
