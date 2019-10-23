#include "JavierOrti48header.h"

void ahorcado(char* palabra, struct datosJugador *pJug) {
	int  longitud, i, flag, letrasRestantes;		
	char *guess = NULL;						
	char letrasProbadas[TAMANIOABECEDARIO];
	char letra;

	*letrasProbadas = '\0';		//LA CADENA EMPIEZA VACIA
	for (i = 0, longitud = 0; *(palabra + i) != '\0'; i++, longitud++); //MIDE LA PALABRA 
	letrasRestantes = longitud;		//LAS LETRAS QUE LE QUEDAN AL USUARIO POR ADIVINAR

	guess = (char*)malloc(longitud * sizeof(char));
	for (i = 0; i < longitud; i++) {	//CREA LA CADENA Y LA INICIALIZA CON '-'
		*(guess + i) = '-';
	}
	*(guess + i) = '\0';

	do {

		printf("Adivinar: %s\n", guess);
		printf("Vidas y puntos %d %d\n", pJug->vidas, pJug->puntos);
		printf("Letra?\n");
		scanf("%c", &letra);
		getchar();

		for (flag = 0, i = 0; *(letrasProbadas + i) != '\0'; i++) {
			if (*(letrasProbadas + i) == letra) {	//COMPRUEBA SI LA PALABRA ESTABA EN LA CADENA, Y EN TAL CASO LEVANTA LA BANDERA
				flag = 1;
			}
		}

		

		if (flag == 0) {
			*(letrasProbadas + i) = letra;		//INSERTA LA LETRA PROBADA EN LA CADENA SI NO ESTABA
			*(letrasProbadas + i + 1) = '\0';
			for (i = 0, flag = 0; i < longitud; i++) {
				if (*(palabra + i) == letra) {
					flag = 1;
					*(guess + i) = *(palabra + i);
					letrasRestantes--;
				}
			}
			if (flag == 1 && letrasRestantes > 0) {
				printf("Has acertado!\n");
			}
			else if (letrasRestantes > 0) {
				printf("Has fallado!\n");
				pJug->vidas--;
			}

			if (flag == 1) {
				pJug->puntos++;
				if (pJug->puntos % 5 == 0) {
					pJug->vidas++;
				}
			}
		}



	} while (pJug->vidas > 0 && letrasRestantes > 0);

	if (letrasRestantes > 0)		//SI NO SE HAN ADIVINADO TODAS LAS LETRAS
		printf("Has perdido!\n");
	else
		printf("Has ganado!\n");

	printf("La palabra: %s\n", palabra);

	//free(guess); //POR ALGUNA RAAZON ME PETA EL FREE
}

int strLength(char *string) {
	int i;
	for (i = 0; *(string + i) != '\0'; i++);
	return i;
}

void strCopy(char *s, char *t) {
	while (*s++ = *t++);
}

void Reordenar(char **string, int npalabras, int indAct) {		//RECOLOCA TODAS LAS DIRECCIONES DE MEMORIA DE 0 A N PARA REUSAR

	for (; indAct < npalabras; indAct++) {
		*(string + indAct) = *(string + indAct + 1);
	}
}

struct datosJugador inicializar_jugador() {
	struct datosJugador jugador;
	
	printf("nombre?\n");
	scanf("%s", jugador.nombre);
	getchar();
	jugador.vidas = 5;
	jugador.puntos = 0;

	return jugador;
}