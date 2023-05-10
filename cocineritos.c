#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
const coordenada_t MOVER_DERECHA = {0, 1};
const coordenada_t MOVER_IZQUIERDA = {0, -1};

/*------------TECLAS-----------------*/
const char ARRIBA = 'W'; 
const char ABAJO = 'S';
const char DERECHA = 'D';
const char IZQUIERDA = 'A';
const char CAMBIAR_PERSONAJE = 'X';
const char ACTIVAR_MATAFUEGO = 'M';
const char ACTIVAR_CUCHILLO = 'C';
const char ACTIVAR_HORNO = 'H';
const char AGARRAR = 'R';
const char PASAR = 'T';

//------------------------------------------FUNCIONES VARIAS --------------------------------------------------

coordenada_t generar_coordenada_aleatoria(int fil_inicial, int amplitud_fila, int col_inicial, int amplitud_columna){
	coordenada_t posicion;
	posicion.fil = rand() % amplitud_fila + fil_inicial; //Ambos inclusives;
	posicion.col = rand() % amplitud_columna + col_inicial; //Ambos inclusives;
	return posicion;
}

coordenada_t generar_posicion_nueva(personaje_t personaje, char movimiento){
	coordenada_t posicion_jugador;
	if(movimiento == ARRIBA){
		posicion_jugador.fil = personaje.posicion.fil - 1;
		posicion_jugador.col = personaje.posicion.col;
	}else if( movimiento == ABAJO){
		posicion_jugador.fil = personaje.posicion.fil + 1;
		posicion_jugador.col = personaje.posicion.col;
	}else if(movimiento == DERECHA){
		posicion_jugador.fil = personaje.posicion.fil;
		posicion_jugador.col = personaje.posicion.col + 1;
	}else if(movimiento == IZQUIERDA){
		posicion_jugador.fil = personaje.posicion.fil;
		posicion_jugador.col = personaje.posicion.col -1;
	}
	return posicion_jugador;
}

void mover_jugador(personaje_t* jugador, char movimiento){
	if(movimiento == ARRIBA){
		jugador->posicion.fil += MOVER_ARRIBA.fil;
		jugador->posicion.col += MOVER_ARRIBA.col;
	}else if(movimiento == ABAJO){
		jugador->posicion.fil += MOVER_ABAJO.fil;
		jugador->posicion.col += MOVER_ABAJO.col;
	}else if(movimiento == DERECHA){
		jugador->posicion.fil += MOVER_DERECHA.fil;
		jugador->posicion.col += MOVER_DERECHA.col;
	}else if(movimiento == IZQUIERDA){
		jugador->posicion.fil += MOVER_IZQUIERDA.fil;
		jugador->posicion.col += MOVER_IZQUIERDA.col;
	}
}


char buscar_tipo_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes, int fila, int columna){
	char tipo_ingrediente = ' ';
	bool encontro = false;
	int i = 0;
	while(i < tope_ingredientes && !encontro){
		if(ingrediente[i].posicion.fil == fila && ingrediente[i].posicion.col == columna){
			tipo_ingrediente = ingrediente[i].tipo;
			encontro = true;
		}
		i++;
	}
	return tipo_ingrediente;
}

void ocultar_ingrediente(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes){
	bool encontro = false;
	int i = 0;
	while(i < tope_ingredientes && !encontro){
		if(ingrediente[i].tipo == tipo_ingrediente){
			ingrediente[i].posicion.fil = -1;
			ingrediente[i].posicion.col = -1;
			encontro = true;
		}
		i++;
	}
}

void cambiar_posicion_ingrediente(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes, int fila, int columna){
	bool encontro = false;
	int i = 0;
	while(i < tope_ingredientes && !encontro){
		if(ingrediente[i].tipo == tipo_ingrediente){
			ingrediente[i].posicion.fil = fila;
			ingrediente[i].posicion.col = columna;
			encontro = true;
		}
		i++;
	}
}

void cortar_ingrediente(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes){
	bool cortado = false;
	int i = 0;
	while(i < tope_ingredientes && !cortado){
		if(ingrediente[i].tipo == tipo_ingrediente){
			ingrediente[i].esta_cortado = true;
			cortado = true;
		}
		i++;
	}
}

