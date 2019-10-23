#include "iostream"
#include "TablaHashDeEstudiantes.h"

using namespace std;

void main() {

	int capacidad; // Capacidad de la tabla hash
	int opcion; // Opcion de menu introducida por teclado

	cout << "Introduce la capacidad de la tabla: ";
	cin >> capacidad;

	TablaHashDeEstudiantes tabla(capacidad);


	do {
		// Imprimimos el menu y pedimos la opcion
		cout << "0. Salir\n";
		cout << "1. Imprimir tabla\n";
		cout << "2. Comprobar si esta un estudiante\n";
		cout << "3. Ver un estudiante\n";
		cout << "4. Meter un estudiante\n";
		cout << "5. Eliminar un estudiante\n";
		cout << "Introduzca opcion: ";
		cin >> opcion;

		int clave; // Clave para algunas opciones
		string nombre; // Nombre del estudiante para la opcion de meter

		// Gestionamos la opcion
		switch (opcion) {
		case 0:
			break;
		case 1:
			tabla.imprimir();
			break;
		case 2:
			// Comprobar si está un estudiante
			cout << "Introduzca el numero de matricula del estudiante: ";
			cin >> clave;
			if (tabla.existeEstudiante(clave)) cout << "El estudiante SI esta\n";
			else cout << "El estudiante NO esta\n";
			break;
		case 3:
			// Ver un estudiante (obtener su nombre)
			cout << "Introduzca el numero de matricula del estudiante: ";
			cin >> clave;
			cout << "El estudiante se llama " << tabla.getEstudiante(clave) << endl;
			break;
		case 4:
			// Meter un estudiante
			cout << "Introduzca el numero de matricula del estudiante: ";
			cin >> clave;
			cout << "Introduzca el nombre del estudiante: ";
			cin >> nombre;
			tabla.introducirEstudiante(clave, nombre);
			break;
		case 5:
			// Eliminar un estudiante
			cout << "Introduzca el numero de matricula del estudiante: ";
			cin >> clave;
			tabla.eliminarEstudiante(clave);
			break;
		default:
			cout << "Opcion incorrecta\n";
			break;

		} // Fin switch

	} while (opcion != 0); 

}