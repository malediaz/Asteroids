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

int main(){
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Atari Asteroids");


	// BEGIN código de Male y Agus
  
  srand(time(NULL));
  
  bool press_start = true;
  bool first_game = true;
  bool nave_dibujada = true;
	unsigned int score = 0;
	unsigned int high_score = 0;
	size_t nasteroides = ASTEROIDES_NUEVOS;
	size_t vidas = 0;
	int dormir = 0;
  
  
  nave_t *nave = nave_crear();
  if(nave == NULL)
    return EXIT_FAILURE;

  nave_inicializar(nave);

	lista_t *asteroides = lista_crear();
  if(asteroides == NULL){
    nave_destruir(nave);

    return EXIT_FAILURE;
  }

	lista_t *disp = lista_crear();
  if(disp == NULL){
    nave_destruir(nave);
    lista_destruir(asteroides, NULL);

    return EXIT_FAILURE;
  }

  if(!graficador_inicializar("sprites.bin", renderer)){
    nave_destruir(nave);
    lista_destruir(asteroides, NULL);
    lista_destruir(disp, NULL);

		return EXIT_FAILURE;
  }

  float px = 0, py = 0;
  double angulo = 0;
  int eje_x = 0, eje_y = 0;
  float tracker;

	// END código de Male y Agus

	unsigned int ticks = SDL_GetTicks();

	while(1){
		if(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT)
				break;

      if(event.type == SDL_KEYDOWN){

				// BEGIN código de Male y Agus

        switch(event.key.keysym.sym){
					case SDLK_UP:
            if(!press_start && tracker > 1)
              nave_potencia_incrementar(nave);

            break;

					case SDLK_SPACE:
            if (!press_start && tracker > 1) {
              px = nave_px(nave);
              py = nave_py(nave);
              angulo = nave_angulo(nave);
            
              disparo_t *bala = disparo_crear();
              if(bala == NULL){
                nave_destruir(nave);
                lista_destruir(disp, free);
                lista_destruir(asteroides, free);
                graficador_finalizar();

                return EXIT_FAILURE;
              }

              disparo_inicializar(bala, px, py, angulo);
              lista_insertar_comienzo(disp, bala);
            }
            
              break;
            
					case SDLK_LEFT:
            if(!press_start && tracker > 1)
              nave_rotar_izquierda(nave);

            break;

					case SDLK_RIGHT:
            if(!press_start)
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
    
    if(press_start) {
      tracker = 1;
      if(first_game) 
        dibujo_mensajes_inicio_juego(renderer);
      else {
        if(score > high_score)
          high_score = score;
        
        dibujo_mensajes_fin_juego(score, high_score, renderer);
      }
        
      if(event.key.keysym.sym == SDLK_SPACE) {
        press_start = false;
        vidas = NAVE_VIDAS_INICIALES;
        score = 0;
        nasteroides = 0;

        for(size_t i = 0; i < ASTEROIDES_INICIALES; i++){                             
          ast_t *ast = asteroide_crear();
          if(ast == NULL) {
            nave_destruir(nave);
            lista_destruir(asteroides, NULL);

            return EXIT_FAILURE;
          }
          
          asteroide_ejes_elegir(&eje_x, &eje_y);
          asteroide_ejes_inicializar(ast, eje_x, eje_y);

          lista_insertar_comienzo(asteroides, ast);
        }
        
        first_game = false;
      }
    }
    else {
      if(tracker >= 1 && nave_dibujada) {
        nave_dibujar(nave);
        nave_mover(nave, DT);
      }
      
      tracker += DT;
      
      nave_vidas_dibujar(vidas);
      dibujo_mensajes_en_juego(score, high_score, renderer);

      // Iterador para disparos

      iterador_t *disp_li = iterador_crear(disp);
      if(disp_li == NULL)
        break;

      for( ; !iterador_termino(disp_li); iterador_siguiente(disp_li)){
        disparo_t *disp_actual = iterador_actual(disp_li);
        disparo_mover(disp_actual, DT);

        if(disparo_vida(disp_actual) > DISPARO_VIDA){
          iterador_eliminar(disp_li);

          break;
        }

        disparo_dibujar(disp_actual);
      }

      iterador_destruir(disp_li);

      // Iterador para asteroides
      iterador_t *ast_li = iterador_crear(asteroides);
      if(ast_li == NULL)
        return false;

      for( ; !iterador_termino(ast_li); iterador_siguiente(ast_li)){
        ast_t *ast_actual = iterador_actual(ast_li);

        asteroide_mover(ast_actual, DT);
        asteroide_dibujar(ast_actual);
      
        px = nave_px(nave);
        py = nave_py(nave);
      
        if(!lista_es_vacia(disp)){
          iterador_t *disp_li = iterador_crear(disp);
          if(disp_li == NULL){
            nave_destruir(nave);
            lista_destruir(asteroides, free);
            iterador_destruir(ast_li);
            iterador_destruir(disp_li);
            graficador_finalizar();

            return EXIT_FAILURE;
          }

          for ( ; !iterador_termino(disp_li); iterador_siguiente(disp_li)){
            disparo_t *disp_actual = iterador_actual(disp_li);

            px = disparo_px(disp_actual);
            py = disparo_py(disp_actual);

            if(asteroide_colisiona(ast_actual, px, py)){
              iterador_eliminar(disp_li);

              int ast_radio = asteroide_radio(ast_actual);
              float ast_px = asteroide_px(ast_actual);
              float ast_py = asteroide_py(ast_actual);
              char *ast_tipo = asteroide_tipo(ast_actual);

              iterador_eliminar(ast_li);

              switch(ast_radio){
                case ROCK_MAX_R:
                  score += 20;
                  
                  break;

                case ROCK_MAX_R / 2:
                  score += 50;
                  
                  break;

                case ROCK_MAX_R / 4:
                  score += 100;
							
                  break;
              }

              if(ast_radio > ROCK_MIN_R){
                for(size_t i = 0; i < ASTEROIDES_NUEVOS; i++){
                  ast_t *ast = asteroide_crear();             
                  if(ast == NULL) {
                    nave_destruir(nave);
                    lista_destruir(disp, free);
                    lista_destruir(asteroides, free);
                    iterador_destruir(ast_li);
                    iterador_destruir(disp_li);
                    graficador_finalizar();

                    return EXIT_FAILURE;
                  }

                  asteroide_inicializar(ast, ast_radio / 2, ast_px, ast_py, ast_tipo);
                  iterador_insertar(ast_li, ast);
                }
              }
              
              break;
            }
          }

          iterador_destruir(disp_li);
        }
      
        px = nave_px(nave);
        py = nave_py(nave);
      
        if(asteroide_colisiona(ast_actual, px, py) && tracker >= 1){
          if(nave_dibujada) {
            iterador_eliminar(ast_li);
            nave_inicializar(nave);
            vidas--;
            tracker = 0;
            nave_dibujada = false;
        
            break;
          }
        }
        else
          nave_dibujada = true;
      }

      iterador_destruir(ast_li);

      if(lista_es_vacia(asteroides)){
        asteroides = lista_crear();
        nasteroides += 2;

        for(size_t i = 0; i < (ASTEROIDES_INICIALES + nasteroides); i++){
          ast_t *ast = asteroide_crear();
          if(ast == NULL) {
            nave_destruir(nave);
            lista_destruir(asteroides, free);

            return EXIT_FAILURE;
          }

          asteroide_ejes_elegir(&eje_x, &eje_y);
          asteroide_ejes_inicializar(ast, eje_x, eje_y);

          lista_insertar_comienzo(asteroides, ast);
        }
      }
      
		//Finalizacion de la partida
    
      if(vidas == 0) {
        lista_destruir(asteroides, free);
        asteroides = lista_crear();
        press_start = true;
      }
    }
  
    // END código de Male y Agus

    dibujo_fiuba_inc(renderer);
    
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
  lista_destruir(disp, free);
  lista_destruir(asteroides, free);
  graficador_finalizar();

	// END código de Male y Agus

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