void cocinar_ingrediente(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes){
	bool cocinado = false;
	int i = 0;
	while(i < tope_ingredientes && !cocinado){
		if(ingrediente[i].tipo == tipo_ingrediente){
			ingrediente[i].esta_cocinado = true;
			cocinado = true;
		}
		i++;
	}
}


char buscar_tipo_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna){
	char tipo_herramienta = ' ';
	bool encontro = false;
	int i = 0;
	while(i < tope_herramientas && !encontro){
		if(herramientas[i].posicion.fil == fila && herramientas[i].posicion.col == columna){
			tipo_herramienta = herramientas[i].tipo;
			encontro = true;
		}
		i++;
	}
	return tipo_herramienta;
}

void ocultar_herramienta(char tipo_herramienta, objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas){
	bool encontro = false;
	int i = 0;
	while(i < tope_herramientas && !encontro){
		if(herramientas[i].tipo == tipo_herramienta){
			herramientas[i].posicion.fil = -1;
			herramientas[i].posicion.col = -1;
			encontro = true;
		}
		i++;
	}
}


int orden_actual(char comida_actual){
	int orden = 0;
	if(comida_actual == PIZZA){
		orden = 1;
	}else if(comida_actual == HAMBURGUESA){
		orden = 2;
	}else if (comida_actual == SANDWICH){
		orden = 3;
	}
	return orden;
}

void asignar_posicion_agujero(objeto_t obstaculos[MAX_OBSTACULOS], int* tope_obstaculos, coordenada_t posicion, char tipo_obstaculo){
	obstaculos[*tope_obstaculos].posicion.fil = posicion.fil;
	obstaculos[*tope_obstaculos].posicion.col = posicion.col;
	obstaculos[*tope_obstaculos].tipo = tipo_obstaculo;
	(*tope_obstaculos)++;

}

//------------------------------------------BOOLEANOS---------------------------------------------------------

bool hay_jugador(juego_t juego, int fila, int columna){
	return (juego.stitch.posicion.fil == fila && juego.stitch.posicion.col == columna) || (juego.reuben.posicion.fil == fila && juego.reuben.posicion.col == columna);
}

