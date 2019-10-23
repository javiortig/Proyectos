
#define MAXPLATAFORMA 10


class Videojuego : public Producto {
	//atributos privados//
private:
	char plataforma[MAXPLATAFORMA];
	int jugadores;
	bool vR;

public:
	//constructor//
	Videojuego(const char* titulo, const char *descipcion, float precio);

	//metodos//
	void SetPlataforma(const char *plataforma);
	const char* GetPlataforma();
	void SetJugadores(int jugadores);
	int GetJugadores();
	void SetVR();
	void SetNoVR();
	bool getVR();

	//metodos virtuales heredados//
	const char* GetTipo();
	void Mostrar();
};
