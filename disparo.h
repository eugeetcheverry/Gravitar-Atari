#ifndef DISPARO_H
#define DISPARO_H
#include <stdio.h>
#include <stdbool.h>
#include "disparo.h"
#include "lista.h"
#include "figuras.h"
#include "nave.h"

typedef struct disparo disparo_t;

//Destruye un disparo
void destruir_disparo(void* disparo);

//Crea un disparo y lo agrega en una lista
void agregar_disparo_lista(lista_t* lista, float posicion_x, float posicion_y , float angulo , bool enemigo);

//Devuelve la true si el disparo esta cerca de la figura
bool disparo_colisiona_figura(disparo_t *disparo, figura_t *figura, float escala);

//Crea disparos en la posicion de las torretas y las agrega a la lista
void disparos_de_torreta(lista_t *disparos , lista_t *torretas, nave_t *nave, float escala);

//Disminuye el tiempo de todos los disparos en la lista
//Y destruye los disparos y los objetos q golpean
void disparos_setear_iteracion(lista_t *lista, nave_t *nave, bool escudo , lista_t *torretas, lista_t *reactor , figura_t *nivel , float escala);

//Dibuja los disparos en la lista
void dibujar_disparos(lista_t *lista, void* renderer ,float f ,float centro_x, float centro_y, figura_t *figura);



#endif