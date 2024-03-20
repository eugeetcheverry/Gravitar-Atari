#include <math.h>
#include <stdio.h>
#include "nave.h"
#include "figuras.h"
#include <stdlib.h>
#include "polilinea.h"
#include "config.h"

#define VIDAS_INICIO 3

struct nave{
    figura_t *figura;
    float posicion_x;
    float posicion_y;
    float angulo;
    float velocidad_x;
    float velocidad_y;
    float aceleracion_x;
    float aceleracion_y;
    figura_t *escudo;
    figura_t *escudo_nivel;
    int vidas;
    float puntos;
    float combustible;
};

double computar_velocidad(double vi, double a, double dt) {
    return dt * a + vi;
}

double computar_posicion(double pi, double vi, double dt) {
    return dt * vi + pi;
}

nave_t* crear_nave(figura_t *escudo1, figura_t *escudo2){
    nave_t* nave = malloc(sizeof(nave_t));
    if (nave == NULL) return NULL;
    nave -> posicion_x = 388;
    nave -> posicion_y = 218;
    nave -> velocidad_x = 0;
    nave -> velocidad_y = 0;
    nave -> aceleracion_x = 0;
    nave -> aceleracion_y = 0;
    nave -> angulo = PI/2;
    nave -> vidas = VIDAS_INICIO;
    nave -> puntos = 0;
    nave -> combustible = JUEGO_COMBUSTIBLE_INICIAL;
    nave -> escudo = escudo1;
    nave -> escudo_nivel = escudo2;
    return nave;
}

void destruir_nave(nave_t *nave) {
    free(nave);
}

void asignar_nave_figura(nave_t *nave, figura_t *clon){
    nave -> figura = clon;
}

void asignar_escudo_figura(nave_t *nave, figura_t *figura_escudo){
    figura_t *clon = clonar_figura(figura_escudo);
    nave -> escudo = clon;
}

void rotar_nave_derecha(nave_t* nave) {
    nave->angulo -= NAVE_ROTACION_PASO;
}

void rotar_nave_izquierda(nave_t* nave) {
    nave->angulo += NAVE_ROTACION_PASO;
}

void setear_aceleracion(nave_t *nave, double a_nave){
    nave -> aceleracion_x = a_nave * cos(nave -> angulo);
    nave -> aceleracion_y = a_nave * sin(nave -> angulo);
}

void nave_computar_movimiento(nave_t* nave){
    double dt = 1.0/(JUEGO_FPS);
    nave-> velocidad_x = computar_velocidad(nave->velocidad_x, nave -> aceleracion_x, dt);
    nave-> velocidad_y = computar_velocidad(nave->velocidad_y, nave -> aceleracion_y, dt);
    nave-> posicion_x = computar_posicion(nave->posicion_x, nave->velocidad_x, dt);
    nave-> posicion_y = computar_posicion(nave->posicion_y, nave->velocidad_y, dt);
}

static double gravedad_estrella_x(nave_t* nave) {
    double comp_x = 457 - nave -> posicion_x;
    double comp_y = 374 - nave -> posicion_y;
    double angulo_estrella = atan2(comp_y, comp_x);
    return cos(angulo_estrella) * G;
}

static double gravedad_estrella_y(nave_t* nave) {
    double comp_x = 457 - (nave -> posicion_x);
    double comp_y = 374 - (nave -> posicion_y);
    double angulo_estrella = atan2(comp_y, comp_x);
    return sin(angulo_estrella) * G;
}

void gravedad_estrella(nave_t *nave, bool chorro){
    if(!chorro){
        nave -> aceleracion_x = gravedad_estrella_x(nave);
        nave -> aceleracion_y = gravedad_estrella_y(nave);
    }else if(chorro){
        nave -> aceleracion_x = cos(nave -> angulo) * NAVE_ACELERACION;
        nave -> aceleracion_y = sin(nave -> angulo) * NAVE_ACELERACION;
        nave -> combustible -= JUEGO_COMBUSTIBLE_POT_X_SEG/JUEGO_FPS;
    }
}

void nave_computar_rotar(nave_t *nave){
    for (size_t i = 0; i < figura_cant_polilineas(nave -> figura); i++) {
        rotar(figura_polilinea(nave -> figura, i), nave -> angulo);
    }
}

void nave_dibujar(nave_t *nave, void *renderer, float escala, float centro_x, float centro_y, bool escudo, bool en_un_nivel){
    figura_dibujar(nave -> figura, renderer, escala, nave -> posicion_x + centro_x, nave -> posicion_y + centro_y);
    if(escudo && (en_un_nivel == false)){
        escudo_combustible(nave);
        figura_dibujar(nave -> escudo, renderer, escala, nave -> posicion_x + centro_x, nave -> posicion_y + centro_y);
    }else if(escudo && en_un_nivel){
        figura_dibujar(nave -> escudo_nivel, renderer, escala, nave -> posicion_x + centro_x, nave -> posicion_y + centro_y);
        escudo_combustible(nave);
    }
}

