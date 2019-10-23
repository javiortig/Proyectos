#include "ListaContigua.h"
#include "cassert"
#include "cstdlib" // Para realloc()
#include "cstring" // Para memmove()
using namespace std;

bool ListaContigua::isLlena() {
	return (n == capacidad);
}

ListaContigua::ListaContigua() {
	vector = NULL; // No hay que reservar memoria ya que la ListaContigua se crea vacía en un principio
	n = 0;
	capacidad = 0;
}

ListaContigua::ListaContigua(const ListaContigua & origen) {
	this->capacidad = origen.capacidad;
	this->n = origen.n;

	this->vector = (int*)malloc(this->capacidad * sizeof(int));
	for (int i = 0; i < this->n; i++) {
		this->vector[i] = origen.vector[i];
	}
}

int ListaContigua::getValor(int posicion) {
	assert(posicion >= 0 && posicion <= n - 1);
	return (vector[posicion]);
}

void ListaContigua::setValor(int posicion, int nuevoValor) {
	assert(posicion >= 0 && posicion <= n - 1);
	vector[posicion] = nuevoValor;
}

int ListaContigua::getN() {
	return (n);
}

int ListaContigua::getCapacidad() {
	return (capacidad);
}

void ListaContigua::insertarAlFinal(int nuevoValor) {
	insertar(n, nuevoValor);
}

void ListaContigua::eliminarAlFinal() {
	eliminar(n - 1);
}

void ListaContigua::insertar(int posicion, int nuevoValor) {
	assert(posicion >= 0 && posicion <= n);

	// Si la ListaContigua está ya llena, antes de insertar ampliamos su capacidad en INCREMENTO
	if (isLlena()) {
		vector = (int*)realloc(vector, sizeof(int) * (capacidad + INCREMENTO));
		capacidad += INCREMENTO;
	}

	// Dejamos hueco para el nuevo elemento, desplazando a la derecha los que hay a partir de posicion hasta el final
	memmove(&vector[posicion + 1], &vector[posicion], sizeof(int) * (n - posicion));

	// Metemos el nuevo elemento
	n++;
	setValor(posicion, nuevoValor);
}

void ListaContigua::eliminar(int posicion) {
	assert(posicion >= 0 && posicion <= n - 1);

	// Tapamos el hueco dejado por el elemento eliminado. Para ello, desplazamos a la izquierda los
	// elementos que hay a partir de posicion+1 hasta el final
	memmove(&vector[posicion], &vector[posicion + 1], sizeof(int) * (n - posicion - 1));
	n--;

	// Si la capacidad sobrante es demasiada (2*INCREMENTO), la reducimos en INCREMENTO unidades
	if (capacidad - n == 2 * INCREMENTO) {
		vector = (int*)realloc(vector, sizeof(int) * (capacidad - INCREMENTO));
		capacidad -= INCREMENTO;
	}

}

void ListaContigua::concatenar(ListaContigua * listaAConcatenar) {
	assert(listaAConcatenar != NULL);

	// Tamaño de la lista a concatenar. Por convención, cuando tenemos
	// dos listas, el tamaño de una es "n" y el de la otra es "m"
	int m = listaAConcatenar->getN();

	// Primero vamos a ampliar la capacidad para asegurarnos de que los
	// nuevos elementos quepan. Para curarnos en salud, ampliamos la 
	// capacidad en el tamaño de la listaAConcatenar
	// Complejidad temporal O(n) 
	// Complejidad espacial O(m+n)
	vector = (int*)realloc(vector, sizeof(int) * (capacidad + m));
	capacidad += m;

	// Vamos insertando al final elemento a elemento. Fíjate en que insertar un elemento al final
	// es O(1) si no tenemos que ampliar la capacidad (la cual ya está ampliada)
	// Complejidad temporal O(m)
	// Complejidad espacial O(1)
	for (int i = 0; i < m; i++) {
		insertarAlFinal(listaAConcatenar->getValor(i));
	}
}

int ListaContigua::buscar(int elementoABuscar) {
	int posicion = 0; // Posición actual en donde buscamos
	bool encontrado = false; // Nos indica si hemos encontrado o no el elemento

	// Buscamos el elemento hasta que lo encontremos o hasta que lleguemos al final
	while (!encontrado && posicion < n) {
		if (vector[posicion] == elementoABuscar) encontrado = true;
		posicion++;
	}

	// Devolvemos la posición si lo hemos encontrado, o -1 en caso contrario
	if (encontrado) return (posicion - 1);
	else return (-1);
}


ListaContigua::~ListaContigua() {
	free(vector);
	n = 0;
	capacidad = 0;
}


