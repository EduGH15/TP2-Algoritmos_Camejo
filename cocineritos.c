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

coordenada_t generar_coordenada_aleatoria(int fil_inicial, int amplitud_fila, int col_inicial, int amplitud_columna){
	coordenada_t posicion;
	posicion.fil = rand() % amplitud_fila + fil_inicial; //Ambos inclusives;
	posicion.col = rand() % amplitud_columna + col_inicial; //Ambos inclusives;
	return posicion;
}

//------------------------------------------BOOLEANOS---------------------------------------------------------

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

bool hay_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna){
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

bool hay_ingrediente(comida_t comida[MAX_COMIDA], int tope_comida, int fila, int columna){
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
	return encontro;
}
//---------------------------------------INICIALIZACION POR PARTES --------------------------------------------------------
void inicializar_precio_total(juego_t* juego, int precio){
	juego->precio_total = precio;
}

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

void inicializar_mesa(juego_t* juego){
	juego->mesa.fil = 10;
	juego->mesa.col = 10;
}

void inicializar_agujeros(juego_t* juego){
	juego->tope_obstaculos = 0;
	int cuadrante_stitch = 0;
	int cuadrante_reuben = 0;

	while(cuadrante_stitch < 10){
		coordenada_t posicion_agujero = generar_coordenada_aleatoria(1, 9, 1, 19);
		juego->obstaculos[juego->tope_obstaculos].posicion.fil = posicion_agujero.fil;
		juego->obstaculos[juego->tope_obstaculos].posicion.col = posicion_agujero.col; 
		juego->obstaculos[juego->tope_obstaculos].tipo = 'A';
		(juego->tope_obstaculos)++;
		cuadrante_stitch++;
	}

	while(cuadrante_reuben < 10){
		coordenada_t posicion_agujero = generar_coordenada_aleatoria(11, 9, 1, 19);
		juego->obstaculos[juego->tope_obstaculos].posicion.fil = posicion_agujero.fil;
		juego->obstaculos[juego->tope_obstaculos].posicion.col = posicion_agujero.col; 
		juego->obstaculos[juego->tope_obstaculos].tipo = 'A';
		(juego->tope_obstaculos)++;
		cuadrante_reuben++;
	}
}

void inicializar_herramientas(juego_t* juego){
	juego->tope_herramientas = 0;
	int herramientas_stitch = 0;
	int herramientas_reuben = 0;

	while(herramientas_stitch < 2){
		coordenada_t posicion_herramienta = generar_coordenada_aleatoria(1, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_herramienta.fil, posicion_herramienta.col)){
			juego->herramientas[juego->tope_herramientas].posicion.fil = posicion_herramienta.fil;
			juego->herramientas[juego->tope_herramientas].posicion.col = posicion_herramienta.col;
			juego->herramientas[juego->tope_herramientas].tipo = 'C';
			(juego->tope_herramientas)++;
			herramientas_stitch++;
		}
	}

	while(herramientas_reuben < 2){
		coordenada_t posicion_herramienta = generar_coordenada_aleatoria(11, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_herramienta.fil, posicion_herramienta.col)){
			juego->herramientas[juego->tope_herramientas].posicion.fil = posicion_herramienta.fil;
			juego->herramientas[juego->tope_herramientas].posicion.col = posicion_herramienta.col;
			juego->herramientas[juego->tope_herramientas].tipo = 'H';
			(juego->tope_herramientas)++;
			herramientas_reuben++;
		}
	}
}

void inicializar_ingrediente_ensalada(juego_t* juego){
	juego->comida[0].tope_ingredientes = 0;
	int cantidad_lechuga = 0;
	int cantidad_tomate = 0;
	for(int i = 0; i < MAX_INGREDIENTES; i++){
		juego->comida[0].ingrediente[juego->comida[0].tope_ingredientes].esta_cocinado = false;
		juego->comida[0].ingrediente[juego->comida[0].tope_ingredientes].esta_cortado = false;
		if(i == 0){
			while(cantidad_lechuga < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[0].ingrediente[juego->comida[0].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[0].ingrediente[juego->comida[0].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[0].ingrediente[juego->comida[0].tope_ingredientes].tipo = LECHUGA;
					(juego->comida[0].tope_ingredientes)++;
					cantidad_lechuga++;
				}
			}
		}else if(i == 1){
			while(cantidad_tomate < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[0].ingrediente[juego->comida[0].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[0].ingrediente[juego->comida[0].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[0].ingrediente[juego->comida[0].tope_ingredientes].tipo = TOMATE;
					(juego->comida[0].tope_ingredientes)++;
					cantidad_tomate++;
				}
			}
		}
	
	}
}

void inicializar_comida(juego_t* juego){
	juego->tope_comida = 0;
	juego->comida[0].tipo = ENSALADA;
	juego->comida[1].tipo = PIZZA;
	juego->comida[2].tipo = HAMBURGUESA;
	juego->comida[3].tipo = SANDWICH;
	if(juego->precio_total <= 100){
		juego->tope_comida = 2;
	}else if(juego->precio_total <= 150){
		juego->tope_comida = 3;
	}else if(juego->tope_comida < 150){
		juego->tope_comida = 4;
	}
	inicializar_ingrediente_ensalada(juego);
}

//--------------------------------------------------INICIALIZACIÓN CENTRALIZADA--------------------------------------
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
	grilla[juego.mesa.fil][juego.mesa.col] = '_';
	for(int i = 0;i < juego.tope_obstaculos; i++){
		grilla[juego.obstaculos[i].posicion.fil][juego.obstaculos[i].posicion.col] = juego.obstaculos[i].tipo;
	}
	for(int i = 0; i < juego.tope_herramientas; i++){
		grilla[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = juego.herramientas[i].tipo;
	}
	for(int i = 0; i < juego.comida[0].tope_ingredientes; i++){
		grilla[juego.comida[0].ingrediente[i].posicion.fil][juego.comida[0].ingrediente[i].posicion.col] = juego.comida[0].ingrediente[i].tipo;
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
	inicializar_precio_total(juego, precio);
	inicializar_paredes(juego);
	inicializar_mesa(juego);
	inicializar_agujeros(juego);
	inicializar_herramientas(juego);
	inicializar_comida(juego);
}

void imprimir_terreno(juego_t juego){
	char grilla[MAX_FIL][MAX_COL];
	inicializar_grilla_vacia(grilla);
	llenar_grilla(juego, grilla);
	dibujar_grilla(grilla);
}

//void realizar_jugada(juego_t* juego, char movimiento)

//int estado_juego(juego_t juego)














