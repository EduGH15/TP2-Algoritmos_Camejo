#include <stdio.h>
#include <stdbool.h>

#include "cocineritos.h"

void inicializar_juego(juego_t* juego, int precio){
	//Stich
	juego->stitch.posicion.fil = 3; //La posicion de stich deberia ser random
	juego->stitch.posicion.col = 10;
	juego->stitch.tipo = 'S';
	juego->stitch.objeto_en_mano = ' '; //No tiene nada en la mano
	//Reuben
	juego->reuben.posicion.fil = 15;
	juego->reuben.posicion.col = 10;
	juego->reuben.tipo = 'R';
	juego->reuben.objeto_en_mano = ' ';
	//------------------
	juego->personaje_activo = 'S';// comienza estando activo stich y luego pasa a Reuben si se presiona X
	//----------------------
	juego->comida_actual = 'E'; //Ensalada, luego siguen otros...
	//Paredes
	juego->paredes[0].fil = 0; //Pero quedan mas paredes para agregar, solo agregué la pared que esta en (0,0)
	juego->tope_paredes = 1;
	juego->paredes[1].col = 0;
	juego->tope_paredes = 2;
	//Herramientas
	juego->herramientas[0].posicion.fil = 1;
	juego->tope_herramientas = 1;
	juego->herramientas[1].posicion.col = 1;
	juego->tope_herramientas = 2;
	juego->herramientas[2].tipo = 'C'; //cuchillo
	juego->tope_herramientas = 3; //Pero quedan mas herramientas para agregar (1,1,C)
	//Salida
	juego->salida.fil = 20; //Pero debe ser random
	juego->salida.col = 10;
	//Mesa
	juego->mesa.fil = 10;
	juego->mesa.col = 10;
	//Obstaculos
	juego->obstaculos[0].posicion.fil = 9;
	juego->tope_obstaculos = 1;
	juego->obstaculos[1].posicion.col = 9;
	juego->tope_obstaculos = 2;
	juego->obstaculos[2].tipo = 'A'; // Agujero pero tambien falta el fuego
	juego->tope_herramientas = 3;
	//Comida: comienza con ensalada, luego con...
	juego->comida[0].ingrediente[0].posicion.fil = 0;


	

}
//void realizar_jugada(juego_t* juego, char movimiento)
//void imprimir_terreno(juego_t juego)
//int estado_juego(juego_t juego)














