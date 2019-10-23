#include "MainHeader.h"

Videojuego::Videojuego(const char* titulo, const char *descipcion, float precio) : Producto(titulo, descipcion, precio) {}

void Videojuego::SetPlataforma(const char *plataforma) {
	if (strcmp(plataforma, "PC") != 0 && strcmp(plataforma, "PS4") != 0 && strcmp(plataforma, "XBOXOne") != 0 && strcmp(plataforma, "WiiU") != 0 && strcmp(plataforma, "Nintendo3DS") != 0 && strcmp(plataforma, "Otra") != 0) {
		cout << "ERROR. Introduzca una plataforma valida" << endl;
	}
	else {
		strcpy(this->plataforma, plataforma);
	}
}

const char* Videojuego::GetPlataforma() {
	if (!this->plataforma) {
		return "ERROR";
	}
	else {
		return this->plataforma;
	}
	
}

void Videojuego::SetJugadores(int jugadores) {
	if (jugadores > 0) {
		this->jugadores = jugadores;
	}
	else {
		this->jugadores = INTERROR;
		cout << "ERROR. Introduzca un valor valido" << endl;
	}
}

int Videojuego::GetJugadores() {
	return this->jugadores;
}

void Videojuego::SetVR() {
	this->vR = true;
}

void Videojuego::SetNoVR() {
	this->vR = false;
}

bool Videojuego::getVR() {
	return this->vR;
}



const char* Videojuego::GetTipo() {


	return "Videojuego";
}

void Videojuego::Mostrar() {
	cout << "Titulo: "<< this->titulo;
	cout << endl;

	if (this->descripcion != NULL) {
		cout << "Descripcion: "<< this->descripcion << endl;
	}
	else {
		cout << "SIN DESCRIPCION" << endl;
	}

	cout << "Jugadores: ";
	if (this->jugadores > 0) {
		cout << this->jugadores;
	}
	else {
		cout << "SIN DATOS";
	}
	cout << endl;

	cout << "Plataforma: ";
	if (strcmp(this->plataforma, "PC") != 0 && strcmp(this->plataforma, "PS4") != 0 && strcmp(this->plataforma, "XBOXOne") != 0 && strcmp(this->plataforma, "WiiU") != 0 && strcmp(this->plataforma, "Nintendo3DS") != 0 && strcmp(this->plataforma, "Otra") != 0) {
		cout << "DESCONOCIDA" << endl;
	}
	else {
		cout << this->plataforma;
	}
	cout << " - ";
	if (this->precio < 0) {
		cout << "???";
	}
	else {
		cout << this->precio;
	}
	cout << " Euros" << endl;

	if (this->vR) {
		cout << "Disfrutalo con VR" << endl;
	}

	cout << endl;
}
