#pragma once
#include "RegistroPuntaje.h"
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;


public ref class GestorPuntajes {
public:
	static String^ ObtenerRutaCarpeta() {
		String^ carpeta = Path::Combine(Application::StartupPath, "FILES");
		if (!Directory::Exists(carpeta)) {
			Directory::CreateDirectory(carpeta);
		}
		return carpeta;
	}

	static String^ ObtenerRutaArchivo() {
		return Path::Combine(ObtenerRutaCarpeta(), "SCORES.bin");
	}


	static List<RegistroPuntaje^>^ CargarTodos() {
		List<RegistroPuntaje^>^ lista = gcnew List<RegistroPuntaje^>();
		String^ ruta = ObtenerRutaArchivo();
		if (!File::Exists(ruta)) {
			return lista;
		}
		FileStream^ fs = nullptr;
		BinaryReader^ lector = nullptr;
		try {
			fs = gcnew FileStream(ruta, FileMode::Open, FileAccess::Read);
			lector = gcnew BinaryReader(fs);
			while (fs->Position < fs->Length) {
				String^ nombre = lector->ReadString();
				int puntaje = lector->ReadInt32();
				String^ fecha = lector->ReadString();
				lista->Add(gcnew RegistroPuntaje(nombre, puntaje, fecha));
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(
				"El archivo SCORES.bin esta danado o tiene un formato invalido.\n"
				"Se reiniciara el historial de puntajes.\n\nDetalle: " + ex->Message,
				"Error de puntajes", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			lista->Clear();
		}
		finally {
			if (lector != nullptr) lector->Close();
			if (fs != nullptr) fs->Close();
		}
		return lista;
	}

	static void Agregar(RegistroPuntaje^ registro) {
		String^ ruta = ObtenerRutaArchivo();
		FileStream^ fs = nullptr;
		BinaryWriter^ escritor = nullptr;
		try {
			fs = gcnew FileStream(ruta, FileMode::Append, FileAccess::Write);
			escritor = gcnew BinaryWriter(fs);
			escritor->Write(registro->nombre);
			escritor->Write(registro->puntaje);
			escritor->Write(registro->fecha);
		}
		catch (Exception^ ex) {
			MessageBox::Show("No se pudo guardar el puntaje en SCORES.bin.\n\nDetalle: " + ex->Message,
				"Error de puntajes", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		finally {
			if (escritor != nullptr) escritor->Close();
			if (fs != nullptr) fs->Close();
		}
	}
};