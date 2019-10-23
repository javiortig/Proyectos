#include "ListaEnlazada.h"
#include "cassert"
using namespace std;

Nodo * ListaEnlazada::getNodo (int posicion) {
	assert(n > 0);
	assert(posicion >= 0 && posicion <= n-1);

	Nodo *resultado = NULL; // Aquí guardaremos el puntero al nodo resultado 
	
	// Si el nodo que queremos buscar es igual que el último accedido
	if (posicion == posicionUltimoNodoAccedido && posicionUltimoNodoAccedido!=-1) 
		resultado=punteroUltimoNodoAccedido;

	// Si el nodo que queremos buscar es el siguiente al último accedido
	else if (posicion == posicionUltimoNodoAccedido+1 && posicionUltimoNodoAccedido != -1) {
		resultado = punteroUltimoNodoAccedido->siguienteNodo;
	}

	// Si el nodo que queremos buscar es el anterior al último accedido
	else if (posicion == posicionUltimoNodoAccedido - 1 && posicionUltimoNodoAccedido != -1) {
		resultado = punteroUltimoNodoAccedido->anteriorNodo;
	}

	// Si el nodo no es contiguo al ultimo accedido, y se llega antes a él iterando hacia delante	
	else if (posicion <= n / 2) {
		resultado = lista; // Hacemos que el resultado apunte al primer nodo
		for (int i = 0; i < posicion; i++) resultado = resultado->siguienteNodo;
	}

	// Si el nodo no es contiguo al ultimo accedido, y se llega antes a él iterando hacia atrás	
	else {
		resultado = lista->anteriorNodo; // Hacemos que el resultado apunte al último nodo
		for (int i = n-1; i > posicion; i--) 
			resultado = resultado->anteriorNodo;
	}

	// Actualizamos los atributos del ultimo nodo accedido
	posicionUltimoNodoAccedido = posicion;
	punteroUltimoNodoAccedido = resultado;

	return (resultado);
}

ListaEnlazada::ListaEnlazada() {
	lista = NULL; 
	n=0;
	posicionUltimoNodoAccedido = -1; // -1 significa que no se ha accedido aun a ninguno
	punteroUltimoNodoAccedido = NULL; // NULL significa que no se ha accedido aun a ninguno
}

Estudiante ListaEnlazada::getValor(int posicion) {
	assert(n > 0);
	assert (posicion >= 0 && posicion <= n-1); 
	// Obtenemos el nodo que contiene el elemento
	Nodo *nodoQueContieneResultado = getNodo (posicion);
	return (nodoQueContieneResultado->elemento);
}

void ListaEnlazada::setValor(int posicion, Estudiante nuevoValor) {
	assert(n > 0);
	assert (posicion >= 0 && posicion <= n-1); 
	getNodo(posicion)->elemento = nuevoValor;
}

int ListaEnlazada::getN() {
	return (n);
}

void ListaEnlazada::insertar (int posicion, Estudiante nuevoValor) {
	assert (posicion >= 0 && posicion <= n); 

	// Creamos el nuevo nodo con el nuevo valor
	Nodo *nuevoNodo = new Nodo;
	nuevoNodo->elemento = nuevoValor;

	// Si la lista estaba vacia...
	if (n==0) {
		nuevoNodo->siguienteNodo = nuevoNodo;
		nuevoNodo->anteriorNodo = nuevoNodo;
	}

	// Si la lista no está vacía
	else {
		// Primero obtenemos el nodo que está a continuación del que queremos insertar
		// Nota que, si queremos insertar al final, su siguiente es el primero
		Nodo *nodoSiguiente; // Nodo a continuación del que queremos insertar
		if (posicion == n) nodoSiguiente = lista;
		else nodoSiguiente = getNodo(posicion);

		// Obtenemos el nodo anterior al que queremos insertar
		// Tengamos cuidado en hacerlo en O(1)
		Nodo *nodoAnterior = nodoSiguiente->anteriorNodo;

		// Actualizamos los punteros del nuevo nodo
		nuevoNodo->anteriorNodo=nodoAnterior;
		nuevoNodo->siguienteNodo=nodoSiguiente;

		// Actualizamos los punteros de los dos nodos que rodean al nuevo nodo
		// El puntero siguiente del anterior y el puntero anterior del siguiente apuntarán ambos al nuevo nodo
		nodoSiguiente->anteriorNodo=nuevoNodo;
		nodoAnterior->siguienteNodo=nuevoNodo;
	} // Fin else
	
	// Si estamos insertando al principio de la lista, hay que modificar el puntero a la lista
	if (posicion == 0) lista = nuevoNodo;

	// Incrementamos el numero de elementos
	n++;

	// Como hemos cambiado la configuracion de la lista, reseteamos el ultimo nodo accedido
	posicionUltimoNodoAccedido = -1; // -1 significa que no se ha accedido aun a ninguno
	punteroUltimoNodoAccedido = NULL; // NULL significa que no se ha accedido aun a ninguno
}


