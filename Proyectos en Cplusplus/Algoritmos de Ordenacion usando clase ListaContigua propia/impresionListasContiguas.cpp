#include "impresionListasContiguas.h"
#include "iostream"
#include "cassert"
using namespace std;

void imprimirListaContigua(ListaContigua* lista) {
	assert(lista != NULL);

	// Imprimimos tamaño y capacidad
	cout << "n=" << lista->getN() << "|Max=" << lista->getCapacidad() << "|ListaContigua=";

	// Si la ListaContigua está vacía, imprimimos algo especial
	if (lista->getN() == 0) cout << "vacia";

	// Si no está vacía, imprimimos los elementos separados por comas, siempre que no sea demasiado grande
	// Si es demasiado grande, imprimimos un mensaje especial
	else {
		if (lista->getN() > 20) cout << "demasiadosElementosParaMostrar";
		else {
			for (int i = 0; i < lista->getN(); i++) {
				cout << lista->getValor(i);
				if (i < lista->getN() - 1) cout << ","; // Imprimimos "," si no estamos al final
			}
		}
	}
	cout << endl;
}