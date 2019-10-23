#include "JavierOrti48header.h"

/*int main() {
	int nPalabras = 0, indAct;	//INDACT=PALABRA ACTUAL CON LA QUE ESTAMOS TRABAJANDO
	char** listapalabras=NULL;
	char palabraActual[50];
	char eleccion;
	listapalabras = (char**)malloc(MAXPALABRAS * sizeof(char*));


	do {		//PIDE PALABRAS AL USUARIO HASTA QUE EL NO QUIERA MAS O HAYA ESCRITO 10
		printf("Introducir una palabra:\n"); //LAS METE EN UN ARRAY DE PUNTEROS, DONDE CADA PUNTERO ES UNA CADENA
		scanf("%s", palabraActual);
		getchar();

		*(listapalabras + nPalabras) = (char*)malloc((strLength(palabraActual) + 1) * sizeof(char));
		strCopy(*(listapalabras + nPalabras), palabraActual);

		nPalabras++;
		if (nPalabras < 10) {
			printf("Quieres mas (S/N)?\n");
			scanf("%c", &eleccion);
			getchar();
		}
	} while ((eleccion == 'S' || eleccion == 's') && nPalabras<10 );

	srand (10);
	do {
		indAct = rand() % (nPalabras);
		ahorcado(*(listapalabras+indAct));
		free(*(listapalabras + indAct));
		Reordenar(listapalabras, nPalabras, indAct);		//REORDENA LAS CADENAS VACIAS

		nPalabras--;
		if (nPalabras > 0) {		//SI QUEDAN PALABRAS PREGUNTA AL JUGADOR SI QUIERE JUGAR OTRA
			printf("Otra Partida (S/N)?\n");
			scanf("%c", &eleccion);
			getchar();
		}
	} while (nPalabras>0 && (eleccion == 'S' || eleccion == 's'));

	free(listapalabras);



	return 0;
}*/


//ESTE MAIN DE ABAJO SERIA UNA OPCION MENOS EFICIENTE, PUESTO QUE PUEDE ELEGIR ALEATORIAMENTE 50 VECES UN ESPACIO EN BLANCO Y 
//ENTRAR EN UN LARGO BUCLE. ESPECIALMENTE SI LA LISTA DE PALABRAS ES GRANDE



int main() {
	int nPalabras = 10, indAct, i, puntos=0;
	char** listapalabras = NULL;
	char palabraActual[50];
	char eleccion;
	
	char *lista[10] = { "coche","mesa","ahora", "gato", "hola", "uno", "una","chewbacca", "daenerys", "tyrion" };
	struct datosJugador jugador;
	listapalabras = (char**)malloc(MAXPALABRAS * sizeof(char*));

	jugador = inicializar_jugador();

	/*do {		//PIDE PALABRAS AL USUARIO HASTA QUE EL NO QUIERA MAS O HAYA ESCRITO 10
		printf("Introducir una palabra:\n");	//LAS METE EN UN ARRAY DE PUNTEROS, DONDE CADA PUNTERO ES UNA CADENA
		scanf("%s", palabraActual);
		getchar();

		*(listapalabras + nPalabras) = (char*)malloc((strLength(palabraActual) + 1) * sizeof(char));
		strCopy(*(listapalabras + nPalabras), palabraActual);

		nPalabras++;
		if (nPalabras < 10) {
			printf("Quieres mas (S/N)?\n");
			scanf("%c", &eleccion);
			getchar();
		}
	} while ((eleccion == 'S' || eleccion == 's') && nPalabras < 10);*/


	//srand(10);
	i = nPalabras;
	indAct = 0;
	do {
		/*do {		//	COMPRUEBA QUE LA CADENA ELEGIDA NO HAYA SIDO USADA PREVIAMENTE
			indAct = rand() % (nPalabras);
		} while (*(listapalabras + indAct) == NULL);*/

		ahorcado(lista[indAct], &jugador);
		i--;
		indAct++;

		printf(">>> %s %d %d\n", jugador.nombre, jugador.vidas, jugador.puntos);	//IMPRIME LOS DATOS DEL JUGADOR
		if (i > 0 && jugador.vidas>0) {		//SI QUEDAN PALABRAS y VIDAS PREGUNTA AL JUGADOR SI QUIERE JUGAR OTRA
			printf("Otra Partida (S/N)?\n");
			scanf("%c", &eleccion);
			getchar();
		}
	} while (i > 0 && jugador.vidas>0 && (eleccion == 'S' || eleccion == 's'));

	/*for (i = 0; i < nPalabras; i++) {
		free(*(listapalabras + i));
	}
	free(listapalabras);*/



	return 0;
}

