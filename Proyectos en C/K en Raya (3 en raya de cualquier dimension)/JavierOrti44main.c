#include "JavierOrtiHeader.h"

int main() {
	int tamanio, k, i, j, fila, columna, condition;	
	char** tablero = NULL;
	char jugador='O';

	printf("Tamanio del tablero:\n");
	scanf("%d", &tamanio);
	printf("El valor K:\n");
	scanf("%d", &k);

	tablero = InicializarTablero(tamanio);

	condition = 0;	//COND 0 SIGUE JUGANDO, 1 HAY GANADOR, 2 EMPATE
	do {
		if (jugador == 'X')	//CAMBIA DE JUGADOR
			jugador = 'O';
		else
			jugador = 'X';

		printf("Jugador %c elige posicion del tablero\n", jugador);
		printf("Fila:\n");
		scanf("%d", &fila);
		printf("Columna:\n");
		scanf("%d", &columna);
		printf("\n");
		if (ComprobarMovimiento(tablero, tamanio, columna, fila)) {

			RealizarMovimiento(tablero, columna, fila, jugador);


			for (i = 0; i < tamanio; i++) {	//IMPRIME EL TABLERO TRAS EL MOVIMIENTO
				for (j = 0; j < tamanio; j++) {
					printf("|%c|", tablero[i][j]);
				}
				printf("\n");
			}
			printf("\n");

			//COMPRUEBA QUE HAYA UN GANADOR (1) O QUE HAYA EMPATE (2)
			if (ComprobarKenRaya(tablero, tamanio, k, jugador))
				condition = 1;
			else if (ComprobarLleno(tablero, tamanio))
				condition = 2;
			
		}
		else {
			printf("ERROR\n");
			if (jugador == 'X')	
				jugador = 'O';
			else
				jugador = 'X';
		}

	} while (condition==0);

	if (condition == 1)
		printf("Ganador jugador %c\n", jugador);
	else if (condition == 2)
		printf("Empate");	
	

	LiberarTablero(tablero, tamanio);
		


	return 0;
}