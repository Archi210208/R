#pragma once
using namespace System;


public ref class RegistroPuntaje {
public:
	String^ nombre;
	int puntaje;
	String^ fecha;

	RegistroPuntaje() {}
	RegistroPuntaje(String^ nombre, int puntaje, String^ fecha) {
		this->nombre = nombre;
		this->puntaje = puntaje;
		this->fecha = fecha;
	}
};