#include "validaciones.h"

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

bool hay_vacio(juego_t juego, int orden, int fila, int columna){
	return !hay_pared(juego.paredes, juego.tope_paredes, fila, columna) && !hay_mesa(juego.mesa, fila, columna) && !hay_obstaculo(juego.obstaculos, juego.tope_obstaculos, fila, columna) && !hay_herramienta(juego.herramientas, juego.tope_herramientas, fila, columna) && !hay_ingrediente(juego.comida[orden].ingrediente, juego.comida[orden].tope_ingredientes, fila, columna) && !hay_jugador(juego, fila, columna);
}

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

bool estan_mismo_cuadrante(int fila_objeto_1,  int fila_objeto_2){
	return ((fila_objeto_1 >= 1 && fila_objeto_1 <= 9) && (fila_objeto_2 >=1 && fila_objeto_2 <= 9)) || ((fila_objeto_1 >= 11 && fila_objeto_1 <= 19) && (fila_objeto_2 >=11 && fila_objeto_2 <= 19));
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
