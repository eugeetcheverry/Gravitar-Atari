#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "polilinea.h"
#include <math.h>
#include "config.h"


#define MASK_R 0x01
#define MASK_G 0x02 
#define MASK_B 0x04 
#define MASK_N 0x03ff 

struct polilinea{
    float (*puntos)[2];
    size_t n;
    color_t color_polilinea;
};

void trasladar(polilinea_t *polilinea, float dx, float dy){
    for (size_t i = 0; i < (polilinea -> n); i++) {
        polilinea -> puntos[i][0] = polilinea -> puntos[i][0] + dx;
        polilinea -> puntos[i][1] = polilinea -> puntos[i][1] + dy;
    }
}

void rotar(polilinea_t *polilinea, double rad) {

    float componentex;
    float componentey;
    double cosangulo = cos(rad);
    double sinangulo = sin(rad);

    for (size_t i = 0; i < (polilinea -> n); i++) {
        componentex = polilinea -> puntos[i][0];
        componentey = polilinea -> puntos[i][1];
        polilinea -> puntos[i][0] = componentex * cosangulo - componentey * sinangulo;
        polilinea -> puntos[i][1] = componentex * sinangulo + componentey * cosangulo;
    }
}

polilinea_t *polilinea_crear_vacia(size_t n){
    
    polilinea_t *polilinea = malloc(sizeof(polilinea_t));
    if(polilinea == NULL){
        return NULL;
    }
    polilinea -> n = n;
    polilinea -> puntos = malloc(n*sizeof(float[2]));
    if(polilinea -> puntos == NULL){
        free(polilinea);
        return NULL;
    }

    return polilinea;
}

polilinea_t *polilinea_crear(const float puntos[][2], size_t n, color_t color){
    
    polilinea_t *polilineacrear = polilinea_crear_vacia(n);
    if(polilineacrear == NULL){
        return NULL;
    }
    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < 2; j++){
            polilineacrear->puntos[i][j] = puntos[i][j];
        }
    }

    polilineacrear -> color_polilinea = color;

    return polilineacrear;
}

void polilinea_destruir(polilinea_t *polilinea){
    free(polilinea -> puntos);
    free(polilinea);
}

polilinea_t *polilinea_clonar(const polilinea_t *polilinea){
    
    polilinea_t *polilinea_clon = polilinea_crear((const float(*)[2])polilinea -> puntos, polilinea -> n, polilinea -> color_polilinea);
    
    return polilinea_clon;
}

float obtener_punto_polilinea(polilinea_t *polilinea,size_t fila,size_t columna){
    return polilinea->puntos[fila][columna];
}

bool polilinea_setear_color(polilinea_t* polilinea, color_t color) {
    polilinea -> color_polilinea = color;
    return true;
}

bool polilinea_setear_punto(polilinea_t* polilinea, size_t pos, float x, float y){
    if(pos >= (polilinea->n)){
        return false;
    }
    polilinea->puntos[pos][0] = x;
    polilinea->puntos[pos][1] = y;

    return true;
}

size_t polilinea_cantidad_puntos(const polilinea_t* polilinea) {
    return polilinea->n;
}

color_t polilinea_color(polilinea_t* polilinea) {
    return polilinea->color_polilinea;
}

polilinea_t* leer_polilinea(FILE* f) {

    uint16_t aux;
    _Bool r, g, b;
    if (fread(&aux, sizeof(uint16_t), 1, f) != 1) return NULL;
    r = aux >> 15;
    g = (aux >> 13) & MASK_G;
    b = (aux >> 11) & MASK_B;
    color_t color = color_crear(r, g, b);
    size_t n = (aux & MASK_N);
    polilinea_t* polilinea = polilinea_crear_vacia(n);
    if(!polilinea_setear_color(polilinea, color)) return NULL;
    float x;
    float y;
    for (size_t i = 0; i < n; i++) {
        if (fread(&x, sizeof(float), 1, f) != 1) {
            polilinea_destruir(polilinea);
            return NULL;
        }
        if (fread(&y, sizeof(float), 1, f) != 1) {
            polilinea_destruir(polilinea);
            return NULL;
        }
        if(!polilinea_setear_punto(polilinea, i, x, y)) return NULL;
    }
    return polilinea;
}

