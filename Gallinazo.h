#pragma once
using namespace System::Drawing;
class Gallinazo {
private:
	int x, y;
	int dx;
	int contadorTiro;
	int intervaloTiro; // cantidad de ticks del timer entre cada roca lanzada
	int idx; // fotograma actual de la animacion de vuelo (0-3)
	int ancho, alto; // tamano de cada fotograma dentro de la hoja
	double zoom;
public:
	static const int FRAMES = 4;
	Gallinazo(int x, int y, int anchoFrame, int altoFrame, double zoom);
	void setIntervaloTiro(int valor);
	void mover(int anchoPanel);
	void dibujar(Graphics^ graficos, Bitmap^ bmp);
	bool debeDisparar();
	int getX();
	int getY();
	int getAncho();
	int getAlto();
};
Gallinazo::Gallinazo(int x, int y, int anchoFrame, int altoFrame, double zoom) {
	this->x = x;
	this->y = y;
	this->ancho = anchoFrame;
	this->alto = altoFrame;
	this->zoom = zoom;
	dx = 7;
	contadorTiro = 0;
	intervaloTiro = 40; // con el timer a 50ms, tira una roca cada ~2 segundos
	idx = 0;
}
void Gallinazo::setIntervaloTiro(int valor) {
	intervaloTiro = valor;
}
void Gallinazo::mover(int anchoPanel) {
	x += dx;
	if (x < 0 || x + ancho * zoom >= anchoPanel) {
		dx *= -1;
	}
	contadorTiro++;
	idx++;
	idx = idx % FRAMES;
}
bool Gallinazo::debeDisparar() {
	if (contadorTiro >= intervaloTiro) {
		contadorTiro = 0;
		return true;
	}
	return false;
}
int Gallinazo::getX() { return x; }
int Gallinazo::getY() { return y; }
int Gallinazo::getAncho() { return (int)(ancho * zoom); }
int Gallinazo::getAlto() { return (int)(alto * zoom); }
void Gallinazo::dibujar(Graphics^ graficos, Bitmap^ bmp) {
	Rectangle section = Rectangle(idx * ancho, 0, ancho, alto);
	Rectangle mostrar = Rectangle(x, y, (int)(ancho * zoom), (int)(alto * zoom));
	if (dx < 0) {
		// el sprite mira hacia la derecha por defecto: se espeja al volar a la izquierda
		graficos->DrawImage(bmp, gcnew array<Point>{
			Point(mostrar.Right, mostrar.Top),
				Point(mostrar.Left, mostrar.Top),
				Point(mostrar.Right, mostrar.Bottom)
		}, section, GraphicsUnit::Pixel);
	}
	else {
		graficos->DrawImage(bmp, mostrar, section, GraphicsUnit::Pixel);
	}
}