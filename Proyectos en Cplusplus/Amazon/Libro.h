
#define MAXGENERO 20

class Libro: public Producto {
	//atributos privados//
private:
	char genero[MAXGENERO];
	int paginas;
	bool disponibleEBook;
	//metodos publicos//
public:
	//costructor//
	Libro(const char* titulo, const char *descipcion, float precio);
	//metodos//
	void SetGenero(const char* genero);
	char* GetGenero();
	void SetPaginas(int nPaginas);
	int GetPaginas();
	void SetEBook();
	void SetNoEBook();
	bool GetEBook();

	//metodos virtuales heredados//
	const char *GetTipo();//-------------SE HACE ASI LO DE LAS FUNCIONES VIRTUALES??????
	void Mostrar();
};
