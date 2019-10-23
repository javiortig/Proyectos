#include "JavierOrtiHeader.h"

char** InicializarTablero(int tamanio) {
	char** tablero = NULL;
	int i, j;

	tablero = (char**)malloc(tamanio * sizeof(char*));	//CREAR MEMORIA FILAS


	for (i = 0; i < tamanio; i++) {		//CREAR MEMORIA COLUMNAS
		*(tablero + i) = (char*)malloc(tamanio * sizeof(char));
	}

	//INICIALIZAR TABLERO EN ' '
	for (i = 0; i < tamanio; i++)
		for (j = 0; j < tamanio; j++)
			tablero[i][j] = ' ';
	return tablero;
}

int ComprobarLleno(char** tablero, int tamanio){
	int i, j;

	for (i = 0; i < tamanio; i++) {	//COMPRUEBA CADA POS QUE NO HAYA ESPACIOS
		for (j = 0; j < tamanio; j++) {
			if (tablero[i][j] == ' ')
				return 0;
		}
	}

	return 1;
	
}

int ComprobarMovimiento(char** tablero, int tamanio, int posX, int posY) {

	if (posX >= tamanio || posX<0 || posY >= tamanio || posY<0 || tablero[posY][posX]!=' ')
		return 0;

	return 1;
}

void RealizarMovimiento(char** tablero, int posX, int posY, char jugador) {

	tablero[posY][posX] = jugador;
}

int ComprobarKenRaya(char** tablero, int tamanio, int k, char jugador) {
	int cont, i, j, temp;

	for (i = 0; i < tamanio; i++) {	//COMPRUEBA LINEAS
		cont = 0;
		for (j = 0; j < tamanio; j++) {
			if (tablero[i][j] != jugador) {
				cont = 0;
			}
			else {
				cont++;
			}
			if (cont == k) {
				return 1;
			}
			
		}
	}

	for (j = 0; j < tamanio; j++) { //COMPRUEBA COLUMNAS
		cont = 0;
		for (i = 0; i < tamanio; i++) {
			if (tablero[i][j] != jugador) {
				cont = 0;
			}
			else {
				cont++;
			}
			if (cont == k) {
				return 1;
			}
		}
	}

	cont = 0;
	for (i = tamanio-1; i >= 0; i--) {	//COMPRUEBA DIAGONALES PRIMARIAS. PARTE 1
		cont = 0;
		for (temp = i, j = 0; temp < tamanio && j < tamanio; temp++, j++) {
			if (tablero[temp][j] != jugador) {
				cont = 0;
			}
			else {
				cont++;
			}
			if (cont == k) {
				return 1;
			}
		}
	}
	cont = 0;
	for (j = 1; j < tamanio; j++) {	//COMPRUEBA DIAGONALES PRIMARIAS. PARTE 2
		cont = 0;
		for (i = 0, temp=j; i < tamanio && temp < tamanio; i++, temp++) {
			if (tablero[i][temp] != jugador) {
				cont = 0;
			}
			else {
				cont++;
			}
			if (cont == k) {
				return 1;
			}
		}
	}


	cont = 0;
	for (i = tamanio - 1; i >= 0; i--) {	//COMPRUEBA DIAGONALES SECUNDARIAS. PARTE 1
		cont = 0;
		for (temp = i, j = tamanio-1; temp <tamanio && j >=0; temp++, j--) {
			if (tablero[temp][j] != jugador) {
				cont = 0;
			}
			else {
				cont++;
			}
			if (cont == k) {
				return 1;
			}
		}
	}
	cont = 0;
	for (j = tamanio-2; j >=0; j--) {	//COMPRUEBA DIAGONALES SECUNDARIAS. PARTE 2
		cont = 0;
		for (i = 0, temp = j; i < tamanio && temp >= 0; i++, temp--) {
			if (tablero[i][temp] != jugador) {
				cont = 0;
			}
			else {
				cont++;
			}
			if (cont == k) {
				return 1;
			}
		}
	}

	return 0;
}

void LiberarTablero(char** tablero, int tamanio) {
	int i;

	for (i = 0; i < tamanio; i++) {
		free(*(tablero + i));
	}

	free(tablero);
}
