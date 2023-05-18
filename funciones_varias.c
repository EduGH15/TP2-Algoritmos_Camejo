#include "funciones_varias.h"


coordenada_t generar_coordenada_aleatoria(int fil_inicial, int amplitud_fila, int col_inicial, int amplitud_columna){
	coordenada_t posicion;
	posicion.fil = rand() % amplitud_fila + fil_inicial; 
	posicion.col = rand() % amplitud_columna + col_inicial; 
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
		jugador->posicion.fil += -1;
	}else if(movimiento == ABAJO){
		jugador->posicion.fil += 1;
	}else if(movimiento == DERECHA){
		jugador->posicion.col += 1;
	}else if(movimiento == IZQUIERDA){
		jugador->posicion.col += -1;
	}
}

char buscar_tipo_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes, int fila, int columna){
	char tipo_ingrediente = ESPACIO_BLANCO;
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
			ingrediente[i].posicion.fil = POSICION_INVALIDA_FIL;
			ingrediente[i].posicion.col = POSICION_INVALIDA_COL;
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
		if(ingrediente[i].tipo == tipo_ingrediente && (tipo_ingrediente != CARNE && tipo_ingrediente != MILANESA && tipo_ingrediente != MASA)){
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
		if(ingrediente[i].tipo == tipo_ingrediente && (tipo_ingrediente == CARNE || tipo_ingrediente == MILANESA || tipo_ingrediente == MASA)){
			ingrediente[i].esta_cocinado = true;
			cocinado = true;
		}
		i++;
	}
}

char buscar_tipo_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int fila, int columna){
	char tipo_herramienta = ESPACIO_BLANCO;
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
			herramientas[i].posicion.fil = POSICION_INVALIDA_FIL;
			herramientas[i].posicion.col = POSICION_INVALIDA_COL;
			encontro = true;
		}
		i++;
	}
}

int orden_actual(char comida_actual){
	int orden = ORDEN_ENSALADA;
	if(comida_actual == PIZZA){
		orden = ORDEN_PIZZA;
	}else if(comida_actual == HAMBURGUESA){
		orden = ORDEN_HAMBURGUESA;
	}else if (comida_actual == SANDWICH){
		orden = ORDEN_SANDWICH;
	}
	return orden;
}

void asignar_obstaculo(objeto_t obstaculos[MAX_OBSTACULOS], int* tope_obstaculos, coordenada_t posicion, char tipo_obstaculo){
	obstaculos[*tope_obstaculos].posicion.fil = posicion.fil;
	obstaculos[*tope_obstaculos].posicion.col = posicion.col;
	obstaculos[*tope_obstaculos].tipo = tipo_obstaculo;
	(*tope_obstaculos)++;

}

void asignar_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int* tope_herramientas, coordenada_t posicion, char tipo_herramienta){
	herramientas[*tope_herramientas].posicion.fil = posicion.fil;
	herramientas[*tope_herramientas].posicion.col = posicion.col;
	herramientas[*tope_herramientas].tipo = tipo_herramienta;
	(*tope_herramientas)++;
}

void asignar_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int* tope_ingredientes, coordenada_t posicion, char tipo_ingrediente){
	ingrediente[*tope_ingredientes].posicion.fil = posicion.fil;
	ingrediente[*tope_ingredientes].posicion.col = posicion.col;
	ingrediente[*tope_ingredientes].tipo = tipo_ingrediente;
	(*tope_ingredientes)++;
}

void asignar_personaje(personaje_t* personaje, coordenada_t posicion, char tipo, char objeto_en_mano){
    personaje->posicion.fil = posicion.fil;
	personaje->posicion.col = posicion.col;
	personaje->objeto_en_mano = objeto_en_mano;
	personaje->tipo = tipo;
}

void cargar_vector(juego_t* juego, int orden){
	juego->comida_lista[juego->tope_comida_lista].posicion.fil = juego->reuben.posicion.fil;
	juego->comida_lista[juego->tope_comida_lista].posicion.col = juego->reuben.posicion.col;
	juego->comida_lista[juego->tope_comida_lista].tipo = juego->reuben.objeto_en_mano;
	juego->comida_lista[juego->tope_comida_lista].esta_cortado = esta_cortado(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
	juego->comida_lista[juego->tope_comida_lista].esta_cocinado = esta_cocinado(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
	(juego->tope_comida_lista)++;
	
}

void cambiar_nivel(juego_t* juego){
	if(juego->comida_actual == ENSALADA && juego->tope_comida_lista == 2){
		juego->comida_actual = PIZZA;
		juego->tope_comida_lista = SIN_COMIDA_LISTA;
		juego->comida[ORDEN_PIZZA].tipo = PIZZA;
		(juego->tope_comida)++;
		inicializar_ingredientes_pizza(juego);
	}else if(juego->comida_actual == PIZZA && juego->tope_comida_lista == 3){
		juego->comida_actual = HAMBURGUESA;
		juego->tope_comida_lista = SIN_COMIDA_LISTA;
		juego->comida[ORDEN_HAMBURGUESA].tipo = HAMBURGUESA;
		(juego->tope_comida)++;
		inicializar_ingredientes_hamburguesa(juego);
	}else if(juego->comida_actual == HAMBURGUESA && juego->tope_comida_lista == 4){
		juego->comida_actual = SANDWICH;
		juego->tope_comida_lista = SIN_COMIDA_LISTA;
		juego->comida[ORDEN_SANDWICH].tipo = SANDWICH;
		(juego->tope_comida)++;
		inicializar_ingredientes_sandwich(juego);
	}
}