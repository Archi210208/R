#pragma once
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

// Dialogo simple para pedir el nombre del jugador antes de guardar su puntaje.
public ref class FormNombreJugador : public Form {
private:
	Label^ lblTitulo;
	TextBox^ txtNombre;
	Button^ btnAceptar;

public:
	FormNombreJugador() {
		this->Text = "Guardar puntaje";
		this->Size = System::Drawing::Size(360, 180);
		this->StartPosition = FormStartPosition::CenterParent;
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->BackColor = Color::FromArgb(35, 24, 16);

		lblTitulo = gcnew Label();
		lblTitulo->Text = L"Ingresa tu nombre para la tabla de puntajes:";
		lblTitulo->Font = gcnew System::Drawing::Font("Segoe UI", 10.5f);
		lblTitulo->ForeColor = Color::White;
		lblTitulo->Location = System::Drawing::Point(20, 20);
		lblTitulo->Size = System::Drawing::Size(310, 40);
		this->Controls->Add(lblTitulo);

		txtNombre = gcnew TextBox();
		txtNombre->Font = gcnew System::Drawing::Font("Segoe UI", 11);
		txtNombre->Location = System::Drawing::Point(20, 65);
		txtNombre->Size = System::Drawing::Size(300, 26);
		txtNombre->MaxLength = 20;
		this->Controls->Add(txtNombre);

		btnAceptar = gcnew Button();
		btnAceptar->Text = L"Aceptar";
		btnAceptar->Font = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
		btnAceptar->BackColor = Color::FromArgb(60, 45, 30);
		btnAceptar->ForeColor = Color::White;
		btnAceptar->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnAceptar->Location = System::Drawing::Point(110, 105);
		btnAceptar->Size = System::Drawing::Size(130, 32);
		btnAceptar->Click += gcnew EventHandler(this, &FormNombreJugador::aceptar_Click);
		this->Controls->Add(btnAceptar);
		this->AcceptButton = btnAceptar;
	}

	String^ ObtenerNombre() {
		if (txtNombre->Text == nullptr || txtNombre->Text->Trim()->Length == 0) {
			return "Jugador";
		}
		return txtNombre->Text->Trim();
	}

private:
	System::Void aceptar_Click(Object^ sender, EventArgs^ e) {
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
};