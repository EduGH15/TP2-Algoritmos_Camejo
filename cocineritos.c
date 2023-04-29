#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

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

//------------------------------------------FUNCIONES VARIAS --------------------------------------------------

coordenada_t generar_coordenada_aleatoria(int fil_inicial, int fil_final, int col_inicial, int col_final){
	coordenada_t posicion;
	posicion.fil = rand() % fil_final + fil_inicial; //Ambos inclusives;
	posicion.col = rand() % col_final + col_inicial; //Ambos inclusives;
	return posicion;
}

//------------------------------------------BOOLEANOS---------------------------------------------------------


//---------------------------------------INICIALIZANDO--------------------------------------------------------
void inicializar_paredes(juego_t* juego){
	juego->tope_paredes = 0;
	for(int i = 0; i < MAX_FIL; i++){
		for(int j = 0; j < MAX_COL; j++){
			if(j == 0 || j == 20){
				juego->paredes[juego->tope_paredes].fil = i;
				juego->paredes[juego->tope_paredes].col = j;
				(juego->tope_paredes)++;
			}
			if((j > 0 && j < 20) && (i == 0 || (i == 10 && j != 10)|| i == 20)){
				juego->paredes[juego->tope_paredes].fil = i;
				juego->paredes[juego->tope_paredes].col = j;
				(juego->tope_paredes)++;
			}
		} 
	}
}


void inicializar_agujeros_stitch(juego_t* juego){
	juego->tope_obstaculos = 0;
	int cuadrante_stitch = 0;
	while(cuadrante_stitch < 10){
		coordenada_t posicion_agujero = generar_coordenada_aleatoria(1, 9, 1, 19);
		juego->obstaculos[juego->tope_obstaculos].posicion.fil = posicion_agujero.fil;
		juego->obstaculos[juego->tope_obstaculos].posicion.col = posicion_agujero.col; 
		juego->obstaculos[juego->tope_obstaculos].tipo = 'A';
		(juego->tope_obstaculos)++;
		cuadrante_stitch++;
	}
}

void inicializar_agujeros_reuben(juego_t* juego){
	int cuadrante_reuben = 0;
	while(cuadrante_reuben < 10){
		coordenada_t posicion_agujero = generar_coordenada_aleatoria(11, 8, 1, 19);
		juego->obstaculos[juego->tope_obstaculos].posicion.fil = posicion_agujero.fil;
		juego->obstaculos[juego->tope_obstaculos].posicion.col = posicion_agujero.col; 
		juego->obstaculos[juego->tope_obstaculos].tipo = 'A';
		(juego->tope_obstaculos)++;
		cuadrante_reuben++;
	}
}


void inicializar_grilla_vacia(char grilla[MAX_FIL][MAX_COL]){
    for(int i = 0; i < MAX_FIL; i++){
        for(int j = 0; j < MAX_COL; j++){
           grilla[i][j] = ' ';
        }
    }
}

void llenar_grilla(juego_t juego, char grilla[MAX_FIL][MAX_COL]){
	for(int i = 0; i < juego.tope_paredes; i++){
		grilla[juego.paredes[i].fil][juego.paredes[i].col] = '#';
	}
	for(int i = 0;i < juego.tope_obstaculos; i++){
		grilla[juego.obstaculos[i].posicion.fil][juego.obstaculos[i].posicion.col] = juego.obstaculos[i].tipo;
	}
}

void dibujar_grilla(char grilla[MAX_FIL][MAX_COL]){
    for(int i = 0; i < MAX_FIL; i++){
        for(int j = 0; j < MAX_COL; j++){
            if(j < 20){
                printf(" %c |", grilla[i][j]);
            }else{
                printf(" %c ", grilla[i][j]);
            }
        }
        if(i < 20){
            printf("\n------------------------------------------------------------------------------------\n");
        }
    }
    printf("\n");
}

void inicializar_juego(juego_t* juego, int precio){
	inicializar_paredes(juego);
	inicializar_agujeros_stitch(juego);
	inicializar_agujeros_reuben(juego);
}

void imprimir_terreno(juego_t juego){
	char grilla[MAX_FIL][MAX_COL];
	inicializar_grilla_vacia(grilla);
	llenar_grilla(juego, grilla);
	dibujar_grilla(grilla);
}

//void realizar_jugada(juego_t* juego, char movimiento)

//int estado_juego(juego_t juego)














