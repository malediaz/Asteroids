#ifndef _DIBUJAR_H_
#define _DIBUJAR_H_

/*La voy a utilizar para poder dibujar las palabras del juego*/
void dibujo_cadena(char cad[], float f, float cx, float cy, SDL_Renderer *renderer);

/*Esta funcion la voy a utilizar para dibujar las variables que dependen del 
comportamiento del juego*/
void dibujo_num(int num, int escala, float cx, float cy, SDL_Renderer *renderer);

void dibujo_mensajes_inicio_juego(SDL_Renderer *renderer);

void dibujo_mensajes_fin_juego(unsigned int score, unsigned int high_score, SDL_Renderer *renderer);

void dibujo_mensajes_en_juego(unsigned int score, unsigned int high_score, SDL_Renderer *renderer);

void dibujo_fiuba_inc(SDL_Renderer *renderer);

#endif // _DIBUJAR_H_

