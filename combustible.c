#include "combustible.h"
#include "figuras.h"
#include "lista.h"
#include "planeta.h"
#include "nave.h"
#include <stdbool.h>
#include <stdlib.h>

struct combustible{
    figura_t *combustible;
    float posicion_x;
    float posicion_y;
    float angulo;
};

combustible_t *crear_combustible(figura_t *combustible_figura, float pos_x, float pos_y, float angulo, bool disponible){
    combustible_t *nuevo = malloc(sizeof(combustible_t));
    if(nuevo == NULL) return NULL;
    nuevo -> combustible = combustible_figura;
    nuevo -> posicion_x = pos_x;
    nuevo -> posicion_y = pos_y;
    nuevo -> angulo = angulo;
    return nuevo;
}

static void destruir_combustible_(combustible_t *combustible){
    free(combustible);
}

void destruir_combustible(void *combustible){
    destruir_combustible_(combustible);
}

void dibujar_combustible(lista_t *lista, void *renderer , float f, float centro_x, float centro_y){
    lista_iter_t *iter = lista_iter_crear(lista);
    while(!lista_iter_al_final(iter)){
        combustible_t *combustible_aux = lista_iter_ver_actual(iter);
        figura_t *figura_clon = clonar_figura(combustible_aux -> combustible);
        rotar_figura(figura_clon, combustible_aux -> angulo);
        figura_dibujar(figura_clon, renderer, f, ((combustible_aux -> posicion_x) * f) + centro_x, ((combustible_aux -> posicion_y) * f) + centro_y);
        destruir_figura(figura_clon);
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

figura_t *combustible_figura(combustible_t *combustible_fig){
    return  combustible_fig -> combustible;
}

float combustible_posicion_x(combustible_t *combustible){
    return combustible -> posicion_x;
}

float combustible_posicion_y(combustible_t *combustible){
    return combustible -> posicion_y;
}




