#ifndef _ASTEROIDES_H_
#define _ASTEROIDES_H_

typedef struct asteroide ast_t;

ast_t *asteroide_crear();

void asteroide_inicializar(ast_t *ast_actual, float radio, float x, float y, char tipo[]);

bool asteroide_ejes_inicializar(ast_t *ast, float eje_x, float eje_y);

void asteroide_ejes_elegir(int *x, int *y);

/* Grafica todos los asteroides activos en el momento */
bool asteroide_graficar(ast_t *ast);

/* Mueve los asteroides la posición correspondiente dado un dt de tiempo */
bool asteroide_mover(ast_t *ast, float dt);

float asteroide_py(ast_t *ast);

float asteroide_px(ast_t *ast);

int asteroide_radio(ast_t *ast);

char *asteroide_tipo(ast_t *ast);

bool asteroide_colisiona(ast_t *ast_actual, float x, float y);


#endif // _ASTEROIDES_H_
