#pragma once

// Numero de posiciones en que se incrementa/decrementa la capacidad de la ListaContigua cada vez que es necesario
// Precondici�n: INCREMENTO >= 1
#define INCREMENTO 2

// Clase que representa a una lista contigua en memoria y cuya capacidad se redimensiona autom�ticamente
// de modo que el usuario no tiene que preocuparse por su capacidad
class ListaContigua
{
	// Puntero que apuntar� a la zona de memoria en donde empieza la ListaContigua
	int* vector;

	// Numero actual de elementos que tiene la ListaContigua
	// Precondici�n: n>=0
	int n;

	// Capacidad actual de la ListaContigua
	// Precondiciones: capacidad >= n
	int capacidad;

	// Nos dice si la ListaContigua est� llena o no.
	// Retorno: verdadero si est� llena, falso si no est� llena
	// Complejidad temporal y espacial: O(1)
	bool isLlena();

public:

	ListaContigua();
	ListaContigua(const ListaContigua &origen);
	int getValor(int posicion);
	void setValor(int posicion, int nuevoValor);
	int getN();
	int getCapacidad();
	void insertarAlFinal(int nuevoValor);
	void eliminarAlFinal();
	void insertar(int posicion, int nuevoValor);
	void eliminar(int posicion);
	void concatenar(ListaContigua* listaAConcatenar);
	int buscar(int elementoABuscar);
	~ListaContigua();
};