#include <stdlib.h>
#include <stdbool.h>

#include "lista.h"

struct nodo {
  void *dato;
  struct nodo *sig;
};

struct lista {
  nodo_t *prim;
};

nodo_t *nodo_crear(void *d) {
  nodo_t *n = malloc(sizeof(nodo_t));

  if (n == NULL)
    return NULL;

  n->sig = NULL;
  n->dato = d;

  return n;
}

lista_t *lista_crear() {
  lista_t *l = malloc(sizeof(lista_t));
  
  if (l == NULL)
    return NULL;
    
  l->prim = NULL;
  
  return l;
}

void *lista_extraer_primero(lista_t *l){
  if (l->prim == NULL)
    return NULL;

  nodo_t *aux = l->prim;
  void *dato = aux->dato;

  l->prim = aux->sig;
  free(aux);
  
  return dato;
}


bool lista_insertar_comienzo(lista_t *l, void *d){
  nodo_t *n = nodo_crear(d);

  if (n == NULL)
    return false;

  n->sig = l->prim;
  l->prim = n;

  return true;

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
}

