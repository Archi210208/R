#pragma once
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public ref class FormInstrucciones : public Form {
private:
	Label^ lblTitulo;
	Label^ lblTexto;
	Button^ btnComenzar;

public:
	FormInstrucciones() {
		this->Text = "Como jugar";
		this->Size = System::Drawing::Size(460, 430);
		this->StartPosition = FormStartPosition::CenterParent;
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->BackColor = Color::FromArgb(35, 24, 16);

		lblTitulo = gcnew Label();
		lblTitulo->Text = L"Explorando el Peru";
		lblTitulo->Font = gcnew System::Drawing::Font("Segoe UI", 16, FontStyle::Bold);
		lblTitulo->ForeColor = Color::Gold;
		lblTitulo->Location = System::Drawing::Point(20, 15);
		lblTitulo->Size = System::Drawing::Size(400, 30);
		this->Controls->Add(lblTitulo);

		lblTexto = gcnew Label();
		lblTexto->Text =
			L"Objetivo:\n"
			L"Recoge las 4 llaves doradas escondidas en el mapa.\n\n"
			L"Controles:\n"
			L"  Flechas direccionales -> mover al explorador\n\n"
			L"Peligros:\n"
			L"  Un gallinazo sobrevuela el cielo y deja caer rocas.\n"
			L"  Si una roca te golpea, pierdes una vida (corazon).\n"
			L"  Si pierdes las 3 vidas, GAME OVER.\n\n"
			L"Victoria:\n"
			L"  Al reunir las 4 llaves, debes responder correctamente\n"
			L"  una pregunta de historia del Peru para confirmar tu triunfo.\n\n"
			L"Presiona ESC en cualquier momento para salir.";
		lblTexto->Font = gcnew System::Drawing::Font("Segoe UI", 10.5f, FontStyle::Regular);
		lblTexto->ForeColor = Color::White;
		lblTexto->Location = System::Drawing::Point(20, 55);
		lblTexto->Size = System::Drawing::Size(410, 290);
		this->Controls->Add(lblTexto);

		btnComenzar = gcnew Button();
		btnComenzar->Text = L"Comenzar";
		btnComenzar->Font = gcnew System::Drawing::Font("Segoe UI", 11, FontStyle::Bold);
		btnComenzar->BackColor = Color::FromArgb(60, 45, 30);
		btnComenzar->ForeColor = Color::White;
		btnComenzar->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnComenzar->Location = System::Drawing::Point(150, 355);
		btnComenzar->Size = System::Drawing::Size(140, 36);
		btnComenzar->Click += gcnew EventHandler(this, &FormInstrucciones::comenzar_Click);
		this->Controls->Add(btnComenzar);
		this->AcceptButton = btnComenzar;
	}

private:
	System::Void comenzar_Click(Object^ sender, EventArgs^ e) {
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
};