#include "figuras.h"
#include "lista.h"
#include "torreta.h"
#include <stdbool.h>
#include <stdlib.h>
#include "nave.h"

#define TORRETA_TIEMPO 5 * JUEGO_FPS
#define TORRETA_DESTRUIDA 250

struct torreta{
    float pos_x;
    float pos_y;
    float angulo;
    float tiempo;
    figura_t *encendido;
    figura_t *apagado;
    bool disparo;
};

torreta_t *crear_torreta(float pos_x ,float pos_y,float angulo, figura_t *encendido, figura_t *apagado){
    torreta_t *torreta = malloc(sizeof(torreta_t));
    torreta->pos_x = pos_x;
    torreta->pos_y = pos_y;
    torreta->angulo = angulo;
    torreta->tiempo = 0;
    torreta->encendido = encendido;
    torreta->apagado = apagado;
    torreta->disparo = false;
    return torreta;
}

bool agregar_torreta_lista(lista_t *lista, float posicion_x, float posicion_y , float angulo , figura_t *encendido,figura_t *apagado){
    torreta_t *torreta = crear_torreta(posicion_x, posicion_y, angulo, encendido, apagado);
    if(torreta == NULL){
        return false;
    }
    if(lista_insertar_primero(lista, torreta)){
        return true;
    }
    return false;
}

static void destruir_torreta_(torreta_t *torreta){
    free(torreta);
}

void torreta_destruir(void *torreta){
    destruir_torreta_(torreta);
}

bool torreta_colision_disparo(lista_t *torretas, nave_t *nave, float disparo_x, float disparo_y, bool enemigo, float escala){
    lista_iter_t *iter = lista_iter_crear(torretas);
    while(!lista_iter_al_final(iter)){
        torreta_t *torreta_aux = lista_iter_ver_actual(iter);
        if(!enemigo){
            if(norma(disparo_x - (torreta_aux -> pos_x) * escala, disparo_y - (torreta_aux -> pos_y) * escala) < 20){
                torreta_destruir(lista_iter_borrar(iter)); 
                lista_iter_destruir(iter);
                nave_sumar_puntos(nave, TORRETA_DESTRUIDA);
                return true;
            }
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return false;
}

bool torreta_dispara(torreta_t *torreta){
    torreta -> tiempo++;
    if(torreta -> tiempo == TORRETA_TIEMPO){
        encender_torreta(torreta);
        torreta -> tiempo = 0;
        return true;
    }
    apagar_torreta(torreta);
    return false;
}

float torreta_pos_x(torreta_t *torreta){
    return torreta-> pos_x;
}

float torreta_pos_y(torreta_t *torreta){
    return torreta->pos_y;
}

float torreta_angulo(torreta_t *torreta){
    return torreta->angulo;
}

void dibujar_torreta(lista_t *lista, void *renderer , float f, float centro_x, float centro_y){
    lista_iter_t *iter = lista_iter_crear(lista);
    while(!lista_iter_al_final(iter)){
        torreta_t *torreta_aux = lista_iter_ver_actual(iter);
        if(torreta_aux -> disparo){
            figura_t *figura_clon = clonar_figura(torreta_aux->encendido);
            rotar_figura(figura_clon, torreta_aux -> angulo);
            figura_dibujar(figura_clon, renderer, f, ((torreta_aux -> pos_x) * f) + centro_x, ((torreta_aux -> pos_y) * f) + centro_y);
            destruir_figura(figura_clon);
        }else{
            figura_t *figura_clon = clonar_figura(torreta_aux->apagado);
            rotar_figura(figura_clon, torreta_aux -> angulo);
            figura_dibujar(figura_clon, renderer, f, ((torreta_aux -> pos_x) * f) + centro_x, ((torreta_aux -> pos_y) * f) + centro_y);
            destruir_figura(figura_clon);
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

void encender_torreta(torreta_t *torreta){
    torreta -> disparo = true;
}

void apagar_torreta(torreta_t *torreta){
    torreta -> disparo = false;
}

