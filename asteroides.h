#ifndef _ASTEROIDES_H_
#define _ASTEROIDES_H_

typedef struct asteroides asteroides_t;

/* Crea los asteroideds a utilizar y los devuelve por nombre */
asteroides_t *asteroides_crear();

/* Destruye la lista creada */
void asteroides_destruir(asteroides_t *ast);

#endif // _ASTEROIDES_H_