bool hay_pared(coordenada_t paredes[MAX_PAREDES], int tope_paredes, int fila, int columna){
	bool encontro = false;
	int i = 0;
	while(i < tope_paredes && !encontro){
		if(paredes[i].fil == fila && paredes[i].col == columna){
			encontro = true;
		}
		i++;
	}
	return encontro;
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

bool hay_fuego(objeto_t obstaculos[MAX_OBSTACULOS],int tope_obstaculo, int fila, int columna){
	bool encontro = false;
	int i = 0;
	while(i < tope_obstaculo && !encontro){
		if(obstaculos[i].tipo == FUEGO && obstaculos[i].posicion.fil == fila && obstaculos[i].posicion.col == columna){
			encontro = true;
		}
		i++;
	}
	return encontro;
}

bool hay_fuego_cuadrante_stitch(objeto_t obstaculos[MAX_OBSTACULOS],int tope_obstaculo){
	return (tope_obstaculo == 21) && (obstaculos[tope_obstaculo - 1].posicion.fil >= 1 &&  obstaculos[tope_obstaculo - 1].posicion.fil <= 9);
}

bool hay_fuego_cuadrante_reuben(objeto_t obstaculos[MAX_OBSTACULOS],int tope_obstaculo){
	return (tope_obstaculo == 21) && (obstaculos[tope_obstaculo - 1].posicion.fil >= 11 &&  obstaculos[tope_obstaculo - 1].posicion.fil <= 19);
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

bool hay_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes, int fila, int columna){
	bool encontro = false;
	int i = 0;
	while(i < tope_ingredientes && !encontro){
		if(ingrediente[i].posicion.fil == fila && ingrediente[i].posicion.col == columna){
			encontro = true;
		}
		i++;
	}	
	return encontro;
}

bool hay_mesa(coordenada_t mesa, int fila, int columna){
	return mesa.fil == fila && mesa.col == columna;
}

/*
bool hay_vacio(juego_t juego, int fila, int columna){
	return !hay_pared(juego.paredes, juego.tope_paredes, fila, columna) && !hay_mesa(juego.mesa, fila, columna) && !hay_obstaculo(juego.obstaculos, juego.tope_obstaculos, fila, columna) && !hay_herramienta(juego.herramientas, juego.tope_herramientas, fila, columna) && !hay_ingrediente(juego.comida[juego.tope_comida - 1].ingrediente, juego.comida[juego.tope_comida -1].tope_ingredientes, fila, columna) && !hay_jugador(juego, fila, columna);
}
*/

bool hay_horno(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna){
	bool encontro = false;
	int i = 0;
	while(i < tope_herramientas && !encontro){
		if(herramientas[i].tipo == HORNO && herramientas[i].posicion.fil == fila && herramientas[i].posicion.col == columna){
			encontro = true;
		}
		i++;
	}
	return encontro;
}

bool hay_matafuegos(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna){
	bool encontro = false;
	int i = 0;
	while(i < tope_herramientas && !encontro){
		if(herramientas[i].tipo == MATAFUEGOS && herramientas[i].posicion.fil == fila && herramientas[i].posicion.col == columna){
			encontro = true;
		}
		i++;
	}
	return encontro;
}

bool hay_puerta_salida(coordenada_t puerta_salida, int fila, int columna){
	return puerta_salida.fil == fila && puerta_salida.col == columna;
}

bool es_movimiento_valido(juego_t juego, int fila, int columna){
	return !hay_pared(juego.paredes, juego.tope_paredes, fila, columna) && !hay_mesa(juego.mesa, fila, columna) && !hay_horno(juego.herramientas, juego.tope_herramientas, fila, columna) && !hay_fuego(juego.obstaculos, juego.tope_obstaculos, fila, columna);
}

bool distancia_manhattan(coordenada_t posicion_jugador, coordenada_t posicion_elemento, int distancia){
	int resta_1 = abs(posicion_jugador.fil - posicion_elemento.fil);
	int resta_2 = abs(posicion_jugador.col - posicion_elemento.col);
	int respuesta = resta_1 + resta_2;
	return respuesta <= distancia;
}

bool esta_cortado(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes){
	bool cortado = false;
	int i = 0;
	while(i < tope_ingredientes && !cortado){
		if(ingrediente[i].tipo == tipo_ingrediente){
			cortado = ingrediente[i].esta_cortado;
		}
		i++;
	}
	return cortado;
}

bool esta_cocinado(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes){
	bool cocinado = false;
	int i = 0;
	while(i < tope_ingredientes && !cocinado){
		if(ingrediente[i].tipo == tipo_ingrediente){
			cocinado = ingrediente[i].esta_cocinado;
		}
		i++;
	}
	return cocinado;
}

bool estan_mismo_cuadrante(int fila_objeto_1,  int fila_objeto_2){
	return ((fila_objeto_1 >= 1 && fila_objeto_1 <= 9) && (fila_objeto_2 >=1 && fila_objeto_2 <= 9)) || ((fila_objeto_1 >= 11 && fila_objeto_1 <= 19) && (fila_objeto_2 >=11 && fila_objeto_2 <= 19));
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
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_agujero.fil, posicion_agujero.col)){
			asignar_posicion_agujero(juego->obstaculos, &(juego)->tope_obstaculos, posicion_agujero, AGUJEROS);
			cuadrante_stitch++;
		}
	}

	while(cuadrante_reuben < 10){
		coordenada_t posicion_agujero = generar_coordenada_aleatoria(11, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_agujero.fil, posicion_agujero.col)){
			asignar_posicion_agujero(juego->obstaculos, &(juego)->tope_obstaculos, posicion_agujero, AGUJEROS);
			cuadrante_reuben++;
		}
	}
}

