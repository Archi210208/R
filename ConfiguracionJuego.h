#pragma once
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;

public ref class ConfiguracionJuego {
public:
	int vidasIniciales;
	int cantidadLlaves;
	int intervaloDisparoGallinazo; // ticks del timer entre cada roca lanzada
	double velocidadRoca;          // pixeles que cae la roca por tick
	double zoomExplorador;         // escala del sprite del explorador

	ConfiguracionJuego() {
		// valores por defecto, se usan si el archivo no existe o esta danado
		vidasIniciales = 3;
		cantidadLlaves = 4;
		intervaloDisparoGallinazo = 40;
		velocidadRoca = 6.0;
		zoomExplorador = 1.5;
	}

	static String^ ObtenerRutaCarpeta() {
		String^ carpeta = Path::Combine(Application::StartupPath, "FILES");
		if (!Directory::Exists(carpeta)) {
			Directory::CreateDirectory(carpeta);
		}
		return carpeta;
	}

	static String^ ObtenerRutaArchivo() {
		return Path::Combine(ObtenerRutaCarpeta(), "PARAMETERS.txt");
	}


	void Cargar() {
		String^ ruta = ObtenerRutaArchivo();
		if (!File::Exists(ruta)) {
			Guardar(); // primera ejecucion: crea el archivo con los valores actuales
			return;
		}
		StreamReader^ lector = nullptr;
		try {
			lector = gcnew StreamReader(ruta);
			vidasIniciales = int::Parse(LeerValor(lector->ReadLine()));
			cantidadLlaves = int::Parse(LeerValor(lector->ReadLine()));
			intervaloDisparoGallinazo = int::Parse(LeerValor(lector->ReadLine()));
			velocidadRoca = Double::Parse(LeerValor(lector->ReadLine()));
			zoomExplorador = Double::Parse(LeerValor(lector->ReadLine()));
		}
		catch (Exception^ ex) {
			MessageBox::Show(
				"El archivo PARAMETERS.txt no existe o tiene un formato invalido.\n"
				"Se usaran valores por defecto y el archivo sera regenerado.\n\nDetalle: " + ex->Message,
				"Error de configuracion", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			vidasIniciales = 3;
			cantidadLlaves = 4;
			intervaloDisparoGallinazo = 40;
			velocidadRoca = 6.0;
			zoomExplorador = 1.5;
			Guardar();
		}
		finally {
			if (lector != nullptr) lector->Close();
		}
	}

	void Guardar() {
		String^ ruta = ObtenerRutaArchivo();
		StreamWriter^ escritor = nullptr;
		try {
			escritor = gcnew StreamWriter(ruta, false);
			escritor->WriteLine("VIDAS_INICIALES=" + vidasIniciales);
			escritor->WriteLine("CANTIDAD_LLAVES=" + cantidadLlaves);
			escritor->WriteLine("INTERVALO_DISPARO_GALLINAZO=" + intervaloDisparoGallinazo);
			escritor->WriteLine("VELOCIDAD_ROCA=" + velocidadRoca);
			escritor->WriteLine("ZOOM_EXPLORADOR=" + zoomExplorador);
		}
		catch (Exception^ ex) {
			MessageBox::Show("No se pudo guardar PARAMETERS.txt.\n\nDetalle: " + ex->Message,
				"Error de configuracion", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		finally {
			if (escritor != nullptr) escritor->Close();
		}
	}

private:
	static String^ LeerValor(String^ linea) {
		if (linea == nullptr) throw gcnew Exception("Falta una linea en el archivo.");
		int pos = linea->IndexOf('=');
		if (pos < 0) throw gcnew Exception("Formato invalido: " + linea);
		return linea->Substring(pos + 1)->Trim();
	}
};