#pragma once
#include "string"
#include "ListaEnlazada.h"

using namespace std;

// Tabla hash que guarda los nombres de los estudiantes de una universidad. Utiliza dispersión abierta
// para resolver colisiones.
class TablaHashDeEstudiantes
{

protected:

	int capacidad; // Capacidad de la tabla. Permanece invariante a lo largo de la vida del objeto
	int n; // Numero actual de elementos de la tabla. Puede ser mayor que capacidad

	ListaEnlazada *tabla; // La tabla hash será un vector de listas enlazadas

	// Método de hashing (tenemos dos versiones). 
	// Parámetros: 
	// - clave: la clave del estudiante (es su número de matrícula)
	// - version: 0 ó 1 según el método de hashing que queramos ejecutar. 
	//   Si es 0, devuelve el resto de dividir la clave entre capacidad. Si es 1, devuelve su simétrico en la tabla.
	// Retorno: la posición donde el estudiante debería estar o ponerse en la tabla hash
	// Precondición: version es 0 ó 1
	// Complejidad temporal y espacial en todos los casos: O(1)
	int obtenerPosicion (int clave, int version);

public:

	// Constructor
	// Parámetro: la capacidad (capacidad) de la lista
	// Precondición: capacidad > 0
	// Complejidad temporal: O(capacidad) en todos los casos (porque "new" llama al constructor de todos las listas)
	// Complejidad espacial: O(capacidad) en todos los casos (porque reservamos memoria para capacidad listas)
	TablaHashDeEstudiantes(int capacidad);

	// Comprueba si un estudiante está o no en la tabla hash
	// Parámetro: la clave del estudiante
	// Retorno: true si está, false si no
	// Complejidad temporal: O(1) en mejor caso, O(n) en peor caso
	// Complejidad espacial: O(1) en todos los casos
	bool existeEstudiante (int clave);

	// Obtiene un estudiante (su nombre) a partir de su clave
	// Parámetro: la clave del estudiante
	// Retorno: el nombre del estudiante
	// Precondición: el estudiante debe estar en la tabla hash
	// Complejidad temporal: O(1) en mejor caso, O(n) en peor caso
	// Complejidad espacial: O(1) en todos los casos
	string getEstudiante (int clave);

	// Inserta un estudiante en la tabla
	// Parámetros:
	// - clave: el número de matrícula del estudiante
	// - estudiante: el nombre del estudiante
	// Precondición: el estudiante no existe en la tabla hash
	// Complejidad espacial y temporal: O(1) en todos los casos
	void introducirEstudiante (int clave, string estudiante);

	// Elimina un estudiante de la tabla
	// Parámetro: la clave del estudiante a eliminar
	// Precondición: el estudiante debe estar en la tabla hash
	// Complejidad temporal: O(1) en mejor caso, O(n) en peor caso
	// Complejidad espacial: O(1) en todos los casos
	void eliminarEstudiante (int clave);

	// Imprime toda la tabla hash
	// Complejidad temporal:
	// - O(capacidad) en el mejor caso (tabla vacia)
	// - O(n+capacidad) en el peor (los n elementos en una única posición de la tabla)
	//   Por la regla de la suma, O(n+capacidad) será igual a O(capacidad) ó O(n) dependiendo de si capacidad es mayor o menor que n respectivamente
	// Complejidad espacial: O(1) en todos los casos
	void imprimir();

	// Destructor
	// Complejidad: al destruir la tabla, también se llama a los destructores de cada lista, 
	// así pues la complejidad es igual que en imprimir
	~TablaHashDeEstudiantes();

};

