#include "inicializar_juego.h"

void inicializar_precio_total(juego_t* juego, int precio){
	juego->precio_total = precio;
}

void inicializar_paredes(juego_t* juego){
	juego->tope_paredes = 0;
	for(int i = 0; i < MAX_FIL; i++){
		for(int j = 0; j < MAX_COL; j++){
			if(j == PRIMERA_COLUMNA || j == ULTIMA_COLUMNA){
				juego->paredes[juego->tope_paredes].fil = i;
				juego->paredes[juego->tope_paredes].col = j;
				(juego->tope_paredes)++;
			}
			if((j > PRIMERA_COLUMNA && j < ULTIMA_COLUMNA) && (i == PRIMERA_FILA || (i == FILA_DEL_MEDIO && j != CENTRO_COLUMNA)|| i == ULTIMA_FILA)){
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

	while(cuadrante_stitch < CANTIDAD_AGUJEROS_CUADRANTE){
		coordenada_t posicion_agujero = generar_coordenada_aleatoria(1, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_agujero.fil, posicion_agujero.col)){
			asignar_obstaculo(juego->obstaculos, &(juego)->tope_obstaculos, posicion_agujero, AGUJEROS);
			cuadrante_stitch++;
		}
	}

	while(cuadrante_reuben < CANTIDAD_AGUJEROS_CUADRANTE){
		coordenada_t posicion_agujero = generar_coordenada_aleatoria(11, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_agujero.fil, posicion_agujero.col)){
			asignar_obstaculo(juego->obstaculos, &(juego)->tope_obstaculos, posicion_agujero, AGUJEROS);
			cuadrante_reuben++;
		}
	}
}

void inicializar_herramientas(juego_t* juego){
	juego->tope_herramientas = 0;
	int herramientas_stitch = 0;
	int herramientas_reuben = 0;

	while(herramientas_stitch < CANTIDAD_HERRAMIENTAS_CUADRANTE){
		coordenada_t posicion_herramienta = generar_coordenada_aleatoria(1, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_herramienta.fil, posicion_herramienta.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_herramienta.fil, posicion_herramienta.col)){
			asignar_herramienta(juego->herramientas, &(juego)->tope_herramientas, posicion_herramienta, CUCHILLO);
			herramientas_stitch++;
		}
	}

	while(herramientas_reuben < CANTIDAD_HERRAMIENTAS_CUADRANTE){
		coordenada_t posicion_herramienta = generar_coordenada_aleatoria(11, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_herramienta.fil, posicion_herramienta.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_herramienta.fil, posicion_herramienta.col)){
			asignar_herramienta(juego->herramientas, &(juego)->tope_herramientas, posicion_herramienta, HORNO);
			herramientas_reuben++;
		}
	}
}

void inicializar_ingredientes_ensalada(juego_t* juego){
	juego->comida[ORDEN_ENSALADA].tope_ingredientes = 0;
	int cantidad_lechuga = 0;
	int cantidad_tomate = 0;
	for(int i = 0; i < MAX_INGREDIENTES; i++){
		juego->comida[ORDEN_ENSALADA].ingrediente[juego->comida[ORDEN_ENSALADA].tope_ingredientes].esta_cocinado = false;
		juego->comida[ORDEN_ENSALADA].ingrediente[juego->comida[ORDEN_ENSALADA].tope_ingredientes].esta_cortado = false;
		if(i == 0){
			while(cantidad_lechuga < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_ENSALADA].ingrediente, juego->comida[ORDEN_ENSALADA].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_ENSALADA].ingrediente, &(juego)->comida[ORDEN_ENSALADA].tope_ingredientes, posicion_ingrediente, LECHUGA);
					cantidad_lechuga++;
				}
			}
		}else if(i == 1){
			while(cantidad_tomate < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_ENSALADA].ingrediente, juego->comida[ORDEN_ENSALADA].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_ENSALADA].ingrediente, &(juego)->comida[ORDEN_ENSALADA].tope_ingredientes, posicion_ingrediente, TOMATE);
					cantidad_tomate++;
				}
			}
		}
	
	}
}

