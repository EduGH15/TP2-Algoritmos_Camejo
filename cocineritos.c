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
const char STITCH = 'S';
const char REUBEN = 'R';
//const char PERSONAJE_AGUJERO = '*';
//const char PERSONAJE_HERRAMIENTA = '@';
//const char PERSONAJE_INGREDIENTE = '$';

/*------ELEMENTOS DE LA MATRIZ------*/
const char PARED = '#';
const char MESA = '_';
const char PUERTA_SALIDA = 'P';
const char VACIO = ' ';
const int CENTRO_FILA = 10;
const int CENTRO_COLUMNA = 10;
const int PRIMERA_FILA = 0;
const int FILA_DEL_MEDIO = 10;
const int ULTIMA_FILA = 20;

/*------------COORDENADAS----------*/
const coordenada_t MOVER_ARRIBA = {-1, 0};
const coordenada_t MOVER_ABAJO = {1, 0};
const coordenada_t MOVER_DERECHA = {1, 0};
const coordenada_t MOVER_IZQUIERDA = {-1, 0};

/*------------TECLAS-----------------*/
const char ARRIBA = 'W';
const char ABAJO = 'S';
const char DERECHA = 'D';
const char IZQUIERDA = 'A';

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
	juego->mesa.fil = CENTRO_FILA;
	juego->mesa.col = CENTRO_COLUMNA;
}

void inicializar_agujeros(juego_t* juego){
	juego->tope_obstaculos = 0;
	int cuadrante_stitch = 0;
	int cuadrante_reuben = 0;

	while(cuadrante_stitch < 10){
		coordenada_t posicion_agujero = generar_coordenada_aleatoria(1, 9, 1, 19);
		juego->obstaculos[juego->tope_obstaculos].posicion.fil = posicion_agujero.fil;
		juego->obstaculos[juego->tope_obstaculos].posicion.col = posicion_agujero.col; 
		juego->obstaculos[juego->tope_obstaculos].tipo = AGUJEROS;
		(juego->tope_obstaculos)++;
		cuadrante_stitch++;
	}

	while(cuadrante_reuben < 10){
		coordenada_t posicion_agujero = generar_coordenada_aleatoria(11, 9, 1, 19);
		juego->obstaculos[juego->tope_obstaculos].posicion.fil = posicion_agujero.fil;
		juego->obstaculos[juego->tope_obstaculos].posicion.col = posicion_agujero.col; 
		juego->obstaculos[juego->tope_obstaculos].tipo = AGUJEROS;
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
			juego->herramientas[juego->tope_herramientas].tipo = CUCHILLO;
			(juego->tope_herramientas)++;
			herramientas_stitch++;
		}
	}

	while(herramientas_reuben < 2){
		coordenada_t posicion_herramienta = generar_coordenada_aleatoria(11, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_herramienta.fil, posicion_herramienta.col)){
			juego->herramientas[juego->tope_herramientas].posicion.fil = posicion_herramienta.fil;
			juego->herramientas[juego->tope_herramientas].posicion.col = posicion_herramienta.col;
			juego->herramientas[juego->tope_herramientas].tipo = HORNO;
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

void inicializar_ingrediente_pizza(juego_t* juego){
	juego->comida[1].tope_ingredientes = 0;
	int cantidad_masa = 0;
	int cantidad_jamon = 0;
	int cantidad_queso = 0; 
	for(int i = 0; i < MAX_INGREDIENTES; i++){
		juego->comida[1].ingrediente[juego->comida[1].tope_ingredientes].esta_cocinado = false;
		juego->comida[1].ingrediente[juego->comida[1].tope_ingredientes].esta_cortado = false;
		if(i == 0){
			while(cantidad_masa < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(11, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[1].ingrediente[juego->comida[1].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[1].ingrediente[juego->comida[1].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[1].ingrediente[juego->comida[1].tope_ingredientes].tipo = MASA;
					(juego->comida[1].tope_ingredientes)++;
					cantidad_masa++;
				}
			}
		}else if(i == 1){
			while(cantidad_jamon < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[1].ingrediente[juego->comida[1].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[1].ingrediente[juego->comida[1].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[1].ingrediente[juego->comida[1].tope_ingredientes].tipo = JAMON;
					(juego->comida[1].tope_ingredientes)++;
					cantidad_jamon++;
				}
			}
		}else if(i == 2){
			while(cantidad_queso < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[1].ingrediente[juego->comida[1].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[1].ingrediente[juego->comida[1].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[1].ingrediente[juego->comida[1].tope_ingredientes].tipo = QUESO;
					(juego->comida[1].tope_ingredientes)++;
					cantidad_queso++;
				}
			}
		}
	}
}

void inicializar_ingrediente_hamburguesa(juego_t* juego){
	juego->comida[2].tope_ingredientes = 0;
	int cantidad_pan = 0; 
	int cantidad_carne = 0;
	int cantidad_lechuga = 0;
	int cantidad_tomate = 0;
	for(int i = 0; i < MAX_INGREDIENTES; i++){
		juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].esta_cocinado = false;
		juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].esta_cortado = false;
		if(i == 0){
			while(cantidad_pan < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].tipo = PAN;
					(juego->comida[2].tope_ingredientes)++;
					cantidad_pan++;
				}
			}
		}else if(i == 1){
			while(cantidad_carne < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(11, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].tipo = CARNE;
					(juego->comida[2].tope_ingredientes)++;
					cantidad_carne++;
				}
			}
		}else if(i == 2){
			while(cantidad_lechuga < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].tipo = LECHUGA;
					(juego->comida[2].tope_ingredientes)++;
					cantidad_lechuga++;
				}
			}
		}else if(i == 3){
			while(cantidad_tomate < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[2].ingrediente[juego->comida[2].tope_ingredientes].tipo = TOMATE;
					(juego->comida[2].tope_ingredientes)++;
					cantidad_tomate++;
				}
			}
		}
	}
}

