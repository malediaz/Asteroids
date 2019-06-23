#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "nave.h"
#include "graficador.h"


int main() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Asteroids");

	int dormir = 0;

	// BEGIN código de Male y Agus

  nave_t *nave = nave_crear();
  nave_inicializar(nave);

  if(!graficador_inicializar("sprites.bin", renderer))
		return EXIT_FAILURE;

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
            
					case SDLK_SPACE:
            // Disparamos
            
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
		
    if(!nave_dibujar(nave))
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
  
	// Damos la información del puntaje obtenido por stdout
  //printf("\nGAME OVER\n\nSCORE: %0.f\n\n", score);

	// END código de Male y Agus

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
