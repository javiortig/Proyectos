#include "Header.h"

void Instrucciones() {
	int i, j, k;
	system("CLS");
	Sleep(100);
	for (i = 0; INSTRUCCIONES[i] != '\0'; i++) {
		Sleep(40);
		printf("%c", INSTRUCCIONES[i]);
		if (INSTRUCCIONES[i] == '.' || INSTRUCCIONES[i] == ')' || INSTRUCCIONES[i] == ',' || INSTRUCCIONES[i] == ':')
			Sleep(225);
	}
	
	
	getch();
}

void Inicializar_tablero(struct pieza tablero[8][8]) {
	int i, j;
	//Casillas en blanco//
	for (i = 2; i < 6; i++) {
		for (j = 0; j < 8; j++) {
			tablero[i][j].tipo = ' ';
			tablero[i][j].color = SINCOLOR;
		}
	}

	//Peones Blancos//
	for (i = 6, j = 0; j < 8; j++) {
		tablero[i][j].color = 'b';
		tablero[i][j].numero=j+1;
		tablero[i][j].posicion.columna = j;
		tablero[i][j].posicion.fila = i;
		tablero[i][j].tipo = 'i';
	}

	//Fichas Principales Blancas//
	for (i = 7, j = 0; j < 8; j++) {
		tablero[i][j].color = 'b';
		//Torres Blancas//
		if (j == 0 || j == 7) {
			tablero[i][j].numero = (j == 0) ? 1:2;
			tablero[i][j].posicion.columna = j;
			tablero[i][j].posicion.fila = i;
			tablero[i][j].tipo = 't';
		}

		//Caballos Blancos//
		else if (j == 1 || j == 6) {
			tablero[i][j].numero = (j == 1) ? 1 : 2;
			tablero[i][j].posicion.columna = j;
			tablero[i][j].posicion.fila = i;
			tablero[i][j].tipo = 'c';
		}

		//Alfiles Blancos//
		else if (j == 2 || j == 5) {
			tablero[i][j].numero = (j == 2) ? 1 : 2;
			tablero[i][j].posicion.columna = j;
			tablero[i][j].posicion.fila = i;
			tablero[i][j].tipo = 'a';
		}

		//Dama Blanca//
		else if (j==3) {
			tablero[i][j].numero = 1;
			tablero[i][j].posicion.columna = j;
			tablero[i][j].posicion.fila = i;
			tablero[i][j].tipo = 'd';
		}

		//Rey Blanco//
		else {
			tablero[i][j].numero = 1;
			tablero[i][j].posicion.columna = j;
			tablero[i][j].posicion.fila = i;
			tablero[i][j].tipo = 'r';
		}
	}

	//---------------------------------------------//
	//Peones Negros//
	for (i = 1, j = 0; j < 8; j++) {
		tablero[i][j].color = 'n';
		tablero[i][j].numero = j + 1;
		tablero[i][j].posicion.columna = j;
		tablero[i][j].posicion.fila = i;
		tablero[i][j].tipo = 'i';
	}

	//Fichas Principales Negras//
	for (i = 0, j = 0; j < 8; j++) {
		tablero[i][j].color = 'n';
		//Torres Negras//
		if (j == 0 || j == 7) {
			tablero[i][j].numero = (j == 0) ? 1 : 2;
			tablero[i][j].posicion.columna = j;
			tablero[i][j].posicion.fila = i;
			tablero[i][j].tipo = 't';
		}

		//Caballos Negras//
		else if (j == 1 || j == 6) {
			tablero[i][j].numero = (j == 1) ? 1 : 2;
			tablero[i][j].posicion.columna = j;
			tablero[i][j].posicion.fila = i;
			tablero[i][j].tipo = 'c';
		}

		//Alfiles Negras//
		else if (j == 2 || j == 5) {
			tablero[i][j].numero = (j == 2) ? 1 : 2;
			tablero[i][j].posicion.columna = j;
			tablero[i][j].posicion.fila = i;
			tablero[i][j].tipo = 'a';
		}

		//Dama Negras//
		else if (j == 3) {
			tablero[i][j].numero = 1;
			tablero[i][j].posicion.columna = j;
			tablero[i][j].posicion.fila = i;
			tablero[i][j].tipo = 'd';
		}

		//Rey Negras//
		else {
			tablero[i][j].numero = 1;
			tablero[i][j].posicion.columna = j;
			tablero[i][j].posicion.fila = i;
			tablero[i][j].tipo = 'r';
		}
	}
	//Espacios en Blanco//
	for (i = 2; i < 6; i++) {
		for (j = 0; j < 8; j++) {
			tablero[i][j].numero = SINNUMERO;
			tablero[i][j].color = SINCOLOR;
			tablero[i][j].tipo = ' ';
			tablero[i][j].posicion.columna = j;
			tablero[i][j].posicion.fila = i;
		}
	}
	
}

