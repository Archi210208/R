#pragma once
#include "Roca.h"
class VectorRocas {
private:
	Roca** elementos;
	int cantidad;
public:
	VectorRocas();
	Roca* getElemento(int indice);
	void addElemento(Roca* roca);
	void deleteElemento(int indice);
	int getCantidad();
};
VectorRocas::VectorRocas() {
	cantidad = 0;
}
Roca* VectorRocas::getElemento(int indice) {
	if (indice < 0 || indice >= cantidad) {
		return nullptr;
	}
	return elementos[indice];
}
void VectorRocas::addElemento(Roca* elemento) {
	Roca** temp = new Roca * [cantidad + 1];
	for (int i = 0; i < cantidad; i++) {
		temp[i] = elementos[i];
	}
	temp[cantidad] = elemento;
	cantidad++;
	elementos = temp;
}
void VectorRocas::deleteElemento(int indice) {
	if (indice < 0 || indice >= cantidad) {
		return;
	}
	Roca** temp = new Roca * [cantidad - 1];
	for (int i = 0, j = 0; i < cantidad; i++) {
		if (indice != i) {
			temp[j] = elementos[i];
			j++;
		}
	}
	cantidad--;
	elementos = temp;
}
int VectorRocas::getCantidad() {
	return cantidad;
}