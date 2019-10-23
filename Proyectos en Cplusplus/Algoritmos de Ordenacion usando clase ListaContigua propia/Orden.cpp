#include "Orden.h"

void Orden::swap(ListaContigua* lista, int i, int j) {
	int temp = lista->getValor(i);
	lista->setValor(i, lista->getValor(j));
	lista->setValor(j, temp);
}

bool Orden::esOrdenada(ListaContigua* lista, int orden) {
	assert(orden == ASC || orden == DESC);

	int i;

	if (orden == ASC) {	//Si es ascendente comprueba que el anterior sea menor que el actual. En caso contrario false
		for (i = 1; i < lista->getN(); i++) {
			if (lista->getValor(i - 1) > lista->getValor(i)) return false;
		}
	}
	else { //Si es descendente comprueba que el anterior sea mayor que el actual. En caso contrario false
		for (i = 1; i < lista->getN(); i++) {
			if (lista->getValor(i - 1) < lista->getValor(i)) return false;
		}
	}

	return true;
}

void Orden::insertionSort(ListaContigua * lista, int orden) {	//Nota comprobar asc y desc
	assert(orden == ASC || orden == DESC);

	int i, key, j;

	if (orden == ASC) {
		for (i = 1; i < lista->getN(); i++) {
			key = lista->getValor(i);
			j = i - 1;
			while (j >= 0 && lista->getValor(j) > key) {
				lista->setValor(j + 1, lista->getValor(j));
				j = j - 1;
			}
			lista->setValor(j + 1, key);
		}
	}
	else {
		for (i = 1; i < lista->getN(); i++) {
			key = lista->getValor(i);
			j = i - 1;
			while (j >= 0 && lista->getValor(j) < key) {
				lista->setValor(j + 1, lista->getValor(j));
				j = j - 1;
			}
			lista->setValor(j + 1, key);
		}
	}
}


void Orden::selectionSort(ListaContigua * lista, int orden) {
	assert(orden == ASC || orden == DESC);

	int i, j, idx, temp;

	if (orden == ASC) {
		for (i = 0; i < lista->getN() - 1; i++)
		{
			// busca el elemento mas pequeño en el array  
			idx = i;
			for (j = i + 1; j < lista->getN(); j++)
				if (lista->getValor(j) < lista->getValor(idx))
					idx = j;

			// cambia el elemento mas pequeño por el primer elemento no ordenado 
			swap(lista, idx, i);
		}
	}
	else {
		for (i = 0; i < lista->getN() - 1; i++)
		{
			// busca el elemento mas grande en el array  
			idx = i;
			for (j = i + 1; j < lista->getN(); j++)
				if (lista->getValor(j) > lista->getValor(idx))
					idx = j;

			// cambia el elemento mas pequeño por el primer elemento no ordenado 
			swap(lista, idx, i);
		}
	}

}

void Orden::burbujaSort(ListaContigua * lista, int orden) {		//Nota comprobar asc y desc
	assert(orden == ASC || orden == DESC);
	int i, j, temp;														//Como antes, necesitaremos una variable temporal para hacer el swap
	if (orden == ASC) {
		for (i = 0; i < lista->getN() - 1; i++)
			for (j = 0; j < lista->getN() - i - 1; j++)
				if (lista->getValor(j) > lista->getValor(j + 1)) {		//Comparamos los valores por parejas cambiandolos si se cumple la condicion (mayor o menor que dependiendo del orden)
					swap(lista, j, j + 1);
				}
	}
	else {
		for (i = 0; i < lista->getN() - 1; i++)
			for (j = 0; j < lista->getN() - i - 1; j++)
				if (lista->getValor(j) < lista->getValor(j + 1)) {
					swap(lista, j, j + 1);
				}
	}
}


void Orden::mergeSort(ListaContigua * lista, int orden) {
	assert(orden == ASC || orden == DESC);
	trueMergeSort(lista, 0, lista->getN() - 1, orden);
}

void Orden::divideAndMerge(ListaContigua * lista, int l, int m, int r, int orden) {	//comprobar asc y desc
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));
	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = lista->getValor(l + i);
	for (j = 0; j < n2; j++)
		R[j] = lista->getValor(m + 1 + j);

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (orden == ASC) {
			if (L[i] <= R[j])
			{
				lista->setValor(k, L[i]);
				i++;
			}
			else
			{
				lista->setValor(k, R[j]);
				j++;
			}
			k++;
		}
		else {
			if (L[i] >= R[j])
			{
				lista->setValor(k, L[i]);
				i++;
			}
			else
			{
				lista->setValor(k, R[j]);
				j++;
			}
			k++;
		}
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		lista->setValor(k, L[i]);
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		lista->setValor(k, R[j]);
		j++;
		k++;
	}
}


void Orden::trueMergeSort(ListaContigua * lista, int l, int r, int orden) {
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		trueMergeSort(lista, l, m, orden);
		trueMergeSort(lista, m + 1, r, orden);

		divideAndMerge(lista, l, m, r, orden);
	}
}




void Orden::trueQuickSort(ListaContigua * lista, int left, int right, int orden) {
	int i = left, j = right;

	int tmp;

	int pivot = (lista->getValor(left) + lista->getValor(right)) / 2;

	/* particion */
	while (i <= j) {

		if (orden == ASC) {
			while (lista->getValor(i) < pivot)
				i++;

			while (lista->getValor(j) > pivot)
				j--;
		}
		else {
			while (lista->getValor(i) > pivot)
				i++;

			while (lista->getValor(j) < pivot)
				j--;
		}

		if (i <= j) {
			swap(lista, i, j);
			i++;
			j--;
		}
	}

	if (left < j)
		trueQuickSort(lista, left, j, orden);

	if (i < right)
		trueQuickSort(lista, i, right, orden);
}

int Orden::particion(ListaContigua * lista, int low, int high, int orden) {
	float pivot = (lista->getValor(high) + lista->getValor(low)) / 2;    // pivot 


	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or 
		// equal to pivot 
		if (orden == ASC) {	//si el orden es ascendente
			if (lista->getValor(j) <= pivot)
			{
				i++;    // increment index of smaller element 
				swap(lista, i, j);
			}
		}
		else {	//si el orden es descendente
			if (lista->getValor(j) >= pivot)
			{
				i++;    // increment index of smaller element 
				swap(lista, i, j);
			}
		}
	}
	swap(lista, i + 1, high);
	return (i + 1);

}

void Orden::quickSort(ListaContigua * lista, int orden) {
	assert(orden == ASC || orden == DESC);
	trueQuickSort(lista, 0, lista->getN() - 1, orden);
}



void Orden::rangoSort(ListaContigua * lista, int orden) {
	assert(orden == ASC || orden == DESC);

	int i, j, contador[MAX + 1] = { 0 };	//en c++ se puede inicializar todo a 0 sin necesidad del for



	for (i = 0; i < lista->getN(); i++)
		contador[lista->getValor(i)]++;	 //contamos el n de veces que sale cada numero

	if (orden == ASC) {
		j = 0;
		for (i = 0; i <= MAX; i++) {
			while (contador[i] > 0) {
				lista->setValor(j, i);
				contador[i]--;
				j++;
			}
		}
	}
	else {
		j = 0;
		for (i = MAX; i >= 0; i--) {
			while (contador[i] > 0) {
				lista->setValor(j, i);
				contador[i]--;
				j++;
			}
		}
	}



}

