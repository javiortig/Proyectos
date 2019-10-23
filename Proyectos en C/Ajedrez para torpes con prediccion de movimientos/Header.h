#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>


#define MAX 30
#define FINCADENA -13
#define SINCOLOR '0'
#define SINNUMERO -1
#define MOVEXTRAS "asfghjklñzxvbnmqw"
#define INSTRUCCIONES "Si es su primera vez jugando al ajedrez, no se preocupe.\nEste programa le dira en todo momento que movimientos puede o no hacer.\nComo bien sabemos, el objetivo principal es hacer jaque mate al rey oponente, representado por 'r'.\nCuando su rey este bajo amenaza de jaque, el programa se lo indicara.\nSi en algun momento usted hace un movimiento incorrecto (como pueda ser mover el rey al enemigo o dejarlo desprotegido)\nEl programa se lo impedira.\nLas fichas BLANCAS se representan con MAYUSCULAS y las negras con minusculas.\nPara seleccionar la ficha que desea mover, tan solo debe pulsar las teclas que la representan:\n-Ejemplo 'c1' para escoger al primer caballo.\nTras elegir su ficha, el programa le mostrara todos los posibles movimientos de la ficha seleccionada.\nPara seleccionar el movimiento deseado, basta con pulsar el caracter correspondiente al movimiento mostrado en pantalla.\nRecuerde algunas reglas especiales que tiene el ajedrez:\n-Los peones pueden mover doble en su primer movimiento.\n-Los peones se convierten en damas al llegar a la ultima casilla del oponente.\n\nEsperamos que disfrute de su partida\n\nPulse cualquier tecla para comenzar.\0"



struct coordenada {
	int fila;
	int columna;
};



struct pieza {
	char tipo;	// i=peon, t=torre, c=caballo, a=alfil, d=dama, r=rey. ' '=nada;
	int numero;

	char color;
	struct coordenada posicion;
	struct coordenada posiblesMovimientos[MAX];

};

void Instrucciones();
void ImprimirTablero(struct pieza tablero[8][8]);	
void Imprimir_seleccion(struct pieza tablero[8][8], struct coordenada eleccion, struct coordenada posiblesMovimientos[MAX], int blink);

void Inicializar_tablero(struct pieza tablero[8][8]);
struct coordenada Seleccionar_Ficha(struct pieza tablero[8][8], char jugador);
void Calcular_Posibles_Movimientos(struct pieza tablero[8][8], struct coordenada posiblesMovimientos[MAX], struct coordenada eleccion, char jugador);	
int Es_Movimiento_Valido(struct pieza tablero[8][8], struct coordenada movimiento, char jugador);	
int Leer_Movimiento(struct coordenada posiblesMovimientos[MAX]);	
void Mover_Ficha(struct pieza tablero[8][8], struct coordenada eleccion, struct coordenada posiblesMovimientos[MAX], int input);
char Cambiar_Jugador(char jugador);

struct coordenada BuscarRey(struct pieza tablero[8][8], char jugador);

//ESTAS DOS FUNCIONES NOS HAN COSTADO MAS QUE TODO EL PROGRAMA JUNTO VIVA DENNIS RITCHIE
int ComprobarJaqueAEnemigo(struct pieza tablero[8][8], char jugador, struct coordenada posiblesMovimientos[MAX]);
int ComprobarJaqueMate(struct pieza tablero[8][8], char jugadorAtacado, struct coordenada posiblesMovimientos[MAX]);
//


void CopiarPieza(struct pieza *destino, struct pieza *source);
int ContarPiezas(struct pieza tablero[8][8], char jugador, char pieza);


