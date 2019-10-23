#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** InicializarTablero(int tamanio);
int ComprobarLleno(char** tablero, int tamanio);
int ComprobarMovimiento(char** tablero, int tamanio, int posX, int posY);
void RealizarMovimiento(char** tablero, int posX, int posY, char jugador);
int ComprobarKenRaya(char** tablero, int tamanio, int k, char jugador);
void LiberarTablero(char** tablero, int tamanio);

