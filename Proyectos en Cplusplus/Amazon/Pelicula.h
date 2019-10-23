#define MAXFORMATO 10


class Pelicula: public Producto{
	//atributos privados//
private:
	char formato[MAXFORMATO];
	int duracion;
	bool premiada;
	
	
public:
	//constructor//
	Pelicula(const char* titulo, const char *descipcion, float precio);
	//metodos//
	void SetFormato(const char *formato);
	const char* GetFormato();
	void SetDuracion(int duracion);
	int GetDuracion();
	void SetPremiada();
	void SetNoPremiada();
	bool GetPremio();

	//metodos virtuales heredados//
	const char* GetTipo();
	void Mostrar();
};
