#include <stdio.h>
#include "chambuchito.h"

//Tipos de pan:
#define BLANCO 'B'
#define INTEGRAL 'I'
#define AVENA_MIEL 'A'

//Tipos de queso:
#define QUESO_OREGANO 'Q'
#define DAMBO 'D'
#define CHEDDAR 'C'
#define GRUYERE 'G'
#define SIN_QUESO 'S'

//Tipos de proteina
#define ROAST 'R'
#define ATUN 'A'
#define POLLO 'P'
#define SOJA 'S'
#define NADA_PROTE 'N'

//Auxiliares
#define AUXILIAR_1 'X'
#define AUXILIAR_2 'Y'

//Precios
const float PRECIO_BASICO = 5, PRECIO_ESPECIAL = 8, PRECIO_ROAST = 7, PRECIO_ATUN = 9, PRECIO_POLLO = 5, PRECIO_SOJA = 3, MINIMO = 15, MAXIMO = 30, CONSTANTE = (float) 0.3, SI = 'S', NO = 'N';

/*
Pre: -----------------------------
Pos: Carga la variable medida con valores válidos (números comprendidos entre 15 y 30 inclusives).
*/
void preguntar_medida_sandwich(float* medida){
    while(*medida < MINIMO || *medida > MAXIMO){
        printf("¿De que medida desea su chambuchito? Ingrese un número entre el 15 y el 30 (inclusives):\n");
        scanf("%f", medida);
    }
}

/*
Pre: -------------------------------
Pos: Carga la variable pan con valores válidos como 'B', 'I', 'A', 'Q'.
*/
void preguntar_tipo_pan(char* pan){
    while(*pan != BLANCO && *pan != INTEGRAL && *pan != AVENA_MIEL && *pan != QUESO_OREGANO){
        printf("¿Qué pan desea en su chambuchito? Las opciones son Pan Blaco [B], Pan Integral[I], Avena y Miel[A], Queso y Orégano[Q]:\n");
        scanf(" %c", pan);
    }
} 

/*
Pre: -------------------------------------------
Pos: Carga la variable queso con valores válidos como 'D', 'C', 'G', 'S'.
*/
void preguntar_tipo_queso(char* queso){
    while(*queso != DAMBO && *queso != CHEDDAR && *queso != GRUYERE && *queso != SIN_QUESO){
        printf("¿Qué queso querés en tu chambuchito? Las opciones son Dambo[D], Cheddar[C], Gruyere[G], Sin Queso[S]:\n");
        scanf(" %c", queso);
    }
}

/*
Pre: ------------------------------------------------
Pos:Carga la variable proteina con valores válidos como 'R', 'A', 'S', 'P', 'N'.
*/
void preguntar_tipo_proteina(char* proteina){
    while(*proteina != ROAST && *proteina != ATUN && *proteina != SOJA && *proteina != POLLO && *proteina != NADA_PROTE){
        printf("¿Qué proteina querés en tu chambuchito? Las opciones son Roast Beef[R], Atún[A], Soja[S], Pollito[P], Nada de Proteina[N]:\n");
        scanf(" %c", proteina);
    }
}

/*
Pre: ---------------------------------------------------
Pos: Carga la variable calentar con valores válidos como 'S' o 'N'.
*/
void preguntar_si_calienta_comida(char* calentar){
    while(*calentar != SI && *calentar != NO){
        printf("¿Deseás tu chambuchito caliente? Las opciones son Si[S] o No[N]:\n");
        scanf(" %c", calentar);
    }
}

/*
Pre: ----------------------------------------------
Pos: Carga la variable precio con valores válidos dependiendo del producto. Si precio tiene un valor anterior, se le suma el valor actual.
*/
void sumar_al_precio(char producto, float* precio_producto){
    switch(producto){
        case BLANCO:
        case INTEGRAL:
        case DAMBO:
        case CHEDDAR:
            *precio_producto += PRECIO_BASICO;
            break;
        case AVENA_MIEL:
        case QUESO_OREGANO:
        case GRUYERE:
            *precio_producto += PRECIO_ESPECIAL;
            break;
        case ROAST:
            *precio_producto += PRECIO_ROAST;
            break;
        case AUXILIAR_2:
            *precio_producto += PRECIO_ATUN;
            break;
        case POLLO:
            *precio_producto += PRECIO_POLLO;
            break;
        case SOJA:
            *precio_producto += PRECIO_SOJA;
            break;
    }
}

/*
Pre: ----------------------------------------------
Pos: Cambia el valor del producto (con opciones que elige el usuario) por alguna constante auxiliar (que no se repita en el switch)
*/
void redefinir_valor_de_producto(char* producto, char letra){
    *producto = letra;
}

/*
Pre: Debe recibir las variables con valores válidos (medida toma valores entre 15 y 30 inclusives).
Post: Devuelve el precio total del sandwich como dato de tipo entero
*/
int calcular_total(float precio, float medida){
    return (int)(precio * medida * CONSTANTE);
}

void calcular_precio_chambuchito (int* precio){
    float medida = 0, precio_auxiliar = 0;
    char pan = ' ', queso = ' ', proteina = ' ', calentar = ' ';

    preguntar_medida_sandwich(&medida);

    preguntar_tipo_pan(&pan);
    sumar_al_precio(pan, &precio_auxiliar);

    preguntar_tipo_queso(&queso);
    if(queso == SIN_QUESO){
        redefinir_valor_de_producto(&queso, AUXILIAR_1);
    }
    sumar_al_precio(queso, &precio_auxiliar);

    preguntar_tipo_proteina(&proteina);
    if(proteina == ATUN){
        redefinir_valor_de_producto(&proteina, AUXILIAR_2);
    }
    sumar_al_precio(proteina, &precio_auxiliar);
    if(proteina != AUXILIAR_2){
        preguntar_si_calienta_comida(&calentar);
    }

    *precio = calcular_total(precio_auxiliar, medida);
    printf("El precio total es: -%i-\n", *precio);
}