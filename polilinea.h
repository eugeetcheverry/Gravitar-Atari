#ifndef _POLILINEA_H_
#define _POLILINEA_H_

#include "polilinea.h"
#include <stdio.h>
#include "color.h"
#include <math.h>
#include <SDL2/SDL.h>


typedef struct polilinea polilinea_t;

void rotar(polilinea_t *polilinea, double rad);

void trasladar(polilinea_t *polilinea, float dx, float dy);

polilinea_t *polilinea_crear_vacia(size_t n);
 
polilinea_t *polilinea_crear(const float puntos[][2], size_t n, color_t color);

void polilinea_destruir(polilinea_t *polilinea);

polilinea_t *polilinea_clonar(const polilinea_t *polilinea);

float obtener_punto_polilinea(polilinea_t *polilinea,size_t fila,size_t columna);

size_t polilinea_cantidad_puntos(const polilinea_t *polilinea);

color_t polilinea_color(polilinea_t* polilinea);

bool polilinea_setear_punto(polilinea_t* polilinea, size_t pos, float x, float y);

polilinea_t *leer_polilinea(FILE *f);

bool polilinea_setear_color(polilinea_t* polilinea, color_t color);

void polilinea_obtener_punto(polilinea_t *polilinea, size_t pos, float *x, float *y);

double producto_interno(float ax, float ay, float bx, float by);

double norma(float ax, float ay);

double distancia_punto_segmento(float ax, float ay, float bx, float by, float px, float py);

double distancia_punto_a_polilinea(polilinea_t *polilinea, float px, float py, float escala);

double polilinea_alto(polilinea_t *polilinea);

double  polilinea_minimo_x(polilinea_t *polilinea);

double polilinea_ancho(polilinea_t *polilinea);

double  polilinea_minimo_y(polilinea_t *polilinea);

void polilinea_dibujar(polilinea_t *polilinea, void *renderer, float escala, float posicion_x, float posicion_y);

#endif //_POLILINEA_H_