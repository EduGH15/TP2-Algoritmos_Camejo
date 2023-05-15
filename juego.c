#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cocineritos.h"
#include "chambuchito.h"
#include "funciones_varias.h"
#include "interaccion.h"


void imprimir_struct(juego_t juego){
    //printf("Tu tope de paredes es de: %i\n", juego.tope_paredes);

    printf("Tu tope de obstaculos es de: %i\n", juego.tope_obstaculos);
    //for(int i = 0; i < juego.tope_obstaculos; i++){
    //   printf("tienes obstaculos en: ( %i , %i ) y es de tipo %c\n", juego.obstaculos[i].posicion.fil, juego.obstaculos[i].posicion.col, juego.obstaculos[i].tipo);
    //}
    
    printf("Tu tope de herramientas es de: %i\n", juego.tope_herramientas);
    //for(int i = 0; i < juego.tope_herramientas; i++){
    //   printf("tienes herramientas en: (%i, %i) y es de tipo %c\n", juego.herramientas[i].posicion.fil, juego.herramientas[i].posicion.col, juego.herramientas[i].tipo);
    //}

    //printf("la comida actual es: %c\n", juego.comida_actual);
    printf("El tope del struct de comida es de: %i\n", juego.tope_comida);
    //for(int i = 0; i < juego.tope_comida; i++){
    //    printf("Las comidas presentes en el struct son: %c\n", juego.comida[i].tipo);
    //}
    

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

    //printf("esta activo el personaje: %c\n", juego.personaje_activo);
    printf("Stitch esta en (%i, %i)\n", juego.stitch.posicion.fil, juego.stitch.posicion.col);
    //printf("STITCH tiene en la mano: %c\n", juego.stitch.objeto_en_mano);

    
    //printf("Hiciste hasta ahora %i movimientos\n", juego.movimientos);

    //for(int i = 0; i < juego.tope_obstaculos; i++){
    //    if(juego.obstaculos[i].tipo == 'F'){
    //        printf("ALERTAAAAAAAAAAAAA TIENES UN FUEGO EN (%i, %i)\n", juego.obstaculos[i].posicion.fil, juego.obstaculos[i].posicion.col);
    //    }
    //}

    //  printf("Tienes un matafuego en (%i, %i)\n", juego.herramientas[20].posicion.fil, juego.herramientas[20].posicion.col);

    //printf("El ingrediente %c que tiene en mano está cortado %s \n", juego.comida[0].ingrediente[0].tipo ,juego.comida[0].ingrediente[0].esta_cortado ? "true" : "false");
    //printf("El ingrediente %c que tiene en mano está cocinado %s \n",juego.comida[0].ingrediente[0].tipo  ,juego.comida[0].ingrediente[0].esta_cocinado ? "true" : "false");

    //printf("El ingrediente %c que tiene en mano está cortado %s \n",juego.comida[0].ingrediente[1].tipo, juego.comida[0].ingrediente[1].esta_cortado ? "true" : "false");
    //printf("El ingrediente %c que tiene en mano está cocinado %s \n",juego.comida[0].ingrediente[1].tipo  ,juego.comida[0].ingrediente[1].esta_cocinado ? "true" : "false");


    //printf("La puerta de salida esta en (%i, %i)\n", juego.salida.fil, juego.salida.col);

    //printf("Reuben esta en (%i, %i)\n", juego.reuben.posicion.fil, juego.reuben.posicion.col);
    printf("REUBEN tiene en la mano %c\n", juego.reuben.objeto_en_mano);

    //printf("El tope de comida lista es %i\n", juego.tope_comida_lista);
    //for(int i = 0; i < juego.tope_comida_lista; i++){
    //    printf("Tienes ingredientes del tipo %c en (%i, %i)\n", juego.comida_lista[i].tipo, juego.comida_lista[i].posicion.fil, juego.comida_lista[i].posicion.col);
    //    printf("El ingrediente %c está cortado: %s\n", juego.comida_lista[i].tipo ,juego.comida_lista[i].esta_cortado ? "true" : "false");
    //    printf("El ingrediente %c está cocinado: %s\n", juego.comida_lista[i].tipo, juego.comida_lista[i].esta_cocinado ? "true" : "false");
    //}
}

int main(){
    srand (( unsigned)time(NULL));

    int precio = 0;
    char movimiento = ' ';
    juego_t juego;
    //ejecutar_introduccion();
    //calcular_precio_chambuchito(&precio);
    inicializar_juego(&juego, precio);
    
    while(estado_juego(juego) == 0){
        system("clear");
        cambiar_nivel(&juego);
        imprimir_terreno(juego);
        //imprimir_struct(juego);
        //interaccion(juego, movimiento);       
        preguntar_jugada(&movimiento);
        realizar_jugada(&juego, movimiento);
    }
    
    
    return 0;
}