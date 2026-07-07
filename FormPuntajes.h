#pragma once
#include "RegistroPuntaje.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

// Ventana que muestra la tabla de puntajes actualizada al finalizar cada partida.
public ref class FormPuntajes : public Form {
private:
	Label^ lblTitulo;
	ListView^ listaPuntajes;
	Button^ btnCerrar;

public:
	FormPuntajes(List<RegistroPuntaje^>^ puntajes) {
		this->Text = "Tabla de puntajes";
		this->Size = System::Drawing::Size(440, 460);
		this->StartPosition = FormStartPosition::CenterParent;
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->BackColor = Color::FromArgb(35, 24, 16);

		lblTitulo = gcnew Label();
		lblTitulo->Text = L"Mejores puntajes";
		lblTitulo->Font = gcnew System::Drawing::Font("Segoe UI", 14, FontStyle::Bold);
		lblTitulo->ForeColor = Color::Gold;
		lblTitulo->Location = System::Drawing::Point(20, 15);
		lblTitulo->Size = System::Drawing::Size(380, 30);
		this->Controls->Add(lblTitulo);

		listaPuntajes = gcnew ListView();
		listaPuntajes->View = View::Details;
		listaPuntajes->FullRowSelect = true;
		listaPuntajes->GridLines = true;
		listaPuntajes->Location = System::Drawing::Point(20, 55);
		listaPuntajes->Size = System::Drawing::Size(380, 320);
		listaPuntajes->Columns->Add("Jugador", 160);
		listaPuntajes->Columns->Add("Puntaje", 90);
		listaPuntajes->Columns->Add("Fecha", 120);
		this->Controls->Add(listaPuntajes);

		// ordena los puntajes de mayor a menor (burbuja simple, la lista no es grande)
		List<RegistroPuntaje^>^ ordenados = gcnew List<RegistroPuntaje^>(puntajes);
		for (int i = 0; i < ordenados->Count - 1; i++) {
			for (int j = 0; j < ordenados->Count - 1 - i; j++) {
				if (ordenados[j]->puntaje < ordenados[j + 1]->puntaje) {
					RegistroPuntaje^ temp = ordenados[j];
					ordenados[j] = ordenados[j + 1];
					ordenados[j + 1] = temp;
				}
			}
		}

		for (int i = 0; i < ordenados->Count; i++) {
			RegistroPuntaje^ r = ordenados[i];
			ListViewItem^ item = gcnew ListViewItem(r->nombre);
			item->SubItems->Add(r->puntaje.ToString());
			item->SubItems->Add(r->fecha);
			listaPuntajes->Items->Add(item);
		}

		btnCerrar = gcnew Button();
		btnCerrar->Text = L"Cerrar";
		btnCerrar->Font = gcnew System::Drawing::Font("Segoe UI", 11, FontStyle::Bold);
		btnCerrar->BackColor = Color::FromArgb(60, 45, 30);
		btnCerrar->ForeColor = Color::White;
		btnCerrar->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnCerrar->Location = System::Drawing::Point(150, 385);
		btnCerrar->Size = System::Drawing::Size(140, 34);
		btnCerrar->Click += gcnew EventHandler(this, &FormPuntajes::cerrar_Click);
		this->Controls->Add(btnCerrar);
		this->AcceptButton = btnCerrar;
	}

private:
	System::Void cerrar_Click(Object^ sender, EventArgs^ e) {
		this->Close();
	}
};