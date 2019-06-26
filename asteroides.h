#ifndef _ASTEROIDES_H_
#define _ASTEROIDES_H_

typedef struct asteroides asteroides_t;


/* Crea los asteroideds a utilizar y los devuelve por nombre */
asteroides_t *asteroides_crear();

/* Destruye la lista creada */
void asteroides_destruir(asteroides_t *ast);

/* Inicializa los asteroides correspondientes al inicio de la partida */
bool asteroides_primeros_insertar(asteroides_t *ast);

/* Grafica todos los asteroides activos en el momento */
bool asteroides_graficar(asteroides_t *ast);

/* Mueve los asteroides la posición correspondiente dado un dt de tiempo */
bool asteroides_mover(asteroides_t *ast, float dt);

#endif // _ASTEROIDES_H_
