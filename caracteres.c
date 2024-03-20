#include "caracteres.h"
#include "color.h"
#include "polilinea.h"
#include "figuras.h"
#include <stdbool.h>


const float caracter_a[7][2] = {
	{0, 0},
	{0, 4},
	{2, 6},
	{4, 4},
	{4, 0},
	{4, 2},
	{0, 2}
};

const float caracter_b[12][2] = {
	{0, 3},
	{0, 6},
	{3, 6},
	{4, 5},
	{4, 4},
	{3, 3},
	{0, 3},
	{0, 0},
	{3, 0},
	{4, 1},
	{4, 2},
	{3, 3},
};

const float caracter_c[4][2] = {
	{4, 0},
	{0, 0},
	{0, 6},
	{4, 6},
};

const float caracter_d[7][2] = {
	{0, 0},
	{0, 6},
	{2, 6},
	{4, 4},
	{4, 2},
	{2, 0},
	{0, 0}
};

const float caracter_e[7][2] = {
	{4, 0},
	{0, 0},
	{0, 3},
	{3, 3},
	{0, 3},
	{0, 6},
	{4, 6},
};

const float caracter_f[6][2] = {
	{0, 0},
	{0, 3},
	{3, 3},
	{0, 3},
	{0, 6},
	{4, 6},
};

const float caracter_g[7][2] = {
	{2, 2},
	{4, 2},
	{4, 0},
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 4},
};

const float caracter_h[6][2] = {
	{0, 0},
	{0, 6},
	{0, 3},
	{4, 3},
	{4, 6},
	{4, 0},
};

const float caracter_i[6][2] = {
	{0, 0},
	{4, 0},
	{2, 0},
	{2, 6},
	{4, 6},
	{0, 6},
};

const float caracter_j[4][2] = {
	{0, 2},
	{2, 0},
	{4, 0},
	{4, 6},
};

const float caracter_k[6][2] = {
	{0, 0},
	{0, 6},
	{0, 3},
	{3, 6},
	{0, 3},
	{3, 0},
};

const float caracter_l[3][2] = {
	{4, 0},
	{0, 0},
	{0, 6},
};

const float caracter_m[5][2] = {
	{0, 0},
	{0, 6},
	{2, 4},
	{4, 6},
	{4, 0},
};

const float caracter_n[4][2] = {
	{0, 0},
	{0, 6},
	{4, 0},
	{4, 6},
};

const float caracter_o[5][2] = {
	{4, 0},
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 0},
};

const float caracter_p[5][2] = {
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 3},
	{0, 3},
};

const float caracter_q[9][2] = {
	{2, 2},
	{3, 1},
	{2, 0},
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 2},
	{3, 1},
	{4, 0},
};

const float caracter_r[7][2] = {
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 3},
	{0, 3},
	{1, 3},
	{4, 0},
};

const float caracter_s[6][2] = {
	{0, 0},
	{4, 0},
	{4, 3},
	{0, 3},
	{0, 6},
	{4, 6},
};

const float caracter_t[4][2] = {
	{2, 0},
	{2, 6},
	{4, 6},
	{0, 6},
};

const float caracter_u[4][2] = {
	{0, 6},
	{0, 0},
	{4, 0},
	{4, 6},
};

const float caracter_v[3][2] = {
	{0, 6},
	{2, 0},
	{4, 6},
};

const float caracter_w[5][2] = {
	{0, 6},
	{0, 0},
	{2, 2},
	{4, 0},
	{4, 6},
};

const float caracter_x[5][2] = {
	{0, 0},
	{4, 6},
	{2, 3},
	{0, 6},
	{4, 0},
};

const float caracter_y[5][2] = {
	{0, 6},
	{2, 4},
	{4, 6},
	{2, 4},
	{2, 0},
};

const float caracter_z[4][2] = {
	{0, 6},
	{4, 6},
	{0, 0},
	{4, 0},
};

const float caracter_0[5][2] = {
	{4, 0},
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 0},
};

const float caracter_1[2][2] = {
	{2, 0},
	{2, 6},
};

const float caracter_2[6][2] = {
	{0, 6},
	{4, 6},
	{4, 3},
	{0, 3},
	{0, 0},
	{4, 0},
};

