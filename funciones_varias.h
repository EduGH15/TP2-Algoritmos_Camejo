#ifndef __FUNCIONES_VARIAS_H__
#define __FUNCIONES_VARIAS_H__

#include "cocineritos.h"
#include "validaciones.h"

coordenada_t generar_coordenada_aleatoria(int fil_inicial, int amplitud_fila, int col_inicial, int amplitud_columna);

coordenada_t generar_posicion_nueva(personaje_t personaje, char movimiento);

void mover_jugador(personaje_t* jugador, char movimiento);

char buscar_tipo_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes, int fila, int columna);

void ocultar_ingrediente(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes);

void cambiar_posicion_ingrediente(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes, int fila, int columna);

void cortar_ingrediente(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes);

void cocinar_ingrediente(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes);

char buscar_tipo_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna);

void ocultar_herramienta(char tipo_herramienta, objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas);

int orden_actual(char comida_actual);

void asignar_obstaculo(objeto_t obstaculos[MAX_OBSTACULOS], int* tope_obstaculos, coordenada_t posicion, char tipo_obstaculo);

void asignar_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int* tope_herramientas, coordenada_t posicion, char tipo_herramienta);

void asignar_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int* tope_ingredientes, coordenada_t posicion, char tipo_ingrediente);

void asignar_personaje(personaje_t* personaje, coordenada_t posicion, char tipo, char objeto_en_mano);

void cargar_vector(juego_t* juego, int orden);

void cambiar_nivel(juego_t* juego);

#endif /*__FUNCIONES_VARIAS_H__*/