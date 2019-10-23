#include "MainHeader.h"


Pelicula::Pelicula(const char* titulo, const char *descipcion, float precio) : Producto(titulo, descipcion, precio) {}





void Pelicula::SetFormato(const char *formato) {
	if (strcmp(formato, "BluRay")!=0 && strcmp(formato, "DVD") != 0) {
		cout << "ERROR. Introduzca un formato adecuado" << endl;
	}
	else {
		strcpy(this->formato, formato);
	}
}

const char* Pelicula::GetFormato(){	
	if (!this->formato) {
		return "ERROR";
	}
	else {
		return this->formato;
	}
	
}

void Pelicula::SetDuracion(int duracion) {
	if (duracion > 0) {
		this->duracion = duracion;
	}
	else {
		this->duracion = INTERROR;
		cout << "ERROR. Numero no valido" << endl;
	}
 }

int Pelicula::GetDuracion() {
	return this->duracion;
}

void Pelicula::SetPremiada() {
	this->premiada = true;
}

void Pelicula::SetNoPremiada() {
	this->premiada = false;
}

bool Pelicula::GetPremio() {
	return premiada;
}

const char* Pelicula::GetTipo() {	


	return "Pelicula";
}

void Pelicula::Mostrar() {
	cout << "Titulo: " << this->titulo;
	if (this->premiada) {
		cout << "*";
	}
	cout << endl;

	if (this->descripcion != NULL) {
		cout << "Descripcion: " << this->descripcion << endl;
	}
	else {
		cout << "SIN DESCRIPCION" << endl;
	}

	cout << "Duracion: ";
	if (this->duracion > 0) {
		cout << this->duracion << " min";
	}
	else {
		cout << "DESCONOCIDA";
	}
	cout << endl;

	if (strcmp(this->formato, "BluRay") != 0 && strcmp(this->formato, "DVD") != 0) {
		cout << "Sin formato" << endl;
	}
	else {
		cout << this->formato;
	}
	cout << " - ";
	if (this->precio < 0) {
		cout << "???";
	}
	else {
		cout << this->precio;
	}
	cout << " Euros" << endl;
	cout << endl;
}

