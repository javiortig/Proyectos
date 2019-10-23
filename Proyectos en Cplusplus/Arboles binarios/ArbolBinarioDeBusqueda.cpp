#include "ArbolBinarioDeBusqueda.h"

ArbolBinarioDeBusqueda::ArbolBinarioDeBusqueda() {	//Crea un arbol vacio
	this->raiz = NULL;
	this->n = 0;
}

ArbolBinarioDeBusqueda::~ArbolBinarioDeBusqueda() {	//libera el arbol por completo
	
	if (this->raiz != NULL)
		liberarArbol(this->raiz);
	this->raiz = NULL;
	this->n = 0;
}

void ArbolBinarioDeBusqueda::liberarArbol(Nodo * raizSubarbol) {
	assert(this->raiz != NULL);

	if (raizSubarbol->hijoIzquierdo != NULL) {
		liberarArbol(raizSubarbol->hijoIzquierdo);
	}
	if (raizSubarbol->hijoDerecho != NULL) {
		liberarArbol(raizSubarbol->hijoDerecho);
	}
	free(raizSubarbol);
}

void ArbolBinarioDeBusqueda::insertar(int nuevoElemento) {
	Nodo* padreTemp;

	this->n++;
	if (this->raiz == NULL) {	//si el arbol esta vacio crea el primer nodo
		padreTemp = new Nodo;
		padreTemp->hijoDerecho = NULL;
		padreTemp->hijoIzquierdo = NULL;
		padreTemp->contenido = nuevoElemento;
		this->raiz = padreTemp;
	}
	else {
		padreTemp = buscarHueco(this->raiz, nuevoElemento);
		if (nuevoElemento < padreTemp->contenido) {	//añade la hoja a la izquierda
			padreTemp->hijoIzquierdo = new Nodo;
			padreTemp->hijoIzquierdo->contenido = nuevoElemento;
			padreTemp->hijoIzquierdo->hijoIzquierdo = NULL;
			padreTemp->hijoIzquierdo->hijoDerecho = NULL;
			padreTemp->hijoIzquierdo->padre = padreTemp;
		}
		else if (nuevoElemento > padreTemp->contenido) {	//añade la hoja a la derecha
			padreTemp->hijoDerecho = new Nodo;
			padreTemp->hijoDerecho->contenido = nuevoElemento;
			padreTemp->hijoDerecho->hijoIzquierdo = NULL;
			padreTemp->hijoDerecho->hijoDerecho = NULL;
			padreTemp->hijoDerecho->padre = padreTemp;
		}
		else {	// Si es igual, no insertará nada
			this->n--;
		}
	}
}

Nodo* ArbolBinarioDeBusqueda::buscarHueco(Nodo * raizSubarbol, int elementoAInsertar) {
	assert(raizSubarbol != NULL);

	if (elementoAInsertar < raizSubarbol->contenido) { // si es menor
		if (raizSubarbol->hijoIzquierdo != NULL)
			return buscarHueco(raizSubarbol->hijoIzquierdo, elementoAInsertar);
		else
			return raizSubarbol;	//Caso Base 1
	}
	else if (elementoAInsertar > raizSubarbol->contenido) { //si es mayor 
		if (raizSubarbol->hijoDerecho != NULL)
			return buscarHueco(raizSubarbol->hijoDerecho, elementoAInsertar);
		else
			return raizSubarbol;	//Caso Base 2
	}
	else {	//si es igual, tiene que evitar meterlo en un sitio diferente, asi que no hará nada
		return raizSubarbol;
	}
}



void ArbolBinarioDeBusqueda::imprimirArbol(int metodo) {	
	assert(metodo == INORDER || metodo == PREORDER || metodo == POSTORDER);

	if (this->raiz != NULL) {
		printf("Tu arbol es: ");
		imprimirRec(this->raiz, metodo);
		printf("\n");
	}
	else
		cout << "Tu Arbol esta vacio" << endl;
}

//Imprime segun el orden descrito
void ArbolBinarioDeBusqueda::imprimirRec(Nodo * raizSubarbol, int orden) {
	if (orden == INORDER) {
		if (raizSubarbol->hijoIzquierdo != NULL) {
			imprimirRec(raizSubarbol->hijoIzquierdo, orden);
		}
		cout << raizSubarbol->contenido << ",";
		if (raizSubarbol->hijoDerecho != NULL) {
			imprimirRec(raizSubarbol->hijoDerecho, orden);
		}
	}
	else if (orden == PREORDER) {
		cout << raizSubarbol->contenido << ",";
		if (raizSubarbol->hijoIzquierdo != NULL) {
			imprimirRec(raizSubarbol->hijoIzquierdo, orden);
		}
		if (raizSubarbol->hijoDerecho != NULL) {
			imprimirRec(raizSubarbol->hijoDerecho, orden);
		}
	}
	else {	//PostOrder
		if (raizSubarbol->hijoIzquierdo != NULL) {
			imprimirRec(raizSubarbol->hijoIzquierdo, orden);
		}
		if (raizSubarbol->hijoDerecho != NULL) {
			imprimirRec(raizSubarbol->hijoDerecho, orden);
		}
		cout << raizSubarbol->contenido << ",";
	}

}

