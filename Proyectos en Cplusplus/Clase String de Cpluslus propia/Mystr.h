#pragma once
#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <cstring>
using namespace std;

class Mystr
{
private:
	int capacidad;
	char *arr;
public:
	//Operadores
	 bool operator==(Mystr& other);
	 bool operator!=(Mystr& other);
	 bool operator<(Mystr& other);
	 bool operator>(Mystr& other);
	 bool operator<=(Mystr& other);
	 bool operator>=(Mystr& other);
	 char& operator[] (int index);
	 Mystr operator+ (Mystr & other);

	 //Operador extra de asignacion (Si no, los objetos no se asignan correctamente)
	 Mystr& operator= (const Mystr & other);
	
	//Constructores y destructores
	Mystr();
	Mystr(const Mystr &a);
	Mystr(const char *cadena);
	~Mystr();

	//Metodos
	int Capacity();	//Devuelve la capacidad de la memoria reservada
	unsigned int Length();//Tama�o del array de caracteres, sin contar la memoria
	int Replace(char find, char replaceBy); //Busca todos los caracteres iguales a �find� y los sustituye por replaceBy
	int Compare(Mystr & other);	//Devuelve 0 si ambas cadenas son iguales, 1 si la primera cadena es mayor que la de �other�, -1 si la de �other� es mayor que la primera. USA STRCMP
	int Remove(char find);; //Busca todos los caracteres iguales a �find� y los borra. Devuelve el n�mero de caracteres borrados
	Mystr Right(unsigned int num);	//Devuelve la subcadena de �num� caracteres empezando por el final.		
	Mystr Left(unsigned int num); //Devuelve la subadena comprendida entre el inicio y �num�. 
	Mystr Substring(unsigned int initialIndex, unsigned int finalIndex); // Devuelve la subcadena partiendo de initialIndex hasta llegar a finalIndex
	int TrimRight(); //Elimina los espacios en blanco que haya por la derecha del texto. Devuelve el n�mero de espacios eliminados.
	int TrimLeft(); //Elimina los espacios en blanco que haya por la izquierda del texto. Devuelve el n�mero de espacios eliminados.
	int Trim();//Elimina los espacios en blanco en ambos lados del texto. Devuelve el n�mero de espacios eliminados
	int ToUpper();//Convierte todos los caracteres en letras may�sculas. Devuelve el n�mero de caracteres que han sido cambiado
	int ToLower();//Convierte todos los caracteres en letras min�sculas. Devuelve el n�mero de caracteres que han sido cambiado
	bool StartsWith(Mystr& other); //Devuelve true si la cadena empieza con �other�. 
	bool EndsWith(Mystr& other);  //Devuelve true si la cadena termina con �other�. 
	Mystr Concatenate(Mystr& other);//Concatena la cadena a�adiendo �other� de manera consecutiva
	Mystr Introduce(Mystr& other, unsigned int index); //Concatena la cadena introduciendola entre medias, empezando en la posici�n indicada por index

	//Funciones extra
	void PrintMyStr();	//Imprime la cadena
	void DecrementarCapacidad(); //Funcion para gestionar el decremento de capacidad
	char *GetArr();	//devuelve el puntero del array
};