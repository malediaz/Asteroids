#ifndef _CONFIG_H_
#define _CONFIG_H_

#define PI 3.14159265358979323846

#define VENTANA_ANCHO 1000
#define VENTANA_ALTO 700

#define JUEGO_FPS 100
#define DT 0.01

#define DISPARO_VELOCIDAD 1000
#define DISPARO_VIDA 0.7

#define ASTEROIDES_INICIALES 4
#define ASTEROIDES_NUEVOS 2

#define ROCK_MAX_R 32
#define ROCK_MIN_R (ROCK_MAX_R / 4)

#define NAVE_X_INICIAL (VENTANA_ANCHO / 2)
#define NAVE_Y_INICIAL (VENTANA_ALTO / 2)
#define NAVE_VX_INICIAL 0
#define NAVE_VY_INICIAL 0
#define NAVE_ANGULO_INICIAL 0
#define NAVE_ROTACION_PASO (PI/20)
#define NAVE_POTENCIA_PASO 1000
#define NAVE_POTENCIA_INICIAL 0
#define NAVE_ESCALA 1
#define NAVE_VIDAS_INICIALES 4


#endif // _CONFIG_H_
