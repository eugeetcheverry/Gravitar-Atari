#include "config.h"
#include "polilinea.h"
#include "lista.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

#define MASK_R 0x01
#define MASK_G 0x02 
#define MASK_B 0x04 
#define MASK_N 0x03ff  
#define MASK_IN 0x40
#define MAX_STRING 20
#define MASK_T 0x0e 

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

const char* nombre[] = {
    [ICONO] = "Icono",
    [NIVEL] = "Nivel",
    [SPRITE] = "Sprite",
    [PLANETA] = "Planeta",
    [BASE] = "Base",
    [COMBUSTIBLE] = "Combustible",
    [TORRETA] = "Torreta",
    [REACTOR] = "Reactor",
};

figura_t* crear_figura(){
    figura_t* figura = malloc(sizeof(figura_t));
    return figura;
}

figura_t *clonar_figura(figura_t *figura){
    figura_t *clon = crear_figura();
    if (clon == NULL) return NULL;
    strcpy(clon -> nombre, figura -> nombre);
    clon -> tipo = figura -> tipo;
    clon -> infinito = figura -> infinito;
    clon -> cantidad_polilinea = figura -> cantidad_polilinea;
    clon -> polilineas = malloc(sizeof(polilinea_t*) * (figura -> cantidad_polilinea));
    if (clon -> polilineas == NULL) return NULL;
    for (size_t i = 0; i < figura -> cantidad_polilinea; i++) {
        clon -> polilineas[i] = polilinea_clonar(figura -> polilineas[i]);
    }
    return clon;
}

static void destruir_figura_(figura_t *figura){
   for(size_t i = 0; i < (figura -> cantidad_polilinea) ; i++) {
        polilinea_destruir((figura -> polilineas[i]));
    }
    free(figura -> polilineas);
    free(figura);
}

void destruir_figura(void *figura){
   destruir_figura_(figura);
}

const char* figura_tipo_a_cadena(figura_tipo_t figura){
    return nombre[figura];
}

bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilinea){
    if(fread(nombre, sizeof(char), (MAX_STRING) , f) != (MAX_STRING)) return false;
    uint8_t aux;
    if(fread(&aux, sizeof(uint8_t), 1, f) != 1) return false;
    *infinito = (aux & MASK_IN);  
    *tipo = (aux & MASK_T) >> 1;
    if(fread(cantidad_polilinea, sizeof(uint16_t), 1, f) != 1) return false;

    return true;
}

figura_t *buscar_figura_nombre(lista_t *list, char *nombre){
    return lista_buscar(list, nombre, strcmp);
}

void figura_dibujar(figura_t *figura, void *renderer, float f, float posicion_x, float posicion_y){
    for(size_t i = 0; i < figura -> cantidad_polilinea; i++){
        polilinea_dibujar(figura -> polilineas[i], renderer, f, posicion_x, posicion_y);
    }
}

lista_t *lista_figuras(FILE *f){
    lista_t *lista = lista_crear();
    if(lista == NULL) return NULL;
    
    while(1){
        figura_t* figura = crear_figura();
        if(!leer_encabezado_figura(f,figura->nombre,&(figura->tipo),&(figura->infinito),&(figura->cantidad_polilinea))){
            destruir_figura(figura);
            break;
        }
        figura->polilineas = malloc(sizeof(polilinea_t*)*(figura -> cantidad_polilinea));
        if(figura -> polilineas == NULL) return NULL;
        for(size_t i = 0; i<figura->cantidad_polilinea; i++) {
            figura->polilineas[i]= leer_polilinea(f);
            if(figura->polilineas[i]== NULL){
                fclose(f);
                return NULL;
            }
        }
        if(!lista_insertar_ultimo(lista,figura)) return NULL;
    }
    return lista;
}

polilinea_t *figura_polilinea(figura_t *figura, size_t n){
    return figura -> polilineas[n];
}

size_t figura_polilinea_n(figura_t *figura, size_t n){
    return polilinea_cantidad_puntos(figura -> polilineas[n]);
}

size_t figura_cant_polilineas(figura_t *figura){
    return (figura -> cantidad_polilinea);
}

bool figura_infinita(figura_t *figura){
    return figura -> infinito;
}

double figura_alto(figura_t *figura){
    double max = polilinea_alto(figura -> polilineas[0]);
    for(size_t i = 0; i< figura-> cantidad_polilinea; i++){
        double aux = polilinea_alto(figura -> polilineas[i]);
        if(aux > max){
            max = aux;
        }
    }
    return max;
}

double figura_minimo_x(figura_t *figura){
    double min = polilinea_minimo_x(figura -> polilineas[0]);
    for(size_t i = 0; i< figura -> cantidad_polilinea; i++){
        double aux = polilinea_minimo_x(figura -> polilineas[i]);
        if(aux < min){
            min = aux;
        }
    }
    return min;
}

double figura_minimo_y(figura_t *figura){
    double min = polilinea_minimo_y(figura -> polilineas[0]);
    for(size_t i = 0; i< figura -> cantidad_polilinea; i++){
        double aux = polilinea_minimo_x(figura -> polilineas[i]);
        if(aux < min){
            min = aux;
        }
    }
    return min;
}

double figura_ancho(figura_t *figura){
    double max = polilinea_ancho(figura -> polilineas[0]);
    for(size_t i = 0; i< figura -> cantidad_polilinea; i++){
        double aux = polilinea_ancho(figura -> polilineas[i]);
        if(aux > max){
            max = aux;
        }
    }
    return max;
}

bool punto_cerca_figura(float px, float py, figura_t *figura, float escala){
    for(size_t i = 0; i < figura -> cantidad_polilinea; i++){
        if(distancia_punto_a_polilinea(figura -> polilineas[i], px, py, escala) < 10){
            return true;
        }
    }
    return false;
}

void rotar_figura(figura_t *figura, float angulo){
    for(size_t i = 0; i < figura -> cantidad_polilinea; i++){
        rotar(figura -> polilineas[i], angulo);
    }
}

