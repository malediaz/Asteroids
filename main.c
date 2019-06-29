#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "config.h"
#include "nave.h"
#include "graficador.h"
#include "disparos.h"
#include "asteroides.h"
#include "dibujar.h"
#include "iterador.h"
#include "lista.h"

int main() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Atari Asteroids");

	int dormir = 0;

	// BEGIN código de Male y Agus

  srand(time(NULL));

	size_t score = 0;
	size_t best_score = 0;

  nave_t *nave = nave_crear();
  if(nave == NULL)
    return EXIT_FAILURE;

  nave_inicializar(nave);
  nave_setear_vidas_iniciales(nave);

	lista_t *ast = lista_crear();
  if (ast == NULL) {
    nave_destruir(nave);
    
    return EXIT_FAILURE;
  }
  
  for (size_t i = 0; i < ASTEROIDES_INICIALES / 2; i++) {
    ast_t *ast1 = asteroide_crear();
    if (ast1 == NULL) {
      nave_destruir(nave);
      lista_destruir(ast, NULL);
      
      return EXIT_FAILURE;
    }
      
    ast_t *ast2 = asteroide_crear();
    if (ast2 == NULL) {
      nave_destruir(nave);
      lista_destruir(ast, NULL);
      
      return EXIT_FAILURE;
    }
      
    asteroide_ejes_inicializar(ast1, 0, 1);
    asteroide_ejes_inicializar(ast2, 1, 0);
    
    lista_insertar_comienzo(ast, ast1);
    lista_insertar_comienzo(ast, ast2);
  }

	lista_t *disp = lista_crear();
  if(disp == NULL){
    nave_destruir(nave);
    lista_destruir(ast, NULL);

    return EXIT_FAILURE;
  }

  if(!graficador_inicializar("sprites.bin", renderer)) {
    nave_destruir(nave);
    lista_destruir(ast, NULL);
    lista_destruir(disp, NULL);

		return EXIT_FAILURE;
  }

    float px = 0, py = 0;
    double angulo = 0;
    //int disp_vida = 0;

	// END código de Male y Agus

	unsigned int ticks = SDL_GetTicks();

	while (1){
		if (SDL_PollEvent(&event)) {
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

            disparo_t *bala = disparo_crear();
            if (bala == NULL) {
              nave_destruir(nave);
            	lista_destruir(disp, NULL);
              lista_destruir(ast, NULL);
              graficador_finalizar();

              return EXIT_FAILURE;
            }
            
            disparo_inicializar(bala, px, py, angulo);
            lista_insertar_comienzo(disp, bala);
            
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
    nave_dibujar(nave);

		nave_vidas_dibujar(nave);

		dibujo_num(best_score, 2, VENTANA_ANCHO / 2, 50, renderer);
		dibujo_num(score, 4, 180, 60, renderer);
		dibujo_cadena("2019 FIUBA INC", 2, VENTANA_ANCHO / 2 - VENTANA_ANCHO / 20, 650, renderer);

    // Iterador para disparos
    
    iterador_t *disp1_li = iterador_crear(disp);
    if(disp1_li == NULL)
      
      // Validar
      
      return EXIT_FAILURE;
    
    for( ; !iterador_termino(disp1_li); iterador_siguiente(disp1_li)) {
      disparo_t *disp1_actual = iterador_actual(disp1_li);
      disparo_mover(disp1_actual, DT);
      
      if(disparo_vida(disp1_actual) > DISPARO_VIDA) {
        iterador_eliminar(disp1_li);
        
        break;
      }
      
      disparo_dibujar(disp1_actual);
    }
       
    iterador_destruir(disp1_li);
    
    
    // Iterador para asteroides
    iterador_t *ast_li = iterador_crear(ast);
    if (ast_li == NULL)
      return false;
      
    for ( ; !iterador_termino(ast_li); iterador_siguiente(ast_li)) {
      ast_t *ast_actual = iterador_actual(ast_li);
      
      asteroide_mover(ast_actual, DT);
      asteroide_graficar(ast_actual);
      
      if(!lista_es_vacia(disp)) {
        iterador_t *disp_li = iterador_crear(disp);
        if (disp_li == NULL) {
          nave_destruir(nave);
          lista_destruir(ast, free);
          iterador_destruir(ast_li);
          iterador_destruir(disp_li);
          graficador_finalizar();
            
          return EXIT_FAILURE;
        }            

        for ( ; !iterador_termino(disp_li); iterador_siguiente(disp_li)) {
          disparo_t *disp_actual = iterador_actual(disp_li);

          px = disparo_px(disp_actual);
          py = disparo_py(disp_actual);
          
          if (asteroide_colisiona(ast_actual, px, py)) {
            iterador_eliminar(disp_li);
            
            float ast_radio = asteroide_radio(ast_actual);
            float ast_px = asteroide_px(ast_actual);
            float ast_py = asteroide_py(ast_actual);
            char *ast_tipo = asteroide_tipo(ast_actual);
            
            iterador_eliminar(ast_li);;
            
            if (ast_radio > ROCK_MIN_R) {
              ast_t *ast1 = asteroide_crear();
              if (ast1 == NULL) {
                nave_destruir(nave);
                lista_destruir(disp, free);
                lista_destruir(ast, free);
                iterador_destruir(ast_li);
                iterador_destruir(disp_li);
                graficador_finalizar();
                
                return EXIT_FAILURE;
              }
                
              ast_t *ast2 = asteroide_crear();
              if (ast2 == NULL) {
                nave_destruir(nave);
                lista_destruir(disp, free);
                lista_destruir(ast, free);
                iterador_destruir(ast_li);
                iterador_destruir(disp_li);
                graficador_finalizar();

                return EXIT_FAILURE;
              }
              
              asteroide_inicializar(ast1, ast_radio / 2, ast_px, ast_py, ast_tipo);
              asteroide_inicializar(ast2, ast_radio / 2, ast_px, ast_py, ast_tipo);
            
              iterador_insertar(ast_li, ast1);
              iterador_insertar(ast_li,ast2);
              
            }
            
            break;
          }
        }
        
        iterador_destruir(disp_li);
      }
      
      px = nave_px(nave);
      py = nave_py(nave);
      
      if(asteroide_colisiona(ast_actual, px, py)) {
        nave_inicializar(nave);
        lista_destruir(disp, free);
        lista_destruir(ast, free);
        
        ast = lista_crear();
        disp = lista_crear();
      
        for (size_t i = 0; i < ASTEROIDES_INICIALES / 2; i++) {
          ast_t *ast1 = asteroide_crear();
          if (ast1 == NULL) {
            nave_destruir(nave);
            lista_destruir(ast, NULL);
      
            return EXIT_FAILURE;
          }
      
          ast_t *ast2 = asteroide_crear();
          if (ast2 == NULL) {
            nave_destruir(nave);
            lista_destruir(ast, NULL);
      
            return EXIT_FAILURE;
          }
      
          asteroide_ejes_inicializar(ast1, 0, 1);
          asteroide_ejes_inicializar(ast2, 1, 0);
    
          lista_insertar_comienzo(ast, ast1);
          lista_insertar_comienzo(ast, ast2);
        }
        
        dibujo_cadena("DESTROYED", 10, 250, VENTANA_ALTO / 2, renderer);
        nave_vidas_decrementar(nave);
        
        dormir = 1500;
                
        break;
      }
    }
    
    iterador_destruir(ast_li);
    
    
		//Finalizacion del juego
    
    if (lista_es_vacia(ast)) {
      nave_inicializar(nave);
      lista_destruir(disp, free);
      lista_destruir(ast, free);
      
      ast = lista_crear();
      disp = lista_crear();
      
      for (size_t i = 0; i < ASTEROIDES_INICIALES / 2; i++) {
        ast_t *ast1 = asteroide_crear();
        if (ast1 == NULL) {
          nave_destruir(nave);
          lista_destruir(ast, NULL);
      
          return EXIT_FAILURE;
        }
      
        ast_t *ast2 = asteroide_crear();
        if (ast2 == NULL) {
          nave_destruir(nave);
          lista_destruir(ast, NULL);
    
          return EXIT_FAILURE;
        }
      
        asteroide_ejes_inicializar(ast1, 0, 1);
        asteroide_ejes_inicializar(ast2, 1, 0);
    
        lista_insertar_comienzo(ast, ast1);
        lista_insertar_comienzo(ast, ast2);
      }
      
      dibujo_cadena("ASTEROIDS DESTROYED", 7, 180, VENTANA_ALTO / 2, renderer);

      dormir = 1500;
    }


    // END código de Male y Agus


    SDL_RenderPresent(renderer);
		ticks = SDL_GetTicks() - ticks;
		if(dormir) {
			SDL_Delay(dormir);
			dormir = 0;
      
    if(nave_vidas(nave) == 0)
      break;
		}
		else if(ticks < 1000 / JUEGO_FPS)
			SDL_Delay(1000 / JUEGO_FPS - ticks);
		ticks = SDL_GetTicks();
	}

	// BEGIN código de Male y Agus

  nave_destruir(nave);
  lista_destruir(disp, free);
  lista_destruir(ast, free);
  graficador_finalizar();

	// Damos la información del puntaje obtenido por stdout
  
  printf("\nGAME OVER\n\nSCORE: %zd\n\n", best_score);

	// END código de Male y Agus

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
  
	return 0;
}
