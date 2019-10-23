#pragma once
#include "Estudiante.h"

// Estructura que representa un nodo de una lista enlazada
struct Nodo
{
	Estudiante elemento; // El elemento que guarda el nodo
	Nodo *anteriorNodo; // Puntero al nodo anterior de la lista enlazada
	Nodo *siguienteNodo; // Puntero al siguiente nodo de la lista enlazada
};