void inicializar_ingredientes_pizza(juego_t* juego){
	juego->comida[ORDEN_PIZZA].tope_ingredientes = 0;
	int cantidad_masa = 0;
	int cantidad_jamon = 0;
	int cantidad_queso = 0; 
	for(int i = 0; i < MAX_INGREDIENTES; i++){
		juego->comida[ORDEN_PIZZA].ingrediente[juego->comida[ORDEN_PIZZA].tope_ingredientes].esta_cocinado = false;
		juego->comida[ORDEN_PIZZA].ingrediente[juego->comida[ORDEN_PIZZA].tope_ingredientes].esta_cortado = false;
		if(i == 0){
			while(cantidad_masa < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(11, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_PIZZA].ingrediente, juego->comida[ORDEN_PIZZA].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_PIZZA].ingrediente, &(juego)->comida[ORDEN_PIZZA].tope_ingredientes, posicion_ingrediente, MASA);
					cantidad_masa++;
				}
			}
		}else if(i == 1){
			while(cantidad_jamon < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_PIZZA].ingrediente, juego->comida[ORDEN_PIZZA].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_PIZZA].ingrediente, &(juego)->comida[ORDEN_PIZZA].tope_ingredientes, posicion_ingrediente, JAMON);
					cantidad_jamon++;
				}
			}
		}else if(i == 2){
			while(cantidad_queso < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_PIZZA].ingrediente, juego->comida[ORDEN_PIZZA].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_PIZZA].ingrediente, &(juego)->comida[ORDEN_PIZZA].tope_ingredientes, posicion_ingrediente, QUESO);
					cantidad_queso++;
				}
			}
		}
	}
}

void inicializar_ingredientes_hamburguesa(juego_t* juego){
	juego->comida[ORDEN_HAMBURGUESA].tope_ingredientes = 0;
	int cantidad_pan = 0; 
	int cantidad_carne = 0;
	int cantidad_lechuga = 0;
	int cantidad_tomate = 0;
	for(int i = 0; i < MAX_INGREDIENTES; i++){
		juego->comida[ORDEN_HAMBURGUESA].ingrediente[juego->comida[ORDEN_HAMBURGUESA].tope_ingredientes].esta_cocinado = false;
		juego->comida[ORDEN_HAMBURGUESA].ingrediente[juego->comida[ORDEN_HAMBURGUESA].tope_ingredientes].esta_cortado = false;
		if(i == 0){
			while(cantidad_pan < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_HAMBURGUESA].ingrediente, juego->comida[ORDEN_HAMBURGUESA].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_HAMBURGUESA].ingrediente, &(juego)->comida[ORDEN_HAMBURGUESA].tope_ingredientes, posicion_ingrediente, PAN);
					cantidad_pan++;
				}
			}
		}else if(i == 1){
			while(cantidad_carne < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(11, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_HAMBURGUESA].ingrediente, juego->comida[ORDEN_HAMBURGUESA].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_HAMBURGUESA].ingrediente, &(juego)->comida[ORDEN_HAMBURGUESA].tope_ingredientes, posicion_ingrediente, CARNE);
					cantidad_carne++;
				}
			}
		}else if(i == 2){
			while(cantidad_lechuga < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_HAMBURGUESA].ingrediente, juego->comida[ORDEN_HAMBURGUESA].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_HAMBURGUESA].ingrediente, &(juego)->comida[ORDEN_HAMBURGUESA].tope_ingredientes, posicion_ingrediente, LECHUGA);
					cantidad_lechuga++;
				}
			}
		}else if(i == 3){
			while(cantidad_tomate < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_HAMBURGUESA].ingrediente, juego->comida[ORDEN_HAMBURGUESA].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_HAMBURGUESA].ingrediente, &(juego)->comida[ORDEN_HAMBURGUESA].tope_ingredientes, posicion_ingrediente, TOMATE);
					cantidad_tomate++;
				}
			}
		}
	}
}

