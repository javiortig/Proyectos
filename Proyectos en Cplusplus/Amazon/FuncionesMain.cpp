#include "MainHeader.h"

void inicializarNull(Producto *lista[MAXPRODUCTOS]) {
	int i;
	for (i = 0; i < MAXPRODUCTOS; i++)
		lista[i] = NULL;
}

void pedirProductos(Producto *lista[MAXPRODUCTOS]) {
	int i = 0, numTemp;
	float precioTemp;
	bool boolTemp;
	char opcionMain = '1', opcionTipo;
	char descripcionTemp[MAXDESCRIPCION], formatoTemp[MAXFORMATO], tituloTemp[MAXTITULO];

	do {
		system("CLS");
		cout << "Producto n" << (char)167 << " " << i + 1 << endl;
		//datos de producto
		do {
			cout << "Tipo de producto: Libro='l', pelicula='p', videojuego = 'v'" << endl;
			cin >> opcionTipo;
			if (opcionTipo != 'l' && opcionTipo != 'p' && opcionTipo != 'v')
				cout << "ERROR. Introduzca un tipo valido";
		} while (opcionTipo != 'l' && opcionTipo != 'p' && opcionTipo != 'v');

		cout << "Nombre:" << endl;
		getchar();
		cin.getline(tituloTemp, MAXTITULO);
		cout << "Descripcion:" << endl;
		cin.getline(descripcionTemp, MAXDESCRIPCION);
		do {
			cout << "Precio:" << endl;
			cin >> precioTemp;
			if (precioTemp < 0) cout << "ERROR. Precio no valido" << endl;

		} while (precioTemp < 0);

		//switch que crea un tipo de producto segun la eleccion
		switch (opcionTipo) {
			//caso libro
		case 'l':
			lista[i] = new Libro(tituloTemp, descripcionTemp, precioTemp);
			getchar();
			do {
				cout << "Genero:" << endl;
				cin.getline(formatoTemp, MAXFORMATO);
				static_cast <Libro *> (lista[i])->SetGenero(formatoTemp);
			} while (strcmp(formatoTemp, "Ciencia-Ficcion") != 0 && strcmp(formatoTemp, "Aventura") != 0 && strcmp(formatoTemp, "Terror") != 0 && strcmp(formatoTemp, "Erotica") != 0 && strcmp(formatoTemp, "Otra") != 0);

			do {
				cout << "Numero de paginas:" << endl;
				cin >> numTemp;
				static_cast <Libro *> (lista[i])->SetPaginas(numTemp);
			} while (numTemp <= 0);

			cout << "Disponible en E-Book? '1' Si, '0' No:" << endl;
			cin >> boolTemp;
			if (boolTemp) static_cast <Libro *> (lista[i])->SetEBook();
			else static_cast <Libro *> (lista[i])->SetNoEBook();

			break;
			//caso pelicula
		case 'p':
			lista[i] = new Pelicula(tituloTemp, descripcionTemp, precioTemp);

			getchar();
			do {
				cout << "Formato:" << endl;
				cin.getline(formatoTemp, MAXFORMATO);
				static_cast <Pelicula *> (lista[i])->SetFormato(formatoTemp);
			} while ((strcmp(formatoTemp, "BluRay") != 0 && strcmp(formatoTemp, "DVD") != 0));

			do {
				cout << "Duracion:" << endl;
				cin >> numTemp;
				static_cast <Pelicula *> (lista[i])->SetDuracion(numTemp);
			} while (numTemp <= 0);

			cout << "Ha sido premiada? '1' Si, '0' No:" << endl;
			cin >> boolTemp;
			if (boolTemp) static_cast <Pelicula *> (lista[i])->SetPremiada();
			else static_cast <Pelicula *> (lista[i])->SetNoPremiada();

			break;
			//caso videojuego
		case 'v':
			lista[i] = new Videojuego(tituloTemp, descripcionTemp, precioTemp);

			getchar();
			do {
				cout << "Plataforma:" << endl;
				cin.getline(formatoTemp, MAXFORMATO);
				static_cast <Videojuego *> (lista[i])->SetPlataforma(formatoTemp);
			} while (strcmp(formatoTemp, "PC") != 0 && strcmp(formatoTemp, "PS4") != 0 && strcmp(formatoTemp, "XBOXOne") != 0 && strcmp(formatoTemp, "WiiU") != 0 && strcmp(formatoTemp, "Nintendo3DS") != 0 && strcmp(formatoTemp, "Otra") != 0);

			do {
				cout << "Maximo de jugadores?:" << endl;
				cin >> numTemp;
				static_cast <Videojuego *> (lista[i])->SetJugadores(numTemp);
			} while (numTemp <= 0);

			cout << "Tiene VR? '1' Si, '0' No:" << endl;
			cin >> boolTemp;
			if (boolTemp) static_cast <Videojuego *> (lista[i])->SetVR();
			else static_cast <Videojuego *> (lista[i])->SetNoVR();

			break;

		default:
			cout << "FATAL ERROR. Por favor, contacte con el soporte" << endl;
		}

		if (i >= 4 && i < MAXPRODUCTOS) {	
			cout << "Si quieres colocar otro producto pulsa '1', en caso contrario pulsa otra tecla" << endl;
			cin >> opcionMain;
		}

		i++;
	} while (opcionMain == '1' && i < MAXPRODUCTOS);
}


