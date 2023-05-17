#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "cocineritos.h"
#include "validaciones.h"
#include "inicializar_juego.h"
#include "funciones_varias.h"


void generar_desplazamiento(juego_t juego, personaje_t* personaje, char movimiento){
	coordenada_t posicion_nueva_jugador = generar_posicion_nueva(*personaje, movimiento);
	if(es_movimiento_valido(juego, posicion_nueva_jugador.fil, posicion_nueva_jugador.col)){
		mover_jugador(personaje, movimiento);
	}
}

/*
juego->stitch.objeto_en_mano = buscar_tipo_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil, juego->stitch.posicion.col);
ocultar_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
*/
void agarrar_ingrediente(personaje_t* personaje, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes){
	personaje->objeto_en_mano = buscar_tipo_ingrediente(ingrediente, tope_ingredientes, personaje->posicion.fil, personaje->posicion.col);
	ocultar_ingrediente(personaje->objeto_en_mano, ingrediente, tope_ingredientes);
}

/*

cambiar_posicion_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil, juego->stitch.posicion.col);
juego->stitch.objeto_en_mano = VACIO;
*/
void soltar_ingrediente(personaje_t* personaje, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes){
	cambiar_posicion_ingrediente(personaje->objeto_en_mano, ingrediente, tope_ingredientes, personaje->posicion.fil, personaje->posicion.col);
	personaje->objeto_en_mano = VACIO;
}

/*
cambiar_posicion_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil + 1, juego->stitch.posicion.col);
juego->stitch.objeto_en_mano = VACIO;
*/
void pasar_ingrediente(personaje_t* personaje, int direccion, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes){
	cambiar_posicion_ingrediente(personaje->objeto_en_mano, ingrediente, tope_ingredientes, personaje->posicion.fil + direccion, personaje->posicion.col);
	personaje->objeto_en_mano = VACIO;
}

/*
juego->stitch.objeto_en_mano = buscar_tipo_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil + 1, juego->stitch.posicion.col);
ocultar_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
*/
void recibir_ingrediente(personaje_t* personaje, int direccion, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes){
	personaje->objeto_en_mano = buscar_tipo_ingrediente(ingrediente, tope_ingredientes, personaje->posicion.fil + direccion, personaje->posicion.col);
	ocultar_ingrediente(personaje->objeto_en_mano, ingrediente, tope_ingredientes);
}

/*juego->tope_obstaculos--;
			juego->tope_herramientas--;
			juego->stitch.objeto_en_mano = VACIO;
			juego->movimientos = 0;*/
void utilizar_matafuegos(personaje_t* personaje, objeto_t obstaculos[MAX_OBSTACULOS], int* tope_obstaculos, objeto_t herramientas[MAX_HERRAMIENTAS], int* tope_herramientas){
	(*tope_obstaculos)--;
	(*tope_herramientas)--;
	personaje->objeto_en_mano = VACIO;
}

void inicializar_juego(juego_t* juego, int precio){
	inicializar_precio_total(juego, precio);
	inicializar_paredes(juego);
	inicializar_mesa(juego);
	inicializar_agujeros(juego);
	inicializar_herramientas(juego);
	juego->tope_comida = 0;
	juego->comida_actual = ENSALADA;
	juego->comida[ORDEN_ENSALADA].tipo = ENSALADA;
	(juego->tope_comida)++;
	inicializar_ingredientes_ensalada(juego);
	//inicializar_comida(juego);
	inicializar_puerta_salida(juego);
	inicializar_personajes(juego);
	juego->movimientos = 0; 
	juego->tope_comida_lista = 0;
}

void imprimir_terreno(juego_t juego){
	char grilla[MAX_FIL][MAX_COL];
	inicializar_grilla_vacia(grilla);
	llenar_grilla(juego, grilla);
	dibujar_grilla(grilla);
}

