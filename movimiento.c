#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "config.h"
#include "movimiento.h"


double computar_velocidad(double vi ,double a ,double dt){
  return vi + a * dt;
}


double computar_posicion(double pi, double vi ,double dt){
  return pi + vi * dt;
}


void vector_rotar(float **v, size_t n, double rad){
  float coseno = cos(rad), seno = sin(rad);
  float x, y;

  for(int i = 0; i < n; i++){
    x = v[i][0] * coseno - v[i][1] * seno;
    y = v[i][0] * seno + v[i][1] * coseno;

    v[i][0] = x;
    v[i][1] = y;
  }
}
