#pragma once
using namespace System;
public ref class PreguntaHistoria {
public:
	String^ pregunta;
	cli::array<String^>^ opciones;
	int correcta; // indice (0-3) de la opcion correcta dentro de "opciones"

	PreguntaHistoria(String^ pregunta, cli::array<String^>^ opciones, int correcta) {
		this->pregunta = pregunta;
		this->opciones = opciones;
		this->correcta = correcta;
	}
};