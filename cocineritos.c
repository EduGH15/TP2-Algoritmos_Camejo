#include <stdio.h>
#include <stdbool.h>

#include "cocineritos.h"

#define MAX_FIL 21
#define MAX_COL 21

/*-------OBSTACULOS----------*/
const char FUEGO = 'F';
const char AGUJEROS = 'A';

/*-------HERRAMIENTAS----------*/
const char MATAFUEGOS = 'M';
const char CUCHILLO = 'C';
const char HORNO = 'H';

/*-------INGREDIENTES----------*/
const char LECHUGA = 'L';
const char TOMATE = 'T';
const char MILANESA = 'I';
const char CARNE = 'B';
const char PAN = 'N';
const char JAMON = 'J';
const char QUESO = 'Q';
const char MASA = 'O';

/*--------COMIDAS-----------*/
const char ENSALADA = 'E';
const char PIZZA = 'P';
const char HAMBURGUESA = 'H';
const char SANDWICH = 'S';

/*------ PERSONAJES -----------*/
const char STICH = 'S';
const char REUBEN = 'R';
//const char PERSONAJE_AGUJERO = '*';
//const char PERSONAJE_HERRAMIENTA = '@';
//const char PERSONAJE_INGREDIENTE = '$';

/*------ELEMENTOS DE LA MATRIZ------*/
const char PARED = '#';
const char MESA = '_';
const char PUERTA_SALIDA = 'P';
const char VACIO = ' ';

bool hay_jugador(juego_t juego, int fila, int columna){
	return (juego.stitch.posicion.fil == fila && juego.stitch.posicion.col == columna) || (juego.reuben.posicion.fil == fila && juego.reuben.posicion.col == columna);
}

bool hay_obstaculo(objeto_t obstaculos[MAX_OBSTACULOS],int tope_obstaculo, int fila, int columna){
	bool encontro = false;
	int i = 0;
	while(i < tope_obstaculo && !encontro){
		if(obstaculos[i].posicion.fil == fila && obstaculos[i].posicion.col == columna){
			encontro = true;
		}
		i++;
	}
	return encontro;
}

hay_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna){
	bool encontro = false;
	int i = 0;
	while(i < tope_herramientas && !encontro){
		if(herramientas[i].posicion.fil == fila && herramientas[i].posicion.col == columna){
			encontro = true;
		}
		i++;
	}
	return encontro;
}

hay_pared(coordenada_t paredes[MAX_PAREDES], int tope_paredes, int fila, int columna){
	bool encontro = false;
	int i = 0;
	while(i < tope_paredes && !encontro){
		if(paredes[i].fil == fila && paredes[i].col == columna){
			encontro == true;
		}
		i++;
	}
	return encontro;
}

hay_mesa(coordenada_t mesa, int fila, int columna){
	return mesa.fil == fila && mesa.col == columna;
}

hay_salida(coordenada_t salida, int fila, int columna){
	return salida.fil == fila && salida.col == columna;
}

hay_ingrediente(comida_t comida[MAX_COMIDA], int tope_comida, int fila, int columna){
	bool encontro = false;
	int i = 0;
	int j = 0;
	while(i < tope_comida && !encontro){
		while(j < comida[i].tope_ingredientes && !encontro){
			if(comida[i].ingrediente[j].posicion.fil == fila && comida[i].ingrediente[j].posicion.col == columna){
				encontro = true;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void inicializar_paredes(coordenada_t paredes[MAX_PAREDES], int *tope_paredes){
	for(int i = 0; i < MAX_FIL; i++){
		paredes[*tope_paredes].fil = i;
		paredes[*tope_paredes].col = 0;
		(*tope_paredes)++;
	}
	for(int i = 0; i < MAX_FIL; i++){
		paredes[*tope_paredes].fil = i;
		paredes[*tope_paredes].col = 20;
		(*tope_paredes)++;
	}

	for(int j = 1; j < MAX_COL - 1; j++){
		paredes[*tope_paredes].fil = 0;
		paredes[*tope_paredes].col = j;
		(*tope_paredes)++;
	}
	for(int j = 1; j < MAX_COL - 1; j++){
		if(j != 10){
			paredes[*tope_paredes].fil = 10;
			paredes[*tope_paredes].col = j;
			(*tope_paredes)++;
		}
	}
	for(int j = 1; j < MAX_COL - 1; j++){
		paredes[*tope_paredes].fil = 20;
		paredes[*tope_paredes].col = j;
		(*tope_paredes)++;
	}
}


void crear_grilla_vacia(){
    char grilla[MAX_FIL][MAX_COL];
    for(int i = 0; i < MAX_FIL; i++){
        for(int j = 0; j < MAX_COL; j++){
           grilla[i][j] = ' ';
        }
    }
}

//void inicializar_juego(juego_t* juego, int precio)
//void realizar_jugada(juego_t* juego, char movimiento)
//void imprimir_terreno(juego_t juego)
//int estado_juego(juego_t juego)














