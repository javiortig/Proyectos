#include "Mystr.h"
/*
	Todas las capacidades que deben de multiplicarse lo hacen de este modo:
	obtiene la longitud de la cadena origen + 1(por el '\0') y la multiplica por dos
*/

//Costructores y destructores
Mystr::Mystr()
{
	this->arr = NULL;
	this->capacidad = 0;
}

Mystr::Mystr(const Mystr& other)
{
	this->capacidad = other.capacidad;
	this->arr = (char*)malloc((this->capacidad) * sizeof(char));
	strcpy(this->arr, other.arr);
}

Mystr::Mystr(const char* cadena)
{
	this->capacidad = 2 * (strlen(cadena) + 1);
	this->arr = (char*)malloc(this->capacidad * sizeof(char));
	strcpy(this->arr, cadena);
}

Mystr::~Mystr()
{
	if (this->arr != NULL)
		free(this->arr);
	this->capacidad = 0;
}

//OPERADORES//
//Para definir los operadores en el cpp no se ha usado en comando inline
bool Mystr::operator==(Mystr & other)
{
	return !(this->Compare(other));
}

bool Mystr::operator!=(Mystr & other) {
	return (this->Compare(other));
}

bool Mystr::operator<(Mystr & other) {
	return (this->Compare(other) < 0) ? true : false;
}

bool Mystr::operator>(Mystr & other) {
	return (this->Compare(other) > 0) ? true : false;
}

bool Mystr::operator<=(Mystr & other) {
	return (this->Compare(other) <= 0) ? true : false;
}

bool Mystr::operator>=(Mystr & other) {
	return (this->Compare(other) >= 0) ? true : false;
}

char& Mystr::operator[] (int index) {
	assert(index < this->Length());

	return this->arr[index];
}

Mystr Mystr::operator+ (Mystr & other) {
	return this->Concatenate(other);
}

//operador extra de asignacion, para permitir que los Mystr que se devuelven al main se copien correctamente
Mystr& Mystr::operator= (const Mystr & other) {
	if (&other != this) {
		this->capacidad = other.capacidad;
		this->arr = (char*)malloc((this->capacidad) * sizeof(char));
		strcpy(this->arr, other.arr);
	}
	return *this;
}


int Mystr::Capacity()
{
	return this->capacidad;
}

unsigned int Mystr::Length()
{
	return strlen(this->arr);
}

int Mystr::Replace(char find, char replaceBy)
{
	int k = 0, longi = this->Length();
	for (int i = 0; i < longi; i++)	//Compara que los caracteres sean iguales a find y los reemplaza
		if (this->arr[i] == find) {
			this->arr[i] = replaceBy;
			k++;
		}
	return k;
}

int Mystr::Compare(Mystr & other)
{
	int comp = strcmp(this->arr, other.arr);
	if (comp == 0) return 0;
	else if (comp < 0) return -1;
	else return 1;
}

int Mystr::Remove(char find)
{
	//Borra los caracteres que coincidan con find
	int i, cont = 0, j, longi = this->Length();
	for (i = 0; i <= longi; i++)
		if (this->arr[i] == find) {
			cont++;
			for (j = i; arr[j] != '\0'; j++)
				this->arr[j] = this->arr[j + 1];
			i--;
		}
	this->DecrementarCapacidad();
	return cont;
}

Mystr Mystr::Right(unsigned int num)
{
	Mystr temp;
	temp.arr = (char*)malloc(sizeof(char) * (num + 1) * 2);
	temp.capacidad = (num + 1) * 2;
	int i, j;
	int longi = this->Length();

	//Va copiando con dos indices en temp desde num hasta la longitud
	for (i = longi - num, j = 0; i <= longi; i++, j++) {
		temp.arr[j] = this->arr[i];
	}
	return temp;
}

Mystr Mystr::Left(unsigned int num)
{
	int i;
	Mystr temp;
	temp.arr = (char*)malloc(sizeof(char) * (num + 1) * 2);
	temp.capacidad = (num + 1) * 2;

	//Va copiando en temp hasta llegar al num deseado y por ultimo le añade el \0
	for (i = 0; i <= num; i++) {
		temp.arr[i] = this->arr[i];
	}
	temp.arr[i] = '\0';
	return temp;
}

Mystr Mystr::Substring(unsigned int initialIndex, unsigned int finalIndex) 
{
	assert(finalIndex > initialIndex);
	int i, j;
	Mystr temp;
	int lenght = finalIndex - initialIndex + 1;
	temp.arr = (char*)malloc(2 * (sizeof(char) * (lenght)));
	temp.capacidad = (lenght) * 2;

	//Va copiando desde initial hasta final y por ultimo añade el \0
	for (i = 0, j = initialIndex; j < finalIndex; i++, j++)
		temp.arr[i] = this->arr[j];
	temp.arr[i] = '\0';
	return temp;
}