void realizar_jugada(juego_t* juego, char movimiento){
	int orden = orden_actual(juego->comida_actual);

	if(movimiento == ARRIBA || movimiento == ABAJO || movimiento == DERECHA || movimiento == IZQUIERDA){
		if(juego->personaje_activo == STITCH){
			/*
			coordenada_t posicion_nueva_jugador = generar_posicion_nueva(juego->stitch, movimiento);
			if(es_movimiento_valido(*juego, posicion_nueva_jugador.fil, posicion_nueva_jugador.col)){
				mover_jugador(&(juego)->stitch, movimiento);
			}
			*/
		    generar_desplazamiento(*juego, &(juego)->stitch, movimiento);
		}else if(juego->personaje_activo == REUBEN){
			/*
			coordenada_t posicion_nueva_jugador = generar_posicion_nueva(juego->reuben, movimiento);
			if(es_movimiento_valido(*juego, posicion_nueva_jugador.fil, posicion_nueva_jugador.col)){
				mover_jugador(&(juego)->reuben, movimiento);
			}
			*/
			generar_desplazamiento(*juego, &(juego)->reuben, movimiento);

		}
		if(!hay_fuego_cuadrante_stitch(juego->obstaculos, juego->tope_obstaculos) && !hay_fuego_cuadrante_reuben(juego->obstaculos, juego->tope_obstaculos)){
			(juego->movimientos)++;
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
			if(juego->stitch.objeto_en_mano == VACIO && !hay_fuego_cuadrante_stitch(juego->obstaculos, juego->tope_obstaculos) && hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil, juego->stitch.posicion.col)){
				/*
				juego->stitch.objeto_en_mano = buscar_tipo_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil, juego->stitch.posicion.col);
				ocultar_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
				*/
				agarrar_ingrediente(&(juego)->stitch, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);

			}else if((juego->stitch.objeto_en_mano != VACIO && juego->stitch.objeto_en_mano != MATAFUEGOS)  && !hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes,juego->stitch.posicion.fil, juego->stitch.posicion.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, juego->stitch.posicion.fil, juego->stitch.posicion.col)){
				/*
				cambiar_posicion_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil, juego->stitch.posicion.col);
				juego->stitch.objeto_en_mano = VACIO;
				*/
				soltar_ingrediente(&(juego)->stitch, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
			}
			
		}else if(juego->personaje_activo == REUBEN){
			if(juego->reuben.objeto_en_mano == VACIO && !hay_fuego_cuadrante_reuben(juego->obstaculos, juego->tope_obstaculos) && hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes,juego->reuben.posicion.fil, juego->reuben.posicion.col)){
				/*
				
				juego->reuben.objeto_en_mano = buscar_tipo_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes,juego->reuben.posicion.fil, juego->reuben.posicion.col);
				ocultar_ingrediente(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
				*/
				agarrar_ingrediente(&(juego)->reuben, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);

			}else if((juego->reuben.objeto_en_mano != VACIO && juego->reuben.objeto_en_mano != MATAFUEGOS) && !hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->reuben.posicion.fil, juego->reuben.posicion.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, juego->reuben.posicion.fil, juego->reuben.posicion.col)){
				/*
				cambiar_posicion_ingrediente(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->reuben.posicion.fil, juego->reuben.posicion.col);
				juego->reuben.objeto_en_mano = VACIO;
				*/
				soltar_ingrediente(&(juego)->reuben, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
			}
		}
	}
		
	if(movimiento == ACTIVAR_CUCHILLO && juego->personaje_activo == STITCH && juego->stitch.objeto_en_mano != VACIO && !hay_fuego_cuadrante_stitch(juego->obstaculos, juego->tope_obstaculos) && hay_herramienta(juego->herramientas, juego->tope_herramientas, juego->stitch.posicion.fil, juego->stitch.posicion.col)){
		cortar_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
	}

	if(movimiento == PASAR){
		if(juego->personaje_activo == STITCH && distancia_manhattan(juego->stitch.posicion, juego->mesa, 1) && !hay_fuego_cuadrante_stitch(juego->obstaculos, juego->tope_obstaculos)){
			if(juego->stitch.objeto_en_mano != VACIO && !hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil + 1, juego->stitch.posicion.col)){
				/*
				cambiar_posicion_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil + 1, juego->stitch.posicion.col);
				juego->stitch.objeto_en_mano = VACIO;
				*/
				pasar_ingrediente(&(juego)->stitch, 1, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
			}else if(juego->stitch.objeto_en_mano == VACIO && hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil + 1, juego->stitch.posicion.col)){
				/*
				juego->stitch.objeto_en_mano = buscar_tipo_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil + 1, juego->stitch.posicion.col);
				ocultar_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
				*/
				recibir_ingrediente(&(juego)->stitch, 1, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
			}
		}else if(juego->personaje_activo == REUBEN  && distancia_manhattan(juego->reuben.posicion, juego->mesa, 1) && !hay_fuego_cuadrante_reuben(juego->obstaculos, juego->tope_obstaculos)){
			if(juego->reuben.objeto_en_mano != VACIO && !hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->reuben.posicion.fil - 1, juego->reuben.posicion.col) ){
				/*
				cambiar_posicion_ingrediente(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->reuben.posicion.fil - 1, juego->reuben.posicion.col);
				juego->reuben.objeto_en_mano = VACIO;
				*/
				pasar_ingrediente(&(juego)->reuben, -1, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);

			}else if(juego->reuben.objeto_en_mano == VACIO && hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes,juego->reuben.posicion.fil - 1, juego->reuben.posicion.col)){
				/*
				juego->reuben.objeto_en_mano = buscar_tipo_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->reuben.posicion.fil - 1, juego->reuben.posicion.col);
				ocultar_ingrediente(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
				*/
				recibir_ingrediente(&(juego)->reuben, -1, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
			}
		}
	}

	if(movimiento == ACTIVAR_MATAFUEGO){
		if(juego->personaje_activo == STITCH && juego->stitch.objeto_en_mano == MATAFUEGOS && distancia_manhattan(juego->stitch.posicion, juego->obstaculos[(juego->tope_obstaculos) - 1].posicion, 2)){
			/*
			juego->tope_obstaculos--;
			juego->tope_herramientas--;
			juego->stitch.objeto_en_mano = VACIO;
			*/
			utilizar_matafuegos(&(juego)->stitch, juego->obstaculos, &(juego)->tope_obstaculos, juego->herramientas, &(juego)->tope_herramientas);
			juego->movimientos = 0;
		}else if(juego->personaje_activo == REUBEN && juego->reuben.objeto_en_mano == MATAFUEGOS && distancia_manhattan(juego->reuben.posicion, juego->obstaculos[(juego->tope_obstaculos) - 1].posicion, 2)){
			/*
			juego->tope_obstaculos--;
			juego->tope_herramientas--;
			juego->reuben.objeto_en_mano = VACIO;
			*/
			utilizar_matafuegos(&(juego)->reuben, juego->obstaculos, &(juego)->tope_obstaculos, juego->herramientas, &(juego)->tope_herramientas);
			juego->movimientos = 0;
		}
	}

	if(movimiento == ACTIVAR_HORNO && juego->personaje_activo == REUBEN && juego->reuben.objeto_en_mano != VACIO && !hay_fuego_cuadrante_reuben(juego->obstaculos, juego->tope_obstaculos) && distancia_manhattan_horno(juego->reuben.posicion, juego->herramientas, juego->tope_herramientas)){
		cocinar_ingrediente(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
	}

	if(juego->movimientos == MOVIMIENTOS_MAX){
		inicializar_fuego(juego, orden);
		inicializar_matafuegos(juego, orden);
		juego->movimientos = MOVIMIENTOS_MAX + 1;
	}
	
	if(juego->personaje_activo == STITCH){
		if(juego->stitch.objeto_en_mano == VACIO && hay_matafuegos(juego->herramientas, juego->tope_herramientas, juego->stitch.posicion.fil, juego->stitch.posicion.col)){
			juego->stitch.objeto_en_mano = buscar_tipo_herramienta(juego->herramientas, juego->tope_herramientas, juego->stitch.posicion.fil, juego->stitch.posicion.col);
			ocultar_herramienta(juego->stitch.objeto_en_mano, juego->herramientas, juego->tope_herramientas);
		}
	}else if(juego->personaje_activo == REUBEN){
		if(juego->reuben.objeto_en_mano == VACIO && hay_matafuegos(juego->herramientas, juego->tope_herramientas, juego->reuben.posicion.fil, juego->reuben.posicion.col)){
			juego->reuben.objeto_en_mano = buscar_tipo_herramienta(juego->herramientas, juego->tope_herramientas, juego->reuben.posicion.fil, juego->reuben.posicion.col);
			ocultar_herramienta(juego->reuben.objeto_en_mano, juego->herramientas, juego->tope_herramientas);
		}
	}

	if(hay_puerta_salida(juego->salida, juego->reuben.posicion.fil, juego->reuben.posicion.col) && (esta_cortado(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes) || esta_cocinado(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes))){
		cargar_vector(juego, orden);
		cambiar_posicion_ingrediente(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->reuben.posicion.fil, juego->reuben.posicion.col);
		juego->reuben.objeto_en_mano = VACIO;
	}

	cambiar_nivel(juego);
}

int estado_juego(juego_t juego){
	int estado = 0;
	if(hay_obstaculo(juego.obstaculos, juego.tope_obstaculos, juego.stitch.posicion.fil, juego.stitch.posicion.col) || hay_obstaculo(juego.obstaculos, juego.tope_obstaculos, juego.reuben.posicion.fil, juego.reuben.posicion.col)){
		estado = -1;
	}else if((juego.precio_total <= 100 && juego.comida_actual == HAMBURGUESA && juego.tope_comida_lista == 0) || ((juego.precio_total > 100 && juego.precio_total <= 150) && juego.comida_actual == SANDWICH && juego.tope_comida_lista == 0) || (juego.precio_total > 150 && juego.comida_actual == SANDWICH && juego.tope_comida_lista == 6)){
		estado = 1;
	}
	return estado;
}