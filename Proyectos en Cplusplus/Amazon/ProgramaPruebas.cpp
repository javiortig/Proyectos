/*#include "MainHeader.h"



void PeliculaFunc() {
	Pelicula *peliculaTemp;
	char descripcionTemp[999], formatoTemp[100], tituloTemp[MAXTITULO];
	float precioTemp, num;
	

	cout << "Nombre:"<< endl;
	getchar();
	cin.getline(tituloTemp, MAXTITULO);
	cout << "Descripcion:" << endl;
	cin.getline(descripcionTemp, 999);
	cout << "Cuanto cuesta?" << endl;
	cin >> precioTemp;

	peliculaTemp = new Pelicula(tituloTemp, descripcionTemp, precioTemp);

	cout << "Cual es su formato?" << endl;
	getchar();
	cin.getline(formatoTemp, 100);
	peliculaTemp->SetFormato(formatoTemp);

	cout << "Tiene premio? '1' para SI, '0' para NO" << endl;
	cin >> num;
	if (num) {
		peliculaTemp->SetPremiada();
	} 
	else {
		peliculaTemp->SetNoPremiada();
	}

	cout << "Cuanto dura?" << endl;
	cin >> num;
	peliculaTemp->SetDuracion(num);


	cout << "Quieres cambiar su precio? '1' para SI, '0' para NO" << endl;
	cin >> num;
	if (num) {
		cout << "Cuanto cuesta?" << endl;
		cin >> precioTemp;
		peliculaTemp->SetPrecio(precioTemp);
	}
	
	system("CLS");
	cout << "Metodo Mostrar:" << endl;
	peliculaTemp->Mostrar();

	cout << endl << endl;
	cout << "El resto de metodos de Pelicula(clase heredada) y su clase base (Producto):" << endl;
	cout << peliculaTemp->GetTitulo();
	if (peliculaTemp->GetPremio()) {
		cout << "*";
	}
	cout << endl;
	cout << peliculaTemp->GetDescripcion() << endl;
	cout << peliculaTemp->GetFormato() << " - " << peliculaTemp->GetDuracion() << " min" << endl;
	cout << peliculaTemp->GetPrecio() << " Euros";
	cout << endl;
	cout << "Tipo de producto: " << peliculaTemp->GetTipo() << endl;
	cout << endl;

	

	system("pause");
}

void VideojuegoFunc() {
	Videojuego *videojuegoTemp;
	char descripcionTemp[999], plataformaTemp[100], tituloTemp[MAXTITULO];
	float precioTemp, num;


	cout << "Nombre:" << endl;
	getchar();
	cin.getline(tituloTemp, MAXTITULO);
	cout << "Descripcion:" << endl;
	cin.getline(descripcionTemp, 999);
	cout << "Cuanto cuesta?" << endl;
	cin >> precioTemp;

	videojuegoTemp = new Videojuego(tituloTemp, descripcionTemp, precioTemp);

	cout << "Cual es su plataforma?" << endl;
	getchar();
	cin.getline(plataformaTemp, 100);
	videojuegoTemp->SetPlataforma(plataformaTemp);

	cout << "Tiene VR? '1' para SI, '0' para NO" << endl;
	cin >> num;
	if (num) {
		videojuegoTemp->SetVR();
	}
	else {
		videojuegoTemp->SetNoVR();
	}

	cout << "Cuantos jugadores maximo?" << endl;
	cin >> num;
	videojuegoTemp->SetJugadores(num);


	cout << "Quieres cambiar su precio? '1' para SI, '0' para NO" << endl;
	cin >> num;
	if (num) {
		cout << "Cuanto cuesta?" << endl;
		cin >> precioTemp;
		videojuegoTemp->SetPrecio(precioTemp);
	}

	system("CLS");
	cout << "Metodo Mostrar:" << endl;
	videojuegoTemp->Mostrar();

	cout << endl << endl;

	cout << "El resto de metodos de Videjuego(clase heredada) y su clase base (Producto):" << endl;
	cout << videojuegoTemp->GetTitulo();
	cout << endl;
	cout << videojuegoTemp->GetDescripcion() << endl;
	cout << videojuegoTemp->GetPlataforma() << " - " << videojuegoTemp->GetJugadores() << " jugadores" << endl;
	cout << videojuegoTemp->GetPrecio() << " Euros";
	cout << endl;
	cout << "Tipo de producto: " << videojuegoTemp->GetTipo() << endl;
	if (videojuegoTemp->getVR()) {
		cout << "Disfrutelo con VR";
	}
	


	system("pause");

}

void LibroFunc() {
	Libro *libroTemp;
	char descripcionTemp[999], generoTemp[100], tituloTemp[MAXTITULO];
	float precioTemp, num;


	cout << "Nombre:" << endl;
	getchar();
	cin.getline(tituloTemp, MAXTITULO);
	cout << "Descripcion:" << endl;
	cin.getline(descripcionTemp, 999);
	cout << "Cuanto cuesta?" << endl;
	cin >> precioTemp;

	libroTemp = new Libro(tituloTemp, descripcionTemp, precioTemp);

	cout << "Cual es su formato?" << endl;
	getchar();
	cin.getline(generoTemp, 100);
	libroTemp->SetGenero(generoTemp);

	cout << "Disponible en E-Book? '1' para SI, '0' para NO" << endl;
	cin >> num;
	if (num) {
		libroTemp->SetEBook();
	}
	else {
		libroTemp->SetNoEBook();
	}

	cout << "Cuantas paginas tiene?" << endl;
	cin >> num;
	libroTemp->SetPaginas(num);


	cout << "Quieres cambiar su precio? '1' para SI, '0' para NO" << endl;
	cin >> num;
	if (num) {
		cout << "Cuanto cuesta?" << endl;
		cin >> precioTemp;
		libroTemp->SetPrecio(precioTemp);
	}

	system("CLS");
	cout << "Metodo Mostrar:" << endl;
	libroTemp->Mostrar();

	cout << endl << endl;
	cout << "El resto de metodos de Pelicula(clase heredada) y su clase base (Producto):" << endl;
	cout << libroTemp->GetTitulo();
	cout << endl;
	cout << libroTemp->GetDescripcion() << endl;
	cout << libroTemp->GetGenero() << " - " << libroTemp->GetPaginas() << " pag" << endl;
	cout << libroTemp->GetPrecio() << " Euros";
	if (libroTemp->GetEBook()) {
		cout << "*";
	}
	cout << endl;
	cout << "Tipo de producto: " << libroTemp->GetTipo() << endl;
	cout << endl;



	system("pause");
}


int main() {
	char opcion;
	do {
		system("CLS");
		cout << "Bienvenido al programa de prueba, pulse:" << endl;
		cout << "'1': Pelicula" << endl << "'2': Videojuego" << endl << "'3': Libro" << endl << "'0': Salir" << endl;
		cin >> opcion;
		system("CLS");
		switch (opcion) {
		case '1':
			PeliculaFunc();
			break;
		case '2':
			VideojuegoFunc();
			break;
		case '3':
			LibroFunc();
			break;
		default:
			break;
		}

	} while (opcion != '0');
	


	return 0;
}

*/