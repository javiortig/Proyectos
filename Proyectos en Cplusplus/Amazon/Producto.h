#define MAXTITULO 50
#define INTERROR -999

using namespace std;

class Producto {
protected:
	char titulo[MAXTITULO];
	char *descripcion;
	float precio;



public:
	static int n_productos;
	//constructores y destructores//
	Producto();
	Producto(const char* titulo, const char *descipcion, float precio);
	~Producto();
	//metodos//
	void SetPrecio(float valor);
	float GetPrecio();
	const char* GetTitulo();
	const char* GetDescripcion();

	//metodos virtuales puros//
	virtual const char* GetTipo() = 0;
	virtual void Mostrar() = 0;

};

