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
#define ESPACIO_BLANCO ' '; 

/*------POSICIONES----------------*/
#define CENTRO_FILA 10
#define CENTRO_COLUMNA 10
#define PRIMERA_FILA 0
#define FILA_DEL_MEDIO 10
#define ULTIMA_FILA 20
#define PRIMERA_COLUMNA 0
#define ULTIMA_COLUMNA 20
#define MAX_FIL 21
#define MAX_COL 21

/*------------VALORES VARIOS-----------*/

#define CANTIDAD_AGUJEROS_CUADRANTE 10
#define CANTIDAD_HERRAMIENTAS_CUADRANTE 2
#define ORDEN_ENSALADA 0
#define ORDEN_PIZZA 1
#define ORDEN_HAMBURGUESA 2
#define ORDEN_SANDWICH 3

/*------------TECLAS-----------------*/

#define ARRIBA 'W'
#define ABAJO 'S'
#define DERECHA 'D'
#define IZQUIERDA 'A'
#define CAMBIAR_PERSONAJE 'X'
#define ACTIVAR_MATAFUEGO 'M'
#define ACTIVAR_CUCHILLO 'C'
#define ACTIVAR_HORNO 'H'
#define AGARRAR 'R'
#define PASAR 'T'

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

#endif /*__INICIALIZAR_JUEGO_H__*/