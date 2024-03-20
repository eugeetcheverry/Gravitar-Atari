#ifndef FIGURAS_H
#define FIGURAS_H
#include "lista.h"
#include "config.h"
#include "polilinea.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

typedef enum{
    ICONO,
    NIVEL,
    SPRITE,
    PLANETA,
    BASE,
    COMBUSTIBLE,
    TORRETA,
    REACTOR,
}figura_tipo_t;

typedef struct{
    char nombre[MAX_STRING];
    figura_tipo_t tipo;
    bool infinito;
    polilinea_t **polilineas;
    size_t cantidad_polilinea;
}figura_t;

//Crea una figura
figura_t* crear_figura();

//Destruye la figura
void destruir_figura(void* figura);

//Clona la figura
figura_t *clonar_figura(figura_t *figura);

//Devuelve una cadena con el tipo de figura
const char* figura_tipo_a_cadena(figura_tipo_t figura);

//Lee los datos de la figura del archivo 
bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilinea);

//Busca una figura de la lista por su nombre
figura_t* buscar_figura_nombre(lista_t *lista , char nombre[]);

//Crea una lista con todas las figuras leidas del archivo
lista_t *lista_figuras(FILE *f);

//Devuelve la polilinea n de la figura
polilinea_t *figura_polilinea(figura_t *figura, size_t n);

//Devuele la cantidad de polilineas
size_t figura_cant_polilineas(figura_t *figura);

//Traslada una figura
void trasladar_figura(figura_t *figura, float posx, float posy);

//Devuelve la cantidad de puntos de la polilinea n de la figura
size_t figura_polilinea_n(figura_t *figura, size_t n);

//Devuelve true si la figura es infinita
bool figura_infinita(figura_t *figura);

//Devuelve la coordenda y del punto mas alto de la figura
double figura_alto(figura_t *figura);

//Devuelve la coordenda x del punto mas chico de la figura
double figura_minimo_x(figura_t *figura);

//Devuelve la coordenda x del punto mas grande de la figura
double figura_ancho(figura_t *figura);

//Devuelve la coordenda y del punto mas chico de la figura
double figura_minimo_y(figura_t *figura);

//Dibuja la figura
void figura_dibujar(figura_t *figura, void *renderer, float f, float posicion_x, float posicion_y);

//Devuelve true si el punto esta cerca de la polilinea
bool punto_cerca_figura(float px, float py, figura_t *figura, float escala);

//Rota la figura un angulo en radianes
void rotar_figura(figura_t *figura, float angulo);

#endif
