/*
	Autores: Javier Borrel y Javier Orti.
	Si el programa tiene solucion, esta se imprimira con flechas para indicar el camino que ha seguido
*/
//ORDEN A SEGUIR: ARRIBA DERECHA ABAJO IZQUIERDA

#include <iostream>
#include <Windows.h>

#define VACIA ' '
#define LLENA 178
#define INICIO 'I'
#define FIN 'F'
#define VISITADO '.'
#define ARRIBA '^'
#define DERECHA '>'
#define IZQUIERDA '<'
#define ABAJO 'V'

using namespace std;


//Comprueba que las casilla de las coordenadas que recibe sea valida
bool EsValida(char **tablero, int i, int j, int n, int m) {
	if (i < 0 || i >= n || j < 0 || j >= m)
		return false;
	else if (tablero[i][j] != VACIA && tablero[i][j] != INICIO && tablero[i][j] != FIN)	//colocamos las comprobaciones de la matriz las ultimas para evitar errores de acceso a memoria no reservada
		return false;					
	else
		return true;

}

void ImprimirTablero(char **tablero, int n, int m) {
	int i, j;
	
	system("CLS");
	//borde superior
	cout << (char)201;
	for (j = 0; j < m; j++)
		cout << (char)205;
	cout << (char)187 << endl;

	//tablero principal y bordes laterales
	for (i = 0; i < n; i++) {
		cout << (char)186;
		for (j = 0; j < m; j++) {
			cout << tablero[i][j];
		}
		cout << (char)186 << endl;
	}

	//borde inferior
	cout << (char)200;
	for (j = 0; j < m; j++)
		cout << (char)205;
	cout << (char)188 << endl;

	cout << endl;
}

//La funcion comprueba si la casilla en la que se encuentra es valida, y en caso afirmativo se llama a si misma por orden probando las 4 posibilades
bool Buscar(char **tablero, int n, int m, int i, int j, char direccion) {
	if (EsValida(tablero, i, j, n, m)) {
		if (tablero[i][j] == FIN)
			return true;
		else {
			switch (direccion)
			{
			case ARRIBA:
				tablero[i][j] = ARRIBA;
				break;
			case DERECHA:
				tablero[i][j] = DERECHA;
				break;
			case ABAJO:
				tablero[i][j] = ABAJO;
				break;
			case IZQUIERDA:
				tablero[i][j] = IZQUIERDA;
				break;
			default:
				break;
			}

			if (Buscar(tablero, n, m, i - 1, j, ARRIBA))			//Arriba
				return true;
			else if (Buscar(tablero, n, m, i, j + 1, DERECHA))		//Derecha
				return true;
			else if (Buscar(tablero, n, m, i + 1, j, ABAJO))		//Abajo
				return true;
			else if (Buscar(tablero, n, m, i, j - 1, IZQUIERDA))		//Izquierda
				return true;
			else
				tablero[i][j] = VACIA;	//Si nada de lo anterior ha servido, vacia la casilla.
			
		}
	}

	return false;
}

int main() {
	char **tablero = NULL;
	int n, m, inicioX, inicioY, finX, finY, i, j;	//X para filas, Y para columnas

	//pide el tamaño del tablero
	do {
		cout << "Introduzca el numero de filas del tablero: ";
		cin >> n;
		if (n <= 1)
			cout << "ERROR" << endl;
	} while (n <= 1);
	do {
		cout << "Introduzca el numero de columnas del tablero: ";
		cin >> m;
		if (m <= 1)
			cout << "ERROR" << endl;
	} while (m <= 1);

	//crea el tablero y lo rellena
	tablero = (char**)malloc(n * sizeof(char*));
	for (i = 0; i < n; i++) {
		tablero[i] = (char*)malloc(m * sizeof(char));
		for (j = 0; j < m; j++)
			tablero[i][j] = VACIA;
	}

	//Pide las casillas bloqueadas (con muro)
	do {
		ImprimirTablero(tablero, n, m);
		cout << "Introduzca un numero base y su indice (Numeros entre 1-9, introduzca 0 0 para salir):" << endl;
		cin >> i >> j;
		i--;
		j--;
		if (i != -1 && j != -1) {	//caso de salida
			if (!EsValida(tablero, i, j, n, m)) {
				cout << "ERROR. CASILLA INVALIDA. PRUEBE DE NUEVO" << endl;
				Sleep(1500);
			}
			else
				tablero[i][j] = LLENA;
		}
		
	} while (i != -1 && j != -1);	// se sale cuando escriba 0 0

	//Pide las coordenadas del inicio
	do {
		ImprimirTablero(tablero, n, m);
		cout << "Introduzca las coordenadas del inicio" << endl;
		cin >> inicioX >> inicioY;
		inicioX--;
		inicioY--;
		if (!EsValida(tablero, inicioX, inicioY, n, m)) {
			cout << "ERROR. CASILLA INVALIDA. PRUEBE DE NUEVO" << endl;
			Sleep(2000);
		}
			
	} while (!EsValida(tablero, inicioX, inicioY, n, m));
	tablero[inicioX][inicioY] = INICIO;

	//Pide las coordenadas del final
	do {
		ImprimirTablero(tablero, n, m);
		cout << "Introduzca las coordenadas del final" << endl;
		cin >> finX >> finY;
		finX--;
		finY--;
		if (!EsValida(tablero, finX, finY, n, m)) {
			cout << "ERROR. CASILLA INVALIDA. PRUEBE DE NUEVO" << endl;
			Sleep(2000);
		}
			
	} while (!EsValida(tablero, finX, finY, n, m));
	tablero[finX][finY] = FIN;
	ImprimirTablero(tablero, n, m);

	cout << "Calculando soluciones..." << endl;

	//LLama a la funcion recursiva. Si tiene solucion imprime la solucion, y en caso contrario avisa que no tiene solucion
	if (Buscar(tablero, n, m, inicioX, inicioY, '.')) {
		tablero[inicioX][inicioY] = INICIO;	//para que se imprima el inicio, puesto que a veces la funcion recursiva lo borra
		tablero[finX][finY] = FIN;
		ImprimirTablero(tablero, n, m);
	}
	else {
		cout << "El tablero no tiene solucion" << endl;
	}

	for (i = 0; i < n; i++)	//libera  la memoria utilizada por el tablero
		free(tablero[i]);
	free(tablero);

	return 0;
}