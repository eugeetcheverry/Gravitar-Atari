#ifndef _NAVE_H_
#define _NAVE_H_

#include "polilinea.h"
#include "figuras.h"

typedef struct nave nave_t;

//crear_nave crea una nave en la base con
//3 vidas y 10000 de combustible
//crear_nave devuelve NULL si falla
nave_t *crear_nave(figura_t *escudo1, figura_t *escudo2);

//destruye la nave y su figura asignada
void destruir_nave(nave_t *nave);

//clona una nave
nave_t *clonar_nave(nave_t *nave);

//le asigna a una nave una figura ya clonada
void asignar_nave_figura(nave_t *nave, figura_t *figura_leida);

// Altera la direccion de la nave en +- NAVE_ROTACION_PASO
void rotar_nave_derecha(nave_t* nave);
void rotar_nave_izquierda(nave_t* nave);

void setear_aceleracion(nave_t *nave, double a_nave);

double computar_velocidad(double vi, double a, double dt);

double computar_posicion(double pi, double vi, double dt);

// Calcula la velocidad y la posicion de la nave en cada iteracion 
void nave_computar_movimiento(nave_t* nave);

// Setea la aceleracio de la nave en el inicio y como esta es afectada por la gravedad de la estrella  
void gravedad_estrella(nave_t *nave, bool chorro);

//Rota la figura de la nave segun los datos de la misma
void nave_computar_rotar(nave_t *nave);

// Dibuja la nave en la pocision
void nave_dibujar(nave_t *nave, void *renderer, float escala, float centro_x, float centro_y, bool escudo, bool en_un_nivel);

// Devuelve la figura asociada a la nave
figura_t *nave_figura(nave_t *nave);

// Devuelvo la cantidad de las polilineas de la figura 
size_t nave_cantidad_polilineas(nave_t *nave);

// Devuelvo la polilinea de la figura
polilinea_t *nave_polilinea(nave_t *nave);

// Cambia el signo de la velocidad cuando llega al borde de la pantalla
void rebotar_nave(nave_t *nave);

// Devuelve la pocision de la nave
float posicion_x_nave(nave_t *nave);
float posicion_y_nave(nave_t *nave);

// Devuelve la velocidad de la nave
float velocidad_x_nave(nave_t *nave);
float velocidad_y_nave(nave_t *nave);

// Devuelve la aceleracion de la nave
float aceleracion_x_nave(nave_t *nave);
float aceleracion_y_nave(nave_t *nave);

// Devuelve el angulo de la nave
float nave_angulo(nave_t *nave);

// Recibe datos y los setea en la nave
void setear_datos_nave(nave_t *nave, float posx, float posy, float rad, float vx, float vy);

// Setea la aceleracio de la nave en los niveles y como esta afectada por la gravedad
void gravedad_planeta(nave_t *nave,  double aceleracion_nave, bool chorro);

float nave_angulo(nave_t *nave);

//Recibe dos naves y replica una en la otra
void igualar_datos_nave(nave_t *nave_origen, nave_t *nave_destino);

//Cambia las cooredenadas de la nave al mismo lugar que la base
void reiniciar_nave_base(nave_t *nave);

// Devuele la true si la nave esta cerca las polilineas de la figura recibida
bool distancia_nave_polilinea(nave_t *nave, figura_t *figura, float escala);

void nave_restar_vida(nave_t* nave);
void nave_sumar_vida(nave_t* nave);

void nave_sumar_puntos(nave_t* nave, size_t puntos);

//Devuelve la cantidad de vidas de la nave
float nave_vidas(nave_t *nave);

//Devuel la cantidad de puntos
float nave_puntos(nave_t *nave);

// Devuelve la cantidad de combustible
float nave_combustible(nave_t *nave);

// Aumenta el combustible en 3000
void aumentar_combustible(nave_t *nave);

// Reduce el combustible de la nave
// El combustible siempre es <= 0
void nave_restar_combustible(nave_t* nave, float combustible);

// Reduce el combustible en JUEGO_COMBUSTIBLE_ESC_X_SEG
void escudo_combustible(nave_t *nave);

#endif




