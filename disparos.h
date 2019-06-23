#ifndef _DISPAROS_H_
#define _DISPAROS_H_

typedef struct balas bala_t;
typedef struct disparos disparos_t;

/* Le avisa al la nave que pasó un instante dt de tiempo y que debe actualizar su posición
  y su estado */
void disparo_mover(disparos_t *disparo, float dt);

/* Le pide al la nave que se dibuje sobre la pantalla */
bool disparo_dibujar(const bala_t *bala);

#endif // _NAVE_H_
