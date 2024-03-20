#ifndef PLANETAS_H
#define PLANETAS_H

#include "planeta.h"
#include "nave.h"
#include <stdbool.h>
#include "figuras.h"
#include "caracteres.h"
#include "torreta.h"
#include "combustible.h"
#include "reactor.h"

typedef struct planeta planeta_t;

planeta_t *crear_planeta(char nombre[MAX_STRING], figura_t *planeta_figura, figura_t *nivel_figura, float pos_x, float pos_y, char *puntaje);//crea un planeta

void planeta_destruir(planeta_t *planeta);//destruye el planeta

void sobre_planeta(nave_t *nave, planeta_t *planeta, int *en_un_nivel);//setea un booleano interno del planeta que indica si la nave, estando en la pantalla inicial, paso por encima de la figura del planeta

void planeta_finito_escala(planeta_t *planeta);//setea la escala de los niveles finitos

void planeta_infinito_escala(planeta_t *planeta, nave_t *nave);//setea la escala de los niveles infinitos

void graficar_planetas_inicio(planeta_t *planeta[], size_t n, void *renderer, float escala);//grafica los planetas en la base

void graficar_nivel(planeta_t *planeta, void *renderer, float centro_x, float centro_y);//grafica los niveles

void setear_datos_planeta(planeta_t *planeta, double escala, double centro_x, double centro_y, bool en_nivel, bool sobre_planeta);//setea los valores del planeta

bool nave_choca_nivel(planeta_t *planeta_nivel, nave_t *nave);//indica si la nave choco con la polilinea del planeta

lista_t *lista_torretas_planeta(planeta_t *planeta);//retorna la lista de torretas del planeta dado

lista_t *lista_combustible_planeta(planeta_t *planeta);//retorna la lista de combustible del planeta dado

lista_t *lista_reactor_planeta(planeta_t *planeta);//retorna la lista de reactores del planeta dado

void recolectar_combustible(nave_t *nave, planeta_t *planeta, float escala, bool escudo);//recolecta una unidad de combustible del nivel si el escudo esta encendido

bool nave_sobre_plantea(planeta_t *planeta);//retorna el booleano del tda que indica si sobre_el_planeta esa encendido

bool planeta_dentro_de_nivel(planeta_t *planeta);//retorna el booleano del tda que indica si dentro_del_nivel esta encendido

void setear_dentro_de_nivel_planeta(planeta_t *planeta, bool ensendido);//setea el booleano del tda dentro_del_nivel

void setear_centro_x_planeta(planeta_t *planeta, float centro_x);//setea el centro x del nivel

float centro_x_planeta(planeta_t *planeta);//retorna el centro x del planeta

float centro_y_planeta(planeta_t *planeta);// retorna el centro y del planeta

float planeta_escala(planeta_t *planeta);// retorna la escala del planeta

figura_t *figura_nivel_planeta(planeta_t *planeta);//retorna la figura del nivel asociado al planeta

void nivel_terminado(planeta_t *planeta, nave_t *nave);//indica si el nivel es terminado

bool planeta_infinito(planeta_t *planeta);// retorna si se trata de un planeta infinito

#endif