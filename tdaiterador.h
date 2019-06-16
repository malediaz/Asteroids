#ifndef _TDAITERADOR_H_
#define _TDAITERADOR_H_

typedef struct nodo nodo_t;
typedef struct lista lista_t;
typedef struct iterador iterador_t;

iterador_t *lista_iterador_crear(lista_t *l);
void lista_iterador_destruir(iterador_t *li);
void *iterador_actual(const iterador_t *li);
bool lista_iterador_siguiente(iterador_t *li);
bool lista_iterador_termino(const iterador_t *li);
void *lista_extraer_primero(lista_t *l);
void *lista_iterador_eliminar(iterador_t *li);
nodo_t *nodo_crear(void *d);
bool lista_insertar_comienzo(lista_t *l, void *dato);
bool lista_iterador_insertar(iterador_t *li, void *dato);

#endif // _TDAITERADOR_H_