void inicializar_ingredientes_sandwich(juego_t* juego){
	juego->comida[ORDEN_SANDWICH].tope_ingredientes = 0;
	int cantidad_milanesa = 0;
	int cantidad_pan = 0;
	int cantidad_tomate = 0;
	int cantidad_lechuga = 0;
	int cantidad_jamon = 0;
	int cantidad_queso = 0;
	for(int i = 0; i < MAX_INGREDIENTES; i++){
		juego->comida[ORDEN_SANDWICH].ingrediente[juego->comida[ORDEN_SANDWICH].tope_ingredientes].esta_cocinado = false;
		juego->comida[ORDEN_SANDWICH].ingrediente[juego->comida[ORDEN_SANDWICH].tope_ingredientes].esta_cortado = false;
		if(i == 0){
			while(cantidad_milanesa < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(11, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_SANDWICH].ingrediente, juego->comida[ORDEN_SANDWICH].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_SANDWICH].ingrediente, &(juego)->comida[ORDEN_SANDWICH].tope_ingredientes, posicion_ingrediente, MILANESA);
					cantidad_milanesa++;
				}
			}
		}else if(i == 1){
			while(cantidad_pan < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_SANDWICH].ingrediente, juego->comida[ORDEN_SANDWICH].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_SANDWICH].ingrediente, &(juego)->comida[ORDEN_SANDWICH].tope_ingredientes, posicion_ingrediente, PAN);
					cantidad_pan++;
				}
			}
		}else if(i == 2){
			while(cantidad_tomate < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_SANDWICH].ingrediente, juego->comida[ORDEN_SANDWICH].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_SANDWICH].ingrediente, &(juego)->comida[ORDEN_SANDWICH].tope_ingredientes, posicion_ingrediente, TOMATE);
					cantidad_tomate++;
				}
			}
		}else if(i == 3){
			while(cantidad_lechuga < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_SANDWICH].ingrediente, juego->comida[ORDEN_SANDWICH].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_SANDWICH].ingrediente, &(juego)->comida[ORDEN_SANDWICH].tope_ingredientes, posicion_ingrediente, LECHUGA);
					cantidad_lechuga++;
				}
			}
		}else if(i == 4){
			while(cantidad_jamon < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[ORDEN_SANDWICH].ingrediente, juego->comida[ORDEN_SANDWICH].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_SANDWICH].ingrediente, &(juego)->comida[ORDEN_SANDWICH].tope_ingredientes, posicion_ingrediente, JAMON);
					cantidad_jamon++;
				}
			}
		}else if(i == 5){
			while(cantidad_queso < CANTIDAD_MAX_POR_INGREDIENTE){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[3].ingrediente, juego->comida[3].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[ORDEN_SANDWICH].ingrediente, &(juego)->comida[ORDEN_SANDWICH].tope_ingredientes, posicion_ingrediente, QUESO);
					cantidad_queso++;
				}
			}
		}
	}
}

void inicializar_puerta_salida(juego_t* juego){
	bool es_posicion_valida = false;
	while(!es_posicion_valida){
		coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(11, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida[ORDEN_ENSALADA].ingrediente, juego->comida[ORDEN_ENSALADA].tope_ingredientes, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_jugador(*juego, posicion_aleatoria.fil, posicion_aleatoria.col)){
			juego->salida.fil = posicion_aleatoria.fil;
			juego->salida.col = posicion_aleatoria.col;
			es_posicion_valida = true;
		}
	}
}

void inicializar_personajes(juego_t* juego){
	juego->personaje_activo = STITCH;
	int posicion_valida_stitch = false;
	int posicion_valida_reuben = false;
	while(!posicion_valida_stitch){
		coordenada_t posicion_personaje = generar_coordenada_aleatoria(1, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_personaje.fil, posicion_personaje.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_personaje.fil, posicion_personaje.col) && !hay_ingrediente(juego->comida[ORDEN_ENSALADA].ingrediente, juego->comida[ORDEN_ENSALADA].tope_ingredientes, posicion_personaje.fil, posicion_personaje.col)){
			asignar_personaje(&(juego)->stitch, posicion_personaje, STITCH, VACIO);
			posicion_valida_stitch = true;
		}
	}
	while(!posicion_valida_reuben){
		coordenada_t posicion_personaje = generar_coordenada_aleatoria(11, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_personaje.fil, posicion_personaje.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_personaje.fil, posicion_personaje.col) && !hay_ingrediente(juego->comida[ORDEN_ENSALADA].ingrediente, juego->comida[ORDEN_ENSALADA].tope_ingredientes, posicion_personaje.fil, posicion_personaje.col) && !hay_puerta_salida(juego->salida, posicion_personaje.fil, posicion_personaje.col)){
			asignar_personaje(&(juego)->reuben, posicion_personaje, REUBEN, VACIO);
			posicion_valida_reuben = true;
		}
	}
}

void inicializar_fuego(juego_t* juego, int orden){
	int posicion_valida_fuego = false;
	while(!posicion_valida_fuego){
		coordenada_t posicion_fuego = generar_coordenada_aleatoria(1, 19, 1, 19);
		if(hay_vacio(*juego, orden, posicion_fuego.fil, posicion_fuego.col)){
			asignar_obstaculo(juego->obstaculos, &(juego)->tope_obstaculos, posicion_fuego, FUEGO);
			posicion_valida_fuego = true;
		}
	}
}

void inicializar_matafuegos(juego_t* juego, int orden){
	int posicion_valida_matafuegos = false;
	while(!posicion_valida_matafuegos){
		coordenada_t posicion_matafuegos = generar_coordenada_aleatoria(1, 19, 1, 19);
		if(hay_vacio(*juego, orden, posicion_matafuegos.fil, posicion_matafuegos.col) && estan_mismo_cuadrante(posicion_matafuegos.fil, juego->obstaculos[(juego->tope_obstaculos)-1].posicion.fil)){
			asignar_herramienta(juego->herramientas, &(juego)->tope_herramientas, posicion_matafuegos, MATAFUEGOS);
			posicion_valida_matafuegos = true;
		}
	}
}