/*


void inicializar_fuego(juego_t* juego){
	int cantidad_fuego = 0;
	while(cantidad_fuego < 1){
		coordenada_t posicion_fuego = generar_coordenada_aleatoria(1, 19, 1, 19);
		if(hay_vacio(*juego, posicion_fuego.fil, posicion_fuego.col)){
			juego->obstaculos[juego->tope_obstaculos].posicion.fil = posicion_fuego.fil;
			juego->obstaculos[juego->tope_obstaculos].posicion.col = posicion_fuego.col; 
			juego->obstaculos[juego->tope_obstaculos].tipo = FUEGO;
			(juego->tope_obstaculos)++;
			cantidad_fuego++;
		}
	}
}

void inicializar_herramientas(juego_t* juego){
	juego->tope_herramientas = 0;
	int herramientas_stitch = 0;
	int herramientas_reuben = 0;

	while(herramientas_stitch < 2){
		coordenada_t posicion_herramienta = generar_coordenada_aleatoria(1, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_herramienta.fil, posicion_herramienta.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_herramienta.fil, posicion_herramienta.col)){
			juego->herramientas[juego->tope_herramientas].posicion.fil = posicion_herramienta.fil;
			juego->herramientas[juego->tope_herramientas].posicion.col = posicion_herramienta.col;
			juego->herramientas[juego->tope_herramientas].tipo = CUCHILLO;
			(juego->tope_herramientas)++;
			herramientas_stitch++;
		}
	}

	while(herramientas_reuben < 2){
		coordenada_t posicion_herramienta = generar_coordenada_aleatoria(11, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_herramienta.fil, posicion_herramienta.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_herramienta.fil, posicion_herramienta.col)){
			juego->herramientas[juego->tope_herramientas].posicion.fil = posicion_herramienta.fil;
			juego->herramientas[juego->tope_herramientas].posicion.col = posicion_herramienta.col;
			juego->herramientas[juego->tope_herramientas].tipo = HORNO;
			(juego->tope_herramientas)++;
			herramientas_reuben++;
		}
	}
}

void inicializar_matafuegos(juego_t* juego){
	int cantidad_matafuegos = 0;
	while(cantidad_matafuegos < 1){
		coordenada_t posicion_matafuegos = generar_coordenada_aleatoria(1, 19, 1, 19);
		if(hay_vacio(*juego, posicion_matafuegos.fil, posicion_matafuegos.col) && estan_mismo_cuadrante(posicion_matafuegos.fil, juego->obstaculos[(juego->tope_obstaculos)-1].posicion.fil)){
			juego->herramientas[juego->tope_herramientas].posicion.fil = posicion_matafuegos.fil;
			juego->herramientas[juego->tope_herramientas].posicion.col = posicion_matafuegos.col; 
			juego->herramientas[juego->tope_herramientas].tipo = MATAFUEGOS;
			(juego->tope_herramientas)++;
			cantidad_matafuegos++;
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
	if(juego->comida_actual == ENSALADA && juego->precio_total <= 100){
		juego->comida[0].tipo = ENSALADA;
		(juego->tope_comida)++;
		inicializar_ingrediente_ensalada(juego);
	}else if(juego->comida_actual == PIZZA && juego->precio_total <= 100){
		juego->comida[1].tipo = PIZZA;
		(juego->tope_comida)++;
		inicializar_ingrediente_pizza(juego);
	}else if(juego->comida_actual == HAMBURGUESA && juego->precio_total <= 150){
		juego->comida[2].tipo = HAMBURGUESA;
		(juego->tope_comida)++;
		inicializar_ingrediente_hamburguesa(juego);
	}else if(juego->comida_actual == SANDWICH && juego->precio_total > 150){
		juego->comida[3].tipo = SANDWICH;
		(juego->tope_comida)++;
		inicializar_ingrediente_sandwich(juego);
	}
}

void inicializar_puerta_salida(juego_t* juego){
	bool es_posicion_valida = false;
	while(!es_posicion_valida){
		coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(11, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida, juego->tope_comida, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_jugador(*juego, posicion_aleatoria.fil, posicion_aleatoria.col)){
			juego->salida.fil = posicion_aleatoria.fil;
			juego->salida.col = posicion_aleatoria.col;
			es_posicion_valida = true;
		}
	}
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

*/

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

	/*
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

	grilla[juego.salida.fil][juego.salida.col] = PUERTA_SALIDA;
	grilla[juego.stitch.posicion.fil][juego.stitch.posicion.col] = juego.stitch.tipo;
	grilla[juego.reuben.posicion.fil][juego.reuben.posicion.col] = juego.reuben.tipo;
	*/
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
	
	/*
	inicializar_herramientas(juego);
	juego->tope_comida = 0;
	juego->comida_actual = ENSALADA;
	inicializar_comida(juego);
	inicializar_puerta_salida(juego);
	inicializar_personajes(juego);
	juego->movimientos = 0; 
	juego->tope_comida_lista = 0;
	*/
}

