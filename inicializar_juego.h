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
#define MOVIMIENTOS_MAX 15
#define MOVIMIENTOS_MIN 0

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

/*
Pre: El parámetro de precio no puede ser negativo
Post: asigna un valor a precio_total del struct de juego
*/
void inicializar_precio_total(juego_t* juego, int precio);

/*
Pre: --------------------------------------------------------
Post: Le asigna una posición a cada pared, siendo en total 98 paredes. El tope del paredes lo inicializa en cero.
*/
void inicializar_paredes(juego_t* juego);

/*
Pre: ............................................................
Post: Le asigna una posición a la mesa del struct de juego.
*/
void inicializar_mesa(juego_t* juego);

/*
Pre:-----------------------------------------------------------
Post:Le asigna una posición y un tipo 'A' al vector de obstáculos, siendo 10 agujeros en el cuadrante de Stitch y 10 en el cuadrante de Reuben. El tope de obstáculo lo inicializa en cero.
*/
void inicializar_agujeros(juego_t* juego);

/*
Pre: ...........................................................
Post: Le asigna una posicion y un tipo ('C' o 'H') al vector de herramientas, siendo dos herramientas por cuadrante. El tope de herramientas lo inicializa en cero.
*/
void inicializar_herramientas(juego_t* juego);

/*
Pre:--------------------------------------------------------
Post: Le asigna una posición a cada ingrediente, un tipo ('L' o 'T') y dos booleanos (esta_cortado y esta_cocinado que comienzan en false) al vector de ingredientes. El tope de ingredientes de la ensalada lo inicializa en cero.
*/
void inicializar_ingredientes_ensalada(juego_t* juego);

/*
Pre:----------------------------------------------------------------
Post:Le asigna una posición a cada ingrediente, un tipo ('J' o 'Q' o 'O') y dos booleanos (esta_cortado y esta_cocinado que comienzan en false) al vector de ingredientes. El tope de ingredientes de la pizza lo inicializa en cero.
*/
void inicializar_ingredientes_pizza(juego_t* juego);

/*
Pre: ...................................................................................
post: Le asigna una posición a cada ingrediente, un tipo ('L' o 'T' o 'N' o 'B') y dos booleanos (esta_cortado y esta_cocinado que comienzan en false) al vector de ingredientes. El tope de ingredientes de la hamburguesa lo inicializa en cero.
*/
void inicializar_ingredientes_hamburguesa(juego_t* juego);

/*
Pre:------------------------------------------------------------------
Post: Le asigna una posición a cada ingrediente, un tipo ('L' o 'T' o 'N' o 'J' o 'I' o 'Q') y dos booleanos (esta_cortado y esta_cocinado que comienzan en false) al vector de ingredientes. El tope de ingredientes del sandwich lo inicializa en cero.
*/
void inicializar_ingredientes_sandwich(juego_t* juego);

/*
Pre:------------------------------------------------------------------------------------------
Post: Dependiendo de cual sea la comida actual, inicializará los ingredientes de la ensalada, la pizza, la hamburguesa o el sandwich.
*/
void inicializar_comida(juego_t* juego);

/*
Pre:......................................................................................
Post: Le asigna una posición y un tipo 'P' a la puerta de salida.
*/
void inicializar_puerta_salida(juego_t* juego);

/*
Pre:-------------------------------------------------------
Post: inicializa a dos personajes (Stitch y Reuben), asignándole dos posiciones, un tipo 'S' o 'R' y objeto en mano.
*/
void inicializar_personajes(juego_t* juego);

/*
Pre:el parámetro orden debe ser válido (0: ensalada, 1: pizza, 2: hamburguesa, 3:sandwich).
Post: Le asigna una posición al fuego y un tipo 'F', el cual es agregado vector de obstáculos.
*/
void inicializar_fuego(juego_t* juego, int orden);

/*
Pre:el parámetro orden debe ser válido (0: ensalada, 1: pizza, 2: hamburguesa, 3:sandwich).
Post: Le asigna una posición al matafuegos y un tipo 'M', el cual es agregado vector de herramientas.
*/
void inicializar_matafuegos(juego_t* juego, int orden);

/*
Pre:-------------------------------------------------
Post: Llena cada posición de la grilla con espacios vacios.
*/
void inicializar_grilla_vacia(char grilla[MAX_FIL][MAX_COL]);

/*
Pre:............................................................
Post: Llena la grilla con cada elemento presente en el Struct de juego a excepción de: personaje_activo, comida_actual, comida_lista, precio_total y movimientos, que son elementos no mostrados en la matriz.
*/
void llenar_grilla(juego_t juego, char grilla[MAX_FIL][MAX_COL]);

/*
Pre: -------------------------------------------------
Post: Imprime la grilla.
*/
void dibujar_grilla(char grilla[MAX_FIL][MAX_COL]);

#endif /*__INICIALIZAR_JUEGO_H__*/