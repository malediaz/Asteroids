#ifndef	_FISICA_DEL_JUEGO_H
#define	_FISICA_DEL_JUEGO_H

#include "fisica_del_juego.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*Esta funcion es de utilidad para, al momento de jugarse otra partida, no se vuelva a escribir
las varialbles relacionadas al movimiento inicial de la nave*/
void movimiento_nave_inicio(double *px, double *py, double *vx, double *vy, float *angulo, float *potencia);

/*La implementacion de esta funcion va a servir para computar la variacion de la posicion respecto
del tiempo tanto de la nave como del chorro*/
double computar_velocidad(double vi, double a, double dt);

/*Es de utilidad esta funcion, ya que es necesaria para saber la posicion
de la nave respecto del tiempo*/
double computar_posicion(double pi, double vi, double dt);

/*Compara una coordenada respecto de un vector(en el juego va a ser representado por el terreno aleatorio),
 dependiendo de su posicion en el eje de las ordenadas computa si la posicion se encuentra arriba o abajo*/
bool esta_arriba(float **coordenadas, size_t *n, float x, float y);

/*Esta funcion traslada un vector, en el juego no va a ser utilizada*/
void trasladar(float **coordenadas, size_t n, float dx, float dy);

/*En el juego es de utilidad para poder rotar objetos*/
void rotar(float **coordenadas, size_t n, double rad);

#endif // _FISICA_DEL_JUEGO_H
