#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "disparo.h"
#include "polilinea.h"
#include "lista.h"
#include "figuras.h"
#include "torreta.h"
#include "reactor.h"
#define MAX_TIEMPO 5 * JUEGO_FPS

struct disparo{
    float angulo;
    float posicion_x;
    float posicion_y; 
    float tiempo;
    bool enemigo;
};

static disparo_t *crear_disparo(float posicion_x, float posicion_y , float angulo , bool enemigo){
    disparo_t *disparo = malloc(sizeof(disparo_t));
    if(disparo==NULL){
        return NULL;
    }
    disparo -> posicion_x = posicion_x;
    disparo -> posicion_y = posicion_y;
    disparo -> angulo = angulo;
    disparo -> enemigo = enemigo;
    disparo -> tiempo = 0;
    return disparo;
}

static void destruir_disparo_(disparo_t* disparo){
    free(disparo);
}

void destruir_disparo(void* disparo){
    destruir_disparo_(disparo);
}

void agregar_disparo_lista(lista_t* lista, float posicion_x, float posicion_y , float angulo , bool enemigo){
    disparo_t *disparo = crear_disparo(posicion_x, posicion_y , angulo, enemigo);
    if(disparo != NULL){
       lista_insertar_ultimo(lista, disparo);
    }
}

static bool disparo_aumentar_tiempo(disparo_t *disparo){
    disparo -> tiempo++;
    if(disparo -> tiempo == MAX_TIEMPO){
        return true;
    }
    return false;
}

static void disparo_aumentar_posicion(disparo_t* disparo){
    disparo -> posicion_x += cos(disparo -> angulo); 
    disparo -> posicion_y += sin(disparo -> angulo);
}

void disparos_de_torreta(lista_t *disparos, lista_t *torretas, nave_t *nave, float escala){
    if((torretas != NULL)){
        lista_iter_t *iter = lista_iter_crear(torretas);
        if(iter != NULL){
            while(!lista_iter_al_final(iter)){
                torreta_t *torreta_aux = lista_iter_ver_actual(iter);
                if(torreta_aux != NULL){
                    if(torreta_dispara(torreta_aux)){
                        float angulo = atan2(posicion_y_nave(nave) - (torreta_pos_y(torreta_aux) + 20 * sin(torreta_angulo(torreta_aux))) * escala, posicion_x_nave(nave) - (torreta_pos_x(torreta_aux) + 20 * cos(torreta_angulo(torreta_aux)) ) * escala);
                        agregar_disparo_lista(disparos, (torreta_pos_x(torreta_aux) + 20 * cos(torreta_angulo(torreta_aux) + PI/2) ) * escala, (torreta_pos_y(torreta_aux) + 20 * sin(torreta_angulo(torreta_aux) + PI/2)) * escala, angulo, true);
                    }
                }
                lista_iter_avanzar(iter);
            }
        }
        lista_iter_destruir(iter);
    }
}


void disparos_setear_iteracion(lista_t *lista, nave_t *nave, bool escudo , lista_t *torretas, lista_t *reactor , figura_t *nivel , float escala){
    lista_iter_t *iter = lista_iter_crear(lista);
    while(!lista_iter_al_final(iter)){
        disparo_t *disparo_aux = lista_iter_ver_actual((const lista_iter_t *)iter);
        disparo_aumentar_posicion(disparo_aux);
        if(disparo_aux -> enemigo){
            if(norma((disparo_aux -> posicion_x) - posicion_x_nave(nave), (disparo_aux->posicion_y) - posicion_y_nave(nave)) < 10){
                if(escudo){
                    destruir_disparo(lista_iter_borrar(iter));
                    continue;
                }else{
                    setear_datos_nave(nave, VENTANA_ANCHO/2, VENTANA_ALTO - 10, -PI/2, 0 , 0);
                    nave_restar_vida(nave);
                }
            }
            if(punto_cerca_figura(disparo_aux -> posicion_x, disparo_aux -> posicion_y, nivel, escala)){
                destruir_disparo(lista_iter_borrar(iter));
                continue;
            }
            if(disparo_aumentar_tiempo(disparo_aux)){
                destruir_disparo(lista_iter_borrar(iter));
                continue;
            }
        }else{
            if(punto_cerca_figura(disparo_aux -> posicion_x, disparo_aux -> posicion_y, nivel, escala)){
                destruir_disparo(lista_iter_borrar(iter));
                continue;
            }
            if(torretas != NULL){
                if(torreta_colision_disparo(torretas, nave, disparo_aux -> posicion_x, disparo_aux->posicion_y, disparo_aux->enemigo, escala)){
                    destruir_disparo(lista_iter_borrar(iter));
                    continue;
                }
            }
            if(reactor != NULL){
                if(reactor_colision_disparo(reactor, disparo_aux -> posicion_x, disparo_aux->posicion_y, disparo_aux->enemigo, escala)){
                    reactor_destruir(lista_iter_borrar(iter));
                    continue;
                }
            }
            if(disparo_aumentar_tiempo(disparo_aux)){
                destruir_disparo(lista_iter_borrar(iter));
                continue;
            }
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

void dibujar_disparos(lista_t *lista, void* renderer, float f, float centro_x, float centro_y, figura_t *figura){
    lista_iter_t *iter = lista_iter_crear(lista);
    while(!lista_iter_al_final(iter)){
        disparo_t *disparo_aux = lista_iter_ver_actual(iter);
        figura_dibujar(figura, renderer, f, (disparo_aux -> posicion_x) + centro_x, (disparo_aux -> posicion_y) + centro_y);
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}