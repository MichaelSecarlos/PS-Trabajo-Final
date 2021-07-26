#include <iostream>

struct Producto
{
	int codigo;
	char laboratorio[20];
	int cantidad;
	float precio;
	Producto *ptrsig;
};