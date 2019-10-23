#pragma once
#include "Nodo.h"

// Clase que representa a una lista enlazada simple. No tiene restricción de tamaño
// Se trata de una lista enlazada de nodos, en donde cada nodo tiene un elemento (un int), y un puntero al siguiente nodo
class ListaEnlazada
{
	// Puntero que apuntará al primer nodo de la lista, o será NULL si la lista está vacía
	Nodo *lista;

	// Numero actual de elementos que tiene la lista
	// Precondición: n>=0
	int n;

	// Posición y puntero del nodo que devolvió la última llamada a getNodo()
	int posicionUltimoNodoAccedido;
	Nodo *punteroUltimoNodoAccedido;

	// Obtiene un nodo de la lista
	// Parámetro: la posición del nodo
	// Retorno: un puntero al nodo que está en dicha posición
	// Precondiciones: 
	// - la posición debe estar en el intervalo [0, n-1]
	// - La lista no esta vacia (n>0)
	// Complejidad temporal: O(n). Como máximo hace n/2 iteraciones porque decide si ir hacia delante o hacia atrás
	// Complejidad espacial: O(1)
	Nodo * getNodo (int posicion);

public:

	// Constructor. Crea una lista de tamaño 0
	// Complejidad temporal y espacial: O(1)
	ListaEnlazada();

	// Devuelve un elemento de la lista en determinada posición
	// Parámetro: la posición del elemento
	// Retorno: una copia del elemento encontrado en esa posición
	// Precondiciones: posicion en [0, n-1] y n>0
	// Complejidad temporal: O(n)
	// Complejidad espacial: O(1)
	Estudiante getValor(int posicion);

	// Modifica un elemento de la lista
	// Parámetros:
	// - posicion: la posición del elemento que queremos modificar
	// - nuevoValor: el nuevo valor del elemento
	// Precondiciones: posicion en [0, n-1] y n>0
	// Complejidad temporal: O(n)
	// Complejidad espacial: O(1)
	void setValor(int posicion, Estudiante nuevoValor);

	// Devuelve el tamaño actual de la lista
	// Complejidad temporal y espacial: O(1)
	int getN(); 

	// Inserta un nuevo elemento en una posición de la lista
	// Los elementos que había desde la posición hasta el final de la lista se desplazarán una posición a la derecha
	// Parámetros:
	// - posición: la posición en donde queremos poner el nuevo elemento. Si es 0 se inserta al principio, si es n se inserta al final
	// - nuevoValor: el nuevo elemento que queremos poner
	// Precondiciones: posicion en [0, n]
	// Complejidad temporal: O(n)
	// Complejidad espacial: O(1)
	void insertar (int posicion, Estudiante nuevoValor);

	// Elimina un elemento en una posición dada.
	// Los elementos que había desde posicion+1 hasta el final de la lista se desplazarán una posición a la izquierda
	// Parámetros:
	// - posicion: la posición del elemento que queremos borrar. Si es 0 se elimina el primero y si es n-1 se elimina el último
	// Precondiciones: posicion en [0, n-1] y n>0
	// Complejidad temporal: O(n)
	// Complejidad espacial: O(1)
	void eliminar (int posicion);

	// Concatena una lista al final de la lista actual
	// Cada uno de los elementos de la lista a concatenar se copian, en orden, al final de la lista actual
	// Parámetro: puntero a la lista cuyos elementos queremos concatenar al final de nuestra lista
	// Precondición: listaAConcatenar!=NULL
	// Complejidad temporal: O(capacidad), siendo capacidad = listaAConcatenar.getN()
	// Complejidad espacial: O(capacidad), siendo capacidad = listaAConcatenar.getN()
	void concatenar(ListaEnlazada *listaAConcatenar);

	// Busca la posición de un elemento en la ListaContigua
	// Parámetro: el elemento a buscar
	// Retorno: posición del elemento (de 0 a n-1) si se encuentra, o -1 en caso contrario
	// Complejidad temporal: O(n)
	// Complejidad espacial: O(1)
	int buscar(Estudiante elementoABuscar);

	// Destructor. Libera memoria
	// Complejidad temporal: O(n)
	~ListaEnlazada();
};







