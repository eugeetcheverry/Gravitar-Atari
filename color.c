#include "color.h"
#include <stdint.h>

#define MASK_R 0x01
#define MASK_G 0x02 
#define MASK_B 0x04 

color_t color_crear(bool r, bool g, bool b){
    color_t color = 0X00;

    if(r){
       color = color | MASK_R;
    }
    if(g){
        color = color | MASK_G;
    }
    if(b){
        color = color | MASK_B;
    }

    return color;
}

void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b){
    *r = 0;
    *g = 0;
    *b = 0;
    if(c & MASK_R){
        *r = 255;
    }
    if(c & MASK_G){
        *g = 255;
    }
    if(c & MASK_B){
        *b = 255;
    }
}