void polilinea_obtener_punto(polilinea_t *polilinea, size_t pos, float *x, float *y){
    *x = polilinea -> puntos[pos][0];
    *y = polilinea -> puntos[pos][1];
}

double producto_interno(float ax, float ay, float bx, float by){
    return ax*bx + ay*by;
}

double norma(float ax, float ay){
    return sqrt(ax*ax + ay*ay);
}

double distancia_punto_segmento(float ax, float ay, float bx, float by, float px, float py){
    
    double a = producto_interno(px - ax, py - ay, bx - ax, by - ay) / producto_interno(bx - ax, by - ay, bx - ax, by - ay);
    if (a <= 0){
        return norma(px - ax, py - ay);
    }
    if (a >= 1){
        return norma(px - bx, py - ay);
    }
    double x = ax + a * (bx - ax);
    double y = ay + a * (by - ay);

    return norma(px-x, py-y);    
}

double distancia_punto_a_polilinea(polilinea_t *polilinea, float px, float py, float escala){
    double distancia = distancia_punto_segmento(polilinea -> puntos[0][0] * escala, polilinea -> puntos[0][1] * escala, polilinea -> puntos[1][0] * escala, polilinea -> puntos[1][1] * escala, px, py);
    double distancia_2;

    for(size_t i = 1; i < ((polilinea -> n) - 1) ; i++){
        distancia_2 = distancia_punto_segmento(polilinea -> puntos[i][0] * escala, polilinea -> puntos[i][1] * escala, polilinea -> puntos[i+1][0] * escala, polilinea -> puntos[i+1][1] * escala, px, py);
        if(distancia_2 < distancia){
            distancia = distancia_2;
        }
    }
    return distancia;
}

double  polilinea_minimo_x(polilinea_t *polilinea){
    double min = polilinea->puntos[0][0];
    for(size_t i=0 ; i < polilinea->n ; i++){
        double aux = polilinea->puntos[i][0];
        if(aux < min){
            min = aux;
        }
    }
    return min;
}

double  polilinea_minimo_y(polilinea_t *polilinea){
    double min = polilinea->puntos[0][1];
    for(size_t i=0 ; i < polilinea->n ; i++){
        double aux = polilinea->puntos[i][1];
        if(aux < min){
            min = aux;
        }
    }
    return min;
}


double polilinea_alto(polilinea_t *polilinea){
    double min = polilinea->puntos[0][1];
    double max = polilinea->puntos[0][1];
    double aux;
    for(size_t i=0 ; i < polilinea->n ; i++){
        aux = polilinea -> puntos[i][1];
        if(aux < min){
            min = aux;
        }
        if(aux > max){
            max = aux;
        }
    }
    return max;
}

double polilinea_ancho(polilinea_t *polilinea){
    double min = polilinea -> puntos[0][0];
    double max = polilinea -> puntos[0][0];
    double aux;
    for(size_t i = 0; i < polilinea -> n; i++){
        aux = polilinea -> puntos[i][0];
        if(aux < min){
            min = aux;
        }
        if(aux > max){
            max = aux;
        }
    }
    return max;
}

void polilinea_dibujar(polilinea_t *polilinea, void *renderer, float escala, float posicion_x, float posicion_y){
    uint8_t r;
    uint8_t g;
    uint8_t b;

    color_t color = polilinea -> color_polilinea;
    color_a_rgb(color, &r, &g, &b);
    SDL_SetRenderDrawColor(renderer, r, g, b, 0X00);
    
    for(size_t i = 0; i < (polilinea -> n) - 1; i++){
        SDL_RenderDrawLine(
            renderer,
            polilinea -> puntos[i][0] * escala + posicion_x,
            -polilinea -> puntos[i][1] * escala + VENTANA_ALTO - posicion_y,
            polilinea -> puntos[i + 1][0] * escala + posicion_x,
            -polilinea -> puntos[i + 1][1] * escala + VENTANA_ALTO - posicion_y
        );
    }
}




