#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cocineritos.h"
#include "chambuchito.h"

void imprimir_struct(juego_t juego){
    printf("Tu tope de paredes es de: %i\n", juego.tope_paredes);
    printf("Tu tope de obstaculos es de: %i\n", juego.tope_obstaculos);
    //for(int i = 0; i < juego.tope_obstaculos; i++){
    //    printf("tienes obstaculos en: (%i, %i)\n", juego.obstaculos[i].posicion.fil, juego.obstaculos[i].posicion.col);
    //}
    printf("Tu tope de herramientas es de: %i\n", juego.tope_herramientas);
    //for(int i = 0; i < juego.tope_herramientas; i++){
    //    printf("tienes herramientas en: (%i, %i) y es de tipo %c\n", juego.herramientas[i].posicion.fil, juego.herramientas[i].posicion.col, juego.herramientas[i].tipo);
    //}
    //for(int i = 0; i < juego.tope_comida; i++){
    //    printf("Las comidas presentes en el struct son: %c\n", juego.comida[i].tipo);
    //}
    printf("El tope del struct de comida es de: %i\n", juego.tope_comida);

    printf("Tu tope de ingredientes en la ensalada es de: %i\n", juego.comida[0].tope_ingredientes);
    //for(int i = 0; i < juego.comida[0].tope_ingredientes; i++){
    //    printf("Tienes ingredientes del tipo %c en (%i, %i)\n", juego.comida[0].ingrediente[i].tipo, juego.comida[0].ingrediente[i].posicion.fil, juego.comida[0].ingrediente[i].posicion.col);
    //}

    //printf("Tu tope de ingredientes en la pizza es de: %i\n", juego.comida[1].tope_ingredientes);
    //for(int i = 0; i < juego.comida[1].tope_ingredientes; i++){
    //    printf("Tienes ingredientes del tipo %c en (%i, %i)\n", juego.comida[1].ingrediente[i].tipo, juego.comida[1].ingrediente[i].posicion.fil, juego.comida[1].ingrediente[i].posicion.col);
    //}

    //printf("Tu tope de ingredientes en la hamburguesa es de: %i\n", juego.comida[2].tope_ingredientes);
    //for(int i = 0; i < juego.comida[2].tope_ingredientes; i++){
    //    printf("Tienes ingredientes del tipo %c en (%i, %i)\n", juego.comida[2].ingrediente[i].tipo, juego.comida[2].ingrediente[i].posicion.fil, juego.comida[2].ingrediente[i].posicion.col);
    //}

    //printf("Tu tope de ingredientes en el sandwich es de: %i\n", juego.comida[3].tope_ingredientes);
    //for(int i = 0; i < juego.comida[3].tope_ingredientes; i++){
    //    printf("Tienes ingredientes del tipo %c en (%i, %i)\n", juego.comida[3].ingrediente[i].tipo, juego.comida[3].ingrediente[i].posicion.fil, juego.comida[3].ingrediente[i].posicion.col);
    //}

    printf("Stitch esta en (%i, %i)\n", juego.stitch.posicion.fil, juego.stitch.posicion.col);
    printf("Reuben esta en (%i, %i)\n", juego.reuben.posicion.fil, juego.reuben.posicion.col);
}

int main(){
    srand (( unsigned)time(NULL));

    int precio = 0;
    juego_t juego;
    //calcular_precio_chambuchito(&precio);
    inicializar_juego(&juego, precio);
    imprimir_terreno(juego);
    imprimir_struct(juego);
    return 0;
}