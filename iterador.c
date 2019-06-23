#include <stdlib.h>
#include <stdbool.h>

#include "lista.h"
#include "iterador.h"

struct nodo {
  void *dato;
  struct nodo *sig;
};

struct lista {
  nodo_t *prim;
};

struct iterador {
  nodo_t *n;    //nodo actual
  nodo_t *ant;  //nodo anterior
  lista_t *l;

};


iterador_t *iterador_crear(lista_t *l) {
  iterador_t *li = malloc(sizeof(iterador_t));

  if (li == NULL)
    return NULL;

  li->l = l;
  li->n = l->prim;
  li->ant = NULL;

  return li;
}


void iterador_destruir(iterador_t *li) {
  free(li);
}


void *iterador_actual(const iterador_t *li){
  if (li == NULL)
    return NULL;

  return li->n->dato;
}


bool iterador_siguiente(iterador_t *li){
  if (li->n == NULL)
    return false;

  li->ant = li->n;
  li->n = li->n->sig;

  return true;
}


bool iterador_termino(const iterador_t *li){
  if (li->n == NULL)
    return true;

  return false;
}


void *iterador_eliminar(iterador_t *li){
  if (li->n == NULL)
   return NULL;

  if (li->ant == NULL) {

    li->n = li->n->sig;
    lista_extraer_primero(li->l);

  }

  void *dato = li->n->dato;
  nodo_t *aux = li->n->sig;

  li->ant->sig = li->n->sig;
  free(li->n);
  li->n = aux;

  return dato;
}


bool iterador_insertar(iterador_t *li, void *dato) {
  if (li->n == NULL)
    return false;

  nodo_t *a = nodo_crear(dato);

  if (a == NULL)
    return false;

  a->sig = li->n->sig;
  li->n->sig = a;

  return true;

}