void ListaEnlazada::eliminar (int posicion) {
	assert(n > 0);
	assert (posicion >= 0 && posicion <= n-1); 

	// Obtenemos el nodo que queremos eliminar
	Nodo *nodoAEliminar = getNodo(posicion);

	// Si la lista sólo tiene un elemento, actualizamos el atributo lista pues la lista se queda vacia
	if (n == 1) lista = NULL;

	// Si la lista tiene más de un elemento, hacemos el caso general
	else {

		// Obtenemos los dos nodos que le rodean
		Nodo *nodoAnterior = nodoAEliminar->anteriorNodo;
		Nodo *nodoSiguiente = nodoAEliminar->siguienteNodo;
		
		// Modificamos los punteros de cada uno de los dos nodos que rodean al que queremos eliminar
		nodoAnterior->siguienteNodo=nodoSiguiente;
		nodoSiguiente->anteriorNodo=nodoAnterior;
		
		// Si el nodo a eliminar era el 0, tenemos que actualizar el atributo lista
		if (posicion == 0) lista = nodoSiguiente;
	} // Fin else

	// Liberamos la memoria del nodo
	delete(nodoAEliminar);

	// Actualizamos n
	n--;

	// Como hemos cambiado la configuracion de la lista, reseteamos el ultimo nodo accedido
	posicionUltimoNodoAccedido = -1; // -1 significa que no se ha accedido aun a ninguno
	punteroUltimoNodoAccedido = NULL; // NULL significa que no se ha accedido aun a ninguno
}

void ListaEnlazada::concatenar(ListaEnlazada *listaAConcatenar) {
	assert(listaAConcatenar != NULL);

	// Tamaño de la lista a concatenar. Por convención, cuando tenemos
	// dos listas, el tamaño de una es "n" y el de la otra es "capacidad"
	int capacidad = listaAConcatenar->getN();

	// Vamos insertando al final elemento a elemento. Fíjate en que insertar un elemento al final
	// es O(1) porque la lista es circular, y por lo tanto podemos acceder al ultimo nodo en O(1)
	// si hemos hecho bien getNodo()
	// - Complejidad temporal O(capacidad). Las sucesivas llamadas a listaAConcatenar->getValor(i) son O(1)
	//   porque getNodo() recuerda el último nodo accedido
	// - Complejidad espacial O(capacidad), porque creamos capacidad nodos nuevos
	for (int i = 0; i < capacidad; i++) {
		Estudiante elementoACopiar = listaAConcatenar->getValor(i);
		insertar(n, elementoACopiar);
	}
}

int ListaEnlazada::buscar(Estudiante elementoABuscar) {
	int posicion = 0; // Posición actual en donde buscamos
	bool encontrado = false; // Nos indica si hemos encontrado o no el elemento

	// Buscamos el elemento (por su clave) hasta que lo encontremos o hasta que lleguemos al final
	while (!encontrado && posicion < n) {
		// Cada llamada a getValor() es O(1) porque getNodo() recuerda el último nodo accedido
		if (getValor(posicion).clave == elementoABuscar.clave) encontrado = true;
		posicion++;
	}

	// Devolvemos la posición si lo hemos encontrado, o -1 en caso contrario
	if (encontrado) return (posicion - 1);
	else return (-1);
}

ListaEnlazada::~ListaEnlazada() {
	// Eliminamos el primer elemento de la lista. Esta operación la repetimos n veces
	// Eliminar el primer elemento de la lista es O(1)
	while (n>0) eliminar(0);
}



