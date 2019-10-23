#pragma once
#include "Nodo.h"
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define INORDER 0
#define PREORDER 1
#define POSTORDER 2	

class ArbolBinarioDeBusqueda {
private:
	Nodo* raiz; // Raiz del árbol, o NULL si el arbol está vacío
	int n; // Numero de nodos del arbol

	void liberarArbol(Nodo* raizSubarbol);	//Funcion recursiva que se llama desde el destructor para liberar la memoria del arbol

	Nodo* buscarHueco(Nodo* raizSubarbol, int elementoAInsertar);	//Funcion interna para buscar un hueco libre para insertar

	void imprimirRec(Nodo* raizSubarbol, int orden);	//Funcion interna para imprimir recursivamente
public:
	ArbolBinarioDeBusqueda();
	~ArbolBinarioDeBusqueda();

	void imprimirArbol(int metodo);	//Funcion de paso para llamar la impresion desde el main
	void insertar(int nuevoElemento);	//Llama a buscarHueco e inserta donde corresponda
};