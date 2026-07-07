#pragma once
#include "PreguntaHistoria.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public ref class FormPregunta : public Form {
private:
	Label^ lblTitulo;
	Label^ lblPregunta;
	cli::array<Button^>^ botones;
	int respuestaCorrecta;
	bool acerto;

public:
	FormPregunta(PreguntaHistoria^ p) {
		respuestaCorrecta = p->correcta;
		acerto = false;

		this->Text = "Historia del Peru";
		this->Size = System::Drawing::Size(440, 340);
		this->StartPosition = FormStartPosition::CenterParent;
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->BackColor = Color::FromArgb(35, 24, 16);

		lblTitulo = gcnew Label();
		lblTitulo->Text = L"Confirma tu victoria";
		lblTitulo->Font = gcnew System::Drawing::Font("Segoe UI", 14, FontStyle::Bold);
		lblTitulo->ForeColor = Color::Gold;
		lblTitulo->Location = System::Drawing::Point(20, 15);
		lblTitulo->Size = System::Drawing::Size(380, 30);
		this->Controls->Add(lblTitulo);

		lblPregunta = gcnew Label();
		lblPregunta->Text = p->pregunta;
		lblPregunta->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Regular);
		lblPregunta->ForeColor = Color::White;
		lblPregunta->Location = System::Drawing::Point(20, 55);
		lblPregunta->Size = System::Drawing::Size(390, 70);
		this->Controls->Add(lblPregunta);

		botones = gcnew cli::array<Button^>(p->opciones->Length);
		for (int i = 0; i < p->opciones->Length; i++) {
			Button^ b = gcnew Button();
			b->Text = p->opciones[i];
			b->Tag = i;
			b->Font = gcnew System::Drawing::Font("Segoe UI", 11);
			b->BackColor = Color::FromArgb(60, 45, 30);
			b->ForeColor = Color::White;
			b->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			b->Location = System::Drawing::Point(20, 135 + i * 42);
			b->Size = System::Drawing::Size(390, 34);
			b->Click += gcnew EventHandler(this, &FormPregunta::opcion_Click);
			this->Controls->Add(b);
			botones[i] = b;
		}
	}

	bool respuestaCorrectaElegida() {
		return acerto;
	}

private:
	System::Void opcion_Click(Object^ sender, EventArgs^ e) {
		Button^ b = (Button^)sender;
		int idx = (int)b->Tag;
		acerto = (idx == respuestaCorrecta);
		this->DialogResult = acerto ? System::Windows::Forms::DialogResult::OK : System::Windows::Forms::DialogResult::No;
		this->Close();
	}
};