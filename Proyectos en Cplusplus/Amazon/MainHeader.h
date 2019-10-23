#include <iostream>
#include <cstdio>
#include <cstring>
#include "Producto.h"
#include "Libro.h"
#include "Pelicula.h"
#include "Videojuego.h"
#define MAXPRODUCTOS 25
#define MAXFORMATO 100
#define MAXDESCRIPCION 999

void inicializarNull(Producto *lista[MAXPRODUCTOS]);
void pedirProductos(Producto *lista[MAXPRODUCTOS]);
void ImprimirLista(Producto *lista[MAXPRODUCTOS]);
void OrdenarPorPrecio(Producto *lista[MAXPRODUCTOS]);
void ObtenerPorCategoria(Producto *lista[MAXPRODUCTOS]);
void OrdenarCategoriaPrecio(Producto *lista[MAXPRODUCTOS]);
void MostrarCienciaFiccion100(Producto *lista[MAXPRODUCTOS]);
void MostrarBluRayPremiadas(Producto *lista[MAXPRODUCTOS]);
void MostrarPS4conVR(Producto *lista[MAXPRODUCTOS]);
void BuscarPorTitulo(Producto *lista[MAXPRODUCTOS]);
void BuscarPorDebajoDe(Producto *lista[MAXPRODUCTOS]);
float AniadirAlCarrito(Producto *lista[MAXPRODUCTOS]);