void inicializar_ingrediente_sandwich(juego_t* juego){
	juego->comida[3].tope_ingredientes = 0;
	int cantidad_milanesa = 0;
	int cantidad_pan = 0;
	int cantidad_tomate = 0;
	int cantidad_lechuga = 0;
	int cantidad_jamon = 0;
	int cantidad_queso = 0;
	for(int i = 0; i < MAX_INGREDIENTES; i++){
		if(i == 0){
			juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].esta_cocinado = false;
			juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].esta_cortado = false;
			while(cantidad_milanesa < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(11, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].tipo = MILANESA;
					(juego->comida[3].tope_ingredientes)++;
					cantidad_milanesa++;
				}
			}
		}else if(i == 1){
			while(cantidad_pan < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].tipo = PAN;
					(juego->comida[3].tope_ingredientes)++;
					cantidad_pan++;
				}
			}
		}else if(i == 2){
			while(cantidad_tomate < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].tipo = TOMATE;
					(juego->comida[3].tope_ingredientes)++;
					cantidad_tomate++;
				}
			}
		}else if(i == 3){
			while(cantidad_lechuga < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].tipo = LECHUGA;
					(juego->comida[3].tope_ingredientes)++;
					cantidad_lechuga++;
				}
			}
		}else if(i == 4){
			while(cantidad_jamon < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].tipo = JAMON;
					(juego->comida[3].tope_ingredientes)++;
					cantidad_jamon++;
				}
			}
		}else if(i == 5){
			while(cantidad_queso < 1){
				coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].posicion.fil = posicion_aleatoria.fil;
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].posicion.col = posicion_aleatoria.col;
					juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].tipo = QUESO;
					(juego->comida[3].tope_ingredientes)++;
					cantidad_queso++;
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
	}else if(juego->tope_comida > 150){
		juego->tope_comida = 4;
	}
	juego->comida_actual = ENSALADA;
	inicializar_ingrediente_ensalada(juego);
}

void inicializar_personajes(juego_t* juego){
	juego->personaje_activo = STITCH;
	int cantidad_stitch = 0;
	int cantidad_reuben = 0;
	while(cantidad_stitch < 1){
		coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(1, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
			juego->stitch.posicion.fil = posicion_aleatoria.fil;
			juego->stitch.posicion.col = posicion_aleatoria.col;
			juego->stitch.tipo = STITCH;
			juego->stitch.objeto_en_mano = ' ';
			cantidad_stitch++;
		}
	}
	while(cantidad_reuben < 1){
		coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(11, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col)){
			juego->reuben.posicion.fil = posicion_aleatoria.fil;
			juego->reuben.posicion.col = posicion_aleatoria.col;
			juego->reuben.tipo = REUBEN;
			juego->reuben.objeto_en_mano = ' ';
			cantidad_reuben++;
		}
	}
}

void inicializar_puerta_salida(juego_t* juego){
	for(int i = 0; i < MAX_FIL; i++){
			coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(11, 10, 0, 21);
			if(posicion_aleatoria.col == 0 || posicion_aleatoria.col == 20){
				juego->salida.fil = posicion_aleatoria.fil;
				juego->salida.col = posicion_aleatoria.col;
			}else if(posicion_aleatoria.fil == 20){
				juego->salida.fil = posicion_aleatoria.fil;
				juego->salida.col = posicion_aleatoria.col;
			}
	}
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

	if(juego.comida_actual == ENSALADA){
		for(int i = 0; i < juego.comida[0].tope_ingredientes; i++){
		grilla[juego.comida[0].ingrediente[i].posicion.fil][juego.comida[0].ingrediente[i].posicion.col] = juego.comida[0].ingrediente[i].tipo;
		}
	}else if(juego.comida_actual == PIZZA){
		for(int i = 0; i < juego.comida[1].tope_ingredientes; i++){
		grilla[juego.comida[1].ingrediente[i].posicion.fil][juego.comida[1].ingrediente[i].posicion.col] = juego.comida[1].ingrediente[i].tipo;
		}
	}else if(juego.comida_actual == HAMBURGUESA){
		for(int i = 0; i < juego.comida[2].tope_ingredientes; i++){
		grilla[juego.comida[2].ingrediente[i].posicion.fil][juego.comida[2].ingrediente[i].posicion.col] = juego.comida[2].ingrediente[i].tipo;
		}
	}else if(juego.comida_actual == SANDWICH){
		for(int i = 0; i < juego.comida[3].tope_ingredientes; i++){
			grilla[juego.comida[3].ingrediente[i].posicion.fil][juego.comida[3].ingrediente[i].posicion.col] = juego.comida[3].ingrediente[i].tipo;
		}
	}

	grilla[juego.stitch.posicion.fil][juego.stitch.posicion.col] = juego.stitch.tipo;
	grilla[juego.reuben.posicion.fil][juego.reuben.posicion.col] = juego.reuben.tipo;
	grilla[juego.salida.fil][juego.salida.col] = PUERTA_SALIDA;
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
	inicializar_personajes(juego);
	juego->movimientos = ' '; 
	inicializar_puerta_salida(juego);
}

void imprimir_terreno(juego_t juego){
	char grilla[MAX_FIL][MAX_COL];
	inicializar_grilla_vacia(grilla);
	llenar_grilla(juego, grilla);
	dibujar_grilla(grilla);
}

//-------------------------------------------- ACTUALIZAR STRUCT----------------------------

//void realizar_jugada(juego_t* juego, char movimiento)

//int estado_juego(juego_t juego)














