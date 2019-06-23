#ifndef _DIBUJAR_H_
#define _DIBUJAR_H_


#define MAX_CADENA 9999
#define MARGEN_SUP 30
#define FLECHAS_ESPACIO 230
#define VALORES_ESPACIO 210
#define VALORES_MARGEN_IZQ (MSJ_INFO_MARGEN_IZQ + VALORES_ESPACIO / 2)
#define VALORES_MARGEN_DER (MSJ_INFO_MARGEN_DER + VALORES_ESPACIO)
#define FIGURA_ESCALA 1
#define MSJ_ALTO 20


/* Dado una cadena, con su posicion inicial y su escala,
  se imprimen los caracteres correspondientes en pantalla, a partir de un margen superior 
  fijo para la impresión de los caracteres */
void dibujar_cadena(char *cadena, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y);

/* Dado un valor, con su posicion inicial y su escala,
 y se imprimen los caracteres correspondientes en pantalla, a partir de un margen
   superior fijo */
void valores_dibujar(float valor, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y);



#endif // _DIBUJAR_H_
