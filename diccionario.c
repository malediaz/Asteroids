#include <stdio.h>
#include <stdlib.h>

#include "diccionario.h"
#include "caracteres.h"

typedef enum caracter {A ,B ,C ,D ,E ,F ,G ,H ,I ,J ,K ,L ,M ,N ,O ,P ,Q ,R ,S ,T , U ,V ,W ,X ,
	Y ,Z ,NUM0 ,NUM1 ,NUM2 ,NUM3 ,NUM4 ,NUM5 ,NUM6 ,NUM7 ,NUM8 ,NUM9 , DERECHA, IZQUIERDA, ARRIBA, ABAJO, ESPACIO}car_t;


matrizc_t caracteres[] = {

	[A] = caracter_a, [N] = caracter_n, [NUM0] = caracter_0, [DERECHA] = caracter_derecha,
	[B] = caracter_b, [O] = caracter_o, [NUM1] = caracter_1, [IZQUIERDA] = caracter_izquierda,
	[C] = caracter_c, [P] = caracter_p, [NUM2] = caracter_2,
	[D] = caracter_d, [Q] = caracter_q, [NUM3] = caracter_3,
	[E] = caracter_e, [R] = caracter_r, [NUM4] = caracter_4,
	[F] = caracter_f, [S] = caracter_s, [NUM5] = caracter_5,
	[G] = caracter_g, [T] = caracter_t, [NUM6] = caracter_6,
	[H] = caracter_h, [U] = caracter_u, [NUM7] = caracter_7,
	[I] = caracter_i, [V] = caracter_v, [NUM8] = caracter_8,
	[J] = caracter_j, [W] = caracter_w, [NUM9] = caracter_9,
	[K] = caracter_k, [X] = caracter_x, [ARRIBA] = caracter_arriba,
	[L] = caracter_l, [Y] = caracter_y, [ABAJO] = caracter_abajo,
	[M] = caracter_m, [Z] = caracter_z, [ESPACIO] = caracter_espacio,
};

const int caracter[] = {

 	[A] = 'A', [N] = 'N', [NUM0] = '0', [DERECHA] = '>',
	[B] = 'B', [O] = 'O', [NUM1] = '1', [IZQUIERDA] = '<',
	[C] = 'C', [P] = 'P', [NUM2] = '2',
	[D] = 'D', [Q] = 'Q', [NUM3] = '3',
	[E] = 'E', [R] = 'R', [NUM4] = '4',
	[F] = 'F', [S] = 'S', [NUM5] = '5',
	[G] = 'G', [T] = 'T', [NUM6] = '6',
	[H] = 'H', [U] = 'U', [NUM7] = '7',
	[I] = 'I', [V] = 'V', [NUM8] = '8',
	[J] = 'J', [W] = 'W', [NUM9] = '9',
	[K] = 'K', [X] = 'X', [ARRIBA] = '^',
	[L] = 'L', [Y] = 'Y', [ABAJO] = 'v',
	[M] = 'M', [Z] = 'Z', [ESPACIO] = ' ',

};

const int tamagno_caracter[] = {7 ,12 ,4 ,7 ,7 ,6 ,7 ,6 ,6 ,4 ,6 ,3 ,5 ,4 ,5 ,5 ,
	9 ,7 ,6 ,4 ,4 ,3 ,5 ,5 ,5 ,4 ,5 ,2 ,6 ,7 ,5 ,6 ,5 ,3 ,7 ,5 ,5 ,5 ,5 ,5 ,1 };

size_t caracter_tam = sizeof(caracter) / sizeof(caracter[0]);

matrizc_t caracter_a_matriz(char c){

	size_t i;
	for (i = 0; i < caracter_tam ; i++){
		if(caracter[i] == c)
			return caracteres[i];
	}
	return NULL;
}

size_t caracter_a_tamagno(char c){

	size_t i;
	for (i = 0; i < caracter_tam ; i++){
		if(caracter[i] == c)
			return tamagno_caracter[i];
	}
	return caracter_tam;
}
