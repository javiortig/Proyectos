#pragma once
#include "iostream"
#include "ListaContigua.h"

// Imprime una lista contigua por pantalla (su "n", su "capacidad" y sus elementos)
// Par�metros:
// - lista: puntero a la lista contigua que queremos imprimir
// Precondici�n: lista!=NULL
// Complejidad temporal: O(n)
// Complejidad espacial: O(1)
void imprimirListaContigua(ListaContigua* lista);