void imprimir_terreno(juego_t juego){
	char grilla[MAX_FIL][MAX_COL];
	inicializar_grilla_vacia(grilla);
	llenar_grilla(juego, grilla);
	dibujar_grilla(grilla);
}

//------------------------------------------- CARGAR VECTOR DE COMIDA LISTA ------------------------------------
/*
void cargar_vector(juego_t* juego){
	juego->comida_lista[juego->tope_comida_lista].posicion.fil = juego->reuben.posicion.fil;
	juego->comida_lista[juego->tope_comida_lista].posicion.col = juego->reuben.posicion.col;
	juego->comida_lista[juego->tope_comida_lista].tipo = juego->reuben.objeto_en_mano;
	juego->comida_lista[juego->tope_comida_lista].esta_cortado = esta_cortado(juego->reuben.objeto_en_mano, juego->comida, juego->tope_comida);
	juego->comida_lista[juego->tope_comida_lista].esta_cocinado = esta_cocinado(juego->reuben.objeto_en_mano, juego->comida, juego->tope_comida);
	(juego->tope_comida_lista)++;
	
}
*/

//-------------------------------------------- ACTUALIZAR STRUCT----------------------------------------------

/*
void realizar_jugada(juego_t* juego, char movimiento){}

	
*/


int estado_juego(juego_t juego){
	int estado = 0;
	if(hay_obstaculo(juego.obstaculos, juego.tope_obstaculos, juego.stitch.posicion.fil, juego.stitch.posicion.col) || hay_obstaculo(juego.obstaculos, juego.tope_obstaculos, juego.reuben.posicion.fil, juego.reuben.posicion.col)){
		estado = -1;
	}if(juego.tope_comida_lista == 3){
		estado = 1;
	}
	return estado;
}




