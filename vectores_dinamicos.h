#ifndef	_VECTORES_DINAMICOS_H
#define	_VECTORES_DINAMICOS_H

#include"vectores_dinamicos.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define COL 2 //Cantidad de columnas de la matriz

/*Esta funcion la voy a utilizar para liberar la memoria asignada a un determinado vector
de manera tal que dicha reserva quede a disposición de cualquier otro proceso.*/
void vector_destruir(float **v, size_t n, size_t m);

/*Funcion que se le asigna el tamaño y crea una matriz dinamica de 2 columnas*/
float **crear_vdin(int n);

/*Esta funcion la voy a utilizar para pasar una matriz a un vector dinamico con la misma
cantidad de elementos*/
float **vector_desde_matriz(const float m[][2], size_t n);

/*Con esta funcion genero un numero aleatorio dentro de un intervalo dado*/
float generar_aleatorio_entre(float max, float min);

/*Esta funcion me va a ser de utilidad cuando quiera calcular la imagen de una
variable x perteneciente a una recta*/
float imagen_de_x(float **v, size_t nv, float x);

/* La funcion vector_densificar la voy a utilizar para, dado un vector de coordenadas,
 genere una versión densificada de la misma con puntos aleatorios.
La cantidad de coordenadas del vector densificado deben ser mayores
a las del vector original. Ya que como condicion necesaria el vector nuevo
debe conservar los puntos del vector original. Especificamente esta funcion la voy
a utilizar para generar el terreno aleatorio, sobre un vector generico ya dado.
*/
float **vector_densificar(float **v, size_t nv, size_t nn, float margen);

#endif // _VECTORES_DINAMICOS_H
