#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "cocineritos.h"
#include "validaciones.h"
#include "inicializar_juego.h"
#include "funciones_varias.h"

void inicializar_juego(juego_t* juego, int precio){
	inicializar_precio_total(juego, precio);
	inicializar_paredes(juego);
	inicializar_mesa(juego);
	inicializar_agujeros(juego);
	inicializar_herramientas(juego);
	juego->tope_comida = 0;
	juego->comida_actual = ENSALADA;
	inicializar_comida(juego);
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
			coordenada_t posicion_nueva_jugador = generar_posicion_nueva(juego->stitch, movimiento);
			if(es_movimiento_valido(*juego, posicion_nueva_jugador.fil, posicion_nueva_jugador.col)){
				mover_jugador(&(juego)->stitch, movimiento);
				if(juego->tope_obstaculos < 21){
					juego->movimientos++;
				}
			}
		}else if(juego->personaje_activo == REUBEN){
			coordenada_t posicion_nueva_jugador = generar_posicion_nueva(juego->reuben, movimiento);
			if(es_movimiento_valido(*juego, posicion_nueva_jugador.fil, posicion_nueva_jugador.col)){
				mover_jugador(&(juego)->reuben, movimiento);
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
			if(juego->stitch.objeto_en_mano == VACIO && !hay_fuego_cuadrante_stitch(juego->obstaculos, juego->tope_obstaculos) && hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil, juego->stitch.posicion.col)){

				juego->stitch.objeto_en_mano = buscar_tipo_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil, juego->stitch.posicion.col);
				ocultar_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);

			}else if((juego->stitch.objeto_en_mano != VACIO && juego->stitch.objeto_en_mano != MATAFUEGOS)  && !hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes,juego->stitch.posicion.fil, juego->stitch.posicion.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, juego->stitch.posicion.fil, juego->stitch.posicion.col)){

				cambiar_posicion_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil, juego->stitch.posicion.col);
				juego->stitch.objeto_en_mano = VACIO;
			}
			
		}else if(juego->personaje_activo == REUBEN){
			if(juego->reuben.objeto_en_mano == VACIO && !hay_fuego_cuadrante_reuben(juego->obstaculos, juego->tope_obstaculos) && hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes,juego->reuben.posicion.fil, juego->reuben.posicion.col)){

				juego->reuben.objeto_en_mano = buscar_tipo_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes,juego->reuben.posicion.fil, juego->reuben.posicion.col);
				ocultar_ingrediente(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);

			}else if((juego->reuben.objeto_en_mano != VACIO && juego->reuben.objeto_en_mano != MATAFUEGOS) && !hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->reuben.posicion.fil, juego->reuben.posicion.col) && !hay_herramienta(juego->herramientas, juego->tope_herramientas, juego->reuben.posicion.fil, juego->reuben.posicion.col)){

				cambiar_posicion_ingrediente(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->reuben.posicion.fil, juego->reuben.posicion.col);
				juego->reuben.objeto_en_mano = VACIO;
			}
		}
	}
		
	if(movimiento == ACTIVAR_CUCHILLO && juego->personaje_activo == STITCH && !hay_fuego_cuadrante_stitch(juego->obstaculos, juego->tope_obstaculos) && hay_herramienta(juego->herramientas, juego->tope_herramientas, juego->stitch.posicion.fil, juego->stitch.posicion.col)){
		cortar_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
	}

	if(movimiento == PASAR){
		if(juego->personaje_activo == STITCH){
			if(juego->stitch.objeto_en_mano != VACIO && esta_cortado(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes) && !hay_fuego_cuadrante_stitch(juego->obstaculos, juego->tope_obstaculos) && !hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil + 1, juego->stitch.posicion.col) && distancia_manhattan(juego->stitch.posicion, juego->mesa, 1)){
				cambiar_posicion_ingrediente(juego->stitch.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->stitch.posicion.fil + 1, juego->stitch.posicion.col);
				juego->stitch.objeto_en_mano = VACIO;
			}
		}else if(juego->personaje_activo == REUBEN){
			if(juego->reuben.objeto_en_mano == VACIO && hay_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes,juego->reuben.posicion.fil - 1, juego->reuben.posicion.col) && !hay_fuego_cuadrante_reuben(juego->obstaculos, juego->tope_obstaculos) && distancia_manhattan(juego->reuben.posicion, juego->mesa, 1)){
				juego->reuben.objeto_en_mano = buscar_tipo_ingrediente(juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->reuben.posicion.fil - 1, juego->reuben.posicion.col);
				ocultar_ingrediente(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
			}
		}
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

	if(movimiento == ACTIVAR_HORNO && juego->personaje_activo == REUBEN && juego->reuben.objeto_en_mano != VACIO && !esta_cortado(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes) && !hay_fuego_cuadrante_reuben(juego->obstaculos, juego->tope_obstaculos) && (distancia_manhattan(juego->reuben.posicion, juego->herramientas[2].posicion, 1) || distancia_manhattan(juego->reuben.posicion, juego->herramientas[3].posicion, 1))){
			cocinar_ingrediente(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes);
	}

	
	if(juego->movimientos == 15){
		inicializar_fuego(juego, orden);
		inicializar_matafuegos(juego, orden);
		juego->movimientos = 16;
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

	if(hay_puerta_salida(juego->salida, juego->reuben.posicion.fil, juego->reuben.posicion.col) && !hay_fuego_cuadrante_reuben(juego->obstaculos, juego->tope_obstaculos) && (esta_cortado(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes) || esta_cocinado(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes))){
		cargar_vector(juego, orden);
		cambiar_posicion_ingrediente(juego->reuben.objeto_en_mano, juego->comida[orden].ingrediente, juego->comida[orden].tope_ingredientes, juego->reuben.posicion.fil, juego->reuben.posicion.col);
		juego->reuben.objeto_en_mano = VACIO;
	}
}

int estado_juego(juego_t juego){
	int estado = 0;
	if(hay_obstaculo(juego.obstaculos, juego.tope_obstaculos, juego.stitch.posicion.fil, juego.stitch.posicion.col) || hay_obstaculo(juego.obstaculos, juego.tope_obstaculos, juego.reuben.posicion.fil, juego.reuben.posicion.col)){
		estado = -1;
	}else if((juego.precio_total <= 100 && juego.tope_comida_lista == 3) || ((juego.precio_total > 100 && juego.precio_total <= 150) && juego.tope_comida_lista == 4) || (juego.precio_total > 150 && juego.tope_comida_lista == 6)){
		estado = 1;
	}
	return estado;
}