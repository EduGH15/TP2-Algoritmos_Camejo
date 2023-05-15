#ifndef __VALIDACIONES_H__
#define __VALIDACIONES_H__

#include <stdbool.h>
#include <stdlib.h>
#include "cocineritos.h"
#include "inicializar_juego.h"

/*
Pre: ---------------------------------------------------
Post: Dada una fila y una columna, devuelve true en caso de que haya un jugador en esa posición. En caso contrario, devuelve false.
*/
bool hay_jugador(juego_t juego, int fila, int columna);

/*
Pre: El parámetro tope de paredes debe ser menor o igual a la constante MAX_PAREDES.
Post: Dada una fila y una columna, devuelve true en caso de que haya una pared en esa posición. En caso contrario, devuelve false.
*/
bool hay_pared(coordenada_t paredes[MAX_PAREDES], int tope_paredes, int fila, int columna);

/*
Pre: El parámetro tope de obstáculos debe ser menor o igual a la constante MAX_OBSTACULOS.
Post: Dada una fila y una columna, devuelve true en caso de que haya un obstaculo en esa posición. En caso contrario, devuelve false.
*/
bool hay_obstaculo(objeto_t obstaculos[MAX_OBSTACULOS],int tope_obstaculo, int fila, int columna);

/*
Pre: El parámetro tope de obstáculos debe ser menor o igual a la constante MAX_OBSTACULOS.
Post: Dada una fila y una columna, devuelve true en caso de que haya un fuego en esa posición. En caso contrario, devuelve false.
*/
bool hay_fuego(objeto_t obstaculos[MAX_OBSTACULOS],int tope_obstaculo, int fila, int columna);

/*
Pre: El parámetro tope de obstáculos debe ser menor o igual a la constante MAX_OBSTACULOS.
Post: Dada una fila y una columna, devuelve true en caso de que haya un fuego en el cuadrante de Stitch. En caso contrario, devuelve false.
*/
bool hay_fuego_cuadrante_stitch(objeto_t obstaculos[MAX_OBSTACULOS],int tope_obstaculo);

/*
Pre: El parámetro tope de obstáculos debe ser menor o igual a la constante MAX_OBSTACULOS.
Post: Dada una fila y una columna, devuelve true en caso de que haya un fuego en el cuadrante de Reuben. En caso contrario, devuelve false.
*/
bool hay_fuego_cuadrante_reuben(objeto_t obstaculos[MAX_OBSTACULOS],int tope_obstaculo);

/*
Pre: El parámetro tope de herramientas debe ser menor o igual a la constante MAX_HERRAMIENTAS.
Post: Dada una fila y una columna, devuelve true en caso de que haya una herramienta en esa posición. En caso contrario, devuelve false.
*/
bool hay_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna);

/*
Pre: El parámetro tope de ingredientes debe de ser menor o igual a la constante MAX_INGREDIENTES.
Post: Dada una fila y una columna, devuelve true en caso de que haya un ingrediente en esa posición. En caso contrario, devuelve false.
*/
bool hay_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes, int fila, int columna);

/*
Pre:-------------------------------------------------------------------
Post: dada una fila y una columna, devuelve true en caso de que haya una mesa en esa posición. En caso contrario, devuelve false.
*/
bool hay_mesa(coordenada_t mesa, int fila, int columna);

/*
Pre: El parámetro tope de herramientas debe ser menor o igual a la constante MAX_HERRAMIENTAS.
Post: Dada una fila y una columna, devuelve true en caso de que haya un horno en esa posición. En caso contrario, devuelve false.
*/
bool hay_horno(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna);

/*
Pre: El parámetro tope de herramientas debe ser menor o igual a la constante MAX_HERRAMIENTAS.
Post: Dada una fila y una columna, devuelve true en caso de que haya un matafuegos en esa posición. En caso contrario, devuelve false.
*/
bool hay_matafuegos(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna);

/*
Pre: ----------------------------------------------------------------------
Post: Dada una fila y una columna, devuelve true en caso de que haya una puerta de salida en esa posición. En caso contrario, devuelve false.
*/
bool hay_puerta_salida(coordenada_t puerta_salida, int fila, int columna);

/*
Pre: ----------------------------------------------------------------------
Post: Dada una fila y una columna, devuelve true en caso de que no haya una pared, un fuego, un horno o una mesa en esa posición. En caso contrario, devuelve false.
*/
bool es_movimiento_valido(juego_t juego, int fila, int columna);

/*
Pre: el parámetro distancia debe ser un número positivo
Post: Devuelve True en caso de que el jugador y el elemento se encuentren a una distancia manhattan igual o menor a la distancia que se pasa por parámetro. En caso contrario, devuelve false.
*/
bool distancia_manhattan(coordenada_t posicion_jugador, coordenada_t posicion_elemento, int distancia);

/*
Pre;-----------------------------------------------------------------
Post: Dada dos filas, devuelve true si ambas pertenecen al mismo cuadrante. En caso contrario, devuelve false.
*/
bool estan_mismo_cuadrante(int fila_objeto_1,  int fila_objeto_2);

/*
Pre: El parámetro tope de ingredientes debe de ser menor o igual a la constante MAX_INGREDIENTES.
Post: Dado un tipo de ingrediente, devuelve true si este se encuentra cortado. En caso contrario, devuelve false.
*/
bool esta_cortado(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes);

/*
Pre: El parámetro tope de ingredientes debe de ser menor o igual a la constante MAX_INGREDIENTES.
Post: Dado un tipo de ingrediente, devuelve true si este se encuentra cocinado. En caso contrario, devuelve false.
*/
bool esta_cocinado(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes);

/*
Pre: el parámetro orden debe tomar valores válidos (0: ensalada, 1: pizza, 2: hamburguesa, 3: sandwich).
Post: Dada una fila y una columna, devuelve true si en esta posición no hay pared, mesa, obstáculo, herramienta, ingrediente, jugador ni puerta de salida.
*/
bool hay_vacio(juego_t juego, int orden, int fila, int columna);


#endif /*__VALIDACIONES_H__*/