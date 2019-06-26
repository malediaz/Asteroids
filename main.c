#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "config.h"
#include "nave.h"
#include "graficador.h"
#include "disparos.h"
#include "asteroides.h"


int main() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Asteroids");

	int dormir = 0;

	// BEGIN código de Male y Agus
  
  srand(time(NULL));

  nave_t *nave = nave_crear();
  if (nave == NULL)
    return EXIT_FAILURE;
    
  nave_inicializar(nave);
  
  
  asteroides_t *ast = asteroides_crear();
  if (ast == NULL) {
    nave_destruir(nave);
    
    return EXIT_FAILURE;
  }
  
  if (!asteroides_primeros_insertar(ast))
    return EXIT_FAILURE;
  
  
  disparos_t *disp = disparos_crear();
  if (disp == NULL) {
    nave_destruir(nave);
    asteroides_destruir(ast);
    
    return EXIT_FAILURE;
  }

  if(!graficador_inicializar("sprites.bin", renderer)) {
    nave_destruir(nave);
    asteroides_destruir(ast);
    disparos_destruir(disp);
    
		return EXIT_FAILURE;
  }
    
    float px = 0, py = 0;
    double angulo = 0;

	// END código de Male y Agus

	unsigned int ticks = SDL_GetTicks();
	while(1) {   
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
      
      if (event.type == SDL_KEYDOWN) {

				// BEGIN código de Male y Agus

        switch(event.key.keysym.sym) {
					case SDLK_UP:
            nave_potencia_incrementar(nave);
            
            break;
            
					case SDLK_SPACE:
            px = nave_px(nave);
            py = nave_py(nave);
            angulo = nave_angulo(nave);
            
            if (!disparo_insertar(disp, px, py, angulo)) {
              nave_destruir(nave);
              disparos_destruir(disp);
              asteroides_destruir(ast);
              graficador_finalizar();
              
              return EXIT_FAILURE;
            }
            
            break;

					case SDLK_LEFT:
            nave_rotar_izquierda(nave);
            
            break;
          
					case SDLK_RIGHT:
            nave_rotar_derecha(nave);

            break;
				}
				// END código de Male y Agus

			}
			continue;
		}
        	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        	SDL_RenderClear(renderer);
        	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);


		// BEGIN código de Male y Agus
    
		nave_mover(nave, DT);

    if (!disparos_es_vacia(disp)) {    
      disparo_mover(disp, DT);
      disparos_graficar(disp);    
    }

    if(!nave_dibujar(nave)) {
      nave_destruir(nave);
      disparos_destruir(disp);
      asteroides_destruir(ast);
      graficador_finalizar();

			return EXIT_FAILURE;
    }
    
    asteroides_mover(ast, DT);
    
    if (!asteroides_graficar(ast)) 
      return EXIT_FAILURE;
    
		
    // END código de Male y Agus


    SDL_RenderPresent(renderer);
		ticks = SDL_GetTicks() - ticks;
		if(dormir) {
			SDL_Delay(dormir);
			dormir = 0;
		}
		else if(ticks < 1000 / JUEGO_FPS)
			SDL_Delay(1000 / JUEGO_FPS - ticks);
		ticks = SDL_GetTicks();
	}

	// BEGIN código de Male y Agus
  
  nave_destruir(nave);
  disparos_destruir(disp);
  asteroides_destruir(ast);
  graficador_finalizar();
  
	// Damos la información del puntaje obtenido por stdout
  //printf("\nGAME OVER\n\nSCORE: %0.f\n\n", score);

	// END código de Male y Agus

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