/*
	
	int orden = orden_actual(juego->comida_actual);

	if(movimiento == ARRIBA || movimiento == ABAJO || movimiento == DERECHA || movimiento == IZQUIERDA){
		if(juego->personaje_activo == STITCH){
			coordenada_t posicion_nueva_jugador = generar_posicion_nueva(juego->stitch, movimiento);
			if(es_movimiento_valido(*juego, posicion_nueva_jugador.fil, posicion_nueva_jugador.col)){
				mover_jugador(&(juego->stitch), movimiento);
				if(juego->tope_obstaculos < 21){
					juego->movimientos++;
				}
			}
		}else if(juego->personaje_activo == REUBEN){
			coordenada_t posicion_nueva_jugador = generar_posicion_nueva(juego->reuben, movimiento);
			if(es_movimiento_valido(*juego, posicion_nueva_jugador.fil, posicion_nueva_jugador.col)){
				mover_jugador(&(juego->reuben), movimiento);
				if(juego->tope_obstaculos < 21){
					juego->movimientos++;
				}
			}
		}

		
	}

	if(movimiento == CAMBIAR_PERSONAJE){
		if(juego->personaje_activo == STITCH){
			juego->personaje_activo = REUBEN;
		}else if(juego->personaje_activo == REUBEN){
			juego->personaje_activo = STITCH;
		}
	}


	if(movimiento == AGARRAR){
		if(juego->personaje_activo == STITCH){
			if(juego->stitch.objeto_en_mano == VACIO && !hay_fuego_cuadrante_stitch(juego->obstaculos, juego->tope_obstaculos) && hay_ingrediente(juego->comida, juego->tope_comida, juego->stitch.posicion.fil, juego->stitch.posicion.col)){

				juego->stitch.objeto_en_mano = buscar_tipo_ingrediente(juego->comida[juego->tope_comida - 1].ingrediente, juego->comida[juego->tope_comida -1].tope_ingredientes, juego->stitch.posicion.fil, juego->stitch.posicion.col);
				ocultar_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);

			}else if((juego->stitch.objeto_en_mano != VACIO && juego->stitch.objeto_en_mano != MATAFUEGOS)  && !hay_ingrediente(juego->comida, juego->tope_comida,juego->stitch.posicion.fil, juego->stitch.posicion.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, juego->stitch.posicion.fil, juego->stitch.posicion.col)){

				cambiar_posicion_ingrediente(juego->stitch.objeto_en_mano, juego->comida[juego->tope_comida - 1].ingrediente, juego->comida[juego->tope_comida -1].tope_ingredientes, juego->stitch.posicion.fil, juego->stitch.posicion.col);
				juego->stitch.objeto_en_mano = VACIO;
			}
			
		}else if(juego->personaje_activo == REUBEN){
			if(juego->reuben.objeto_en_mano == VACIO && !hay_fuego_cuadrante_reuben(juego->obstaculos, juego->tope_obstaculos) && hay_ingrediente(juego->comida, juego->tope_comida,juego->reuben.posicion.fil, juego->reuben.posicion.col)){

				juego->reuben.objeto_en_mano = buscar_tipo_ingrediente(juego->comida[juego->tope_comida - 1].ingrediente, juego->comida[juego->tope_comida -1].tope_ingredientes,juego->reuben.posicion.fil, juego->reuben.posicion.col);
				ocultar_ingrediente(juego->reuben.objeto_en_mano, juego->comida[juego->tope_comida - 1].ingrediente, juego->comida[juego->tope_comida -1].tope_ingredientes);

			}else if((juego->reuben.objeto_en_mano != VACIO && juego->reuben.objeto_en_mano != MATAFUEGOS) && !hay_ingrediente(juego->comida, juego->tope_comida, juego->reuben.posicion.fil, juego->reuben.posicion.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, juego->reuben.posicion.fil, juego->reuben.posicion.col)){

				cambiar_posicion_ingrediente(juego->reuben.objeto_en_mano, juego->comida[juego->tope_comida - 1].ingrediente, juego->comida[juego->tope_comida -1].tope_ingredientes, juego->reuben.posicion.fil, juego->reuben.posicion.col);
				juego->reuben.objeto_en_mano = VACIO;
			}
		}
		
	}

	if(movimiento == ACTIVAR_CUCHILLO && juego->personaje_activo == STITCH && !hay_fuego_cuadrante_stitch(juego->obstaculos, juego->tope_obstaculos) && hay_herramienta(juego->herramientas, juego->tope_herramientas, juego->stitch.posicion.fil, juego->stitch.posicion.col)){
		cortar_ingrediente(juego->stitch.objeto_en_mano, juego->comida[juego->tope_comida - 1].ingrediente, juego->comida[juego->tope_comida - 1].tope_ingredientes);
	}
	
	if(movimiento == PASAR){
		if(juego->personaje_activo == STITCH){
			if(juego->stitch.objeto_en_mano != VACIO && esta_cortado(juego->stitch.objeto_en_mano, juego->comida[juego->tope_comida - 1].ingrediente, juego->comida[juego->tope_comida - 1].tope_ingredientes) && !hay_fuego_cuadrante_stitch(juego->obstaculos, juego->tope_obstaculos) && !hay_ingrediente(juego->comida, juego->tope_comida, juego->stitch.posicion.fil + 1, juego->stitch.posicion.col) && distancia_manhattan(juego->stitch.posicion, juego->mesa, 1)){
				cambiar_posicion_ingrediente(juego->stitch.objeto_en_mano, juego->comida[juego->tope_comida - 1].ingrediente, juego->comida[juego->tope_comida - 1].tope_ingredientes, juego->stitch.posicion.fil + 1, juego->stitch.posicion.col);
				juego->stitch.objeto_en_mano = VACIO;
			}
		}else if(juego->personaje_activo == REUBEN){
			if(juego->reuben.objeto_en_mano == VACIO && !hay_fuego_cuadrante_reuben(juego->obstaculos, juego->tope_obstaculos) && distancia_manhattan(juego->reuben.posicion, juego->mesa, 1)){
				juego->reuben.objeto_en_mano = buscar_tipo_ingrediente(juego->comida[juego->tope_comida - 1].ingrediente, juego->comida[juego->tope_comida -1].tope_ingredientes, juego->reuben.posicion.fil - 1, juego->reuben.posicion.col);
				ocultar_ingrediente(juego->reuben.objeto_en_mano, juego->comida[juego->tope_comida - 1].ingrediente, juego->comida[juego->tope_comida - 1].tope_ingredientes);
			}
		}
	}
}


	

	if(movimiento == ACTIVAR_HORNO && juego->personaje_activo == REUBEN && juego->reuben.objeto_en_mano != VACIO && !esta_cortado(juego->reuben.objeto_en_mano, juego->comida, juego->tope_comida) && !hay_fuego_cuadrante_reuben(juego->obstaculos, juego->tope_obstaculos) && (distancia_manhattan(juego->reuben.posicion, juego->herramientas[2].posicion, 1) || distancia_manhattan(juego->reuben.posicion, juego->herramientas[3].posicion, 1))){
			cocinar_ingrediente(juego->reuben.objeto_en_mano, juego->comida, juego->tope_comida);
		}

	if(juego->movimientos == 15){
		inicializar_fuego(juego);
		inicializar_matafuegos(juego);
		juego->movimientos = 16;
	}
	
	if(movimiento == ACTIVAR_MATAFUEGO){
		if(juego->personaje_activo == STITCH && juego->stitch.objeto_en_mano == MATAFUEGOS && distancia_manhattan(juego->stitch.posicion, juego->obstaculos[(juego->tope_obstaculos) - 1].posicion, 2)){
			juego->tope_obstaculos--;
			juego->tope_herramientas--;
			juego->stitch.objeto_en_mano = VACIO;
			juego->movimientos = 0;
		}else if(juego->personaje_activo == REUBEN && juego->reuben.objeto_en_mano == MATAFUEGOS && distancia_manhattan(juego->reuben.posicion, juego->obstaculos[(juego->tope_obstaculos) - 1].posicion, 2)){
			juego->tope_obstaculos--;
			juego->tope_herramientas--;
			juego->reuben.objeto_en_mano = VACIO;
			juego->movimientos = 0;
		}
	}

	if(hay_puerta_salida(juego->salida, juego->reuben.posicion.fil, juego->reuben.posicion.col) && !hay_fuego_cuadrante_reuben(juego->obstaculos, juego->tope_obstaculos) && (esta_cortado(juego->reuben.objeto_en_mano, juego->comida, juego->tope_comida) || esta_cocinado(juego->reuben.objeto_en_mano, juego->comida, juego->tope_comida))){
		cargar_vector(juego);
		cambiar_posicion_ingrediente(juego->reuben.objeto_en_mano, juego->comida, juego->tope_comida, juego->reuben.posicion.fil, juego->reuben.posicion.col);
		juego->reuben.objeto_en_mano = VACIO;
	}

	if(juego->comida_actual == ENSALADA && juego->tope_comida_lista == 2){
		juego->comida_actual = PIZZA;
		inicializar_comida(juego);
		juego->tope_comida_lista = 0;
	}else if(juego->comida_actual == PIZZA && juego->tope_comida_lista == 3){
		juego->comida_actual = HAMBURGUESA;
		inicializar_comida(juego);
		juego->tope_comida_lista = 0;
	}else if(juego->comida_actual == HAMBURGUESA && juego->tope_comida_lista == 4){
		juego->comida_actual = SANDWICH;
		inicializar_comida(juego);
		juego->tope_comida_lista = 0;
	}
	
*/







