#include <stdio.h>
#include <stdlib.h>


#define PALABRACLAVE "chewbacca"
#define VIDASMAX 5
#define TAMANIOABECEDARIO 27
#define MAXPALABRAS 10

struct datosJugador {
	int nombre[10];
	int vidas;
	int puntos;
};

void ahorcado(char* palabra, struct datosJugador *pJug);
int strLength(char *string);
void strCopy(char *s, char *t);
void Reordenar(char **string, int npalabras, int indAct);
struct datosJugador inicializar_jugador();
