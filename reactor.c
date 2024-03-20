#include "reactor.h"
#include "figuras.h"
#include "lista.h"
#include "reactor.h"
#include "caracteres.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>


#define REACTOR_TIEMPO_MAX 50

struct reactor{
    figura_t *reactor;
    float posicion_x;
    float posicion_y;
    float angulo;
    float tiempo;
};

reactor_t *crear_reactor(figura_t *reactor_figura, float pos_x, float pos_y, float angulo){
    reactor_t *nuevo = malloc(sizeof(reactor_t));
    if(nuevo == NULL) return NULL;
    nuevo -> reactor = reactor_figura;
    nuevo -> posicion_x = pos_x;
    nuevo -> posicion_y = pos_y;
    nuevo -> angulo = angulo;
    nuevo -> tiempo = 25;
    return nuevo;
}

static void destruir_reactor_(reactor_t *reactor){
    free(reactor);
}

void reactor_destruir(void *reactor){
    destruir_reactor_(reactor);
}

float reactor_devolver_tiempo(reactor_t *reactor){
    return reactor->tiempo;
}


void dibujar_reactor(lista_t *lista, void *renderer , float f, float centro_x, float centro_y){
    lista_iter_t *iter = lista_iter_crear(lista);
    reactor_t *reactor_aux;
    char contador[10];
    while(!lista_iter_al_final(iter)){
        reactor_aux = lista_iter_ver_actual(iter);
        SDL_itoa(reactor_aux -> tiempo, contador, 10);
        figura_dibujar(reactor_aux -> reactor, renderer, f, ((reactor_aux -> posicion_x) * f) + centro_x, ((reactor_aux -> posicion_y) * f) + centro_y);
        if(reactor_aux -> tiempo < 11){
            dibujar_cadena(contador, VENTANA_ANCHO/2 - 100, VENTANA_ALTO/2 -100 , renderer, 4, true, false, false);
        }else{
            dibujar_cadena(contador, VENTANA_ANCHO/2 - 100, VENTANA_ALTO/2 -100, renderer, 4, true, false, true);
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

bool reactor_computar_tiempo(lista_t *reactores){
    lista_iter_t *iter = lista_iter_crear(reactores);
    while(!lista_iter_al_final(iter)){
        reactor_t *reactor_aux = lista_iter_ver_actual(iter);
        if(reactor_aux -> tiempo <= 0){
            reactor_aux -> tiempo = 25;
            lista_iter_destruir(iter);
            return true;
        }
        reactor_aux -> tiempo -= 1.0/JUEGO_FPS; 
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return false;
}


float reactor_devolver_posicion_x(reactor_t* reactor){
    return reactor->posicion_x;
}

float reactor_devolver_posicion_y(reactor_t* reactor){
    return reactor->posicion_y;
}

bool reactor_colision_disparo(lista_t *reactor, float disparo_x, float disparo_y, bool enemigo, float escala){
    lista_iter_t *iter = lista_iter_crear(reactor);
    while(!lista_iter_al_final(iter)){
        reactor_t *reactor_aux = lista_iter_ver_actual(iter);
        if(!enemigo){
            if(norma(disparo_x - (reactor_aux -> posicion_x) * escala, disparo_y - (reactor_aux -> posicion_y) * escala) < 20){
                reactor_destruir(lista_iter_borrar(iter)); 
                lista_iter_destruir(iter);
                return true;
            }
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return false;
}

void reactor_setear_tiempo(reactor_t *reactor, float tiempo){
    reactor -> tiempo = tiempo;
}

