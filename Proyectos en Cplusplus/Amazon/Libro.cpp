#include "MainHeader.h"

//metodos libro//

Libro::Libro(const char* titulo, const char *descipcion, float precio) : Producto(titulo, descipcion, precio) {} 
	


void Libro::SetGenero(const char* genero) {
	

	if (strcmp(genero, "Ciencia-Ficcion") != 0 && strcmp(genero, "Aventura") != 0 && strcmp(genero, "Terror") != 0 && strcmp(genero, "Erotica") != 0 && strcmp(genero, "Otra") != 0){
		cout << "ERROR. Formato incorrecto" << endl;
	}
	else {
		strcpy(this->genero, genero);
	}
}

char* Libro::GetGenero() {

	return this->genero;
}

void Libro::SetPaginas(int nPaginas) {
	if (nPaginas > 0) {
		this->paginas = nPaginas;
	}
	else {
		this->paginas = INTERROR;
		cout << "ERROR. Las paginas deben ser mayores que 0" << endl;
	}


}

int Libro::GetPaginas() {

	return	this->paginas;
}

void Libro::SetEBook() {

	this->disponibleEBook = true;
}

void Libro::SetNoEBook() {

	this->disponibleEBook = false;
}

bool Libro::GetEBook() {

	return this->disponibleEBook;
}

//metodos heredados//
const char* Libro::GetTipo() {	//-------------SE HACE ASI LO DE LAS FUNCIONES VIRTUALES??????


	return "Libro";
}

void Libro::Mostrar() {
	cout << "Titulo: " << this->titulo << endl;
	
	if (this->descripcion != NULL) {
		cout << "Descripcion: " << this->descripcion << endl;
	}
	else {
		cout << "SIN DESCRIPCION" << endl;
	}
	cout << this->genero << " - " << this->paginas << " pag" << endl;

	if (this->precio < 0) {
		cout << "???";
	}
	else {
		cout << this->precio;
	}
	if (disponibleEBook == true) {
		cout << "*";
	}
	cout << " Euros" << endl;

	cout << endl;
}

