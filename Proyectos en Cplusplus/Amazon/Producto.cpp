#include "MainHeader.h"

int Producto::n_productos=0;

Producto::Producto() {
	strcpy(titulo, "VACIO");
	this->descripcion = NULL;
	precio = -1;


	n_productos++;
}

Producto::Producto(const char* titulo, const char *descipcion, float precio) {	//---not sure
	strcpy(this->titulo, titulo);
	this->precio = precio;

	this->descripcion = new char[strlen(descipcion)+1];	

	strcpy(this->descripcion, descipcion);

	n_productos++;
}

Producto::~Producto() {
	if (descripcion != NULL) {
		delete[] this->descripcion;
	}
	
	n_productos--;
}

void Producto::SetPrecio(float valor) {
	

	if (valor < 0) {
		cout << "ERROR. El precio no puede ser un valor negativo." << endl;
	}
	else {
		this->precio = valor;
	}
	
}

float Producto::GetPrecio() {
	if(this->precio < 0)
		cout << "ERROR" << endl;
	
	return this->precio;
}

const char* Producto::GetTitulo() {
	return this->titulo;
}

const char* Producto::GetDescripcion() {
	return this->descripcion;
}

