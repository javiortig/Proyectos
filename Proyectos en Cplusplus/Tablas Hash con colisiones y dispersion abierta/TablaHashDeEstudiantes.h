#pragma once
#include "string"
#include "ListaEnlazada.h"

using namespace std;

// Tabla hash que guarda los nombres de los estudiantes de una universidad. Utiliza dispersi�n abierta
// para resolver colisiones.
class TablaHashDeEstudiantes
{

protected:

	int capacidad; // Capacidad de la tabla. Permanece invariante a lo largo de la vida del objeto
	int n; // Numero actual de elementos de la tabla. Puede ser mayor que capacidad

	ListaEnlazada *tabla; // La tabla hash ser� un vector de listas enlazadas

	// M�todo de hashing (tenemos dos versiones). 
	// Par�metros: 
	// - clave: la clave del estudiante (es su n�mero de matr�cula)
	// - version: 0 � 1 seg�n el m�todo de hashing que queramos ejecutar. 
	//   Si es 0, devuelve el resto de dividir la clave entre capacidad. Si es 1, devuelve su sim�trico en la tabla.
	// Retorno: la posici�n donde el estudiante deber�a estar o ponerse en la tabla hash
	// Precondici�n: version es 0 � 1
	// Complejidad temporal y espacial en todos los casos: O(1)
	int obtenerPosicion (int clave, int version);

public:

	// Constructor
	// Par�metro: la capacidad (capacidad) de la lista
	// Precondici�n: capacidad > 0
	// Complejidad temporal: O(capacidad) en todos los casos (porque "new" llama al constructor de todos las listas)
	// Complejidad espacial: O(capacidad) en todos los casos (porque reservamos memoria para capacidad listas)
	TablaHashDeEstudiantes(int capacidad);

	// Comprueba si un estudiante est� o no en la tabla hash
	// Par�metro: la clave del estudiante
	// Retorno: true si est�, false si no
	// Complejidad temporal: O(1) en mejor caso, O(n) en peor caso
	// Complejidad espacial: O(1) en todos los casos
	bool existeEstudiante (int clave);

	// Obtiene un estudiante (su nombre) a partir de su clave
	// Par�metro: la clave del estudiante
	// Retorno: el nombre del estudiante
	// Precondici�n: el estudiante debe estar en la tabla hash
	// Complejidad temporal: O(1) en mejor caso, O(n) en peor caso
	// Complejidad espacial: O(1) en todos los casos
	string getEstudiante (int clave);

	// Inserta un estudiante en la tabla
	// Par�metros:
	// - clave: el n�mero de matr�cula del estudiante
	// - estudiante: el nombre del estudiante
	// Precondici�n: el estudiante no existe en la tabla hash
	// Complejidad espacial y temporal: O(1) en todos los casos
	void introducirEstudiante (int clave, string estudiante);

	// Elimina un estudiante de la tabla
	// Par�metro: la clave del estudiante a eliminar
	// Precondici�n: el estudiante debe estar en la tabla hash
	// Complejidad temporal: O(1) en mejor caso, O(n) en peor caso
	// Complejidad espacial: O(1) en todos los casos
	void eliminarEstudiante (int clave);

	// Imprime toda la tabla hash
	// Complejidad temporal:
	// - O(capacidad) en el mejor caso (tabla vacia)
	// - O(n+capacidad) en el peor (los n elementos en una �nica posici�n de la tabla)
	//   Por la regla de la suma, O(n+capacidad) ser� igual a O(capacidad) � O(n) dependiendo de si capacidad es mayor o menor que n respectivamente
	// Complejidad espacial: O(1) en todos los casos
	void imprimir();

	// Destructor
	// Complejidad: al destruir la tabla, tambi�n se llama a los destructores de cada lista, 
	// as� pues la complejidad es igual que en imprimir
	~TablaHashDeEstudiantes();

};

