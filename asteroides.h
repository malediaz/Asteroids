#ifndef _ASTEROIDES_H_
#define _ASTEROIDES_H_

typedef struct asteroide ast_t;

/* Crea una asteroide y lo devuelve por nombre */
ast_t *asteroide_crear();

/* Inicializa un asteroide con velocidades y direcciones random en un rango establecido
  con un radio, una posición en x e y y un tipo dados */
void asteroide_inicializar(ast_t *ast_actual, float radio, float x, float y, char tipo[]);

/* Elige el eje sobre el cual se creará un asteroide al inicio de cada juego */
void asteroide_ejes_elegir(int *x, int *y);

/* Luego de llamar a asteroide_ejes_inicializar, se llama a esta función para 
  inicializar los asteroides con el radio máximo establecido para el principio
  del juego */
bool asteroide_ejes_inicializar(ast_t *ast, float eje_x, float eje_y);

/* Dibuja un asteroide en pantalla */
bool asteroide_dibujar(ast_t *ast);

/* Mueve un asteroide dado un dt de tiempo */
bool asteroide_mover(ast_t *ast, float dt);


float asteroide_py(ast_t *ast);

float asteroide_px(ast_t *ast);

int asteroide_radio(ast_t *ast);

char *asteroide_tipo(ast_t *ast);

bool asteroide_colisiona(ast_t *ast_actual, float x, float y);


#endif // _ASTEROIDES_H_
