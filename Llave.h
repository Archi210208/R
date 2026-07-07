#pragma once
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;
class Llave {
private:
	int x, y;
	int tam;
	bool recogida;
public:
	Llave(int x, int y, int tam);
	void dibujar(Graphics^ graficos);
	bool estaRecogida();
	void recoger();
	int getX();
	int getY();
	int getAncho();
	int getAlto();
};
Llave::Llave(int x, int y, int tam) {
	this->x = x;
	this->y = y;
	this->tam = tam;
	recogida = false;
}
bool Llave::estaRecogida() { return recogida; }
void Llave::recoger() { recogida = true; }
int Llave::getX() { return x; }
int Llave::getY() { return y; }
int Llave::getAncho() { return tam; }
int Llave::getAlto() { return tam; }
void Llave::dibujar(Graphics^ graficos) {
	if (recogida) return;

	graficos->SmoothingMode = SmoothingMode::AntiAlias;

	Color colorLlave = Color::Gold;
	Color colorSombra = Color::FromArgb(150, 90, 60, 0);

	float diamAnillo = tam * 0.55f;
	float grosorAnillo = tam * 0.20f;
	float cx = (float)x, cy = (float)y + tam * 0.10f;

	// sombra/contorno suave (dibujada un poco mas grande y detras)
	Pen^ penSombra = gcnew Pen(colorSombra, grosorAnillo + 2.0f);
	graficos->DrawEllipse(penSombra, cx - 1, cy - 1, diamAnillo + 2, diamAnillo + 2);

	// aro dorado de la llave
	Pen^ penAnillo = gcnew Pen(colorLlave, grosorAnillo);
	graficos->DrawEllipse(penAnillo, cx, cy, diamAnillo, diamAnillo);

	// tallo
	SolidBrush^ brushLlave = gcnew SolidBrush(colorLlave);
	float ejeY = cy + diamAnillo / 2.0f - tam * 0.07f;
	float ejeX = cx + diamAnillo - tam * 0.05f;
	graficos->FillRectangle(brushLlave, ejeX, ejeY, tam * 0.55f, tam * 0.14f);

	// dientes
	graficos->FillRectangle(brushLlave, ejeX + tam * 0.30f, ejeY + tam * 0.14f, tam * 0.10f, tam * 0.14f);
	graficos->FillRectangle(brushLlave, ejeX + tam * 0.46f, ejeY + tam * 0.14f, tam * 0.10f, tam * 0.20f);
}