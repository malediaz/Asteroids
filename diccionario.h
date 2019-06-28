#ifndef _DICCIONARIO_H_
#define _DICCIONARIO_H_

#include"diccionario.h"
#include"caracteres.h"
#include<stdio.h>
#include<stdlib.h>

/*Voy a definir darle el nombre matrizc_t del siguiente tipo para que resulte
mas facil su implementacion*/
typedef const int (*matrizc_t)[2];

/*Esta funcion recibe un caracter y devuelve la matriz relacionada a este, 
la cual es una representacion del caracter*/
matrizc_t caracter_a_matriz(char c);

/*La siguiente funcion devuelve la cantidad de filas que tiene la matriz
relacionada al caracter ingresado*/
size_t caracter_a_tamagno(char c);

#endif // _DICCIONARIO_H