void ImprimirLista(Producto *lista[MAXPRODUCTOS]) {
	int i;
	system("CLS");
	for (i = 0; i < lista[0]->n_productos; i++) {
		lista[i]->Mostrar();
		cout << endl;
	}
}


void OrdenarPorPrecio(Producto *lista[MAXPRODUCTOS]) {
	int i, j;
	Producto *aux;
	Producto *listaTemp[MAXPRODUCTOS];

	for (i = 0; i < lista[0]->n_productos; i++) {
		listaTemp[i] = lista[i];
	}

	for (i = 0; i < lista[0]->n_productos; i++) {
		for (j = i + 1; j < lista[0]->n_productos; j++) {
			if (listaTemp[j]->GetPrecio() < listaTemp[i]->GetPrecio()) {
				aux = listaTemp[j];
				listaTemp[j] = listaTemp[i];
				listaTemp[i] = aux;
			}
		}
	}

	ImprimirLista(listaTemp);
	system("pause");
}


void ObtenerPorCategoria(Producto *lista[MAXPRODUCTOS]) {
	char opcion;
	int i;
	system("CLS");
	cout << "Elija: Libros='l', Peliculas='p' Videojuegos='v'" << endl;
	cin >> opcion;

	for (i = 0; i < lista[0]->n_productos; i++) {
		switch (opcion) {
		case 'l':
			if (strcmp("Libro", lista[i]->GetTipo()) == 0)
				lista[i]->Mostrar();
			break;

		case 'p':
			if (strcmp("Pelicula", lista[i]->GetTipo()) == 0)
				lista[i]->Mostrar();
			break;

		case 'v':
			if (strcmp("Videojuego", lista[i]->GetTipo()) == 0)
				lista[i]->Mostrar();
			break;

		default:
			break;
		}
	}
	system("pause");
}

void OrdenarCategoriaPrecio(Producto *lista[MAXPRODUCTOS]) {
	char opcion;
	int i, j;
	Producto *aux;
	Producto *listaTemp[MAXPRODUCTOS];

	for (i = 0; i < lista[0]->n_productos; i++) {
		listaTemp[i] = lista[i];
	}

	for (i = 0; i < lista[0]->n_productos; i++) {
		for (j = i + 1; j < lista[0]->n_productos; j++) {
			if (listaTemp[j]->GetPrecio() < listaTemp[i]->GetPrecio()) {
				aux = listaTemp[j];
				listaTemp[j] = listaTemp[i];
				listaTemp[i] = aux;
			}
		}
	}

	system("CLS");
	cout << "Elija: Libros='l', Peliculas='p' Videojuegos='v'" << endl;
	cin >> opcion;

	for (i = 0; i < lista[0]->n_productos; i++) {
		switch (opcion) {
		case 'l':
			if (strcmp("Libro", listaTemp[i]->GetTipo()) == 0)
				listaTemp[i]->Mostrar();
			break;

		case 'p':
			if (strcmp("Pelicula", listaTemp[i]->GetTipo()) == 0)
				listaTemp[i]->Mostrar();
			break;

		case 'v':
			if (strcmp("Videojuego", listaTemp[i]->GetTipo()) == 0)
				listaTemp[i]->Mostrar();
			break;

		default:
			break;
		}
	}
	system("pause");
}

