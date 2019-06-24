#ifndef _DISPAROS_H_
#define _DISPAROS_H_

typedef struct disparos disparos_t;

/* Crea el lugar dónde se almacenarán los disparos y lo devuelve por nombre */
disparos_t *disparos_crear();

/* Inserta un nuevo disparo que comienza en las posiciones (px, py) con 
  su respectivo ángulo */
bool disparo_insertar(disparos_t *disparo, float px, float py, double angulo);

/* Le avisa al la nave que pasó un instante dt de tiempo y que debe actualizar su posición
  y su estado */
bool disparo_mover(disparos_t *disparo, float dt);

/* Retorna true si hay disparos y false en caso contrario */
bool disparos_es_vacia(disparos_t *disparo);

/* Grafica los disparos en pantalla */
bool disparos_graficar(disparos_t *disparo);

/* Destrue los disparos creados */
void disparos_destruir(disparos_t *disparo);


#endif // _DISPAROS_H_
