#include "planeta.h"
#include "figuras.h"
#include "polilinea.h"
#include "nave.h"
#include <stdbool.h>
#include "config.h"
#include "caracteres.h"
#include "torreta.h"
#include "combustible.h"
#include "reactor.h"
#include "disparo.h"
#include <stdlib.h>

struct planeta{
    char nombre_planeta[MAX_STRING];
    figura_t *planeta;
    figura_t *nivel;
    float posicion_x;
    float posicion_y;
    bool sobre_el_planeta;
    bool dentro_del_nivel;
    double escala;
    double centro_x;
    double centro_y;
    char puntaje[MAX_STRING];
    lista_t *torretas;
    lista_t *combustible;
    lista_t *reactor;
    bool nivel_ganado;
};

planeta_t *crear_planeta(char nombre[MAX_STRING], figura_t *planeta_figura, figura_t *nivel_figura, float pos_x, float pos_y, char *puntaje){
    planeta_t *planeta_nuevo = malloc(sizeof(planeta_t));
    planeta_nuevo -> planeta  = planeta_figura;
    planeta_nuevo -> nivel = nivel_figura;
    planeta_nuevo -> posicion_x = pos_x;
    planeta_nuevo -> posicion_y = pos_y;
    planeta_nuevo -> sobre_el_planeta = false;
    planeta_nuevo -> dentro_del_nivel = false;
    planeta_nuevo -> nivel_ganado = false;
    planeta_nuevo -> centro_x = 0;
    planeta_nuevo -> centro_y = 0;
    planeta_nuevo -> escala = 0;
    strcpy(planeta_nuevo -> nombre_planeta, nombre);
    strcpy(planeta_nuevo -> puntaje, puntaje);
    planeta_nuevo -> torretas = lista_crear();
    planeta_nuevo -> combustible = lista_crear();
    planeta_nuevo -> reactor = lista_crear();
    return planeta_nuevo;
}

void planeta_destruir(planeta_t *planeta){
    lista_destruir(planeta -> torretas, torreta_destruir);
    lista_destruir(planeta -> combustible, destruir_combustible);
    lista_destruir(planeta -> reactor, reactor_destruir);
    free(planeta);
}

void setear_datos_planeta(planeta_t *planeta, double escala, double centro_x, double centro_y, bool en_nivel, bool sobre_planeta){
    planeta -> escala = escala;
    planeta -> centro_x = centro_x;
    planeta -> centro_y = centro_y;
    planeta -> dentro_del_nivel = en_nivel;
    planeta -> sobre_el_planeta = sobre_planeta;
}

bool planeta_infinito(planeta_t *planeta){
    return figura_infinita(planeta -> nivel);
}

void planeta_finito_escala(planeta_t *planeta){
    float planeta_alto = figura_alto(planeta -> nivel);
    float planeta_x_min = figura_minimo_x(planeta-> nivel);
    float planeta_ancho = figura_ancho(planeta -> nivel);
    planeta -> escala = VENTANA_ALTO * 1.0 / planeta_alto;
    if((VENTANA_ANCHO * 1.0 / (planeta_ancho + planeta_x_min)) < planeta -> escala){
        planeta -> escala = VENTANA_ANCHO * 1.0 / (planeta_ancho + planeta_x_min);
    }
    planeta -> centro_x = (planeta_ancho + planeta_x_min) / 2;
}