void MostrarCienciaFiccion100(Producto *lista[MAXPRODUCTOS]) {
	int i;
	bool flag = false;
	system("CLS");
	for (i = 0; i < lista[0]->n_productos; i++) {
		if (strcmp("Libro", lista[i]->GetTipo()) == 0) {
			if (static_cast <Libro *> (lista[i])->GetPaginas() > 100 && strcmp("Ciencia-Ficcion", static_cast <Libro *> (lista[i])->GetGenero()) == 0) {
				lista[i]->Mostrar();
				flag = true;
			}
		}
	}

	if (!flag) {
		cout << "No se han encontrado libros de este tipo" << endl;
	}
	system("pause");
}

void MostrarBluRayPremiadas(Producto *lista[MAXPRODUCTOS]) {
	int i;
	bool flag = false;
	system("CLS");
	for (i = 0; i < lista[0]->n_productos; i++) {
		if (strcmp("Pelicula", lista[i]->GetTipo()) == 0) {
			if (static_cast <Pelicula *> (lista[i])->GetPremio() && strcmp("BluRay", static_cast <Pelicula *> (lista[i])->GetFormato()) == 0) {
				lista[i]->Mostrar();
				flag = true;
			}
		}
	}

	if (!flag) {
		cout << "No se ha encontrado peliculas de este tipo" << endl;
	}
	system("pause");
}

void MostrarPS4conVR(Producto *lista[MAXPRODUCTOS]) {
	int i;
	bool flag = false;
	system("CLS");
	for (i = 0; i < lista[0]->n_productos; i++) {
		if (strcmp("Videojuego", lista[i]->GetTipo()) == 0) {
			if (static_cast <Videojuego *> (lista[i])->getVR() && strcmp("PS4", static_cast <Videojuego *> (lista[i])->GetPlataforma()) == 0) {
				lista[i]->Mostrar();
				flag = true;
			}
		}
	}

	if (!flag) {
		cout << "No se ha encontrado juegos con estas caracteristicas" << endl;
	}
	system("pause");
}

void BuscarPorTitulo(Producto *lista[MAXPRODUCTOS]) {
	int i;
	bool flag = false;
	char tituloTemp[MAXTITULO];
	cout << "Introduzca el titulo del producto a buscar:" << endl;
	getchar();
	cin.getline(tituloTemp, MAXFORMATO);
	for (i = 0; i < lista[0]->n_productos; i++) {
		if (strcmp(tituloTemp, lista[i]->GetTitulo()) == 0) {
			lista[i]->Mostrar();
			flag = true;
		}
	}

	if (!flag) {
		cout << "No se ha encontrado el titulo introducido" << endl;
	}
	system("pause");
}

void BuscarPorDebajoDe(Producto *lista[MAXPRODUCTOS]) {
	int i, precioTemp;
	bool flag = false;

	cout << "Introduce el precio maximo de los productos a mostrar:" << endl;
	cin >> precioTemp;
	for (i = 0; i < lista[0]->n_productos; i++) {
		if (lista[i]->GetPrecio() <= precioTemp) {
			lista[i]->Mostrar();
			flag = true;
		}
	}

	if (!flag) {
		cout << "No se ha encontrado productos por debajo de ese precio" << endl;
	}
	system("pause");
}

float AniadirAlCarrito(Producto *lista[MAXPRODUCTOS]) {
	int i;
	bool flag = false;
	char tituloTemp[MAXTITULO];
	cout << "Introduzca el titulo del producto para meter en el carrito:" << endl;
	getchar();
	cin.getline(tituloTemp, MAXFORMATO);
	for (i = 0; i < lista[0]->n_productos; i++) {
		if (strcmp(tituloTemp, lista[i]->GetTitulo()) == 0) {
			cout << "Producto aniadido al carrito" << endl;
			system("pause");
			return lista[i]->GetPrecio();
		}
	}

	if (!flag) {
		cout << "No se ha encontrado el titulo introducido" << endl;
	}
	system("pause");
}
