#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "nave.h"
#include "figuras.h"
#include "lista.h"
#include "polilinea.h"
#include "color.h"
#include "config.h"
#include "disparo.h"
#include "caracteres.h"
#include "torreta.h"
#include "combustible.h"
#include "reactor.h"
#include "planeta.h"

#define vida_extra 10000

float f = 1;

float vida_plus = vida_extra;

void cargar_nivel(planeta_t *planetas, figura_t *torreta, figura_t *torreta_disparo, float puntos_torretas[][3], size_t cantidad_torretas, figura_t *combustible, float puntos_combustible[][3], size_t cantidad_combustible, figura_t *reactor, float puntos_reactor[][3], size_t cantidad_reactor){
    if(torreta != NULL && torreta_disparo != NULL){
        for(size_t i = 0; i < cantidad_torretas; i++){
            torreta_t *torreta_1 = crear_torreta(puntos_torretas[i][0], puntos_torretas[i][1], puntos_torretas[i][2], torreta_disparo, torreta);
            lista_insertar_ultimo(lista_torretas_planeta(planetas), torreta_1);
        }
    }
    if(combustible != NULL){
        for(size_t j = 0; j < cantidad_combustible; j++){
            combustible_t *combustible_1 = crear_combustible(combustible, puntos_combustible[j][0], puntos_combustible[j][1], puntos_combustible[j][2], true);
            lista_insertar_ultimo(lista_combustible_planeta(planetas), combustible_1);
        }
    }
    if(reactor != NULL){
        for(size_t k = 0; k < cantidad_reactor; k++){
            reactor_t *reactor_1 = crear_reactor(reactor, puntos_reactor[k][0], puntos_reactor[k][1], puntos_reactor[k][2]);
            lista_insertar_ultimo(lista_reactor_planeta(planetas), reactor_1);
        }
    }
}

