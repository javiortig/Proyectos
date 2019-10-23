#include "TablaHashDeEstudiantes.h"
#include "ListaEnlazada.h"
#include "cassert"
#include "iostream"
#include "impresionListasEnlazadas.h" // Para el método imprimir de la tabla hash

using namespace std;

int TablaHashDeEstudiantes::obtenerPosicion (int clave, int version) {
	assert (version==0 || version==1);

	int posicion = clave%capacidad; // Posicion original (resto de dividir la clave entre capacidad)
	switch (version) {
	case (0): // Devolvemos la posicion original
		break;
	case (1): // Devolvemos la posición opuesta en la tabla a la original
		posicion += capacidad/2; // La posición opuesta de la tabla estará a capacidad/2 posiciones de distancia
		posicion = posicion%capacidad; // Al sumar capacidad/2 posiciones, hemos de tener en cuenta que el siguiente del último elemento es el primero
		break;
	}
	return (posicion);
}

TablaHashDeEstudiantes::TablaHashDeEstudiantes(int capacidad) {
	assert(capacidad>0);

	// Reservamos memoria para la tabla. Creamos capacidad listas enlazadas vacías
	tabla = new ListaEnlazada[capacidad];

	// Inicializamos los atributos
	this->capacidad = capacidad;
	n = 0;
}

bool TablaHashDeEstudiantes::existeEstudiante (int clave) {
	
	// Datos del estudiante a buscar. Sólo nos importa la clave, por lo tanto no rellenamos el nombre
	Estudiante datosEstudiante;
	datosEstudiante.clave = clave;

	// Buscamos el estudiante en ambas posiciones. En cuanto lo encontremos, retornamos con true
	for (int version=0; version<2; version++) {
		int posicionEnTabla = obtenerPosicion(clave, version);
		if (tabla[posicionEnTabla].buscar(datosEstudiante) != -1) return true;
	}

	// Si llegamos hasta aquí, es que no lo hemos encontrado
	return (false);
}

string TablaHashDeEstudiantes::getEstudiante (int clave) {
	assert(existeEstudiante(clave)); // Precondición: el estudiante debe existir
	
	// Datos del estudiante a buscar. Sólo nos importa la clave, por lo tanto no rellenamos el nombre
	Estudiante datosEstudiante;
	datosEstudiante.clave = clave;

	// Buscamos el estudiante en ambas posiciones. En cuanto lo encontremos, retornamos su nombre
	for (int version=0; version<2; version++) {
		int posicionEnTabla = obtenerPosicion(clave, version);
		int posicionEnLista = tabla[posicionEnTabla].buscar(datosEstudiante);
		if (posicionEnLista != -1) return (tabla[posicionEnTabla].getValor(posicionEnLista).nombre);
	}
}

void TablaHashDeEstudiantes::introducirEstudiante (int clave, string nombre) {
	assert(!existeEstudiante(clave)); // Precondición: el estudiante no existía previamente en la tabla

	// Datos del estudiante a introducir.
	Estudiante datosEstudiante;
	datosEstudiante.clave = clave;
	datosEstudiante.nombre = nombre;

	// Obtenemos las dos posiciones
	int posicion1 = obtenerPosicion(clave,0);
	int posicion2 = obtenerPosicion(clave,1);

	// Metemos en la posición cuya lista enlazada sea más corta
	if (tabla[posicion1].getN() <= tabla[posicion2].getN()) tabla[posicion1].insertar(0, datosEstudiante);
	else tabla[posicion2].insertar(0, datosEstudiante);

	// Incrementamos n
	n++;
}

void TablaHashDeEstudiantes::eliminarEstudiante (int clave) {
	assert(existeEstudiante(clave));
	
	// Datos del estudiante a eliminar. Sólo nos importa la clave, por lo tanto no rellenamos el nombre
	Estudiante datosEstudiante;
	datosEstudiante.clave = clave;

	// Buscamos el estudiante en ambas posiciones. En cuanto lo encontremos, lo eliminamos y retornamos
	for (int version=0; version<2; version++) {
		int posicionEnTabla = obtenerPosicion(clave, version);
		int posicionEnLista = tabla[posicionEnTabla].buscar(datosEstudiante);
		if (posicionEnLista != -1) {
			tabla[posicionEnTabla].eliminar(posicionEnLista);
			n--; // Decrementamos n
			return;
		}
	}
}

void TablaHashDeEstudiantes::imprimir() {
	for (int i=0; i<capacidad; i++) {
		cout << "Posicion " << i << ": ";
		imprimirListaEnlazada(&tabla[i]);
	}
}

TablaHashDeEstudiantes::~TablaHashDeEstudiantes() {
	delete[] tabla;
}