struct coordenada Seleccionar_Ficha(struct pieza tablero[8][8], char jugador) {
	int i, j, flag;
	char eleccion[3], ctemp[3];
	struct coordenada posicion;

	flag = 0;
	do {
		printf("Selecciona tu ficha\n");
		eleccion[0] = getch();
		eleccion[1] = getch();
		eleccion[2] = '\0';
		for (i = 0; i < 8; i++) {		//comprueba cada ficha para ver si alguna es la que ha elegido, y si es asi devuelve sus coordenadas
			for(j=0; j<8; j++){
				ctemp[0] = tablero[i][j].tipo;
				ctemp[1] = (tablero[i][j].numero)+48;
				ctemp[2] = '\0';
				if (strcmp(eleccion, ctemp)==0 && tablero[i][j].color==jugador) {
					posicion.columna = j;
					posicion.fila = i;
					return posicion;
				}
			}
		}
		printf("Error, no se ha encontrado tu ficha\n\n");
	} while(flag == 0);
}

//CALCULA LOS POSIBLES MOVIMIENTOS PARA POSTERIORMENTE IMPRIMIRLOS Y QUE EL JUGADOR ELIJA//
void Calcular_Posibles_Movimientos(struct pieza tablero[8][8], struct coordenada posiblesMovimientos[MAX], struct coordenada eleccion, char jugador) {
	int i=eleccion.fila, j=eleccion.columna, k, l;
	int iPosMov=0;	//EL INDICE PARA LA CADENA DE LOS POSIBLES MOVIMIENTOS. ESTA ARRAY ACABARA CON UN -13 
	struct coordenada movTemp;

	//MOVIMIENTO PEON//
	if (tablero[i][j].tipo == 'i') {
		//COMER HACIA LA IZQUIERDA//
		movTemp = eleccion;
		{
			if (jugador == 'b') {
				movTemp.fila--;
			}
			else {
				movTemp.fila++;
			}
			movTemp.columna--;
			//comprueba si el mov se puede hacer. En este caso comprueba si hay alguna ficha para comer//
			if (Es_Movimiento_Valido(tablero, movTemp, jugador) && tablero[movTemp.fila][movTemp.columna].color!= jugador && tablero[movTemp.fila][movTemp.columna].tipo!= ' ') {	
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++; //el indice de la array se mueve al siguiente por si tiene que entrar otro posible movimiento
			}
		}
		//MOVIMIENTO RECTO//
		{
			movTemp = eleccion;	//esto se hace en cada caso. Los posibles mov se calculan respecto a la ficha seleccionada
			if (jugador == 'b') {
				movTemp.fila--;
			}
			else {
				movTemp.fila++;
			}
			if (Es_Movimiento_Valido(tablero, movTemp, jugador) && tablero[movTemp.fila][movTemp.columna].tipo==' ') {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;	
			}
		}
		//MOVIMIENTO DOBLE//
		{
			movTemp = eleccion;	//esto se hace en cada caso. Los posibles mov se calculan respecto a la ficha seleccionada
			if (jugador == 'b') {
				movTemp.fila-=2;
			}
			else {
				movTemp.fila+=2;
			}
			if (Es_Movimiento_Valido(tablero, movTemp, jugador) && tablero[movTemp.fila][movTemp.columna].tipo == ' ' && ((jugador=='b' && i==6 && tablero[i - 1][j].tipo == ' ')||(jugador == 'n' && i == 1 && tablero[i + 1][j].tipo == ' '))) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
			}
		}
		
		//COMER HACIA LA DERECHA//
		{
			movTemp = eleccion;
			if (jugador == 'b') {
				movTemp.fila--;
			}
			else {
				movTemp.fila++;
			}
			movTemp.columna++;
			if (Es_Movimiento_Valido(tablero, movTemp, jugador) && tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++; 
			}
		}
	}

	//MOVIMIENTO CABALLO//
	else if (tablero[i][j].tipo == 'c') {
		// 8 movimientos como max//
		movTemp = eleccion;
		{
			//1
			movTemp.fila -= 2;
			movTemp.columna--;
			if (Es_Movimiento_Valido(tablero, movTemp, jugador)) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
			}
			//2		//a partir de aqui se comprueban los otros movimientos respecto al anterior
			movTemp.columna+=2;
			if (Es_Movimiento_Valido(tablero, movTemp, jugador)) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
			}
			//3
			movTemp.fila++;
			movTemp.columna-=3;
			if (Es_Movimiento_Valido(tablero, movTemp, jugador)) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
			}
			//4
			movTemp.columna+=4;
			if (Es_Movimiento_Valido(tablero, movTemp, jugador)) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
			}
			//5
			movTemp.fila += 2;
			movTemp.columna-=4;
			if (Es_Movimiento_Valido(tablero, movTemp, jugador)) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
			}
			//6
			movTemp.columna += 4;
			if (Es_Movimiento_Valido(tablero, movTemp, jugador)) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
			}
			//7
			movTemp.fila += 1;
			movTemp.columna -= 3;
			if (Es_Movimiento_Valido(tablero, movTemp, jugador)) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
			}
			//8
			movTemp.columna += 2;
			if (Es_Movimiento_Valido(tablero, movTemp, jugador)) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
			}
		}
	}
	//MOVIMIENTO ALFIL//
	else if (tablero[i][j].tipo == 'a') {
		//DIAGONAL ARRIBA IZQUIERDA//
		{
			movTemp = eleccion;
			for (movTemp.fila--, movTemp.columna--; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.fila--, movTemp.columna--) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;	//SI ES UNA PIEZA ENEMIGA, LA AÑADE COMO MOVIMIENTO Y LUEGO SE SALE, PUESTO QUE NO PUEDE ATRAVESARLA
				}
			}
		}
		//DIAGONAL ARRIBA DERECHA//
		{
			movTemp = eleccion;
			for (movTemp.fila--, movTemp.columna++; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.fila--, movTemp.columna++) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;	
				}
			}
		}
		//DIAGONAL ABAJO IZQUIERDA//
		{
			movTemp = eleccion;
			for (movTemp.fila++, movTemp.columna--; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.fila++, movTemp.columna--) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;
				}
			}
		}
		//DIAGONAL ABAJO DERECHA//
		{
			movTemp = eleccion;
			for (movTemp.fila++, movTemp.columna++; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.fila++, movTemp.columna++) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;
				}
			}
		}
	}
	//MOVIMIENTO TORRE//
	else if (tablero[i][j].tipo == 't') {
		//ARRIBA//
		{
			movTemp = eleccion;
			for (movTemp.fila--; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.fila--) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;
				}
			}
		}
		//ABAJO//
		{
			movTemp = eleccion;
			for (movTemp.fila++; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.fila++) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;
				}
			}
		}
		//IZQUIERDA//
		{
			movTemp = eleccion;
			for (movTemp.columna--; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.columna--) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;
				}
			}
		}
		//DERECHA//
		{
			movTemp = eleccion;
			for (movTemp.columna++; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.columna++) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;
				}
			}
		}
	}
	//MOVIMIENTO DAMA//
	else if (tablero[i][j].tipo == 'd') {
	//ARRIBA//
		{
			movTemp = eleccion;
			for (movTemp.fila--; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.fila--) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;
				}
			}
		}
		//ABAJO//
		{
			movTemp = eleccion;
			for (movTemp.fila++; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.fila++) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;
				}
			}
		}
		//IZQUIERDA//
		{
			movTemp = eleccion;
			for (movTemp.columna--; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.columna--) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;
				}
			}
		}
		//DERECHA//
		{
			movTemp = eleccion;
			for (movTemp.columna++; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.columna++) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;
				}
			}
		}
		//DIAGONAL ARRIBA IZQUIERDA//
		{
			movTemp = eleccion;
			for (movTemp.fila--, movTemp.columna--; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.fila--, movTemp.columna--) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;	
				}
			}
		}
		//DIAGONAL ARRIBA DERECHA//
		{
			movTemp = eleccion;
			for (movTemp.fila--, movTemp.columna++; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.fila--, movTemp.columna++) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;
				}
			}
		}
		//DIAGONAL ABAJO IZQUIERDA//
		{
			movTemp = eleccion;
			for (movTemp.fila++, movTemp.columna--; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.fila++, movTemp.columna--) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;
				}
			}
		}
		//DIAGONAL ABAJO DERECHA//
		{
			movTemp = eleccion;
			for (movTemp.fila++, movTemp.columna++; Es_Movimiento_Valido(tablero, movTemp, jugador); movTemp.fila++, movTemp.columna++) {
				posiblesMovimientos[iPosMov] = movTemp;
				iPosMov++;
				if (tablero[movTemp.fila][movTemp.columna].color != jugador && tablero[movTemp.fila][movTemp.columna].tipo != ' ') {
					break;
				}
			}
		}
	}
	//MOVIMIENTO REY//
	else if (tablero[i][j].tipo == 'r') {
		//EL CUADRADO//
		{
			movTemp = eleccion;
			for (movTemp.fila=eleccion.fila-1; movTemp.fila < eleccion.fila + 2; movTemp.fila++) {
				for (movTemp.columna = eleccion.columna-1; movTemp.columna < eleccion.columna + 2; movTemp.columna++) {
					if (Es_Movimiento_Valido(tablero, movTemp, jugador)) {
						posiblesMovimientos[iPosMov] = movTemp;
						iPosMov++;
					}
				}
			}
		}
	}
	

	posiblesMovimientos[iPosMov].columna = FINCADENA; //marca con un numero secreto el fin de la cadena
}

