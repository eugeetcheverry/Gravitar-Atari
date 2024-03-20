#ifndef REACTOR_H
#define REACTOR_H

#include "reactor.h"
#include "lista.h"
#include "figuras.h"
#include "disparo.h"

typedef struct reactor reactor_t;

// Crea un reactor con tiempo=5
reactor_t *crear_reactor(figura_t *reactor_figura, float pos_x, float pos_y, float angulo);

//Destruye el reactor 
void reactor_destruir(void *reactor);

//Dibuja el reactor y su tiempo 
void dibujar_reactor(lista_t *lista, void *renderer , float f, float centro_x, float centro_y);

//Reduce el tiempo y devuelde true si este llega a 0
bool reactor_computar_tiempo(lista_t *reactores);

//Devuelve el tiempo del reactor
float reactor_devolver_tiempo(reactor_t* reactor);

//Devuelve el tiempo del reactos
float reactor_devolver_posicion_x(reactor_t* reactor);
float reactor_devolver_posicion_y(reactor_t* reactor);

//Devuelve true si la posicion dada coincide con la del reactor
bool reactor_colision_disparo(lista_t *reactor, float disparo_x, float disparo_y, bool enemigo, float escala);

//Cambia el tiempo de la nave por el tiempo recibido
void reactor_setear_tiempo(reactor_t *reactor, float tiempo);

#endif