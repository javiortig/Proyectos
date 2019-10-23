/*Trabajo realizado por Javier Borrel Weber y Javier Orti García*/

#include <stdio.h>
#include <time.h>
#include "Orden.h"
#include "impresionListasContiguas.h"

using namespace std;

//ordenación por inserción, por selección, por burbuja, Merge Sort, Quick Sort, Ordenación con Rango.
//el Rando de numeros esta entre 0(MIN) y 99(MAX)

int main() {
	int tam;
	float numeroClicksInicio, numeroClicksFin, segundosTranscurridos;
	ListaContigua listaInsercion;
	Orden ordenador;

	cout << "Introduzca el tamanio de la lista" << endl;
	cin >> tam;
	srand(time(NULL));

	for(int i = 0; i < tam; i++){
		listaInsercion.insertarAlFinal(rand()%(MAX + 1));
	}

	ListaContigua listaSeleccion(listaInsercion);
	ListaContigua listaBurbuja(listaInsercion);
	ListaContigua listaMerge(listaInsercion);
	ListaContigua listaQuick(listaInsercion);
	ListaContigua listaRango(listaInsercion);
	{
		//INSERCION
		// ordenar ascendente
		numeroClicksInicio = clock();
		ordenador.insertionSort(&listaInsercion, ASC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por insercion en caso general he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaInsercion);
		if (ordenador.esOrdenada(&listaInsercion, ASC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
		// volver a ordenar ascendente
		numeroClicksInicio = clock();
		ordenador.insertionSort(&listaInsercion, ASC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por insercion en mejor caso he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaInsercion);
		if (ordenador.esOrdenada(&listaInsercion, ASC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
		// ordenar descendente
		numeroClicksInicio = clock();
		ordenador.insertionSort(&listaInsercion, DESC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por insercion en peor caso he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaInsercion);
		if (ordenador.esOrdenada(&listaInsercion, DESC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
	}
	printf("\n\n");
	{
		//SELECCION
		// ordenar ascendente
		numeroClicksInicio = clock();
		ordenador.selectionSort(&listaSeleccion, ASC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por seleccion en caso general he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaSeleccion);
		if (ordenador.esOrdenada(&listaSeleccion, ASC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
		// volver a ordenar ascendente
		numeroClicksInicio = clock();
		ordenador.selectionSort(&listaSeleccion, ASC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por seleccion en mejor caso he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaSeleccion);
		if (ordenador.esOrdenada(&listaSeleccion, ASC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
		// ordenar descendente
		numeroClicksInicio = clock();
		ordenador.selectionSort(&listaSeleccion, DESC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por seleccion en peor caso he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaSeleccion);
		if (ordenador.esOrdenada(&listaSeleccion, DESC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
	}
	printf("\n\n");
	{
		//BURBUJA
		// ordenar ascendente
		numeroClicksInicio = clock();
		ordenador.burbujaSort(&listaBurbuja, ASC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por burbuja en caso general he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaBurbuja);
		if (ordenador.esOrdenada(&listaBurbuja, ASC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
		// volver a ordenar ascendente
		numeroClicksInicio = clock();
		ordenador.burbujaSort(&listaBurbuja, ASC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por burbuja en mejor caso he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaBurbuja);
		if (ordenador.esOrdenada(&listaBurbuja, ASC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
		// ordenar descendente
		numeroClicksInicio = clock();
		ordenador.burbujaSort(&listaBurbuja, DESC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por burbuja en peor caso he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaBurbuja);
		if (ordenador.esOrdenada(&listaBurbuja, DESC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
	}
	printf("\n\n");
	{
		//MERGE
		// ordenar ascendente
		numeroClicksInicio = clock();
    	ordenador.mergeSort(&listaMerge, ASC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por merge en caso general he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaMerge);
		if (ordenador.esOrdenada(&listaMerge, ASC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
		// volver a ordenar ascendente
		numeroClicksInicio = clock();
		ordenador.mergeSort(&listaMerge, ASC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por merge en mejor caso he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaMerge);
		if (ordenador.esOrdenada(&listaMerge, ASC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
		// ordenar descendente
		numeroClicksInicio = clock();
		ordenador.mergeSort(&listaMerge, DESC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por merge en peor caso he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaMerge);
		if (ordenador.esOrdenada(&listaMerge, DESC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
	}
	printf("\n\n");
	{
		//QUICK
		// ordenar ascendente
		numeroClicksInicio = clock();
		ordenador.quickSort(&listaQuick, ASC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por quick en caso general he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaQuick);
		if (ordenador.esOrdenada(&listaQuick, ASC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
		// volver a ordenar ascendente
		numeroClicksInicio = clock();
		ordenador.quickSort(&listaQuick, ASC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por quick en mejor caso he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaQuick);
		if (ordenador.esOrdenada(&listaQuick, ASC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
		// ordenar descendente
		numeroClicksInicio = clock();
		ordenador.quickSort(&listaQuick, DESC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por quick en peor caso he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaQuick);
		if (ordenador.esOrdenada(&listaQuick, DESC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
	}
	printf("\n\n");
	{
		//RANGO
		// ordenar ascendente
		numeroClicksInicio = clock();
		ordenador.rangoSort(&listaRango, ASC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por rango en caso general he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaRango);
		if (ordenador.esOrdenada(&listaRango, ASC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
		// volver a ordenar ascendente
		numeroClicksInicio = clock();
		ordenador.rangoSort(&listaRango, ASC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por rango en mejor caso he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaRango);
		if (ordenador.esOrdenada(&listaRango, ASC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
		// ordenar descendente
		numeroClicksInicio = clock();
		ordenador.rangoSort(&listaRango, DESC);
		numeroClicksFin = clock();
		segundosTranscurridos = (numeroClicksFin - numeroClicksInicio) / CLOCKS_PER_SEC;
		printf("Con ordenacion por rango en peor caso he tardado %.3f segundos.\n", segundosTranscurridos);
		imprimirListaContigua(&listaRango);
		if (ordenador.esOrdenada(&listaRango, DESC) == false) printf(">>>> EL ALGORITMO NO HA FUNCIONADA CORRECTAMENTE!!! <<<<\n");
	}


	return 0;
}