const float caracter_3[7][2] = {
	{0, 0},
	{4, 0},
	{4, 3},
	{0, 3},
	{4, 3},
	{4, 6},
	{0, 6},
};

const float caracter_4[5][2] = {
	{0, 6},
	{0, 3},
	{4, 3},
	{4, 6},
	{4, 0},
};

const float caracter_5[6][2] = {
	{0, 0},
	{4, 0},
	{4, 3},
	{0, 3},
	{0, 6},
	{4, 6},
};

const float caracter_6[5][2] = {
	{0, 6},
	{0, 0},
	{4, 0},
	{4, 3},
	{0, 3},
};

const float caracter_7[3][2] = {
	{0, 6},
	{4, 6},
	{4, 0},
};

const float caracter_8[7][2] = {
	{0, 3},
	{0, 6},
	{4, 6},
	{4, 0},
	{0, 0},
	{0, 3},
	{4, 3},
};

const float caracter_9[5][2] = {
	{4, 0},
	{4, 6},
	{0, 6},
	{0, 3},
	{4, 3},
};

const float caracter_derecha[5][2] = {
	{0, 3},
	{12, 3},
	{9, 5},
	{9, 1},
	{12, 3},
};

const float caracter_izquierda[5][2] = {
	{12, 3},
	{0, 3},
	{3, 5},
	{3, 1},
	{0, 3},
};

const float caracter_arriba[5][2] = {
	{5, -2},
	{5, 10},
	{3, 7},
	{7, 7},
	{5, 10},
};

const float caracter_abajo[5][2] = {
	{5, 10},
	{5, -2},
	{3, 1},
	{7, 1},
	{5, -2},
};

const float caracter_espacio[1][2] = {
	{0, 0}
};
/*
typedef enum caracteres{
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p,
	q,
	r,
	s,
	t, 
	u,
	v,
	w,
	x,
	y,
	z,
	cero,
	uno,
	dos,
	tres,
	cuatro,
	cinco,
	seis,
	siete,
	ocho,
	nueve,
	derecha,
	izquierda,
	arriba,
	abajo,
	espacio,
}caracteres_t;
*/
struct caracteres{
	char digito;
	const float(*puntos)[2];
	size_t tam;
};