int Mystr::TrimRight()	//Elimina espacios por la derecha
{
	int i, j, longi = this->Length();
	for (i = longi, j = 0; arr[i] == ' ' && i >= 0; i--, j++) {}
	this->arr[this->Length() - j] = '\0';
	this->DecrementarCapacidad();
	return j;
}

int Mystr::TrimLeft()	//Elimina espacios por la izquierda
{
	int i, j, longi = this->Length();
	for (i = 0; this->arr[i] == ' ' && i < longi; i++) {}	//LLega hasta el primer caracter sin espacions

	for (j = 0; i <= longi; i++, j++) {		//reescribe la cadena sin espacios (\0 incluido)
		this->arr[j] = this->arr[i];
	}
	this->DecrementarCapacidad();
	return i;
}

int Mystr::Trim()	//llama a ambos trim para hacer el trim completo
{
	return this->TrimLeft() + this->TrimRight();
}

int Mystr::ToUpper()
{
	int i, j, longi = this->Length();
	for (i = 0, j = 0; i < longi; i++)	//Detecta todas las letras minusculas y las cambia a mayusculas
		if (this->arr[i] >= 'a' && this->arr[i] <= 'z') {
			this->arr[i] -= 32;
			j++;
		}
	return j;
}

int Mystr::ToLower()
{
	int i, j, longi = this->Length();
	for (i = 0, j = 0; i < longi; i++)//Detecta todas las letras mayusculas y las cambia a minusculas
		if (this->arr[i] >= 'A' && this->arr[i] <= 'Z') {
			this->arr[i] += 32;
			j++;
		}

	return j;
}

bool Mystr::StartsWith(Mystr & other)
{
	int thislenght, otherlenght;
	bool ans;
	thislenght = this->Length();
	otherlenght = other.Length();

	//si esta str es menor siempre va a ser falso, si es igual se puede comprobar con Comp y en el ultimo caso si que hay que comprobarlo con un substring
	if (thislenght < otherlenght)
		ans = false;
	else if (thislenght == otherlenght) {
		if (!(this->Compare(other)))
			ans = true;
		else
			ans = false;
	}
	else {
		Mystr temp;
		temp = this->Substring(0, otherlenght);
		if (!(temp.Compare(other)))
			ans = true;
		else
			ans = false;

	}
	return ans;
}

bool Mystr::EndsWith(Mystr & other)
{
	int thislenght, otherlenght;
	bool ans;
	thislenght = this->Length();
	otherlenght = other.Length();

	//Misma logica que Startswith pero empezando por el final
	if (thislenght < otherlenght)
		ans = false;
	else if (thislenght == otherlenght) {
		if (!(this->Compare(other)))
			ans = true;
		else
			ans = false;
	}
	else {
		Mystr temp;
		temp = this->Substring(thislenght - otherlenght, thislenght);
		if (!(temp.Compare(other)))
			ans = true;
		else
			ans = false;

	}
	return ans;
}

Mystr Mystr::Concatenate(Mystr & other)
{
	int thislength, otherlenght, i, j;
	Mystr temp;
	thislength = this->Length();
	otherlenght = other.Length();
	temp.arr = (char*)malloc((thislength + otherlenght + 1) * 2 * sizeof(char));
	temp.capacidad = (thislength + otherlenght + 1) * 2;

	//Concatena primero la original y posteriormente la str other
	for (i = 0; i < thislength; i++)
		temp.arr[i] = this->arr[i];
	for (j = 0; j <= otherlenght; i++, j++)
		temp.arr[i] = other.arr[j];
	return temp;
}

Mystr Mystr::Introduce(Mystr & other, unsigned int index)
{
	//Mismo proceso que concatenar, pero lo hace empezando por un indice, por lo que necesitara de un bucle extra
	int thislenght, otherlenght, i, j;
	thislenght = this->Length();
	otherlenght = other.Length();
	Mystr temp;
	temp.arr = (char*)malloc((thislenght + otherlenght + 1) * 2 * sizeof(char));
	temp.capacidad = (thislenght + otherlenght + 1) * 2;

	for (i = 0; i < index; i++)
		temp.arr[i] = this->arr[i];

	for (j = 0; j < otherlenght; i++, j++)
		temp.arr[i] = other.arr[j];

	for (j = index; j <= thislenght; i++, j++)
		temp.arr[i] = this->arr[j];

	return temp;
}

void Mystr::PrintMyStr()
{
	std::cout << this->arr << std::endl;
}


void Mystr::DecrementarCapacidad()
{
	int len;
	len = this->Length();
	while (this->capacidad > 4 * len)	//Esto es lo que hemos entendido del enunciado
		this->capacidad /= 2;
	/*if (this->capacidad < len)
		this->capacidad *= 2;*/
	this->arr = (char*)realloc(this->arr, sizeof(char) * capacidad);
}

char* Mystr::GetArr() {	//Simplemente devuelve el puntero del array
	return this->arr;
}

