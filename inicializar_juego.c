#include "inicializar_juego.h"

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
			asignar_obstaculo(juego->obstaculos, &(juego)->tope_obstaculos, posicion_agujero, AGUJEROS);
			cuadrante_stitch++;
		}
	}

	while(cuadrante_reuben < 10){
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

	while(herramientas_stitch < 2){
		coordenada_t posicion_herramienta = generar_coordenada_aleatoria(1, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_herramienta.fil, posicion_herramienta.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_herramienta.fil, posicion_herramienta.col)){
			asignar_herramienta(juego->herramientas, &(juego)->tope_herramientas, posicion_herramienta, CUCHILLO);
			herramientas_stitch++;
		}
	}

	while(herramientas_reuben < 2){
		coordenada_t posicion_herramienta = generar_coordenada_aleatoria(11, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_herramienta.fil, posicion_herramienta.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_herramienta.fil, posicion_herramienta.col)){
			asignar_herramienta(juego->herramientas, &(juego)->tope_herramientas, posicion_herramienta, HORNO);
			herramientas_reuben++;
		}
	}
}

void inicializar_ingredientes_ensalada(juego_t* juego){
	juego->comida[0].tope_ingredientes = 0;
	int cantidad_lechuga = 0;
	int cantidad_tomate = 0;
	for(int i = 0; i < MAX_INGREDIENTES; i++){
		juego->comida[0].ingrediente[juego->comida[0].tope_ingredientes].esta_cocinado = false;
		juego->comida[0].ingrediente[juego->comida[0].tope_ingredientes].esta_cortado = false;
		if(i == 0){
			while(cantidad_lechuga < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[0].ingrediente, juego->comida[0].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[0].ingrediente, &(juego)->comida[0].tope_ingredientes, posicion_ingrediente, LECHUGA);
					cantidad_lechuga++;
				}
			}
		}else if(i == 1){
			while(cantidad_tomate < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[0].ingrediente, juego->comida[0].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[0].ingrediente, &(juego)->comida[0].tope_ingredientes, posicion_ingrediente, TOMATE);
					cantidad_tomate++;
				}
			}
		}
	
	}
}

void inicializar_ingredientes_pizza(juego_t* juego){
	juego->comida[1].tope_ingredientes = 0;
	int cantidad_masa = 0;
	int cantidad_jamon = 0;
	int cantidad_queso = 0; 
	for(int i = 0; i < MAX_INGREDIENTES; i++){
		juego->comida[1].ingrediente[juego->comida[1].tope_ingredientes].esta_cocinado = false;
		juego->comida[1].ingrediente[juego->comida[1].tope_ingredientes].esta_cortado = false;
		if(i == 0){
			while(cantidad_masa < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(11, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[1].ingrediente, juego->comida[1].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[1].ingrediente, &(juego)->comida[1].tope_ingredientes, posicion_ingrediente, MASA);
					cantidad_masa++;
				}
			}
		}else if(i == 1){
			while(cantidad_jamon < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[1].ingrediente, juego->comida[1].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[1].ingrediente, &(juego)->comida[1].tope_ingredientes, posicion_ingrediente, JAMON);
					cantidad_jamon++;
				}
			}
		}else if(i == 2){
			while(cantidad_queso < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[1].ingrediente, juego->comida[1].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[1].ingrediente, &(juego)->comida[1].tope_ingredientes, posicion_ingrediente, QUESO);
					cantidad_queso++;
				}
			}
		}
	}
}

void inicializar_ingredientes_hamburguesa(juego_t* juego){
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
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[2].ingrediente, juego->comida[2].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[2].ingrediente, &(juego)->comida[2].tope_ingredientes, posicion_ingrediente, PAN);
					cantidad_pan++;
				}
			}
		}else if(i == 1){
			while(cantidad_carne < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(11, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[2].ingrediente, juego->comida[2].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[2].ingrediente, &(juego)->comida[2].tope_ingredientes, posicion_ingrediente, CARNE);
					cantidad_carne++;
				}
			}
		}else if(i == 2){
			while(cantidad_lechuga < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[2].ingrediente, juego->comida[2].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[2].ingrediente, &(juego)->comida[2].tope_ingredientes, posicion_ingrediente, LECHUGA);
					cantidad_lechuga++;
				}
			}
		}else if(i == 3){
			while(cantidad_tomate < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[2].ingrediente, juego->comida[2].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[2].ingrediente, &(juego)->comida[2].tope_ingredientes, posicion_ingrediente, TOMATE);
					cantidad_tomate++;
				}
			}
		}
	}
}