void inicializar_grilla_vacia(char grilla[MAX_FIL][MAX_COL]){
    for(int i = 0; i < MAX_FIL; i++){
        for(int j = 0; j < MAX_COL; j++){
           grilla[i][j] = ESPACIO_BLANCO;
        }
    }
}

/*
Pre: El tope_paredes debe ser mayor o igual a cero y menor o igual a la constante MAX_PAREDES
Post: Le asigna al caracter '#' una posición en la grilla
*/
void posicionar_paredes(coordenada_t paredes[MAX_PAREDES], int tope_paredes, char grilla[MAX_FIL][MAX_COL]){
	for(int i = 0; i < tope_paredes; i++){
		grilla[paredes[i].fil][paredes[i].col] = PARED;
	}
}

/*
pre:El tope de obstáculos debe ser mayor o igual a cero y menor o igual a la constante MAX_OBSTACULOS
Post: Le asigna al caracter 'A' o 'F' una posición en la grilla
*/
void posicionar_obstaculos(objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos, char grilla[MAX_FIL][MAX_COL]){
	for(int i = 0; i < tope_obstaculos; i++){
		grilla[obstaculos[i].posicion.fil][obstaculos[i].posicion.col] = obstaculos[i].tipo;
	}
}

/*
pre:El tope de herramientas debe ser mayor o igual a cero y menor o igual a la constante MAX_HERRAMIENTAS
Post: Le asigna al caracter 'C' o 'H' o 'M' una posición en la grilla 
*/
void posicionar_herramientas(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, char grilla[MAX_FIL][MAX_COL]){
	for(int i = 0; i < tope_herramientas; i++){
		grilla[herramientas[i].posicion.fil][herramientas[i].posicion.col] = herramientas[i].tipo;
	}
}

/*
pre:--------------------------------------------------------------------------------------
Post: Le asigna a todos los caracteres de ingredientes una posición en la grilla, dependiendo de cual sea la comida/nivel actual.
*/
void posicionar_ingredientes(juego_t juego, char grilla[MAX_FIL][MAX_COL]){
	if(juego.comida_actual == ENSALADA){
		for(int i = 0; i < juego.comida[ORDEN_ENSALADA].tope_ingredientes; i++){
		grilla[juego.comida[ORDEN_ENSALADA].ingrediente[i].posicion.fil][juego.comida[ORDEN_ENSALADA].ingrediente[i].posicion.col] = juego.comida[ORDEN_ENSALADA].ingrediente[i].tipo;
		}
	}else if(juego.comida_actual == PIZZA){
		for(int i = 0; i < juego.comida[ORDEN_PIZZA].tope_ingredientes; i++){
		grilla[juego.comida[ORDEN_PIZZA].ingrediente[i].posicion.fil][juego.comida[ORDEN_PIZZA].ingrediente[i].posicion.col] = juego.comida[ORDEN_PIZZA].ingrediente[i].tipo;
		}
	}else if(juego.comida_actual == HAMBURGUESA){
		for(int i = 0; i < juego.comida[ORDEN_HAMBURGUESA].tope_ingredientes; i++){
		grilla[juego.comida[ORDEN_HAMBURGUESA].ingrediente[i].posicion.fil][juego.comida[ORDEN_HAMBURGUESA].ingrediente[i].posicion.col] = juego.comida[ORDEN_HAMBURGUESA].ingrediente[i].tipo;
		}
	}else if(juego.comida_actual == SANDWICH){
		for(int i = 0; i < juego.comida[ORDEN_SANDWICH].tope_ingredientes; i++){
			grilla[juego.comida[ORDEN_SANDWICH].ingrediente[i].posicion.fil][juego.comida[ORDEN_SANDWICH].ingrediente[i].posicion.col] = juego.comida[ORDEN_SANDWICH].ingrediente[i].tipo;
		}
	}
}

void llenar_grilla(juego_t juego, char grilla[MAX_FIL][MAX_COL]){
	posicionar_paredes(juego.paredes, juego.tope_paredes, grilla);
	grilla[juego.mesa.fil][juego.mesa.col] = MESA;
	posicionar_obstaculos(juego.obstaculos, juego.tope_obstaculos, grilla);
	posicionar_herramientas(juego.herramientas, juego.tope_herramientas, grilla);
	posicionar_ingredientes(juego, grilla);
	grilla[juego.salida.fil][juego.salida.col] = PUERTA_SALIDA;
	grilla[juego.stitch.posicion.fil][juego.stitch.posicion.col] = juego.stitch.tipo;
	grilla[juego.reuben.posicion.fil][juego.reuben.posicion.col] = juego.reuben.tipo;
	
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