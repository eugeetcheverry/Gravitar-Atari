#ifndef _LETRAS_H_
#define _LETRAS_H_
#include "polilinea.h"
#include "figuras.h"
#include <stdbool.h>


#define CARACTER_ANCHO 6
#define CARACTER_ALTO 6

typedef struct caracteres caracteres_t;

const caracteres_t digito_a_puntos(char digito);

polilinea_t *digito_a_polilinea(char digito, bool r, bool g, bool b);

const caracteres_t digito_a_puntos(char digito);

polilinea_t *digito_a_polilinea(char digito, bool r, bool g, bool b);

void dibujar_cadena(char cadena[MAX_STRING], float px , float py , void* renderer , float f, bool r, bool g, bool b);

void dibujar_caracter(char c, float px, float py, void *renderer, float escala, bool r, bool g, bool b);

#endif // _LETRAS_H_