int main(){
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Gravitar");
    
    FILE *archivo = fopen("figuras.bin", "rb");
    if(archivo == NULL){
        fprintf(stderr, "No pudo abrir\n");
        return 1;
    }
    
    lista_t *lista = lista_figuras(archivo);
    if(lista == NULL) return 1;
    fclose(archivo);

    figura_t *figura_nave = buscar_figura_nombre(lista,"NAVE");
    if(figura_nave == NULL){
        puts("error buscando nave");
        return 1;
    } 
     
    figura_t *figura_nave_chorro = buscar_figura_nombre(lista,"NAVE+CHORRO");
    if(figura_nave_chorro == NULL){
        puts("error buscando nave+chorro");
        return 1;
    }
    figura_t *figura_estrella = buscar_figura_nombre(lista,"ESTRELLA");
    if(figura_estrella == NULL){
        puts("error buscando estrella");
        return 1;
    }
    figura_t *figura_escudo1 = buscar_figura_nombre(lista, "ESCUDO"); 
    if(figura_escudo1 == NULL){
        puts("error buscando escudo");
        return 1;
    }
    figura_t *figura_escudo2 = buscar_figura_nombre(lista, "ESCUDO2");
    if(figura_escudo2 == NULL){
        puts("error buscando escudo2");
        return 1;
    }
    figura_t *figura_torreta = buscar_figura_nombre(lista, "TORRETA");
    if(figura_torreta == NULL){
        puts("error buscando torreta");
        return 1;
    }
    figura_t *figura_disparo = buscar_figura_nombre(lista, "DISPARO");
    if(figura_disparo == NULL){
        puts("error buscando disparo");
        return 1;
    }
    figura_t *figura_combustible = buscar_figura_nombre(lista, "COMBUSTIBLE");
    if(figura_combustible == NULL){
        puts("error buscand combustible");
        return 1;
    }
    figura_t *figura_torreta_disparo = buscar_figura_nombre(lista, "TORRETA+DISPARO");
    if(figura_torreta_disparo == NULL){
        puts("error buscando torreta+diapro");
        return 1;
    }
    figura_t *figura_reactor = buscar_figura_nombre(lista, "REACTOR");
    if(figura_reactor == NULL){
        puts("error busvando reactor");
        return 1;
    }
    //planetas
    figura_t *figura_planeta_1 = buscar_figura_nombre(lista, "PLANETA1");
    if(figura_planeta_1 == NULL){
        puts("error buscando planeta1");
        return 1;
    }
    figura_t *figura_planeta_2 = buscar_figura_nombre(lista, "PLANETA2");
    if(figura_planeta_2 == NULL){
        puts("error buscando planeta2");
        return 1;
    }
    figura_t *figura_planeta_3 = buscar_figura_nombre(lista, "PLANETA3");
    if(figura_planeta_3 == NULL){
        puts("error buscando planeta3");
        return 1;
    }
    figura_t *figura_planeta_4 = buscar_figura_nombre(lista, "PLANETA4");
    if(figura_nave == NULL){
        puts("error buscando planeta4");
        return 1;
    }
    figura_t *figura_planeta_5 = buscar_figura_nombre(lista, "PLANETA5");
    if(figura_planeta_5 == NULL){
        puts("error buscando planeta5");
        return 1;
    }
    //niveles
    figura_t *figura_nivel1 = buscar_figura_nombre(lista, "NIVEL1NE");
    if(figura_nivel1 == NULL){
        puts("error buscand nivel 1");
        return 1;
    }
    figura_t *figura_nivel2 = buscar_figura_nombre(lista, "NIVEL1SE");
    if(figura_nivel2 == NULL){
        puts("error buscando nivel 2");
        return 1;
    }
    figura_t *figura_nivel3 = buscar_figura_nombre(lista, "NIVEL1SW");
    if(figura_nivel3 == NULL){
        puts("error buscando nivel 3");
        return 1;
    }
    figura_t *figura_nivel4 = buscar_figura_nombre(lista, "NIVEL1NW");
    if(figura_nivel4 == NULL){
        puts("error buscando nivel 4");
        return 1;
    }
    figura_t *figura_nivel5 = buscar_figura_nombre(lista, "NIVEL1R");    
    if(figura_nivel5 == NULL){
        puts("error buscando nivel 5");
        return 1;
    }
    //Base
    figura_t *figura_base = buscar_figura_nombre(lista, "BASE");
    if(figura_base == NULL){
        puts("error buscando base");
        return 1;
    }
    //enemigos
    figura_t *figura_enemigo1 = buscar_figura_nombre(lista, "ENEMIGO1");
    if(figura_enemigo1 == NULL){
        puts("error buscando enemigo 1");
        return 1;
    }
    figura_t *figura_enemigo2 = buscar_figura_nombre(lista, "ENEMIGO2");
    if(figura_enemigo2 == NULL){
        puts("error buscando enemigo 2");
        return 1;
    }
    figura_t *figura_enemigo3 = buscar_figura_nombre(lista, "ENEMIGO3");
    if(figura_enemigo3 == NULL){
        puts("error buscando enemigo 3");
        return 1;
    }
    figura_t* figura_vidas = clonar_figura(figura_nave);
    rotar_figura(figura_vidas,PI/2);
    char combustible[10];
    char puntaje[10];

    //creamos la nave
    nave_t *nave = crear_nave(figura_escudo1, figura_escudo2);
    if(nave == NULL){
        puts("error nave");
        return 1;
    }
    //asignamos la figura
    asignar_nave_figura(nave, figura_nave);

    //lista para disparos
    lista_t *disparos_lista = lista_crear();
    //variables locales
    int dormir = 0;    
    bool chorro_prendido = false;
    bool rotar_derecha = false;
    bool rotar_izquierda = false;
    bool escudo = false;
    int en_un_nivel = 0;
    int sobre_estrella = 0;
    bool nave_disparo = false;

    //torretas
    float torreta_1[][3] = {{916, 75, -0.66}, {1425, 159, 0.66}};
    float torreta_2[][3] = {{423, 195, -0.66}, {806, 215, -0.33}, {1254, 153, 0.66}, {1587, 223, 2.23}};
    float torreta_3[][3] = {{70, 46, 0}, {506, 12, 0}, {952, 12, 0}, {1385, 12, 0}, {757, 210, 3.14}, {1161, 210, 3.14}};
    float torreta_4[][3] = {{257, 440, 0.66}, {719, 674, 2.23}, {985, 565, 0}, {1125, 417, 3.8}, {862, 163, 3.8}, {626, 323, 2.23}, {505, 331, 3.8}, {378, 296, 2.23}};
    //combustibles
    float combustible_1[][3] = {{1064, 13, 0}, {1685, 113, 0}};
    float combustible_2[][3] = {{482, 94, 0}, {1751, 247, 0}};
    float combustible_3[][3] = {{820, 46, 0}, {1196, 68, 0}, {1602, 46, 0}};
    float combustible_4[][3] = {{188, 429, 0}, {667, 600, 0}, {1054, 404, 3.14}, {574, 344, 3.14}};
    //reactores
    float reactor_5[][3] = {{815, 309, 0}};
    //planetas
    planeta_t *planeta_1 = crear_planeta("planeta1", figura_planeta_1, figura_nivel1, 663, 473, "2000");
    cargar_nivel(planeta_1, figura_torreta_disparo, figura_torreta, torreta_1, 2, figura_combustible, combustible_1, 2, NULL, NULL, 0);
    planeta_t *planeta_2 = crear_planeta("planeta2", figura_planeta_2, figura_nivel2, 671, 145, "4000");
    cargar_nivel(planeta_2, figura_torreta_disparo, figura_torreta, torreta_2, 4, figura_combustible, combustible_2, 2, NULL, NULL, 0);
    planeta_t *planeta_3 = crear_planeta("planeta3", figura_planeta_3, figura_nivel3, 110, 79, "6000");
    cargar_nivel(planeta_3, figura_torreta_disparo, figura_torreta, torreta_3, 6, figura_combustible, combustible_3, 3, NULL, NULL, 0);
    planeta_t *planeta_4 = crear_planeta("planeta4", figura_planeta_4, figura_nivel4, 204, 455, "8000");
    cargar_nivel(planeta_4, figura_torreta_disparo, figura_torreta, torreta_4, 8, figura_combustible, combustible_4, 4, NULL, NULL, 0);
    planeta_t *planeta_5 = crear_planeta("planeta5", figura_planeta_5, figura_nivel5, 111, 307, "9000");
    cargar_nivel(planeta_5, NULL, NULL, NULL, 0, NULL, NULL, 0, figura_reactor, reactor_5, 1);
    planeta_t *estrella = crear_planeta("estrella", figura_estrella, NULL, 457, 374, " ");
    planeta_t *base = crear_planeta("base", figura_base, NULL, 388, 218, " ");

    planeta_t *planetas[7] = {planeta_1, planeta_2, planeta_3, planeta_4, planeta_5, estrella, base};

    unsigned int ticks = SDL_GetTicks();
    while(1){
        if(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT)
                break;
            if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        chorro_prendido = true;
                        break;
                    case SDLK_DOWN:
                        escudo = true;
                        break;
                    case SDLK_RIGHT:
                        rotar_derecha = true;
                        break;
                    case SDLK_LEFT:
                        rotar_izquierda = true;
                        break;
                    case SDLK_SPACE:
                        nave_disparo= true;
                        break;
                }
            }
            else if(event.type == SDL_KEYUP){
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        chorro_prendido = false;
                        break;
                    case SDLK_DOWN:
                        escudo = false;
                        break;
                    case SDLK_RIGHT:
                        rotar_derecha = false;
                        break;
                    case SDLK_LEFT:
                        rotar_izquierda = false;
                        break;
                    case SDLK_SPACE:
                        nave_disparo= false;
                        break;
                }
            }
            continue;
        }
        
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
    
        //asignar los boleeanos
        if(nave_vidas(nave) == 0 || nave_combustible(nave) == 0){
            for(size_t i = 0; i < 5 * JUEGO_FPS; i++){
                dibujar_cadena("GAME", VENTANA_ANCHO/2 - 150, VENTANA_ALTO/2, renderer, 15, true, false, false);
                dibujar_cadena("OVER", VENTANA_ANCHO/2 - 150, VENTANA_ALTO/2 - 150, renderer, 15, true, false, false);
                SDL_RenderPresent(renderer);
            }
            break;
        }

        figura_t *clon_nave= clonar_figura(figura_nave);
        if(clon_nave == NULL) break;
        figura_t *clon_nave_chorro= clonar_figura(figura_nave_chorro);
        if(clon_nave_chorro == NULL){
            destruir_figura(clon_nave);
            break;
        }
        if(chorro_prendido){
            asignar_nave_figura(nave, clon_nave_chorro);
        }else{
            asignar_nave_figura(nave, clon_nave);
        }
        if(rotar_derecha){
            rotar_nave_derecha(nave);
        }else{
        }
        if(rotar_izquierda){
            rotar_nave_izquierda(nave);
        }
        if(nave_disparo){
            agregar_disparo_lista(disparos_lista, posicion_x_nave(nave), posicion_y_nave(nave), nave_angulo(nave), escudo);
        }

        nave_computar_rotar(nave);

        //zona dibujar
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

        //graficamos caracteres
        dibujar_cadena("SCORE", VENTANA_ANCHO/2 - 30, VENTANA_ALTO - 30, renderer, 2, false, true, true);
        dibujar_cadena("FUEL", VENTANA_ANCHO/2 - 20, VENTANA_ALTO - 50, renderer, 2, false, true, true);

        for(size_t i = 0; i < nave_vidas(nave); i++){
            if(nave_vidas(nave) > 0){
                figura_dibujar(figura_vidas, renderer , 2 , 50 + i * 30 , VENTANA_ALTO - 40);
            }
        }
        if(nave_puntos(nave) >= vida_plus) {
            vida_plus += vida_extra;
            nave_sumar_vida(nave);
        }
        char cadena_vidas[10];
        SDL_itoa(vida_plus,cadena_vidas, 10);
        dibujar_cadena(cadena_vidas, (VENTANA_ANCHO / 2) + 75, VENTANA_ALTO - 70, renderer, 2, false, true, true);
        dibujar_cadena("NEXT SHIP", (VENTANA_ANCHO/2)-100, VENTANA_ALTO-70, renderer, 2, false, true, false);

        SDL_itoa(nave_combustible(nave), combustible, 10);
        dibujar_cadena(combustible, VENTANA_ANCHO/2 + 30, VENTANA_ALTO - 50, renderer, 2, false,true,false);
        SDL_itoa(nave_puntos(nave),puntaje,10);
        dibujar_cadena(puntaje, VENTANA_ANCHO/2 + 40, VENTANA_ALTO - 30, renderer, 2, false,true,false);

        sobre_planeta(nave, planeta_1, &en_un_nivel);
        sobre_planeta(nave, planeta_2, &en_un_nivel);
        sobre_planeta(nave, planeta_3, &en_un_nivel);
        sobre_planeta(nave, planeta_4, &en_un_nivel);
        sobre_planeta(nave, planeta_5, &en_un_nivel);
        sobre_planeta(nave, estrella, &sobre_estrella);

        if(en_un_nivel == 1){
            for(size_t i = 0; i < 7; i++){
                if(nave_sobre_plantea(planetas[i])){
                    if(!planeta_infinito(planetas[i])){
                        planeta_finito_escala(planetas[i]);
                        if(!planeta_dentro_de_nivel(planetas[i])){
                            setear_datos_nave(nave, VENTANA_ANCHO/2, VENTANA_ALTO - 10, -PI/2, 0, 0);
                            setear_dentro_de_nivel_planeta(planetas[i], true);
                        }
                        if(posicion_y_nave(nave) > VENTANA_ALTO){
                            setear_datos_nave(nave, 388, 218, PI/2, 0, 0);
                            setear_datos_planeta(planetas[i], 0, 0, 0, false, false);
                            nivel_terminado(planetas[i], nave);
                            en_un_nivel = 0;
                        }
                        if(nave_choca_nivel(planetas[i], nave)){
                            setear_datos_nave(nave, VENTANA_ANCHO/2, VENTANA_ALTO - 10, -PI/2, 0, 0);
                            nave_restar_vida(nave);
                        }
                        recolectar_combustible(nave, planetas[i], planeta_escala(planetas[i]), escudo);
                        nave_computar_movimiento(nave);
                        disparos_de_torreta(disparos_lista, lista_torretas_planeta(planetas[i]), nave, planeta_escala(planetas[i]));
                        disparos_setear_iteracion(disparos_lista,nave , escudo, lista_torretas_planeta(planetas[i]), lista_reactor_planeta(planetas[i]), figura_nivel_planeta(planetas[i]), planeta_escala(planetas[i]));
                        dibujar_disparos(disparos_lista, renderer, planeta_escala(planetas[i]), 0, 0, figura_disparo);
                        rebotar_nave(nave);
                        graficar_nivel(planetas[i], renderer, -(centro_x_planeta(planetas[i])) * (planeta_escala(planetas[i])) + VENTANA_ANCHO / 2, centro_y_planeta(planetas[i]));
                        nave_dibujar(nave, renderer, planeta_escala(planetas[i]), 0, 0, escudo, en_un_nivel);
                        if(reactor_computar_tiempo(lista_reactor_planeta(planetas[i]))){
                            nave_restar_vida(nave);
                            setear_datos_nave(nave, VENTANA_ANCHO/2, VENTANA_ALTO - 10, -PI/2, 0, 0);
                        }
                        gravedad_planeta(nave, NAVE_ACELERACION, chorro_prendido);
                    }else{
                        double planeta_ancho = figura_ancho(figura_nivel_planeta(planetas[i]));
                        planeta_infinito_escala(planetas[i], nave);
                        if(!planeta_dentro_de_nivel(planetas[i])){
                            setear_datos_nave(nave, VENTANA_ANCHO/2, VENTANA_ALTO - 10, -PI/2, 0 , 0);
                            setear_dentro_de_nivel_planeta(planetas[i], true);
                            setear_centro_x_planeta(planetas[i], VENTANA_ANCHO/2);
                        }
                        if(posicion_y_nave(nave) > VENTANA_ALTO){
                            setear_datos_nave(nave, 388, 218, PI/2, 0, 0);
                            setear_datos_planeta(planetas[i], 0, 0, 0, false, false);
                            nivel_terminado(planetas[i], nave);
                            en_un_nivel = 0;
                        }
                        if(posicion_x_nave(nave) > planeta_ancho){
                            setear_datos_nave(nave, posicion_x_nave(nave) - planeta_ancho, posicion_y_nave(nave), nave_angulo(nave), velocidad_x_nave(nave), velocidad_y_nave(nave));
                            setear_centro_x_planeta(planetas[i], centro_x_planeta(planetas[i]) - planeta_ancho);
                        }
                        if(posicion_x_nave(nave) < 0){
                            setear_datos_nave(nave, posicion_x_nave(nave) + planeta_ancho, posicion_y_nave(nave), nave_angulo(nave), velocidad_x_nave(nave), velocidad_y_nave(nave));
                            setear_centro_x_planeta(planetas[i], centro_x_planeta(planetas[i]) + planeta_ancho);
                        }
                        if(nave_choca_nivel(planetas[i], nave)){
                            setear_datos_nave(nave, VENTANA_ANCHO/2, VENTANA_ALTO - 10, -PI/2, 0 , 0);
                            setear_datos_planeta(planetas[i], planeta_escala(planetas[i]), posicion_x_nave(nave), centro_y_planeta(planetas[i]), true, true);
                            nave_restar_vida(nave);
                        }
                        recolectar_combustible(nave, planetas[i], planeta_escala(planetas[i]), escudo);
                        nave_computar_movimiento(nave);
                        disparos_de_torreta(disparos_lista, lista_torretas_planeta(planetas[i]), nave, planeta_escala(planetas[i]));
                        disparos_setear_iteracion(disparos_lista, nave, escudo, lista_torretas_planeta(planetas[i]), lista_reactor_planeta(planetas[i]), figura_nivel_planeta(planetas[i]), planeta_escala(planetas[i]));
                        dibujar_disparos(disparos_lista, renderer, planeta_escala(planetas[i]), -(centro_x_planeta(planetas[i])) + VENTANA_ANCHO/2, 0, figura_disparo);
                        graficar_nivel(planetas[i], renderer, -planeta_ancho * (planeta_escala(planetas[i]))  - (centro_x_planeta(planetas[i])) * (planeta_escala(planetas[i])) + VENTANA_ANCHO/2, 0);
                        graficar_nivel(planetas[i], renderer, -(centro_x_planeta(planetas[i])) * (planeta_escala(planetas[i])) + VENTANA_ANCHO/2, 0);
                        graficar_nivel(planetas[i], renderer, planeta_ancho * (planeta_escala(planetas[i])) - (centro_x_planeta(planetas[i])) * (planeta_escala(planetas[i])) + VENTANA_ANCHO/2, 0);
                        nave_dibujar(nave, renderer, planeta_escala(planetas[i]),  -(centro_x_planeta(planetas[i])) + VENTANA_ANCHO/2, 0, escudo, en_un_nivel);
                        gravedad_planeta(nave, NAVE_ACELERACION, chorro_prendido);
                        }
                    }
                }
        }else{
            graficar_planetas_inicio(planetas, 7, renderer, f);
            gravedad_estrella(nave, chorro_prendido);
            nave_computar_movimiento(nave);
            rebotar_nave(nave);
            nave_dibujar(nave, renderer, f, 0, 0, escudo, en_un_nivel);
        }
        if(sobre_estrella == 1 && en_un_nivel == 0){
            setear_datos_nave(nave, 388, 218, PI/2, 0, 0);
            sobre_estrella = 0;
            nave_restar_vida(nave);
        }
        //zona de destruir naves clonadas

        destruir_figura(clon_nave);
        destruir_figura(clon_nave_chorro);

        // END código del alumno
        SDL_RenderPresent(renderer);
        ticks = SDL_GetTicks() - ticks;
        if(dormir) {
            SDL_Delay(dormir);
            dormir = 0;
        }
        else if(ticks < 1000 / JUEGO_FPS)
            SDL_Delay(1000 / JUEGO_FPS - ticks);
        ticks = SDL_GetTicks();
    }

    //zona de destruccion
    for(size_t i = 0; i < 7; i++){
        planeta_destruir(planetas[i]);
    }
    destruir_nave(nave);
    lista_destruir(lista, destruir_figura);
    lista_destruir(disparos_lista, destruir_disparo);
    destruir_figura(figura_vidas);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
