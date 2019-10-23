#include "MainHeader.h"


int main() {
	Producto *lista[MAXPRODUCTOS];	//--static_cast <Libro *> (lista[0])->SetEBook();
	int i, nTemp;
	char option;
	float costeTotal = 0;

	//INICIALIZA A NULL
	inicializarNull(lista);


	//PIDE LOS OBJETOS
	pedirProductos(lista);

	do {
		system("CLS");
		cout << "Bienvenido al menu. Elija entre las distintas opciones:" << endl;
		cout << "Ordenar por precio: 'p'" << endl;
		cout << "Obtener los productos de una categoria: 'o'" << endl;
		cout << "Ordenar una categoria por precio: 'c'" << endl;
		cout << "Mostrar libros de Ciencia-Ficcion con mas de 1000 paginas: 'f'" << endl;
		cout << "Mostrar peliculas en BluRay que han sido premiadas: 'b'" << endl;
		cout << "Mostrar juegos de PS4 con VR 'v'" << endl;
		//FUNCIONES EXTRAS AL EJERCICIO//
		cout << "Busqueda por titulo: 't'" << endl;
		cout << "Busqueda por debajo de un precio: 'l'" << endl;
		cout << "A" << (char)164 << "adir al carrito de la compra: 'a'" << endl;
		cout << "Mostrar coste total del carrito de la compra: 's'"<< endl;
		cout << "Para salir: 'e'" << endl;
		cin >> option;
		switch (option) {
		case 'p':
			OrdenarPorPrecio(lista);
			break;
		case 'o':
			ObtenerPorCategoria(lista);
			break;
		case 'c':
			OrdenarCategoriaPrecio(lista);
			break;
		case 'f':
			MostrarCienciaFiccion100(lista);
			break;
		case 'b':
			MostrarBluRayPremiadas(lista);
			break;
		case 'v':
			MostrarPS4conVR(lista);
			break;
		case 't':
			BuscarPorTitulo(lista);
			break;
		case 'l':
			BuscarPorDebajoDe(lista);
			break;
		case 'a':
			costeTotal +=AniadirAlCarrito(lista);
			break;
		case 's':
			cout << "En total, todos sus productos suman " << costeTotal << " Euros" << endl;
			system("pause");
			break;
		default:
			break;
		}
	} while (option != 'e');

	nTemp = lista[0]->n_productos;
	//liberar memoria
	for (i = 0; i<nTemp; i++) {
		delete lista[i];
	}
	return 0;
}