//Comprueba si un movimiento es valido. Devuelve 1 si lo es//
int Es_Movimiento_Valido(struct pieza tablero[8][8], struct coordenada movimiento, char jugador) {
	int i = movimiento.fila, j = movimiento.columna, flag=1;
	
	if (i < 0 || j < 0 || i >= 8 || j >= 8) {	//si se sale del tablero
		flag = 0;
	}
	else if (tablero[i][j].tipo != ' ' && tablero[i][j].color == jugador) {	
		flag = 0;	//si la casilla es la de un compañero
	}

	//si al mover dejas jaque...
	//pensar mas....
	return flag;
}

//DEVUELVE HACIA DONDE QUIERO MOVER LA FICHA//
int Leer_Movimiento(struct coordenada posiblesMovimientos[MAX]) {	
	int i, k, input, flag = 1;
	//CALCULAR CUANTO MIDE LA CADENA//
	for (i = 0; posiblesMovimientos[i].columna != FINCADENA; i++);

	do {
		printf("Elija jugada ('c' para cancelar)\n");
		input = getch();
		if (input == 'c')	//PARA CANCELAR
			return 'c';
		else if (input >= '0' && input <= '9') {	//si es numero
			input -= 48;
		}
		else {	//si es letra
			for (k = 0; MOVEXTRAS[k] != '\0'; k++) {//busca la letra en la cadena de caracteres reservados
				if (input == MOVEXTRAS[k]) {
					input = 10 + k;	//EMPIEZA POR 10 YA QUE POR AHI EMPIEZAN LOS CARACTERES
				}
			}
			if (MOVEXTRAS[k] == '\0')
				flag = 0;
		}
		input -= 1;
		if ((input<0 || input>=i) && flag==1) {
			printf("ERROR. Introduzca un numero valido\n");
		}
	} while (input<0 || input>=i);
	
	return input;

	
}
		//-------------devuelve 1 si se come al rey. borrar esto mas adelante y poner la funcion a void