const caracteres_t caracter[] = {
    {'A', caracter_a, (sizeof(caracter_a)/sizeof(caracter_a[0][0])/2)},
	{ 'B', caracter_b, (sizeof(caracter_b)/sizeof(caracter_b[0][0])/2)},
	{ 'C', caracter_c, (sizeof(caracter_c)/sizeof(caracter_c[0][0])/2)},
	{ 'D', caracter_d, (sizeof(caracter_d)/sizeof(caracter_d[0][0])/2)},
	{ 'E', caracter_e, (sizeof(caracter_e)/sizeof(caracter_e[0][0])/2)},
	{ 'F', caracter_f, (sizeof(caracter_f)/sizeof(caracter_f[0][0])/2)},
	{ 'G', caracter_g, (sizeof(caracter_g)/sizeof(caracter_g[0][0])/2)},
	{ 'H', caracter_h, (sizeof(caracter_h)/sizeof(caracter_h[0][0])/2)},
	{ 'I', caracter_i, (sizeof(caracter_i)/sizeof(caracter_i[0][0])/2)},
	{ 'J', caracter_j, (sizeof(caracter_j)/sizeof(caracter_j[0][0])/2)},
	{ 'K', caracter_k, (sizeof(caracter_k)/sizeof(caracter_k[0][0])/2)},
	{ 'L', caracter_l, (sizeof(caracter_l)/sizeof(caracter_l[0][0])/2)},
	{ 'M', caracter_m, (sizeof(caracter_m)/sizeof(caracter_m[0][0])/2)},
	{ 'N', caracter_n, (sizeof(caracter_n)/sizeof(caracter_n[0][0])/2)},
	{ 'O', caracter_o, (sizeof(caracter_o)/sizeof(caracter_o[0][0])/2)},
	{ 'P', caracter_p, (sizeof(caracter_p)/sizeof(caracter_p[0][0])/2)},
	{ 'Q', caracter_q, (sizeof(caracter_q)/sizeof(caracter_q[0][0])/2)},
	{ 'R', caracter_r, (sizeof(caracter_r)/sizeof(caracter_r[0][0])/2)},
	{ 'S', caracter_s, (sizeof(caracter_s)/sizeof(caracter_s[0][0])/2)},
	{ 'T', caracter_t, (sizeof(caracter_t)/sizeof(caracter_t[0][0])/2)},
	{ 'U', caracter_u, (sizeof(caracter_u)/sizeof(caracter_u[0][0])/2)},
	{ 'V', caracter_v, (sizeof(caracter_v)/sizeof(caracter_v[0][0])/2)},
	{ 'W', caracter_w, (sizeof(caracter_w)/sizeof(caracter_w[0][0])/2)},
	{ 'X', caracter_x, (sizeof(caracter_x)/sizeof(caracter_x[0][0])/2)},
	{ 'Y', caracter_y, (sizeof(caracter_y)/sizeof(caracter_y[0][0])/2)},
	{ 'Z', caracter_z, (sizeof(caracter_z)/sizeof(caracter_z[0][0])/2)},
	{ '0', caracter_0, (sizeof(caracter_0)/sizeof(caracter_0[0][0])/2)},
	{ '1', caracter_1, (sizeof(caracter_1)/sizeof(caracter_1[0][0])/2)},
	{ '2', caracter_2, (sizeof(caracter_2)/sizeof(caracter_2[0][0])/2)},
	{ '3', caracter_3, (sizeof(caracter_3)/sizeof(caracter_3[0][0])/2)},
	{ '4', caracter_4, (sizeof(caracter_4)/sizeof(caracter_4[0][0])/2)},
	{ '5', caracter_5, (sizeof(caracter_5)/sizeof(caracter_5[0][0])/2)},
	{ '6', caracter_6, (sizeof(caracter_6)/sizeof(caracter_6[0][0])/2)},
	{ '7', caracter_7, (sizeof(caracter_7)/sizeof(caracter_7[0][0])/2)},
	{ '8', caracter_8, (sizeof(caracter_8)/sizeof(caracter_8[0][0])/2)},
	{ '9', caracter_9, (sizeof(caracter_9)/sizeof(caracter_9[0][0])/2)},
	{ '>', caracter_derecha, (sizeof(caracter_derecha)/sizeof(caracter_derecha[0][0])/2)},
	{ '<', caracter_izquierda, (sizeof(caracter_izquierda)/sizeof(caracter_izquierda[0][0])/2)},
	{ '^', caracter_arriba, (sizeof(caracter_arriba)/sizeof(caracter_arriba[0][0])/2)},
	{ 'v', caracter_abajo, (sizeof(caracter_abajo)/sizeof(caracter_abajo[0][0])/2)},
	{ ' ', caracter_espacio, (sizeof(caracter_espacio)/sizeof(caracter_espacio[0][0])/2)},
};


const caracteres_t digito_a_puntos(char digito){
	size_t n = sizeof(caracter)/sizeof(caracter[0]);
	for(size_t i = 0 ; i < n ; i++){
		if(caracter[i].digito == digito){
			return caracter[i];
		}
	}
	return caracter[n];
}

polilinea_t *digito_a_polilinea(char digito, bool r, bool g, bool b){ //para la nueva implementacion
	caracteres_t caracter = digito_a_puntos(digito);
	color_t color = color_crear(r, g, b);
	polilinea_t *polilinea = polilinea_crear(caracter.puntos, caracter.tam, color);
	return polilinea;
}

void dibujar_cadena(char *cadena, float px , float py , void* renderer, float f, bool r, bool g, bool b){
	for(size_t i = 0; cadena[i]!= '\0'; i++){
		polilinea_t *aux = digito_a_polilinea(cadena[i], r, g, b);
		polilinea_dibujar(aux, renderer, f, px + f * CARACTER_ANCHO * i, py);
		polilinea_destruir(aux);
	}
}

void dibujar_caracter(char c, float px, float py, void *renderer, float escala, bool r, bool g, bool b){
	polilinea_t *aux = digito_a_polilinea(c, r, g, b);
	polilinea_dibujar(aux, renderer, 10, px, py);
	polilinea_destruir(aux);
}