figura_t *nave_figura(nave_t *nave){
    return nave -> figura;
}

size_t nave_cantidad_polilineas(nave_t *nave){
    return figura_cant_polilineas(nave -> figura);
}

polilinea_t *nave_polilinea(nave_t *nave){
    return figura_polilinea(nave -> figura, 0);
}

void rebotar_nave(nave_t *nave){

    if(nave -> posicion_x <= 0 || nave -> posicion_x >= VENTANA_ANCHO){
        nave -> velocidad_x = -(nave -> velocidad_x);
    }
    if(nave -> posicion_y <= 0|| nave -> posicion_y >= VENTANA_ALTO){
        nave -> velocidad_y = -(nave -> velocidad_y);
    }
    if(nave -> posicion_x <= 0 || nave -> posicion_y <= 0  || nave -> posicion_x >= VENTANA_ANCHO || nave -> posicion_y >= VENTANA_ALTO){
        nave -> angulo -= PI;
    }

}

float posicion_x_nave(nave_t *nave){
    return nave -> posicion_x;
}

float posicion_y_nave(nave_t *nave){
    return nave -> posicion_y;
}

float velocidad_x_nave(nave_t *nave){
    return nave -> velocidad_x;
}

float velocidad_y_nave(nave_t *nave){
    return nave -> velocidad_y;
}

float aceleracion_x_nave(nave_t *nave){
    return nave -> aceleracion_y;
}

void setear_datos_nave(nave_t *nave, float posx, float posy, float rad, float vx, float vy){
    nave -> posicion_x = posx;
    nave -> posicion_y = posy;
    nave -> angulo = rad;
    nave -> velocidad_x = vx;
    nave -> velocidad_y = vy;
}

void gravedad_planeta(nave_t *nave,  double aceleracion_nave, bool chorro){
    if(!chorro){
        nave -> aceleracion_x = 0;
        nave -> aceleracion_y = -G;
    }else if(chorro){
        nave -> aceleracion_x = cos(nave -> angulo) * NAVE_ACELERACION;
        nave -> aceleracion_y = sin(nave -> angulo) * NAVE_ACELERACION;
        nave -> combustible -= JUEGO_COMBUSTIBLE_POT_X_SEG/JUEGO_FPS;
    }   
}

float nave_angulo(nave_t *nave){
    return nave -> angulo;
}

void igualar_datos_nave(nave_t *nave_origen, nave_t *nave_destino){
    nave_destino -> posicion_x = nave_origen -> posicion_x;
    nave_destino -> posicion_y = nave_origen -> posicion_y;
    nave_destino -> angulo = nave_origen -> angulo;
    nave_destino -> velocidad_x = nave_origen -> velocidad_x;
    nave_destino -> velocidad_y = nave_origen -> velocidad_y;
    nave_destino -> aceleracion_x = nave_origen -> aceleracion_x;
    nave_destino -> aceleracion_y = nave_origen -> aceleracion_y;
}

void reiniciar_nave_base(nave_t *nave){
    nave->posicion_x = 388;
    nave->posicion_y = 218;
    nave->velocidad_x = 0;
    nave->velocidad_y = 0;
    nave -> aceleracion_x = 0;
    nave -> aceleracion_y = 0;
    nave->angulo = PI/2;
}

bool distancia_nave_polilinea(nave_t *nave, figura_t *figura, float escala){
    return punto_cerca_figura(nave -> posicion_x, nave -> posicion_y, figura, escala);
}

void nave_restar_vida(nave_t* nave) {
    nave -> vidas -= 1;
}

void nave_sumar_vida(nave_t* nave) {
    nave->vidas++;
}

void nave_sumar_puntos(nave_t* nave, size_t puntos){
    nave -> puntos += puntos;
}

void nave_restar_puntos(nave_t* nave, size_t puntos){
    nave->puntos -= puntos;
}
/*
void nave_sumar_combustible(nave_t* nave, size_t combustible){
    nave->combustible += combustibles;
}

void nave_restar_combustible(nave_t* nave, size_t combustible){
    nave->combustible -= combustibles;
}*/

float nave_vidas(nave_t *nave){
    return nave->vidas;
}

float nave_puntos(nave_t *nave){
    return nave->puntos;
}

float nave_combustible(nave_t *nave){
    return nave -> combustible;
}

void aumentar_combustible(nave_t *nave){
    nave -> combustible += 3000;
}

void nave_restar_combustible(nave_t* nave, float combustible){
    float n = nave->combustible - combustible;
    if(n <= 0){
        nave -> combustible = 0;
    }else{
        nave -> combustible = n;
    }
}

void escudo_combustible(nave_t *nave){
    nave_restar_combustible(nave, JUEGO_COMBUSTIBLE_ESC_X_SEG/JUEGO_FPS);
}