#ifndef _DIBUJAR_H_
#define _DIBUJAR_H_

/* Dibuja los mensajes en la pantalla de inicio */
void dibujo_mensajes_inicio_juego(SDL_Renderer *renderer);

/* Una vez que se termina el juego, dibuja el lema GAME OVER, e informa el puntaje actual y
  el más alto*/
void dibujo_mensajes_fin_juego(unsigned int score, unsigned int high_score, SDL_Renderer *renderer);

/* Dibuja los mensajes correspondientes a la información del juego cuando está en transcurso */
void dibujo_mensajes_en_juego(unsigned int score, unsigned int high_score, SDL_Renderer *renderer);

/* DIbuja el lema 2019 FIUBA INC en pantalla */
void dibujo_fiuba_inc(SDL_Renderer *renderer);

#endif // _DIBUJAR_H_

