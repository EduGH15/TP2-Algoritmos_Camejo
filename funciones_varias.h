#ifndef __FUNCIONES_VARIAS_H__
#define __FUNCIONES_VARIAS_H__

#include "cocineritos.h"
#include "validaciones.h"


/*
Pre: Debe recibir valores válidos (todos los valores ingresados por parámetro deben ser mayores a cero, amplitud fila debe ser mayor a fil_inicial y amplitud columna debe ser mayor col_inicial).
Post: Devuelve una coordenata_t aleatoria
*/
coordenada_t generar_coordenada_aleatoria(int fil_inicial, int amplitud_fila, int col_inicial, int amplitud_columna);



/*
Pre: El parámetro de movimiento debe ser válido (admite valores como w, s, d, a).
post: Devuelve una coordenata_t de la nueva posicion del personaje
*/
coordenada_t generar_posicion_nueva(personaje_t personaje, char movimiento);


/*
Pre: El parámetro de movimiento debe ser válido (admite valores como w, s, d, a).
post: modifica la posicion actual del jugador hacia donde se quiera mover.
*/
void mover_jugador(personaje_t* jugador, char movimiento);


/*
Pre: los parametros fila y columna deben ser valores válidos (mayores a cero).
Post: Devuelve el tipo de ingrediente dada una fila y una columna, si no existe un ingrediente en esa posicion entonces no devuelve nada.
*/
char buscar_tipo_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes, int fila, int columna);

/*
Pre: ------------------------------------------------------------------------------------------------------------
Post: Modifica la posicion actual del ingrediente (en caso de que esté en el vector de ingredientes) y lo manda a una posición no visible para el usuario.
*/
void ocultar_ingrediente(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes);


/*
Pre: el parametro fila y columna deben ser valores válidos (mayores o iguales a 0)
Post: Modifica la posicion actual del ingrediente (en caso de que esté en el vector de ingredientes) y lo manda a una fila y a una columna que se le pase por parámetro.
*/
void cambiar_posicion_ingrediente(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes, int fila, int columna);

/*
Pre: --------------------------------------------------------------------------------------------------------------------------------------------------
Post: Modifica el estado actual del ingrediente (en caso de que esté en el vector de ingredientes). 
si cortado = false ----> cortado = true.
*/
void cortar_ingrediente(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes);

/*
Pre: --------------------------------------------------------------------------------------------------------------------------------------------------
Post: Modifica el estado actual del ingrediente (en caso de que esté en el vector de ingredientes). 
si cocinado = false ----> cocinado = true.
*/
void cocinar_ingrediente(char tipo_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes);

/*
Pre: los parametros fila y columna deben ser valores válidos (mayores a cero).
Post: Devuelve el tipo de herramienta  dada una posicion (en caso de que exista una herramienta en la fila y la columna que se le pase por parámetro). 
*/
char buscar_tipo_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna);

/*
Pre: ------------------------------------------------------------------------------------------------------------
Post: Modifica la posicion actual de la herramienta (en caso de que esté en el vector de herramientas) y lo manda a una posición no visible para el usuario.
*/
void ocultar_herramienta(char tipo_herramienta, objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas);

/*
Pre: el parámetro de comida_actual debe ser un valor válido (toma valores como E, P, H, S).
Post: Devuelve un numero de orden dependiendo de cual sea la comida actual:
*/
int orden_actual(char comida_actual);

/*
Pre: -------------------------------------------------------------------------------------------------------------------------------
Post: Modifica el vector de obstaculo y el tope de obstaculo, asignandole una posicion.fil, una posicion.col y un tipo de obstáculo.
*/
void asignar_obstaculo(objeto_t obstaculos[MAX_OBSTACULOS], int* tope_obstaculos, coordenada_t posicion, char tipo_obstaculo);

/*
Pre: -------------------------------------------------------------------------------------------------------------------------------
Post: Modifica el vector de herramientas y el tope de herramientas, asignandole una posicion.fil, una posicion.col y un tipo de herramienta.
*/
void asignar_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int* tope_herramientas, coordenada_t posicion, char tipo_herramienta);

/*
Pre: -------------------------------------------------------------------------------------------------------------------------------
Post: Modifica el vector de ingredientes y el tope de ingredientes, asignandole una posicion.fil, una posicion.col y un tipo de ingrediente.
*/
void asignar_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int* tope_ingredientes, coordenada_t posicion, char tipo_ingrediente);

/*
Pre:.....................................................................................................
Post: modifica la posicion del personaje, su tipo y el objeto en mano.
*/
void asignar_personaje(personaje_t* personaje, coordenada_t posicion, char tipo, char objeto_en_mano);

/*
Pre: orden debe ser un valor válido (0:ENSALDA, 1: PIZZA, 2: HAMBURGUESA, 3: SANDWICH)
Post: carga el vector de comida lista con los ingredientes correspondientes a cada comida, también carga su posicion final y su estado (cortado o cocinado).
*/
void cargar_vector(juego_t* juego, int orden);

/*
Pre:----------------------------------------------------------------------------
Post: cambia la comida actual, inicializa los ingredientes de la nueva comida y reinicia el tope de comida_lista a cero.
*/
void cambiar_nivel(juego_t* juego);

#endif /*__FUNCIONES_VARIAS_H__*/