void Mover_Ficha(struct pieza tablero[8][8], struct coordenada eleccion, struct coordenada posiblesMovimientos[MAX], int input) {
	int i = eleccion.fila, j = eleccion.columna;	//source
	int  k = posiblesMovimientos[input].fila, l = posiblesMovimientos[input].columna;	//destino

	//CORORAR PEONES A REINAS//
	if (tablero[i][j].tipo == 'i' && ((i==1 && tablero[i][j].color == 'b') || (i==6 && tablero[i][j].color == 'n'))) {
		tablero[i][j].tipo = 'd';
		tablero[i][j].numero = ContarPiezas(tablero, tablero[i][j].color, 'd'); //le da el numero de reina que le corresponda
	}

	//COPIAR FICHA EN DESTINO//
	tablero[k][l] = tablero[i][j];
	tablero[k][l].posicion.fila = k;
	tablero[k][l].posicion.columna = l;


	//BORRAR CASILLA MOVIDA//
	tablero[i][j].color = SINCOLOR;
	tablero[i][j].tipo = ' ';

}

void ImprimirTablero(struct pieza tablero[8][8]) {
	int i, j;
	char EsquinaSuperiorDerecha = 191, EsquinaSuperiorIzquierda = 218, EsquinaInferiorDerecha = 217, EsquinaInferiorIzquierda = 192;

	printf("\n\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", EsquinaSuperiorIzquierda, 196, 196, 194, 196, 196, 194, 196, 196, 194, 196, 196, 194, 196, 196, 194, 196, 196, 194, 196, 196, 194, 196, 196, EsquinaSuperiorDerecha);

	for (i = 0; i < 8; i++) {
		printf("\t\t\t\t\t\t%c", 179);
		for (j = 0; j < 8; j++) {
			if ((tablero[i][j].color) == 'n') {
				printf("%c%d%c", tablero[i][j].tipo, tablero[i][j].numero, 179);
			}
				
			else if ((tablero[i][j].color) == 'b') printf("%c%d|", (tablero[i][j].tipo) - 32, tablero[i][j].numero);
			else printf("  |");

		}
		if (i == 7) {
			printf("\n\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", EsquinaInferiorIzquierda, 196, 196, 193, 196, 196, 193, 196, 196, 193, 196, 196, 193, 196, 196, 193, 196, 196, 193, 196, 196, 193, 196, 196, EsquinaInferiorDerecha);
		}
		else printf("\n\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 195, 196, 196, 197, 196, 196, 197, 196, 196, 197, 196, 196, 197, 196, 196, 197, 196, 196, 197, 196, 196, 197, 196, 196, 180);
	}

	
}

void Imprimir_seleccion(struct pieza tablero[8][8], struct coordenada eleccion, struct coordenada posiblesMovimientos[MAX], int blink){	//blink 0 si se muestra la ficha, 1 si se tapa con el cuadradito
	int i, j, k, iprint=1, flag;	//i j para tablero, k para recorrer los posmovimientos, iprint el indice de impresion de los posmovimientos
	
	if (blink == 0) {
		char EsquinaSuperiorDerecha = 191, EsquinaSuperiorIzquierda = 218, EsquinaInferiorDerecha = 217, EsquinaInferiorIzquierda = 192;

		printf("\n\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", EsquinaSuperiorIzquierda, 196, 196, 194, 196, 196, 194, 196, 196, 194, 196, 196, 194, 196, 196, 194, 196, 196, 194, 196, 196, 194, 196, 196, EsquinaSuperiorDerecha);

		for (i = 0; i < 8; i++) {
			printf("\t\t\t\t\t\t%c", 179);
			for (j = 0; j < 8; j++) {
				for (k=0, flag=0; posiblesMovimientos[k].columna!=FINCADENA && flag == 0; k++){
					if (i == posiblesMovimientos[k].fila && j == posiblesMovimientos[k].columna) {
						flag = 1;
					}
				}
				if (flag == 1) {
					if (k > 9) {
						printf("%c%c%c", 175, MOVEXTRAS[k-10], 179);
					}
					else {
						printf("%c%d%c", 175, k, 179);
					}
				}
				else if (i == eleccion.fila && j == eleccion.columna) {
					printf("%c%c%c", 219, 219, 179);
				}
				else {
					if ((tablero[i][j].color) == 'n') {
						printf("%c%d%c", tablero[i][j].tipo, tablero[i][j].numero, 179);
					}

					else if ((tablero[i][j].color) == 'b') printf("%c%d|", (tablero[i][j].tipo) - 32, tablero[i][j].numero);
					else printf("  |");
				}
				

			}
			if (i == 7) {
				printf("\n\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", EsquinaInferiorIzquierda, 196, 196, 193, 196, 196, 193, 196, 196, 193, 196, 196, 193, 196, 196, 193, 196, 196, 193, 196, 196, 193, 196, 196, EsquinaInferiorDerecha);
			}
			else printf("\n\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 195, 196, 196, 197, 196, 196, 197, 196, 196, 197, 196, 196, 197, 196, 196, 197, 196, 196, 197, 196, 196, 197, 196, 196, 180);
		}
	}

}


char Cambiar_Jugador(char jugador) {

	if (jugador == 'b')
		jugador = 'n';
	else
		jugador = 'b';

	return jugador;
}

//BUSCA EL REY DEL COLOR SELECCIONADO. DEVUELVE -1 -1 SI HAY ERROR//
struct coordenada BuscarRey(struct pieza tablero[8][8], char jugador) {
	int i, j;
	struct coordenada error;
	

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (tablero[i][j].tipo == 'r' && tablero[i][j].color == jugador) {
				return tablero[i][j].posicion;
			}
		}
	}

	//SI NO SE ENCONTRO//
	error.fila = -1;
	error.columna = -1;
	return error;
}




