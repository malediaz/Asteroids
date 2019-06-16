#include <stdlib.h>
#include <stdbool.h>
#include "tdaiterador.h"

typedef struct nodo{

  void *dato;
  struct nodo *sig;
}nodo_t;

typedef struct lista{

  nodo_t *prim;
}lista_t;

typedef struct iterador{

  nodo_t *n;    //nodo actual
  nodo_t *ant;  //nodo anterior
  lista_t *l;

}iterador_t;

iterador_t *lista_iterador_crear(lista_t *l){

  iterador_t *li = malloc(sizeof(iterador_t));

  if(li == NULL)
    return NULL;

  li->l = l;
  li->n = l->prim;
  li->ant = NULL;

  return li;
}

void lista_iterador_destruir(iterador_t *li){

  free(li);
}

void *iterador_actual(const iterador_t *li){

  if(li == NULL)
    return NULL;

  return li->n->dato;
}

bool lista_iterador_siguiente(iterador_t *li){

  if(li->n == NULL)
    return false;

  if(li->n->sig != NULL){

    li->ant = li->n;
    li->n = li->n->sig;

    return true;
  }

  return false;
}

bool lista_iterador_termino(const iterador_t *li){

  if(li->n == NULL)
    return true;

  return false;

}

void *lista_extraer_primero(lista_t *l){

  if(l->prim == NULL)
    return NULL;

  nodo_t *aux = l->prim;
  void *dato = aux->dato;

  l->prim = aux->sig;

  free(aux);
  return dato;

}

void *lista_iterador_eliminar(iterador_t *li){


  if(li->n == NULL)
   return NULL;

  if(li->ant == NULL){

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

nodo_t *nodo_crear(void *d){

  nodo_t *n = malloc(sizeof(nodo_t));

  if(n == NULL)
    return NULL;

  n->sig = NULL;
  n->dato = d;

  return n;
}

bool lista_insertar_comienzo(lista_t *l, void *dato){

  nodo_t *n = nodo_crear(dato);

  if(n == NULL)
    return false;

  n->sig = l->prim;
  l->prim = n;

  return true;

}

bool lista_iterador_insertar(iterador_t *li, void *dato){

  if(li->n == NULL)
    return false;

  nodo_t *a = nodo_crear(dato);

  if(a == NULL)
    return false;

  a->sig = li->n->sig;
  li->n->sig = a;

  return true;

}
