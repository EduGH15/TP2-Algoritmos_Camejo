#ifndef __VALIDACIONES_H__
#define __VALIDACIONES_H__

#include <stdbool.h>
#include <stdlib.h>
#include "cocineritos.h"
#include "inicializar_juego.h"

bool hay_jugador(juego_t juego, int fila, int columna);

bool hay_pared(coordenada_t paredes[MAX_PAREDES], int tope_paredes, int fila, int columna);

bool hay_obstaculo(objeto_t obstaculos[MAX_OBSTACULOS],int tope_obstaculo, int fila, int columna);

bool hay_fuego(objeto_t obstaculos[MAX_OBSTACULOS],int tope_obstaculo, int fila, int columna);

bool hay_fuego_cuadrante_stitch(objeto_t obstaculos[MAX_OBSTACULOS],int tope_obstaculo);

bool hay_fuego_cuadrante_reuben(objeto_t obstaculos[MAX_OBSTACULOS],int tope_obstaculo);

bool hay_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna);

bool hay_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes, int fila, int columna);

bool hay_mesa(coordenada_t mesa, int fila, int columna);

bool hay_horno(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna);

bool hay_matafuegos(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna);

bool hay_puerta_salida(coordenada_t puerta_salida, int fila, int columna);

bool es_movimiento_valido(juego_t juego, int fila, int columna);

bool distancia_manhattan(coordenada_t posicion_jugador, coordenada_t posicion_elemento, int distancia);

bool estan_mismo_cuadrante(int fila_objeto_1,  int fila_objeto_2);

bool esta_cortado(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes);

bool esta_cocinado(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes);

bool hay_vacio(juego_t juego, int orden, int fila, int columna);


#endif /*__VALIDACIONES_H__*/