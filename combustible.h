#ifndef COMBUSTIBLE_H
#define COMBUSTIBLE_H

#include "combustible.h"
#include "lista.h"
#include "figuras.h"
#include "nave.h"
#include "planeta.h"

typedef struct combustible combustible_t;

//Crea combustible
combustible_t *crear_combustible(figura_t *combustible_figura, float pos_x, float pos_y, float angulo, bool disponible);

//Destruye el combustible
void destruir_combustible(void *combustible);

//Dibuja y rota el combustible de toda la lista
void dibujar_combustible(lista_t *lista, void *renderer , float f, float centro_x, float centro_y);

//Devuelve la figura del combustible
figura_t *combustible_figura(combustible_t *combustible_fig);

//Devuelve la posicion del combustible
float combustible_posicion_x(combustible_t *combustible);
float combustible_posicion_y(combustible_t *combustible);


#endif