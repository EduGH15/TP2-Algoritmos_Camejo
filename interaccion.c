#include "interaccion.h"

void imprimir_introduccion_1(){
    printf("_______________________________________________________________________________________________________________________________________________________________\n");
    printf("'#######::'##::::'##:'########:'########::::::'######::'##::::'##::::'###::::'##::::'##:'########::'##::::'##::'######::'##::::'##:'####:'########::'#######::\n");
    printf("'##.... ##: ##:::: ##: ##.....:: ##.... ##::::'##... ##: ##:::: ##:::'## ##::: ###::'###: ##.... ##: ##:::: ##:'##... ##: ##:::: ##:. ##::... ##..::'##.... ##:\n");
    printf(" ##:::: ##: ##:::: ##: ##::::::: ##:::: ##:::: ##:::..:: ##:::: ##::'##:. ##:: ####'####: ##:::: ##: ##:::: ##: ##:::..:: ##:::: ##:: ##::::: ##:::: ##:::: ##:\n");
    printf(" ##:::: ##: ##:::: ##: ######::: ########::::: ##::::::: #########:'##:::. ##: ## ### ##: ########:: ##:::: ##: ##::::::: #########:: ##::::: ##:::: ##:::: ##:\n");
    printf(" ##:::: ##:. ##:: ##:: ##...:::: ##.. ##:::::: ##::::::: ##.... ##: #########: ##. #: ##: ##.... ##: ##:::: ##: ##::::::: ##.... ##:: ##::::: ##:::: ##:::: ##:\n");
    printf(" ##:::: ##::. ## ##::: ##::::::: ##::. ##::::: ##::: ##: ##:::: ##: ##.... ##: ##:.:: ##: ##:::: ##: ##:::: ##: ##::: ##: ##:::: ##:: ##::::: ##:::: ##:::: ##:\n");
    printf(". #######::::. ###:::: ########: ##:::. ##::::. ######:: ##:::: ##: ##:::: ##: ##:::: ##: ########::. #######::. ######:: ##:::: ##:'####:::: ##::::. #######::\n");
    printf(":.......::::::...:::::........::..:::::..::::::......:::..:::::..::..:::::..::..:::::..::........::::.......::::......:::..:::::..::....:::::..::::::.......:::\n");
    printf("________________________________________________________________________________________________________________________________________________________________ \n");
    printf("\n         _________________________________________________________________________________________________________________________________________\n");
    printf("         |                                                                                                                                        |\n");
    printf("         |   El juego consiste en una cocina dividida en dos cuadrantes horizontales, donde en la mitad superior estará Stitch                    |\n");
    printf("         |   que se encargara de cortar ingredientes y de lavar los platos, y del lado inferior estará Reuben cocinando y emplatando.             |\n");
	printf("         |   Para pasar los ingredientes de un lado a otro, en la franja horizontal divisoria, habrá una mesa para apoyar.                        |\n");
	printf("         |                                                                                                                                        |\n");
	printf("         |   La cocina tendrá distintas estaciones con las herramientas a utilizar para llevar a cabo el pedido.                                  |\n");
    printf("         |                                                                                                                                        |\n");
	printf("         |   Se iniciará el juego siendo Stitch, y el pedido se considerará completo una vez que todos los ingredientes se                        |\n");
	printf("         |   posicionen en la puerta de salida, cortados y cocinados.                                                                             |\n");
	printf("         |   Stitch deberá recolectar uno por uno los ingredientes de su cuadrante, cortarlos cuando sea necesario y luego                        |\n");
	printf("         |   dejarlos en la mesa para que Reuben los recolecte, los cocine y los entregue.                                                        |\n");
	printf("         |                                                                                                                                        |\n");
    printf("         |   Desafio:                                                                                                                             |\n");
	printf("         |                                                                                                                                        |\n");
	printf("         |   1.- AGUJEROS:                                                                                                                        |\n");
	printf("         |   En el piso habrá 20 agujeros (10 en cada cuadrante) que provocaran que el personaje se caiga, lo que hará que pierda el juego.       |\n");
	printf("         |                                                                                                                                        |\n");
	printf("         |   2.- FUEGO:                                                                                                                           |\n");
	printf("         |   Cada 15 movimientos, aparecerá un fuego en un lugar aleatorio en uno de los dos cuadrantes disponibles. El                           |\n");
	printf("         |   personaje que este en el mismo cuadrante que el fuego, no podrá realizar otra acción hasta que agarre el matafuego y                 |\n");
	printf("         |   lo active en una distancia manhattan menor o igual 2 del fuego.                                                                      |\n");
	printf("         |                                                                                                                                        |\n");
	printf("         |   3.- MATAFUEGOS                                                                                                                       |\n");
	printf("         |   Al mismo tiempo que aparezca el fuego, deberá aparecer en el mismo cuadrante un matafuegos. Para agarrarlo,                          |\n");
	printf("         |   se deberá estar en la misma posición del mismo. Para poder activarlo, se deberá apretar la letra M. Una vez usado, desaparecerá.     |\n");
	printf("         |                                                                                                                                        |\n");
	printf("         |   4.- CUCHILLOS                                                                                                                        |\n");
	printf("         |   Habrá 2 cuchillos ubicados en el cuadrante de Stitch, que para usarlos, será necesario tener en la mano el alimento que se           |\n");
	printf("         |   quiere cortar y apretar la letra C.                                                                                                  |\n");
	printf("         |                                                                                                                                        |\n");
	printf("         |   5.- HORNOS:                                                                                                                          |\n");
	printf("         |   Habrá dos hornos para cocinar los ingredientes que lo requieran. Para usarlos, se deberá estar a una distancia                       |\n");
	printf("         |   manhattan de 1 y se usará la letra H También, habra una puerta de salida donde habrá que armar el plato para entregar.               |\n");
	printf("         |________________________________________________________________________________________________________________________________________|\n");
	printf("\n                                                                                                                                                  \n");
}

