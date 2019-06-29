#ifndef _MOVIMIENTO_H_
#define _MOVIMIENTO_H_


/* Dada la velocidad actual vi, la aceleración a y el paso temporal dt 
  devuelve la velocidad del próximo instante */
double computar_velocidad(double vi ,double a ,double dt);

/* Dada la posición actual pi, la velocidad actual vi y el paso temporal
  dt devuelva la posición del próximo instante */
double computar_posicion(double pi, double vi ,double dt);

/* Dado un vector v de n coordenadas, rota cada una de ella rad radianes 
  con respecto al origen de coordenadas */
void vector_rotar(float **v, size_t n, double rad);



#endif // _MOVIMIENTO_H
