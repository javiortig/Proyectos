/*
	Autores: Javier Borrel y Javier Orti.
	Muy parecido al algoritmo del ejercicio dos, pero devuelve un booleano al main
*/


#include <iostream>
#include <Windows.h>

#define TAMSUDOKU 9
#define VACIO -1

using namespace std;

void ImprimirTablero(int tablero[TAMSUDOKU][TAMSUDOKU]) {
	int i, j, contI, contJ;

	system("CLS");
	//borde superior
	cout << (char)201;
	for (j = 0; j < TAMSUDOKU; j++)
		cout << (char)205;
	cout << (char)187 << endl;

	//tablero principal y bordes laterales
	for (i = 0; i < TAMSUDOKU; i++) {
		cout << (char)186;
		for (j = 0; j < TAMSUDOKU; j++) {
			if (tablero[i][j] != VACIO)
				cout << tablero[i][j];
			else
				cout << " ";
		}
		cout << (char)186 << endl;
	}

	//borde inferior
	cout << (char)200;
	for (j = 0; j < TAMSUDOKU; j++)
		cout << (char)205;
	cout << (char)188 << endl;

	cout << endl;
}

//Comprueba si la casilla y el valor recibiddo es valido  para el tablero
bool esValido(int sudoku[TAMSUDOKU][TAMSUDOKU], int fila, int columna, int valor) {
	int i, j;

	if (valor <1 || valor>TAMSUDOKU) return false;	//si no es un valor correcto
	for (i = 0; i < TAMSUDOKU; i++) {
		if (i != fila && sudoku[i][columna] == valor) return false; //para evitar comparar con la casilla misma
	}
	for (j = 0; j < TAMSUDOKU; j++) {
		if (j!= columna && sudoku[fila][j] == valor) return false;	//para evitar comparar con la casilla misma
	}
	int despFila = (fila / 3) * 3; //despFila y despColumna se ultilizan para comprobar los cuadrados de 3x3 que correspondan a la casilla que estamos comprobando
	int despColumna = (columna / 3) * 3;
	for (int i = despFila; i < despFila + 3; i++) {
		for (j = despColumna; j < despColumna + 3; j++) {
			if (i!=fila && j !=columna && sudoku[i][j] == valor) return false;
		}
	}
	return true;
}

//Comprueba si sudoku inicial es valido o ya no tiene solucion, antes de entrar a la funcion recursiva a intentar resolverlo
bool ComprobarSudokuInicial(int sudoku[TAMSUDOKU][TAMSUDOKU]) {
	int i, j;

	for (i = 0; i < TAMSUDOKU; i++) {
		for (j = 0; j < TAMSUDOKU; j++) {
			if (sudoku[i][j] != VACIO && !esValido(sudoku, i, j, sudoku[i][j]))
				return false;	//si encuentra un numero no valido, da false
		}
	}

	return true;
}

//Este es el algoritmo recursivo que resuelve el sudoku
bool recurSudoku(int sudoku[TAMSUDOKU][TAMSUDOKU], int i, int j) {
	int valor = 1;

	//condicion para moverse por la matriz, asi si recibe j=10 se resetea la columna y avanza una fila
	if (j == TAMSUDOKU) {
		i++;
		j = 0;
	}
	//Si la casilla ya estaba llena, es que ya era valida (porque venia en el sudoku antes de empezar)
	

	//Caso base: es igual que el recursivo, pero para la ultima casilla
	if (i == TAMSUDOKU - 1 && j == TAMSUDOKU - 1) {
		if (sudoku[i][j] != VACIO)
			return true;
		else {
			do {
				sudoku[i][j] = valor;
				if (esValido(sudoku, i, j, valor)) {
					return true;
				}
				else
					sudoku[i][j] = VACIO;

				valor++;
			} while (valor <= TAMSUDOKU);
		}
	}
	//Caso recursivo
	else {
		if (sudoku[i][j] != VACIO) {		//estas condiciones hay que separarlas ya que si no el programa borra las casillas que venian rellenas por defecto
			if (recurSudoku(sudoku, i, j + 1))
				return true;
		}
		else {
			do {
				sudoku[i][j] = valor;
				if (esValido(sudoku, i, j, valor) && recurSudoku(sudoku, i, j + 1)) {	//si lo que he colocado es valido, y me devuelven true, devuelvo true. sino lo borro
					return true;
				}
				else
					sudoku[i][j] = VACIO;

				valor++;
			} while (valor <= TAMSUDOKU);
		}
	}

	return false;	//si nada sirvio, devuelve false
}

bool resolverSudoku(int sudoku[TAMSUDOKU][TAMSUDOKU]) {
	if (ComprobarSudokuInicial(sudoku) && recurSudoku(sudoku, 0, 0))
		return true;	//Hace falta la primera funcion para comprobar algunos casos de tableros sin solucion
	else
		return false;
};

int main() {
	int sudoku[TAMSUDOKU][TAMSUDOKU];
	int i, j, valor;

	//rellena de VACIO EL SUDOKU
	for (i = 0; i < TAMSUDOKU; i++)
		for (j = 0; j < TAMSUDOKU; j++)
			sudoku[i][j] = VACIO;

	//pide los numeros iniciales del sudoku, 0 0 0 para salir
	do {
		ImprimirTablero(sudoku);
		cout << "Introduzca el indice (El indice empieza en 1) y por ultimo lugar el valor (introduzca  0 0 0 para salir):" << endl;
		cin >> i >> j >> valor;
		i--;
		j--;
		if (i != -1 || j != -1 || valor != 0) {	//caso de salida
			if (i < 0 || i >= TAMSUDOKU || j < 0 || j >= TAMSUDOKU || sudoku[i][j] != VACIO || !esValido(sudoku, i, j, valor)) {	//si no entra en el tablero o no es valida la jugada, lo impide
				cout << "ERROR. CASILLA INVALIDA. PRUEBE DE NUEVO" << endl;
				Sleep(1500);
			}
			else {
				sudoku[i][j] = valor;
			}
		}
	} while (i != -1 || j != -1 || valor != 0);	// se sale cuando escriba 0 0 0
	

	if (resolverSudoku(sudoku)) {
		ImprimirTablero(sudoku);
		cout << "Aqui tienes tu sudoku resuelto" << endl;
	}
	else {
		cout << "El sudoku no tiene solucion" << endl;
	}

	return 0;
}