void imprimir_introduccion_2(){
	printf("         _________________________________________________________________________________________________________________________________________\n");
    printf("         |                                                                                                                                        |\n");
    printf("         |   NIVEL !: ENSALADA                                                                                                                    |\n");
    printf("         |   La ensalada necesitará de 1 lechuga y 1 tomate. Ambos se inicializarán en el cuadrante de Stitch. Ambos deberán ser cortados.        |\n");
	printf("         |                                                                                                                                        |\n");
	printf("         |   NIVEL 2: PIZZA                                                                                                                       |\n");
	printf("         |   La pizza necesitará una masa, 1 jamón y 1 queso. El jamón y el queso requieren cortarse por lo que se inicializarán                  |\n");
    printf("         |   del lado de Stitch, mientras que la masa deberá ser cocinada, por lo que se inicializará del lado de Reuben.                         |\n");
	printf("         |   				                                                                                                          |\n");
	printf("         |   NIVEL 3: HAMBURGUESA                                                                                                                 |\n");
	printf("         |   Los ingredientes de la hamburguesa serán pan, carne, 1 lechuga y 1 tomate. Las verduras y el pan estarán                             |\n");
	printf("         |   en el cuadrante de Stitch para poder cortarse, mientras que la carne estará en el cuadrante de Reuben para poder cocinarse           |\n");
	printf("         |                                                                                                                                        |\n");
    printf("         |   NIVEL 4: SANDWICH                                                                                                                    |\n");
	printf("         |   El sandwich llevara 1 milanesa que deberá cocinarse, por lo que irá del lado de Reuben. Mientras que el pan, el tomate, la lechuga,  |\n");
	printf("         |   el jamón y el queso, iran del lado de Stitch y precisarán cortarse.                                                                  |\n");
	printf("         |________________________________________________________________________________________________________________________________________|\n");
	printf("          ________________________________________________________________________________________________________________________________________\n");
	printf("         |                                                                                                                                        |\n");
	printf("         |   IMPORTANTE! Para poder pasarle los ingredientes a Rouben, se deberan cortar y dejarlos en la mesa del medio. Para                    |\n");
	printf("         |   esto, es necesario estar a una distancia manhattan de 1 y apretar la letra T. Si un ingrediente ya se encuentra en la mesa,          |\n");
    printf("         |   no podrá ubicarse otro.                                                                                                              |\n");
    printf("         |                                                                                                                                        |\n");
    printf("         |   TERRENO                                                                                                                              |\n");
    printf("         |   El terreno será representado con una matriz de 21x21, dividida en 2 cuadrantes con una mesa en el medio,                             |\n");
	printf("         |________________________________________________________________________________________________________________________________________|\n");
	printf("\n                                                                                                                                                 \n");
}

