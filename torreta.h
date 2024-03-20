#ifndef TORRETA_H
#define TORRETA_H

#include "figuras.h"
#include "lista.h"
#include "torreta.h"
#include <stdbool.h>
#include <stdlib.h>
#include "nave.h"

typedef struct torreta torreta_t;

//Crea una torreta
torreta_t *crear_torreta(float pos_x , float pos_y, float angulo, figura_t *encendido, figura_t *apagado);

//Crea una torreta y la agrega a la lista
bool agregar_torreta_lista(lista_t *lista, float posicion_x, float posicion_y , float angulo , figura_t *encendido,figura_t *apagado);

//Torreta destruir
void torreta_destruir(void *torreta);

//Devuelve true si la torreta es golpeada
bool torreta_colision_disparo(lista_t *torretas, nave_t *nave, float disparo_x, float disparo_y, bool enemigo, float escala);

//Si ya es tiempo de disparar devulve true y cambia el disparo a true
bool torreta_dispara(torreta_t *torreta);

//Devuelve la posicion de la torreta
float torreta_pos_x(torreta_t *torreta);
float torreta_pos_y(torreta_t *torreta);

//Devuelve el angulo de la torreta
float torreta_angulo(torreta_t *torreta);

//Dibuja todas las torretas en la lista
void dibujar_torreta(lista_t *lista, void* renderer , float f, float centro_x, float centro_y);

//Cambia el estado de disparo
void encender_torreta(torreta_t *torreta);
void apagar_torreta(torreta_t *torreta);



#endif