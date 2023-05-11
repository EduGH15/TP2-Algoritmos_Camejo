#ifndef __COCINERITOS_H__
#define __COCINERITOS_H__

#include <stdbool.h>

#define MAX_INGREDIENTES 10
#define MAX_PAREDES 200
#define MAX_HERRAMIENTAS 50
#define MAX_OBSTACULOS 50
#define MAX_COMIDA 5
#define MAX_FIL 21
#define MAX_COL 21

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


typedef struct coordenada{
	int fil;
	int col;
}coordenada_t;

typedef struct objeto{
	coordenada_t posicion;
	char tipo;
}objeto_t;

typedef struct ingrediente{
	coordenada_t posicion;
	char tipo;
	bool esta_cortado;
	bool esta_cocinado;
}ingrediente_t;

typedef struct comida{
	ingrediente_t ingrediente[MAX_INGREDIENTES];
	int tope_ingredientes;
	char tipo;
}comida_t;

typedef struct personaje{
	coordenada_t posicion;
	char tipo;
	char objeto_en_mano;
}personaje_t;

typedef struct juego{
	personaje_t stitch; 
	personaje_t reuben; 
	char personaje_activo;
	char comida_actual; 
	coordenada_t paredes[MAX_PAREDES]; //Listo
	int tope_paredes; //Listo
	objeto_t herramientas[MAX_HERRAMIENTAS];
	int tope_herramientas; //Falta matafuego
	coordenada_t salida; 
	coordenada_t mesa; //Listo
	objeto_t obstaculos[MAX_OBSTACULOS]; //Falta fuego
	int tope_obstaculos;//Falta fuego
	comida_t comida[MAX_COMIDA];
	int tope_comida;
	ingrediente_t comida_lista[MAX_INGREDIENTES]; //Al inicio no hay comida lista
	int tope_comida_lista; //Al inicio no hay comida lista
	int precio_total;//Listo
	int movimientos;
}juego_t;

/*
 * Inicializará el juego, cargando toda la información inicial de las comidas, personajes, herramientas y obstáculos.
 * El precio corresponde al precio obtenido en el TP1.
 */
void inicializar_juego(juego_t* juego, int precio);

/*
 * Moverá al personaje correspondiente y se realizarán todas las acciones necesarias.
 *
 */
void realizar_jugada(juego_t* juego, char movimiento);

/*
 * Imprime el juego por pantalla
 */
void imprimir_terreno(juego_t juego);

/*
 * El juego se dará por ganado si los personajes cumplen con los platos pedidos. Si alguno de los personajes cae por
 * un agujero, se considerará perdido.
 * Devuelve:
 * --> 1 si es ganado
 * --> -1 si es perdido
 * --> 0 si se sigue jugando
 */
int estado_juego(juego_t juego);

#endif /* __COCINERITOS_H__ */