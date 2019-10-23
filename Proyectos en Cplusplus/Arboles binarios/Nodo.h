#pragma once

// Nodo del árbol binario de búsqueda
struct Nodo {
	int contenido; // Contenido del nodo
	Nodo* padre; // Apunta al padre, o NULL si no tiene
	Nodo* hijoIzquierdo; // Apunta al hijo izquierdo, o NULL si no tiene hijo izquierdo
	Nodo* hijoDerecho; // Apunta al hijo derecho, o NULL si no tiene hijo derecho
};
