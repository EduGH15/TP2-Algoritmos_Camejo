#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cocineritos.h"
#include "chambuchito.h"
#include "funciones_varias.h"
#include "interaccion.h"

int main(){
    srand (( unsigned)time(NULL));

    int precio = SIN_PRECIO;
    char movimiento = ESPACIO_BLANCO;
    juego_t juego;
    ejecutar_introduccion();
    calcular_precio_chambuchito(&precio);
    inicializar_juego(&juego, precio);
    
    while(estado_juego(juego) == EN_JUEGO){
        system("clear");
        imprimir_terreno(juego);
        printf("Ingrese una jugada:\n");
        scanf(" %c", &movimiento);
        realizar_jugada(&juego, movimiento);
    }
    
    imprimir_resultado(juego);
    
    return 0;
}