#ifndef __INICIALIZAR_JUEGO_H__
#define __INICIALIZAR_JUEGO_H__

#include <stdio.h>
#include "cocineritos.h"
#include "funciones_varias.h"

/*-------OBSTACULOS----------*/
#define FUEGO 'F'
#define AGUJEROS 'A'

/*-------HERRAMIENTAS----------*/
#define MATAFUEGOS 'M'
#define CUCHILLO 'C'
#define HORNO 'H'

/*-------INGREDIENTES----------*/
#define LECHUGA 'L'
#define TOMATE 'T'
#define MILANESA 'I'
#define CARNE 'B'
#define PAN 'N'
#define JAMON 'J'
#define QUESO 'Q'
#define MASA 'O'

/*--------COMIDAS-----------*/
#define ENSALADA 'E'
#define PIZZA 'P'
#define HAMBURGUESA 'H'
#define SANDWICH 'S'

/*------ PERSONAJES -----------*/
#define STITCH 'S'
#define REUBEN 'R'

/*------ELEMENTOS DE LA MATRIZ------*/
#define PARED '#'
#define MESA '_'
#define PUERTA_SALIDA 'P'
#define VACIO 'V'
#define CENTRO_FILA 10
#define CENTRO_COLUMNA 10
#define PRIMERA_FILA 0
#define FILA_DEL_MEDIO 10
#define ULTIMA_FILA 20

void inicializar_precio_total(juego_t* juego, int precio);

void inicializar_paredes(juego_t* juego);

void inicializar_mesa(juego_t* juego);

void inicializar_agujeros(juego_t* juego);

void inicializar_herramientas(juego_t* juego);

void inicializar_ingredientes_ensalada(juego_t* juego);

void inicializar_ingredientes_pizza(juego_t* juego);

void inicializar_ingredientes_hamburguesa(juego_t* juego);

void inicializar_ingredientes_sandwich(juego_t* juego);

void inicializar_comida(juego_t* juego);

void inicializar_puerta_salida(juego_t* juego);

void inicializar_personajes(juego_t* juego);

void inicializar_fuego(juego_t* juego, int orden);

void inicializar_matafuegos(juego_t* juego, int orden);

void inicializar_grilla_vacia(char grilla[MAX_FIL][MAX_COL]);

void llenar_grilla(juego_t juego, char grilla[MAX_FIL][MAX_COL]);

void dibujar_grilla(char grilla[MAX_FIL][MAX_COL]);

#endif