#include "Header.h"



int main() {
	/*
	char tipoSource, tipoDestino, colorSource, colorDestino;
	int numeroSource, numeroDestino;
	struct coordenada posSource, posDestino;
	*/
	struct pieza piezaSource, piezaDestino;
	struct pieza tablero[8][8];
	int i, j;
	int movimientoElegido;
	char jugadorActual, c = '0';
	struct coordenada fichaElegida;
	struct coordenada posiblesMovimientos[MAX];
	int numTurnos = 0;
	int jaque=0, autojaque=0;
	//INSTRUCCIONES//

	printf("Bienvenido al ajedrez.\nPor favor, si es la primera vez que juega, lea atentamente las instrucciones:\nPara leer las instrucciones, pulse '1'\nPara crear una nueva partida, pulse cualquier otra tecla\n");

	c = getch();
	if (c == '1') {
		Instrucciones();
	}
	
	//INICIALIZACION//
	Inicializar_tablero(tablero);
	jugadorActual = 'n';

	//PARTIDA//
	do {
		numTurnos++;
		jugadorActual = Cambiar_Jugador(jugadorActual);
		do {
			system("CLS");
			ImprimirTablero(tablero);

			if (jugadorActual == 'b')
				printf("Juegan las blancas (MAYUSCULAS)\n");
			else
				printf("Juegan las negras (minusculas)\n");
			if (jaque == 1) {
				printf("ESTAS EN JAQUE!!\n");
				jaque = 0;
			}
			else if (autojaque == 1) {
				printf("ERROR. Si mueves esa pieza PIERDES. Prueba de nuevo\n");
				autojaque = 0;
				numTurnos--;//en este caso como se resetea el turno, no se debe contar
			}

			do {
				fichaElegida = Seleccionar_Ficha(tablero, jugadorActual);
				
				CopiarPieza(&piezaSource, &tablero[fichaElegida.fila][fichaElegida.columna]);
				
				Calcular_Posibles_Movimientos(tablero, posiblesMovimientos, fichaElegida, jugadorActual);

				if (posiblesMovimientos[0].columna == FINCADENA) {	//SI LA FICHA NO TIENE MOVS POSIBLES, no elegir
					printf("ERROR. Esta ficha no se puede mover\n");
				}
			} while (posiblesMovimientos[0].columna == FINCADENA);

			system("CLS");
			Imprimir_seleccion(tablero, fichaElegida, posiblesMovimientos, 0);

			movimientoElegido = Leer_Movimiento(posiblesMovimientos);

			////en pieza destino tablero [posiblesMovimientos[movimientoElegido].fila]
			CopiarPieza(&piezaDestino, &tablero[posiblesMovimientos[movimientoElegido].fila][posiblesMovimientos[movimientoElegido].columna]);
			////

			//SI EL MOVIMIENTO NO SE CANCELA//
			if (movimientoElegido !='c') {
				Mover_Ficha(tablero, fichaElegida, posiblesMovimientos, movimientoElegido);
				
				//SE EJECUTA SI AL MOVER TE SUICIDAS. DESHACE EL MOVIMIENTO Y TE VUELVE A DAR EL TURNO//
				if (ComprobarJaqueAEnemigo(tablero, Cambiar_Jugador(jugadorActual), posiblesMovimientos)) {
					CopiarPieza(&tablero[piezaSource.posicion.fila][piezaSource.posicion.columna], &piezaSource);
					CopiarPieza(&tablero[piezaDestino.posicion.fila][piezaDestino.posicion.columna], &piezaDestino);

					jugadorActual = Cambiar_Jugador(jugadorActual);
					autojaque = 1;
				}
				else {
					jaque = ComprobarJaqueAEnemigo(tablero, jugadorActual, posiblesMovimientos);
				}
				
			}

			
			
		} while (movimientoElegido == 'c');
		
	} while (!ComprobarJaqueMate(tablero, Cambiar_Jugador(jugadorActual), posiblesMovimientos));

	//FIN DE PARTIDA//
	system("CLS");
	ImprimirTablero(tablero);
	printf("JAQUE MATE\n");
	if (jugadorActual == 'b')
		printf("LAS BLANCAS GANAN\n");
	else
		printf("LAS NEGRAS GANAN\n");

	printf("La partida ha durado >%d< turnos\n", (numTurnos / 2) + 1);

	return 0;
}
			


	//POSIBLE TIMER//
	/*int flag=0;
	do {
		if (kbhit()) {
			eleccion[0] = getch();
			eleccion[1] = getch();
			eleccion[2] = '\0';
			flag = 1;
		}
		else {
			Sleep(500);
			system("CLS");
			printf("Hola");
			Sleep(500);
			system("CLS");
			printf("Adios");
		}
	} while (flag == 0);
	system("CLS");
	printf("%s", eleccion);

	return 0;*/
