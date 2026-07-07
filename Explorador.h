#pragma once
#include <cstdlib>
using namespace System::Windows::Forms;
using namespace System::Drawing;
class Explorador { //clase Explorador (personaje principal / secundarios)
private: //atributos
	int pasos;
	int dx, dy;
	int x, y;
	int ancho, alto;
	double zoom;
	int idx, idy;
	int sumaIdx, sumaIdy;
	static const int FRAMES_POR_FILA = 8; // sprite_tf2: 8 fotogramas de animacion por fila
	static constexpr double PORC_LIMITE_CIELO = 0.30; // el 30% superior del canvas es "cielo": no se puede caminar ahi
public: //metodos
	Explorador(int x, int y, int ancho, int alto, double zoom);
	~Explorador();
	void mover(Graphics^ graficos);
	void mover(Keys tecla, Graphics^ graficos);
	void dibujar(Graphics^ graficos, Bitmap^ bmp);
	void cambiarColor(Keys tecla);
	void cambiarColor();
	int getX();
	int getY();
	int getAncho();
	int getAlto();
};
Explorador::Explorador(int x, int y, int ancho, int alto, double zoom) { //constructor
	this->x = x;
	this->y = y;
	this->ancho = ancho;
	this->alto = alto;
	this->zoom = zoom;
	sumaIdx = 0;
	sumaIdy = 0;
	dx = dy = 0;
	pasos = 5;
	idx = idy = 0;
}
Explorador::~Explorador() { //destructor
}
void Explorador::mover(Graphics^ graficos) { //movimiento aleatorio
	int anchoPanel = graficos->VisibleClipBounds.Width;
	int altoPanel = graficos->VisibleClipBounds.Height;
	int limiteSuperior = (int)(altoPanel * PORC_LIMITE_CIELO); // no puede entrar al cielo
	idx++;
	idx = idx % FRAMES_POR_FILA;
	if (dx == 0 && dy == 0) {
		dx = pasos;
		dy = pasos;
	}
	int numeroRandom = rand() % 100 + 1;
	if (numeroRandom >= 95) {
		dx *= -1;
	}
	numeroRandom = rand() % 100 + 1;
	if (numeroRandom >= 95) {
		dy *= -1;
	}
	if (x + dx < 0 || x + dx + ancho * zoom >= anchoPanel) {
		dx *= -1;
	}
	if (y + dy < limiteSuperior || y + dy + alto * zoom >= altoPanel) {
		dy *= -1;
	}
	if (dy < 0) {
		idy = 0; // arriba
	}
	else if (dy > 0) {
		idy = 1; // abajo
	}
	if (dx < 0) {
		idy = 2; // izquierda
	}
	else if (dx > 1) {
		idy = 3; // derecha
	}
	x += dx;
	y += dy;
}
void Explorador::mover(Keys tecla, Graphics^ graficos) {
	int anchoPanel = graficos->VisibleClipBounds.Width;
	int altoPanel = graficos->VisibleClipBounds.Height;
	int limiteSuperior = (int)(altoPanel * PORC_LIMITE_CIELO); // no puede entrar al cielo
	this->dx = this->dy = 0;
	switch (tecla) {
	case Keys::Up:
		idy = 0;
		this->dy = -pasos;
		break;
	case Keys::Down:
		idy = 1;
		this->dy = pasos;
		break;
	case Keys::Left:
		idy = 2;
		this->dx = -pasos;
		break;
	case Keys::Right:
		idy = 3;
		this->dx = pasos;
		break;
	}
	idx++;
	idx = idx % FRAMES_POR_FILA;
	if (x + dx < 0 || x + dx + ancho * zoom >= anchoPanel) {
		return;
	}
	if (y + dy < limiteSuperior || y + dy + alto * zoom >= altoPanel) {
		return;
	}
	this->x += this->dx;
	this->y += this->dy;
}
void Explorador::dibujar(Graphics^ graficos, Bitmap^ bmp) {
	Rectangle section = Rectangle((idx + sumaIdx) * ancho, (idy + sumaIdy) * alto, ancho, alto);
	Rectangle mostrar = Rectangle(x, y, ancho * zoom, alto * zoom);
	graficos->DrawImage(bmp, mostrar, section, GraphicsUnit::Pixel);
}
void Explorador::cambiarColor(Keys tecla) {
	// El sprite_tf2 solo tiene 4 filas (una por direccion) y usa las 8 columnas
	// completas para la animacion: no hay lugar para variantes de color.
	switch (tecla) {
	case Keys::B:
	case Keys::V:
	case Keys::Z:
	case Keys::A:
		sumaIdx = 0;
		sumaIdy = 0;
		break;
	}
}
void Explorador::cambiarColor() {
	sumaIdx = 0;
	sumaIdy = 0;
}
int Explorador::getX() { return x; }
int Explorador::getY() { return y; }
int Explorador::getAncho() { return (int)(ancho * zoom); }
int Explorador::getAlto() { return (int)(alto * zoom); }