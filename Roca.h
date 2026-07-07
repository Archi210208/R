#pragma once
using namespace System::Drawing;
class Roca {
private:
	int x, y;
	int velocidadCaida;
	int ancho, alto;
	double zoom;
public:
	Roca(int x, int y, int ancho, int alto, double zoom);
	void setVelocidadCaida(int valor);
	void mover();
	void dibujar(Graphics^ graficos, Bitmap^ bmp);
	int getX();
	int getY();
	int getAncho();
	int getAlto();
};
Roca::Roca(int x, int y, int ancho, int alto, double zoom) {
	this->x = x;
	this->y = y;
	this->ancho = ancho;
	this->alto = alto;
	this->zoom = zoom;
	velocidadCaida = 6;
}
void Roca::setVelocidadCaida(int valor) {
	velocidadCaida = valor;
}
void Roca::mover() {
	y += velocidadCaida;
}
void Roca::dibujar(Graphics^ graficos, Bitmap^ bmp) {
	Rectangle mostrar = Rectangle(x, y, (int)(ancho * zoom), (int)(alto * zoom));
	graficos->DrawImage(bmp, mostrar, 0, 0, ancho, alto, GraphicsUnit::Pixel);
}
int Roca::getX() { return x; }
int Roca::getY() { return y; }
int Roca::getAncho() { return (int)(ancho * zoom); }
int Roca::getAlto() { return (int)(alto * zoom); }