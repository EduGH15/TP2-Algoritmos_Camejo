#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cocineritos.h"
#include "chambuchito.h"

int main(){
    srand (( unsigned)time(NULL));

    int precio = 0;
    juego_t juego;
    //calcular_precio_chambuchito(&precio);
    inicializar_juego(&juego, precio);
    imprimir_terreno(juego);
    return 0;
}