void planeta_infinito_escala(planeta_t *planeta, nave_t *nave){
    planeta -> escala = 1;
    if(posicion_y_nave(nave) > VENTANA_ALTO * MARGEN_ALTURA)
        planeta -> escala = VENTANA_ALTO * MARGEN_ALTURA / posicion_y_nave(nave);
    if(planeta -> escala < ESCALA_MINIMA)
        planeta -> escala = ESCALA_MINIMA;
    if((posicion_x_nave(nave) - planeta -> centro_x) *  planeta -> escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
        planeta -> centro_x = posicion_x_nave(nave) - VENTANA_ANCHO / 2 * MARGEN_ANCHO / planeta -> escala;
    else if((planeta -> centro_x - posicion_x_nave(nave)) * planeta -> escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
        planeta -> centro_x = posicion_x_nave(nave) + VENTANA_ANCHO / 2 * MARGEN_ANCHO / planeta -> escala;
}

void sobre_planeta(nave_t *nave, planeta_t *planeta, int *en_un_nivel){
    if(norma(posicion_x_nave(nave) - (planeta -> posicion_x), posicion_y_nave(nave) - (planeta -> posicion_y)) < 15 && (*en_un_nivel == 0)){
        planeta -> sobre_el_planeta = true;
        *en_un_nivel = 1;
    }
}

void nivel_terminado(planeta_t *planeta, nave_t *nave){
    if(lista_esta_vacia(planeta -> torretas) && (planeta -> nivel_ganado == false)){
        nave_sumar_puntos(nave, atof(planeta -> puntaje));
        planeta -> nivel_ganado = true;
    }
}

void graficar_nivel(planeta_t *planeta, void *renderer, float centro_x, float centro_y){
    figura_dibujar(planeta -> nivel, renderer, planeta -> escala, centro_x, centro_y);
    dibujar_combustible(planeta -> combustible, renderer, planeta -> escala, centro_x, centro_y);
    dibujar_torreta(planeta -> torretas, renderer, planeta -> escala, centro_x, centro_y);
    dibujar_reactor(planeta -> reactor, renderer, planeta -> escala, centro_x, centro_y);
}

void graficar_planetas_inicio(planeta_t *planeta[], size_t n, void *renderer, float escala){
    for(size_t i = 0; i < n; i++){
        figura_dibujar(planeta[i] -> planeta, renderer, escala, planeta[i] -> posicion_x, planeta[i] -> posicion_y);
        dibujar_cadena(planeta[i] -> puntaje, planeta[i] -> posicion_x, planeta[i] -> posicion_y + 20, renderer, escala, false, true, true);
    }
}

bool nave_choca_nivel(planeta_t *planeta_nivel, nave_t *nave){
    return distancia_nave_polilinea(nave, planeta_nivel -> nivel, planeta_nivel -> escala);
}

lista_t *lista_torretas_planeta(planeta_t *planeta){
    return planeta -> torretas;
}

lista_t *lista_combustible_planeta(planeta_t *planeta){
    return planeta -> combustible;
}

lista_t *lista_reactor_planeta(planeta_t *planeta){
    return planeta -> reactor;
}

void recolectar_combustible(nave_t *nave, planeta_t *planeta, float escala, bool escudo){
   if(escudo){
        lista_iter_t *iter = lista_iter_crear(planeta -> combustible);
        while(!lista_iter_al_final(iter)){
            combustible_t *combustible_aux = lista_iter_ver_actual(iter);
            if(norma(posicion_x_nave(nave) - (combustible_posicion_x(combustible_aux)) * escala, posicion_y_nave(nave) - (combustible_posicion_y(combustible_aux)) * escala) < 60 * escala){
                destruir_combustible(lista_iter_borrar(iter));
                aumentar_combustible(nave);
                break;
            }
            lista_iter_avanzar(iter);
        }
        lista_iter_destruir(iter);
    }
}

bool nave_sobre_plantea(planeta_t *planeta){
    return planeta -> sobre_el_planeta;
}

bool planeta_dentro_de_nivel(planeta_t *planeta){
    return planeta -> dentro_del_nivel;
}

void setear_dentro_de_nivel_planeta(planeta_t *planeta, bool encendido){
    planeta -> dentro_del_nivel = encendido;
}

void setear_centro_x_planeta(planeta_t *planeta, float centro_x){
    planeta -> centro_x = centro_x;
}

float centro_x_planeta(planeta_t *planeta){
    return planeta -> centro_x;
}

float centro_y_planeta(planeta_t *planeta){
    return planeta -> centro_y;
}

float planeta_escala(planeta_t *planeta){
    return planeta -> escala;
}

figura_t *figura_nivel_planeta(planeta_t *planeta){
    return planeta -> nivel;
}

