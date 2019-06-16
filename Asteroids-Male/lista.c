#include <stdlib.h>

#include "lista.h"

typedef struct nodo{
  void *dato;
  struct nodo *sig;
}nodo_t;

typedef struct lista {
  struct nodo *prim;
}lista_t;

lista_t *lista_crear() {
  lista_t *l = malloc(sizeof(lista_t));

  if (l == NULL)
    return NULL;

  l->prim = NULL;

  return l;
}

void lista_destruir(lista_t *l, void (*destruir_dato)(void *d)) {
  struct nodo *n = l->prim;

  while (n != NULL) {
    struct nodo *sig = n->sig;

    if (*destruir_dato != NULL)
      destruir_dato(n->dato);

    free(n);

    n = sig;
  }

  free(l);
  l = NULL;
}