//COMPRUEBA SI SE HACE JAQUE AL OPONENTE//
int ComprobarJaqueAEnemigo(struct pieza tablero[8][8], char jugador, struct coordenada posiblesMovimientos[MAX]) {
	int i, j, k;	//i j recorren el tablero, k recorre posiblesMovimientos
	struct coordenada posReyEnemigo = BuscarRey(tablero, Cambiar_Jugador(jugador));
	
	//CALCULA SI EL POSIBLE MOVIMIENTO DE ALGUNA PIEZA ALIADA COINCIDE CON LAS COORDENADAS DEL REY-->JAQUE//
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (tablero[i][j].color == jugador && tablero[i][j].tipo!=' ') {	//si es pieza aliada
				Calcular_Posibles_Movimientos(tablero, posiblesMovimientos, tablero[i][j].posicion, jugador);

				for (k = 0; posiblesMovimientos[k].columna != FINCADENA; k++) {
					if ((posiblesMovimientos[k].fila == posReyEnemigo.fila) && (posiblesMovimientos[k].columna == posReyEnemigo.columna)) {
						return 1;
					}
				}
			}
		}
	}
	
	return 0;
}

//EXACTAMENTE IGUAL QUE LA FUNCION ANTERIOR, PERO COMPRUEBA QUE EN TODOS LOS CASOS SEA JAQUE//
int ComprobarJaqueMate(struct pieza tablero[8][8], char jugadorAtacado, struct coordenada posiblesMovimientos[MAX]) {
	int i, j, k, flag=0;
	struct coordenada posReyEnemigo = BuscarRey(tablero, jugadorAtacado);
	struct pieza piezaSource, piezaDestino;	//piezas temporales para no perder info
	struct coordenada movimientosTemp[MAX];

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (tablero[i][j].color == jugadorAtacado && tablero[i][j].tipo != ' ') {	//Si es una pieza aliada
				Calcular_Posibles_Movimientos(tablero, posiblesMovimientos, tablero[i][j].posicion, jugadorAtacado);

				for (k = 0; posiblesMovimientos[k].columna != FINCADENA; k++) {
					//copio las fichas que voy a mover temporalmente para no perder la info
					CopiarPieza(&piezaSource, &tablero[i][j]);
					CopiarPieza(&piezaDestino, &tablero[posiblesMovimientos[k].fila][posiblesMovimientos[k].columna]);

					//hago el movimiento temporal y compruebo que haga jaque. si en alguno no lo hay es que no es mate//
					Mover_Ficha(tablero, tablero[i][j].posicion, posiblesMovimientos, k);
					if (!(ComprobarJaqueAEnemigo(tablero, Cambiar_Jugador(jugadorAtacado), movimientosTemp))) {
						flag = 1;
					}
					//coloco las fichas donde estaban//
					CopiarPieza(&tablero[i][j], &piezaSource);
					CopiarPieza(&tablero[posiblesMovimientos[k].fila][posiblesMovimientos[k].columna], &piezaDestino);

					if (flag == 1)
						return 0;
				}
			}
		}
	}

	return 1;
}


void CopiarPieza(struct pieza *destino, struct pieza *source) {
	destino->tipo = source->tipo;
	destino->color = source->color;
	destino->numero = source->numero;
	destino->posicion.fila = source->posicion.fila;
	destino->posicion.columna = source->posicion.columna;
}

//CUENTA LAS PIEZAS QUE TIENE UN JUGADOR DE UN TIPO
int ContarPiezas(struct pieza tablero[8][8], char jugador, char pieza) {
	int cont = 0, i, j;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (tablero[i][j].tipo == pieza && tablero[i][j].color== jugador) {
				cont++;
			}
		}
	}

	return cont;
}


