#ifndef _DISPAROS_H_
#define _DISPAROS_H_

typedef struct disparo disparo_t;


/* Crea un disparo */
disparo_t *disparo_crear();

/* Inicializa un disparo en una posición y e y con un angulo dado en cuya dirección viajará */
void disparo_inicializar(disparo_t *disp, float px, float py, double angulo);

/* Devuelve el tiempo de vida de un disparo */
float disparo_vida(disparo_t *disp);

/* Devuelve la posición en x de un disparo */
float disparo_px(disparo_t *disp);

/* Devuelve la posición en y de un disparo */
float disparo_py(disparo_t *disp);

/* Le avisa al la nave que pasó un instante dt de tiempo y que debe actualizar su 
  posición y su estado */
bool disparo_mover(disparo_t *disp, float dt);

/* Grafica los disparos en pantalla */
bool disparo_dibujar(disparo_t *disp);


#endif // _DISPAROS_H_