void imprimir_lista_movimientos(){
    printf("          ________________________________________________________________________________________________________________________________________ \n");
    printf("         |                                                                                                                                        |\n");
	printf("         |   LETRAS QUE SE PUEDEN USAR                                                                                                            |\n");
    printf("         |                                                                                                                                        |\n");
    printf("         |   MOVER ARRIBA ---------------------> W                                                                                                |\n");
	printf("         |   MOVER ABAJO ----------------------> S                                                                                                |\n");
	printf("         |   MOVER IZQUIERDA ------------------> A                                                                                                |\n");
	printf("         |   MOVER DERECHA --------------------> D                                                                                                |\n");
    printf("         |   CAMBIAR PERSONAJE ----------------> X                                                                                                |\n");
	printf("         |   CORTAR INGREDIENTE ---------------> C                                                                                                |\n");
	printf("         |   AGARRAR/SOLTAR INGREDIENTE -------> R                                                                                                |\n");
	printf("         |   PASAR/RECIBIR INGREDIENTE --------> T                                                                                                |\n");
	printf("         |   COCINAR INGREDIENTE---------------> H                                                                                                |\n");
	printf("         |   ACTIVAR MATAFUEGOS ---------------> M                                                                                                |\n");
	printf("         |                                                                                                                                        |\n");
    printf("         |   COMENCEMOS CON UNAS PREGUNTAS!!!!!                                                                                                   |\n");
	printf("         |________________________________________________________________________________________________________________________________________|\n");
	printf("\n                                                                                                                                                  \n");

	printf(".                      ########..##.....##.########.##....##....###........######..##.....##.########.########..########.########\n");
	printf(".                      ##.....##.##.....##.##.......###...##...##.##......##....##.##.....##.##.......##.....##....##....##......\n");
	printf(".                      ##.....##.##.....##.##.......####..##..##...##.....##.......##.....##.##.......##.....##....##....##......\n");
	printf(".                      ########..##.....##.######...##.##.##.##.....##.....######..##.....##.######...########.....##....######..\n");
	printf(".                      ##.....##.##.....##.##.......##..####.#########..........##.##.....##.##.......##...##......##....##......\n");
	printf(".                      ##.....##.##.....##.##.......##...###.##.....##....##....##.##.....##.##.......##....##.....##....##......\n");
	printf(".                      ########...#######..########.##....##.##.....##.....######...#######..########.##.....##....##....########\n");
	printf("\n                                                                                                                               \n");
}

void imprimir_resultado(juego_t juego){
	if(estado_juego(juego) == GANADO){
		printf(":'######::::::'###::::'##::: ##::::'###:::::'######::'########:'########:\n");
		printf("'##... ##::::'## ##::: ###:: ##:::'## ##:::'##... ##:... ##..:: ##.....::\n");
		printf(" ##:::..::::'##:. ##:: ####: ##::'##:. ##:: ##:::..::::: ##:::: ##:::::::\n");
		printf(" ##::'####:'##:::. ##: ## ## ##:'##:::. ##:. ######::::: ##:::: ######:::\n");
		printf(" ##::: ##:: #########: ##. ####: #########::..... ##:::: ##:::: ##...::::\n");
		printf(" ##::: ##:: ##.... ##: ##:. ###: ##.... ##:'##::: ##:::: ##:::: ##:::::::\n");
		printf(". ######::: ##:::: ##: ##::. ##: ##:::: ##:. ######::::: ##:::: ########:\n");
		printf(":......::::..:::::..::..::::..::..:::::..:::......::::::..:::::........::\n");
	}else if(estado_juego(juego) == PERDIDO){
		printf("'########::'########:'########::'########::'####::'######::'########:'########:\n");
		printf(" ##.... ##: ##.....:: ##.... ##: ##.... ##:. ##::'##... ##:... ##..:: ##.....::\n");
		printf(" ##:::: ##: ##::::::: ##:::: ##: ##:::: ##:: ##:: ##:::..::::: ##:::: ##:::::::\n");
		printf(" ########:: ######::: ########:: ##:::: ##:: ##::. ######::::: ##:::: ######:::\n");
		printf(" ##.....::: ##...:::: ##.. ##::: ##:::: ##:: ##:::..... ##:::: ##:::: ##...::::\n");
		printf(" ##:::::::: ##::::::: ##::. ##:: ##:::: ##:: ##::'##::: ##:::: ##:::: ##:::::::\n");
		printf(" ##:::::::: ########: ##:::. ##: ########::'####:. ######::::: ##:::: ########:\n");
		printf("..:::::::::........::..:::::..::........:::....:::......::::::..:::::........::\n");
	}
}

void mostrar_introduccion_1(int numero, bool valido){
	while(!valido){
		system("clear");
		imprimir_introduccion_1();
		printf("Ingrese [1] para continuar:\n");
		scanf(" %i", &numero);
		if(numero == 1){
			valido = true;
		}
	}
}

void mostrar_introduccion_2(int numero, bool valido){
	while(!valido){
		system("clear");
		imprimir_introduccion_2();
		printf("Ingrese [1] para continuar:\n");
		scanf(" %i", &numero);
		if(numero == 1){
			valido = true;
		}
	}
}

void mostrar_lista_movimientos(int numero, bool valido){
	while(!valido){
		system("clear");
		imprimir_lista_movimientos();
		printf("Ingrese [1] para continuar:\n");
		scanf(" %i", &numero);
		if(numero == 1){
			valido = true;
		}
	}
}

void ejecutar_introduccion(){
	int valido_1 = false;
	int valido_2 = false;
	int valido_3 = false;
	int numero_1 = 0;
	int numero_2 = 0;
	int numero_3 = 0;
	mostrar_introduccion_1(numero_1, valido_1);
	mostrar_introduccion_2(numero_2, valido_2);
	mostrar_lista_movimientos(numero_3, valido_3);
}


