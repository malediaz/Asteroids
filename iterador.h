#ifndef _ITERADOR_H_
#define _ITERADOR_H_

typedef struct iterador iterador_t;

/* Crea un nuevo iterador que apunta al primer elemento de la lista l */
iterador_t *iterador_crear(lista_t *l);

/* Destruye el iterador creado */
void iterador_destruir(iterador_t *li);

/* Devuelve el dato actual del iterador o NULL si el iterador ya se terminó */
void *iterador_actual(const iterador_t *li);

/* Incrementa el iterador y devuelve true si la lista aún no se terminó */
bool iterador_siguiente(iterador_t *li);

/* Retorna true si el iterador ya llegó al final de la lista. */
bool iterador_termino(const iterador_t *li);

/* Elimina el nodo actual de la lista y devuelve el dato contenido en ella. 
  El iterador automáticamente pasa a apuntar al elemento siguiente */
void *iterador_eliminar(iterador_t *li);

/* Inserta un nodo nuevo después de la posición actual. El iterador 
  permanece apuntando al dato actual */
bool iterador_insertar(iterador_t *li, void *dato);

void *iterador_extraer(iterador_t *li);


#endif // _ITERADOR_H_