void inicializar_ingredientes_sandwich(juego_t* juego){
	juego->comida[3].tope_ingredientes = 0;
	int cantidad_milanesa = 0;
	int cantidad_pan = 0;
	int cantidad_tomate = 0;
	int cantidad_lechuga = 0;
	int cantidad_jamon = 0;
	int cantidad_queso = 0;
	for(int i = 0; i < MAX_INGREDIENTES; i++){
		juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].esta_cocinado = false;
		juego->comida[3].ingrediente[juego->comida[3].tope_ingredientes].esta_cortado = false;
		if(i == 0){
			while(cantidad_milanesa < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(11, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[3].ingrediente, juego->comida[3].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[3].ingrediente, &(juego)->comida[3].tope_ingredientes, posicion_ingrediente, MILANESA);
					cantidad_milanesa++;
				}
			}
		}else if(i == 1){
			while(cantidad_pan < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[3].ingrediente, juego->comida[3].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[3].ingrediente, &(juego)->comida[3].tope_ingredientes, posicion_ingrediente, PAN);
					cantidad_pan++;
				}
			}
		}else if(i == 2){
			while(cantidad_tomate < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[3].ingrediente, juego->comida[3].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[3].ingrediente, &(juego)->comida[3].tope_ingredientes, posicion_ingrediente, TOMATE);
					cantidad_tomate++;
				}
			}
		}else if(i == 3){
			while(cantidad_lechuga < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[3].ingrediente, juego->comida[3].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[3].ingrediente, &(juego)->comida[3].tope_ingredientes, posicion_ingrediente, LECHUGA);
					cantidad_lechuga++;
				}
			}
		}else if(i == 4){
			while(cantidad_jamon < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[3].ingrediente, juego->comida[3].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[3].ingrediente, &(juego)->comida[3].tope_ingredientes, posicion_ingrediente, JAMON);
					cantidad_jamon++;
				}
			}
		}else if(i == 5){
			while(cantidad_queso < 1){
				coordenada_t posicion_ingrediente = generar_coordenada_aleatoria(1, 9, 1, 19);
				if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_ingrediente(juego->comida[3].ingrediente, juego->comida[3].tope_ingredientes, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_jugador(*juego, posicion_ingrediente.fil, posicion_ingrediente.col) && !hay_puerta_salida(juego->salida, posicion_ingrediente.fil, posicion_ingrediente.col)){
					asignar_ingrediente(juego->comida[3].ingrediente, &(juego)->comida[3].tope_ingredientes, posicion_ingrediente, QUESO);
					cantidad_queso++;
				}
			}
		}
	}
}

void inicializar_comida(juego_t* juego){	
	if(juego->comida_actual == ENSALADA){
		juego->comida[0].tipo = ENSALADA;
		(juego->tope_comida)++;
		inicializar_ingredientes_ensalada(juego);
	}else if(juego->comida_actual == PIZZA){
		juego->comida[1].tipo = PIZZA;
		(juego->tope_comida)++;
		inicializar_ingredientes_pizza(juego);
	}else if(juego->comida_actual == HAMBURGUESA){
		juego->comida[2].tipo = HAMBURGUESA;
		(juego->tope_comida)++;
		inicializar_ingredientes_hamburguesa(juego);
	}else if(juego->comida_actual == SANDWICH){
		juego->comida[3].tipo = SANDWICH;
		(juego->tope_comida)++;
		inicializar_ingredientes_sandwich(juego);
	}
}

void inicializar_puerta_salida(juego_t* juego){
	bool es_posicion_valida = false;
	while(!es_posicion_valida){
		coordenada_t posicion_aleatoria = generar_coordenada_aleatoria(11, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_ingrediente(juego->comida[0].ingrediente, juego->comida[0].tope_ingredientes, posicion_aleatoria.fil, posicion_aleatoria.col) && !hay_jugador(*juego, posicion_aleatoria.fil, posicion_aleatoria.col)){
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
		coordenada_t posicion_personaje = generar_coordenada_aleatoria(1, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_personaje.fil, posicion_personaje.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_personaje.fil, posicion_personaje.col) && !hay_ingrediente(juego->comida[0].ingrediente, juego->comida[0].tope_ingredientes, posicion_personaje.fil, posicion_personaje.col)){
			asignar_personaje(&(juego)->stitch, posicion_personaje, STITCH, VACIO);
			cantidad_stitch++;
		}
	}
	while(cantidad_reuben < 1){
		coordenada_t posicion_personaje = generar_coordenada_aleatoria(11, 9, 1, 19);
		if(!hay_obstaculo(juego->obstaculos, juego->tope_obstaculos, posicion_personaje.fil, posicion_personaje.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, posicion_personaje.fil, posicion_personaje.col) && !hay_ingrediente(juego->comida[0].ingrediente, juego->comida[0].tope_ingredientes, posicion_personaje.fil, posicion_personaje.col) && !hay_puerta_salida(juego->salida, posicion_personaje.fil, posicion_personaje.col)){
			asignar_personaje(&(juego)->reuben, posicion_personaje, REUBEN, VACIO);
			cantidad_reuben++;
		}
	}
}

void inicializar_fuego(juego_t* juego, int orden){
	int cantidad_fuego = 0;
	while(cantidad_fuego < 1){
		coordenada_t posicion_fuego = generar_coordenada_aleatoria(1, 19, 1, 19);
		if(hay_vacio(*juego, orden, posicion_fuego.fil, posicion_fuego.col)){
			asignar_obstaculo(juego->obstaculos, &(juego)->tope_obstaculos, posicion_fuego, FUEGO);
			cantidad_fuego++;
		}
	}
}

void inicializar_matafuegos(juego_t* juego, int orden){
	int cantidad_matafuegos = 0;
	while(cantidad_matafuegos < 1){
		coordenada_t posicion_matafuegos = generar_coordenada_aleatoria(1, 19, 1, 19);
		if(hay_vacio(*juego, orden, posicion_matafuegos.fil, posicion_matafuegos.col) && estan_mismo_cuadrante(posicion_matafuegos.fil, juego->obstaculos[(juego->tope_obstaculos)-1].posicion.fil)){
			asignar_herramienta(juego->herramientas, &(juego)->tope_herramientas, posicion_matafuegos, MATAFUEGOS);
			cantidad_matafuegos++;
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
		grilla[juego.paredes[i].fil][juego.paredes[i].col] = PARED;
	}

	grilla[juego.mesa.fil][juego.mesa.col] = MESA;

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