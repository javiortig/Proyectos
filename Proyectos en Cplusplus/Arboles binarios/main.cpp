/*Practica realizada por Javier Orti Garcia y Javier Borrell Weber*/

#include "ArbolBinarioDeBusqueda.h"


int main() {
	char menu;
	int num, i, rango;
	ArbolBinarioDeBusqueda arbol;
	srand(time(NULL));

	/*
		Hay que tener en cuenta que si un numero se repite no se insertará. Por eso, si se insertan 50 numeros
		aleatorios, si el rango de numeros aleatorios es bajo, se insertarán menos de 50.
	*/
	do {
		printf("1. Introducir numero\n2. Introducir hasta 50 numeros aleatorios (si se repite alguno podrian ser menos)\n3. Mostrar Inorder\n4. Mostrar Preorder\n5. Mostrar Postorder\n6. Salir\n\n");	
		scanf("%c", &menu);
		getchar();
		switch (menu) {	//Menu con las 6 opciones descritas.
		case '1':
			printf("Introduzca su numero\n");
			scanf("%d", &num);
			getchar();
			arbol.insertar(num);
			break;
		case '2':
			printf("Introduce el rango de los numeros aleatorios [0,n]\n");
			scanf("%d", &rango);
			getchar();
			for (i = 0; i < 50; i++) 
				arbol.insertar(rand() % (rango + 1));	
			
			break;
		case '3':
			printf("Impresion por Inorder:\n");
			arbol.imprimirArbol(INORDER);
			break;
		case '4':
			printf("Impresion por Preorder:\n");
			arbol.imprimirArbol(PREORDER);
			break;
		case '5':
			printf("Impresion por Postorder:\n");
			arbol.imprimirArbol(POSTORDER);
			break;
		case '6':
			printf("Saliendo...\n");
			break;
		default:
			printf("Error\n");
			break;
		}
	} while (menu != '6');

	return 0;
}