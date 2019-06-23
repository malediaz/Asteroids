#ifndef _GRAFICADOR_H_
#define _GRAFICADOR_H_


/* Inicializa el módulo. Recibe fn que es el nombre del archivo de sprites y un renderer r .
Esta función debe ser llamada antes de poder acceder a las demás funciones del módulo. */
bool graficador_inicializar(const char *fn, SDL_Renderer *r);

/* Finaliza el módulo. Deben liberarse todos los recursos asociados. Después de llamar a esta
función el módulo debe quedar como antes de llamar a graficador_inicializar() */
void graficador_finalizar();

/* Dibuja el sprite de nombre nombre escalado según escala , rotado según angulo en la posición
x , y de la pantalla (tomando como (0, 0) la esquina inferior izquierda). */
void graficador_ajustar_variables(float *x, float *y);

/* Recibe dos variables x e y y las ajusta dentro del ancho y alto de la pantalla */
bool graficador_dibujar(const char *nombre, float escala, float x, float y, float angulo);


#endif // _GRAFICADOR_H_
