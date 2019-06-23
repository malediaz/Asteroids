#ifndef _LISTA_H_
#define _LISTA_H_

typedef struct lista lista_t;
typedef struct nodo nodo_t;


/* Crea un nuevo nodo que formará parte de la lista dado un dato d
  y lo retorna por nombre */
nodo_t *nodo_crear(void *d);

/* Crea una lista y la retorna por nombre */
lista_t *lista_crear();

/* Dada una lista l, elimira el primer nodo y devuelve el dato
  almacenado en dicho nodo */
void *lista_extraer_primero(lista_t *l);

/* Dada una lista l y un dato d, se inserta un nodo al comienzo de 
  la misma. Retorna true si la inserción fue exitosa */
bool lista_insertar_comienzo(lista_t *l, void *d);

/* Dada una lista l y una función destruir_dato, libera la moemoria
  asociada a dicha lista */
void lista_destruir(lista_t *l, void (*destruir_dato)(void *d));

#endif // _LISTA_H_
