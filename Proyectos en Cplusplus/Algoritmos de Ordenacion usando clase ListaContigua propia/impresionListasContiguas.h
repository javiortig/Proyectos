#pragma once
#include "iostream"
#include "ListaContigua.h"

// Imprime una lista contigua por pantalla (su "n", su "capacidad" y sus elementos)
// Parámetros:
// - lista: puntero a la lista contigua que queremos imprimir
// Precondición: lista!=NULL
// Complejidad temporal: O(n)
// Complejidad espacial: O(1)
void imprimirListaContigua(ListaContigua* lista);

