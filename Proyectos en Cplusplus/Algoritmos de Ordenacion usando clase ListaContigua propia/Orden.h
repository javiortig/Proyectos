#pragma once
#include "ListaContigua.h"
#include <assert.h>
#include <stdlib.h>
#define ASC 0 // de menor a mayor
#define DESC 1 // de mayor a menor
#define MIN 0 //numero mas pequeño posible
#define MAX 99 //numero mas grande posible

class Orden {
private:
	void swap(ListaContigua *lista, int i, int j);

	void trueQuickSort(ListaContigua* lista, int start, int end, int orden);
	int particion(ListaContigua* lista, int low, int high, int orden);

	void divideAndMerge(ListaContigua* lista, int l, int m, int r, int orden);
	void trueMergeSort(ListaContigua* lista, int l, int r, int orden);
public:
	Orden(){};
	bool esOrdenada(ListaContigua* lista, int orden);
	void insertionSort(ListaContigua* lista, int orden);
	void selectionSort(ListaContigua* lista, int orden);
	void burbujaSort(ListaContigua* lista, int orden);
	void mergeSort(ListaContigua* lista, int orden);
	void quickSort(ListaContigua* lista, int orden);
	void rangoSort(ListaContigua* lista, int orden);
	
};

//ordenación por inserción, por selección, por burbuja, Merge Sort, Quick Sort, Ordenación con Rango.