#ifndef _VECTOR_H_
#define _VECTOR_H_

#define CANT_COLS 2


/* Recibe un vector dinámico con su cantidad de coordenadas (n) y de elementos en cada coordenada (m)
  y se libera la memoria asociada al mismo*/
void vector_destruir(float **v ,size_t n ,size_t m);

/* Función auxiliar para la asignación de memoria de un vector dinámico de nCoordx2 que recibe 
  el vector, el número de elementos que tendrá y un mensaje a imprimir para especificar cuál 
  va a ser el vector a crear, y devuelve un puntero al primer elemento de dicho vector dinámico. 
  Si falla la asignación de memoria, libera la memoria pedida y devuelve NULL.
  Precondición: el vector no debe tener un espacio de memoria asigndo previamente*/
float **vector_asignar_memoria(size_t n, size_t m);

/* Recibe una matriz y el numero de filas que posee y devuelve un vector dinámico con
  los mismos elementos. Si falla la conversión, libera la memoria pedida y devuelve
  NULL. */
float **vector_desde_matriz(const float m[][2], size_t n);


/* Recibe un vector y su número de elementos y lo ordena 
   en forma creciente con respecto a sus coordenadas en x */
void vector_ordenar(float **v, size_t nn);

/* Recibe una cadena de caracteres y su longitud y e invierte el orden*/


#endif // _VECTOR_H_

