#ifndef _NAVE_H_
#define _NAVE_H_

typedef struct mi_nave nave_t;


/* Crea una nave y la devuelve por nombre */
nave_t *nave_crear();

/* Destruye la nave creada */
void nave_destruir(nave_t *nave);

/* Setea en nave los valores iniciales de la misma */
void nave_inicializar(nave_t *nave);

/* Incrementa la potencia de la nave en 1000 unidades */
void nave_potencia_incrementar(nave_t *nave);

/* Dibuja la cantidad de vidas que disponemos*/
void nave_vidas_dibujar(size_t vidas);

/* Rota la nave hacia la derecha */
void nave_rotar_derecha(nave_t *nave);

/* Rota la nave hacia la izquierda */
void nave_rotar_izquierda(nave_t *nave);

/* Devuelve el ángulo actual de la nave */
double nave_angulo(nave_t *nave);

/* Devuelve la posición actual en x de la nave */
float nave_px(nave_t *nave);

/* Devuelve la posición actual en y de la nave */
float nave_py(nave_t *nave);

/* Le avisa al la nave que pasó un instante dt de tiempo y que debe actualizar su posición
  y su estado */
void nave_mover(nave_t *nave, float dt);

/* Le pide al la nave que se dibuje sobre la pantalla */
bool nave_dibujar(const nave_t *nave);


#endif // _NAVE_H_
