#include <stdlib.h>
#include <stdbool.h>

#include "vector.h"

#define CANT_COLS 2


void vector_destruir(float **v ,size_t n ,size_t m) {
  for (int j = 0; j < n; j++)
      free(v[j]);
  
  free(v);
  v = NULL;                                    
}

/*
float **vector_asignar_memoria(size_t n, size_t m) {
  float **v = malloc(sizeof(float *) * n);

  if (v == NULL)
    return NULL;
  
  for (int i = 0; i < n; i++) {
    v[i] = malloc(sizeof(float) * m);
     
    if (v[i] == NULL) {
      vector_destruir(v, i, m);
      
      return NULL;
    }
  }
  
  return v;
}


float **vector_desde_matriz(const float m[][2], size_t n) {
  float **v = NULL;

  if ((v = vector_asignar_memoria(n, CANT_COLS)) == NULL)
    return NULL;
   
  for (int i = 0; i < n; i++) { 
    for(int j = 0; j < CANT_COLS; j++)
      v[i][j] = m[i][j];
  }
  
  return v;
}
*/

  
static void swap_coordenadas(float **v0, float **v1) { 
  float *auxiliar = NULL;

    auxiliar = *v1; 
    *v1 = *v0;
    *v0 = auxiliar;  
}


// Cambiarla por otro método de ordenamiento
void vector_ordenar(float **v, size_t nn) {
    int i, j;
    
    for (i = 0; i < (nn - 1); i++) { 
      for (j = i + 1; j < nn; j++) { 
        if (v[j][0] < v[i][0]) { 
          swap_coordenadas(&v[i], &v[j]);
      } 
    }
  } 
}







