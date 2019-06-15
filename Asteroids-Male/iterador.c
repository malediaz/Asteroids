#include <stdlib.h>

#include "lista.h"
#include "iterador.h"

struct iterador {
  struct nodo *actual;
  struct nodo *anterior;
  lista_t *l;
};

iterador_t *lista_iterador_crear(lista_t *l) {
  iterador_t *li = malloc(sizeof(iterador_t));
  
  if (li == NULL)
    return NULL;
    
  li->actual = l->prim;
  li->anterior = NULL;
  li->l = l;
  
  return li;
}

/*
void iterador_destruir(iterador_t *li) {
  free(li->actual);
  li
} */

void *iterador_actual(const iterador_t *li) {
  return li->actual->dato;             // ?????????????
}



