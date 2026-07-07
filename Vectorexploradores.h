#pragma once
#include "Explorador.h"
class VectorExploradores {
private:
	Explorador** elementos;
	int cantidad;
public:
	VectorExploradores();
	Explorador* getElemento(int indice);
	void addElemento(Explorador* cuadrado);
	void deleteElemento(int indice);
	int getCantidad();
};
VectorExploradores::VectorExploradores() {
	cantidad = 0;
}
Explorador* VectorExploradores::getElemento(int indice) {
	if (indice < 0 || indice >= cantidad) {
		return nullptr;
	}
	return elementos[indice];
}
void VectorExploradores::addElemento(Explorador* elemento) {
	Explorador** temp = new Explorador * [cantidad + 1];
	for (int i = 0; i < cantidad; i++) {
		temp[i] = elementos[i];
	}
	temp[cantidad] = elemento;
	cantidad++;
	//delete(elementos)
	elementos = temp;
}
void VectorExploradores::deleteElemento(int indice) {
	if (indice < 0 || indice >= cantidad) {
		//cout << "Indice fuera de rango" << endl;
		return;
	}
	Explorador** temp = new Explorador * [cantidad - 1];
	for (int i = 0, j = 0; i < cantidad; i++) {
		if (indice != i) {
			temp[j] = elementos[i];
			j++;
		}
	}
	cantidad--;
	//delete(elementos)
	elementos = temp;
}
int VectorExploradores::getCantidad() {
	return cantidad;
}