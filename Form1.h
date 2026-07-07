#pragma once
#include <cstdlib>
#include <ctime>
#include "Explorador.h"
#include "VectorExploradores.h"
#include "Gallinazo.h"
#include "Roca.h"
#include "VectorRocas.h"
#include "Llave.h"
#include "PreguntaHistoria.h"
#include "FormPregunta.h"
#include "FormInstrucciones.h"
#include "ConfiguracionJuego.h"
#include "RegistroPuntaje.h"
#include "GestorPuntajes.h"
#include "FormPuntajes.h"
#include "FormNombreJugador.h"
#include "vector"

//int puntaje = llavesRecogidas * 250 + (int)(tiempoSobrevivido * 10) + vidas * 50; asi se calcula el puntaje final al terminar la partida
namespace Caballos {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{

	private:
		Explorador* principal;
		Bitmap^ bmpExplorador;
		Bitmap^ bmpFondo;
		Bitmap^ bmpGallinazo;
		Bitmap^ bmpRoca;
		Graphics^ graficos;
		BufferedGraphics^ buffer;
		VectorExploradores* secundarios;
		int maximoSecundarios = 100;
		Gallinazo* gallinazo;
		VectorRocas* rocas;
		int vidas;
		double tiempoSobrevivido; // en segundos
		bool juegoTerminado;
		bool juegoGanado;
		cli::array<Llave*>^ llaves;
		int llavesRecogidas;
		ConfiguracionJuego^ configuracion;
		int cantidadLlaves;      // viene de PARAMETERS.txt (por defecto 4)
		bool puntajeGuardado;    // evita guardar el puntaje mas de una vez por partida
		cli::array<PreguntaHistoria^>^ preguntas;
		System::Drawing::Font^ fuenteUI;
		System::Drawing::Font^ fuenteGameOver;
		SolidBrush^ brushUI;
		SolidBrush^ brushSombra;
		SolidBrush^ brushGameOver;
		SolidBrush^ brushVictoria;
		SolidBrush^ brushPanelHUD;
		SolidBrush^ brushCorazonLleno;
		SolidBrush^ brushCorazonVacio;
		SolidBrush^ brushOverlay;

	public:
		MyForm(void)
		{
			srand((unsigned int)time(nullptr));
			InitializeComponent();

			// Gestion de archivos: carga (o crea) PARAMETERS.txt con la configuracion del juego
			configuracion = gcnew ConfiguracionJuego();
			configuracion->Cargar();
			cantidadLlaves = configuracion->cantidadLlaves;
			puntajeGuardado = false;

			secundarios = new VectorExploradores();
			graficos = canvas->CreateGraphics(); //crea un objeto Graphics para dibujar en el panel
			buffer = BufferedGraphicsManager::Current->Allocate(graficos, canvas->ClientRectangle); //crea un buffer para dibujar en el panel
			bmpExplorador = gcnew Bitmap("images/sprite_tf2.png"); //un bitmap con la imagen del sprite (ya con fondo transparente)
			bmpFondo = gcnew Bitmap("images/fondo_tf2.png"); //imagen de fondo
			bmpGallinazo = gcnew Bitmap("images/gallinazo_vuelo.png"); //hoja de 4 fotogramas de vuelo
			bmpRoca = gcnew Bitmap("images/roca.png"); //imagen de la roca
			// El sprite_tf2 tiene una cuadricula de 8 columnas (fotogramas) x 4 filas (direcciones)
			// Cada fotograma es de ~39x45 px
			// Empieza abajo a la izquierda para no toparse con el limite del cielo
			int altoFrame = bmpExplorador->Height / 4;
			int yInicial = canvas->Height - (int)(altoFrame * 1.5) - 10;
			principal = new Explorador(20, yInicial, bmpExplorador->Width / 8, altoFrame, configuracion->zoomExplorador);
			// gallinazo_vuelo.png tiene 4 fotogramas en una fila
			gallinazo = new Gallinazo(50, 30, bmpGallinazo->Width / Gallinazo::FRAMES, bmpGallinazo->Height, 0.3);
			gallinazo->setIntervaloTiro(configuracion->intervaloDisparoGallinazo);
			rocas = new VectorRocas();

			vidas = configuracion->vidasIniciales;
			tiempoSobrevivido = 0.0;
			juegoTerminado = false;
			juegoGanado = false;
			llavesRecogidas = 0;
			// llaves en posiciones aleatorias distintas cada vez, repartidas por la zona caminable
			llaves = gcnew cli::array<Llave*>(cantidadLlaves);
			generarLlaves();
			cargarPreguntas();
			fuenteUI = gcnew System::Drawing::Font("Segoe UI", 13, FontStyle::Bold);
			fuenteGameOver = gcnew System::Drawing::Font("Segoe UI", 40, FontStyle::Bold);
			brushUI = gcnew SolidBrush(Color::White);
			brushSombra = gcnew SolidBrush(Color::FromArgb(160, 0, 0, 0));
			brushGameOver = gcnew SolidBrush(Color::OrangeRed);
			brushVictoria = gcnew SolidBrush(Color::Gold);
			brushPanelHUD = gcnew SolidBrush(Color::FromArgb(120, 20, 15, 10));
			brushCorazonLleno = gcnew SolidBrush(Color::Crimson);
			brushCorazonVacio = gcnew SolidBrush(Color::FromArgb(90, 255, 255, 255));
			brushOverlay = gcnew SolidBrush(Color::FromArgb(170, 0, 0, 0));

			timer->Enabled = false;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ canvas;
	protected:
	private: System::Windows::Forms::Timer^ timer;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->canvas = (gcnew System::Windows::Forms::Panel());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// canvas
			// 
			this->canvas->Location = System::Drawing::Point(12, 12);
			this->canvas->Name = L"canvas";
			this->canvas->Size = System::Drawing::Size(667, 606);
			this->canvas->TabIndex = 0;
			this->canvas->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::canvas_Paint);
			this->canvas->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::canvas_MouseClick);
			// 
			// timer
			// 
			this->timer->Enabled = true;
			this->timer->Interval = 50;
			this->timer->Tick += gcnew System::EventHandler(this, &MyForm::timer_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(691, 630);
			this->Controls->Add(this->canvas);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		int aleatorioEntre(int minVal, int maxVal) {
			return minVal + rand() % (maxVal - minVal + 1);
		}

		void generarLlaves() {
			int margen = 20;
			int tamLlave = 26;
			int limiteSuperior = (int)(canvas->Height * 0.30) + 20; // un poco debajo del cielo
			int limiteInferior = canvas->Height - tamLlave - margen;
			int limiteIzquierdo = margen;
			int limiteDerecho = canvas->Width - tamLlave - margen;
			int separacionMinima = 90;

			for (int i = 0; i < cantidadLlaves; i++) {
				int x = margen, y = limiteSuperior;
				bool valida = false;
				int intentos = 0;
				while (!valida && intentos < 60) {
					x = aleatorioEntre(limiteIzquierdo, limiteDerecho);
					y = aleatorioEntre(limiteSuperior, limiteInferior);
					valida = true;
					for (int j = 0; j < i; j++) {
						int dx = x - llaves[j]->getX();
						int dy = y - llaves[j]->getY();
						if (dx * dx + dy * dy < separacionMinima * separacionMinima) {
							valida = false;
							break;
						}
					}
					intentos++;
				}
				llaves[i] = new Llave(x, y, tamLlave);
			}
		}

		void cargarPreguntas() {
			preguntas = gcnew cli::array<PreguntaHistoria^>(7);
			preguntas[0] = gcnew PreguntaHistoria("En que anio se proclamo la independencia del Peru?",
				gcnew cli::array<String^> { "1810", "1821", "1824", "1879" }, 1); //respuesta correcta: 1821
			preguntas[1] = gcnew PreguntaHistoria("Quien fundo la ciudad de Lima en 1535?",
				gcnew cli::array<String^> { "Diego de Almagro", "Francisco Pizarro", "Sebastian de Belalcazar", "Hernando de Soto" }, 1); //respuesta correcta: Francisco Pizarro
			preguntas[2] = gcnew PreguntaHistoria("Cual fue la capital del Imperio Incaico?",
				gcnew cli::array<String^> { "Lima", "Cusco", "Arequipa", "Trujillo" }, 1); //respuesta correcta: Cusco
			preguntas[3] = gcnew PreguntaHistoria("Que inca fue capturado y ejecutado por los espanioles en Cajamarca?",
				gcnew cli::array<String^> { "Huayna Capac", "Tupac Amaru II", "Atahualpa", "Manco Inca" }, 2); //respuesta correcta: Atahualpa
			preguntas[4] = gcnew PreguntaHistoria("Quien dio a conocer Machu Picchu al mundo occidental en 1911?",
				gcnew cli::array<String^> { "Hiram Bingham", "Charles Wiener", "Antonio Raimondi", "Julio C. Tello" }, 0); //respuesta correcta: Hiram Bingham
			preguntas[5] = gcnew PreguntaHistoria("Cual es la moneda actual del Peru?",
				gcnew cli::array<String^> { "Peso", "Sol", "Boliviano", "Real" }, 1); //respuesta correcta: Sol
			preguntas[6] = gcnew PreguntaHistoria("En que batalla se consolido la independencia sudamericana en 1824?",
				gcnew cli::array<String^> { "Batalla de Junin", "Batalla de Ayacucho", "Batalla de Boyaca", "Batalla de Carabobo" }, 1); //respuesta correcta: Batalla de Ayacucho
		}

		void confirmarVictoriaConPreguntas() {
			timer->Enabled = false;
			bool acerto = false;
			while (!acerto && vidas > 0) {
				int idx = aleatorioEntre(0, preguntas->Length - 1);
				FormPregunta^ dlg = gcnew FormPregunta(preguntas[idx]);
				dlg->ShowDialog(this);
				acerto = dlg->respuestaCorrectaElegida();
				if (!acerto) {
					vidas--;
					MessageBox::Show(String::Format("Respuesta incorrecta. Vidas restantes: {0}", vidas), "Historia del Peru");
				}
			}
			if (acerto) {
				juegoGanado = true;
			}
			else {
				juegoTerminado = true;
			}
			timer->Enabled = true; // se reactiva para dibujar la pantalla final y luego detenerse solo
		}

		GraphicsPath^ ObtenerRectRedondeado(Rectangle rect, int radio) {
			GraphicsPath^ path = gcnew GraphicsPath();
			int d = radio * 2;
			path->AddArc(rect.X, rect.Y, d, d, 180, 90);
			path->AddArc(rect.Right - d, rect.Y, d, d, 270, 90);
			path->AddArc(rect.Right - d, rect.Bottom - d, d, d, 0, 90);
			path->AddArc(rect.X, rect.Bottom - d, d, d, 90, 90);
			path->CloseFigure();
			return path;
		}

		System::Void dibujarCorazon(Graphics^ g, float x, float y, float tam, Brush^ brush) {
			GraphicsPath^ path = gcnew GraphicsPath();
			float m = tam / 2.0f;
			path->AddBezier(x + m, y + tam * 0.3f, x + m, y, x, y, x, y + m * 0.6f);
			path->AddBezier(x, y + m * 0.6f, x, y + tam * 0.9f, x + m, y + tam, x + m, y + tam);
			path->AddBezier(x + m, y + tam, x + m, y + tam * 0.9f, x + tam, y + m * 0.6f, x + tam, y + m * 0.6f);
			path->AddBezier(x + tam, y + m * 0.6f, x + tam, y, x + m, y, x + m, y + tam * 0.3f);
			path->CloseFigure();
			g->FillPath(brush, path);
		}

		System::Void dibujarTextoConSombra(Graphics^ g, String^ texto, System::Drawing::Font^ fuente, Brush^ brush, float x, float y) {
			g->DrawString(texto, fuente, brushSombra, x + 2.0f, y + 2.0f);
			g->DrawString(texto, fuente, brush, x, y);
		}

		System::Void dibujarHUD(Graphics^ g) {
			g->SmoothingMode = SmoothingMode::AntiAlias;

			Rectangle panelRect(10, 10, 168, 64);
			g->FillPath(brushPanelHUD, ObtenerRectRedondeado(panelRect, 16));

			// corazones (vidas)
			float hx = panelRect.X + 14.0f;
			float hy = panelRect.Y + 10.0f;
			for (int i = 0; i < 3; i++) {
				Brush^ b = (i < vidas) ? (Brush^)brushCorazonLleno : (Brush^)brushCorazonVacio;
				dibujarCorazon(g, hx + i * 32.0f, hy, 24.0f, b);
			}

			// tiempo sobrevivido en formato mm:ss
			int minutos = (int)(tiempoSobrevivido / 60.0);
			int segundos = (int)tiempoSobrevivido % 60;
			String^ texto = String::Format("{0:00}:{1:00}", minutos, segundos);
			dibujarTextoConSombra(g, texto, fuenteUI, brushUI, panelRect.X + 14.0f, panelRect.Y + 36.0f);

			g->SmoothingMode = SmoothingMode::Default;
		}

		System::Void dibujarHUDLlaves(Graphics^ g) {
			g->SmoothingMode = SmoothingMode::AntiAlias;

			Rectangle panelRect(canvas->Width - 132, 10, 122, 44);
			g->FillPath(brushPanelHUD, ObtenerRectRedondeado(panelRect, 16));

			Llave iconoTemp(panelRect.X + 12, panelRect.Y + 4, 22);
			iconoTemp.dibujar(g);

			String^ texto = String::Format("{0}/{1}", llavesRecogidas, cantidadLlaves);
			dibujarTextoConSombra(g, texto, fuenteUI, brushUI, panelRect.X + 50.0f, panelRect.Y + 12.0f);

			g->SmoothingMode = SmoothingMode::Default;
		}

		System::Void dibujarGameOver(Graphics^ g) {
			g->SmoothingMode = SmoothingMode::AntiAlias;
			g->FillRectangle(brushOverlay, canvas->ClientRectangle);

			String^ titulo = "GAME OVER";
			SizeF tamTitulo = g->MeasureString(titulo, fuenteGameOver);
			float tx = (canvas->Width - tamTitulo.Width) / 2.0f;
			float ty = (canvas->Height - tamTitulo.Height) / 2.0f - 16.0f;
			dibujarTextoConSombra(g, titulo, fuenteGameOver, brushGameOver, tx, ty);

			String^ subtitulo = String::Format("Sobreviviste {0:00}:{1:00}", (int)(tiempoSobrevivido / 60.0), (int)tiempoSobrevivido % 60);
			SizeF tamSub = g->MeasureString(subtitulo, fuenteUI);
			float sx = (canvas->Width - tamSub.Width) / 2.0f;
			float sy = ty + tamTitulo.Height + 12.0f;
			dibujarTextoConSombra(g, subtitulo, fuenteUI, brushUI, sx, sy);

			g->SmoothingMode = SmoothingMode::Default;
		}

		System::Void dibujarVictoria(Graphics^ g) {
			g->SmoothingMode = SmoothingMode::AntiAlias;
			g->FillRectangle(brushOverlay, canvas->ClientRectangle);

			String^ titulo = "VICTORIA!";
			SizeF tamTitulo = g->MeasureString(titulo, fuenteGameOver);
			float tx = (canvas->Width - tamTitulo.Width) / 2.0f;
			float ty = (canvas->Height - tamTitulo.Height) / 2.0f - 16.0f;
			dibujarTextoConSombra(g, titulo, fuenteGameOver, brushVictoria, tx, ty);

			String^ subtitulo = String::Format("Reuniste las {0} llaves en {1:00}:{2:00}", cantidadLlaves, (int)(tiempoSobrevivido / 60.0), (int)tiempoSobrevivido % 60);
			SizeF tamSub = g->MeasureString(subtitulo, fuenteUI);
			float sx = (canvas->Width - tamSub.Width) / 2.0f;
			float sy = ty + tamTitulo.Height + 12.0f;
			dibujarTextoConSombra(g, subtitulo, fuenteUI, brushUI, sx, sy);

			g->SmoothingMode = SmoothingMode::Default;
		}

	private:
		void GuardarPuntajeYMostrarTabla() {
			FormNombreJugador^ dlgNombre = gcnew FormNombreJugador();
			String^ nombreJugador = "Jugador";
			if (dlgNombre->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
				nombreJugador = dlgNombre->ObtenerNombre();
			}

			int puntaje = llavesRecogidas * 250 + (int)(tiempoSobrevivido * 10) + vidas * 50;
			String^ fecha = DateTime::Now.ToString("dd/MM/yyyy HH:mm");
			RegistroPuntaje^ registro = gcnew RegistroPuntaje(nombreJugador, puntaje, fecha);
			GestorPuntajes::Agregar(registro);

			List<RegistroPuntaje^>^ todos = GestorPuntajes::CargarTodos();
			FormPuntajes^ dlgPuntajes = gcnew FormPuntajes(todos);
			dlgPuntajes->ShowDialog(this);
		}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		FormInstrucciones^ dlgInstrucciones = gcnew FormInstrucciones();
		dlgInstrucciones->ShowDialog(this);
		canvas->Focus();
		timer->Enabled = true;
	}

	private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e) {
		bool finalizado = juegoTerminado || juegoGanado;
		if (!finalizado) {
			tiempoSobrevivido += timer->Interval / 1000.0;
		}

		buffer->Graphics->DrawImage(bmpFondo, canvas->ClientRectangle);

		// llaves dispersas por el mapa (las ya recogidas no se dibujan)
		for (int i = 0; i < cantidadLlaves; i++) {
			llaves[i]->dibujar(buffer->Graphics);
		}

		principal->dibujar(buffer->Graphics, bmpExplorador);
		for (int i = 0; i < secundarios->getCantidad(); i++) {
			secundarios->getElemento(i)->dibujar(buffer->Graphics, bmpExplorador);
		}

		// gallinazo: se mueve de un lado a otro del cielo y de a ratos lanza una roca
		gallinazo->mover(canvas->Width);
		gallinazo->dibujar(buffer->Graphics, bmpGallinazo);
		if (!finalizado && gallinazo->debeDisparar()) {
			Roca* nuevaRoca = new Roca(gallinazo->getX() + gallinazo->getAncho() / 2, gallinazo->getY() + gallinazo->getAlto(),
				bmpRoca->Width, bmpRoca->Height, 0.4);
			nuevaRoca->setVelocidadCaida((int)configuracion->velocidadRoca);
			rocas->addElemento(nuevaRoca);
		}

		// rocas: caen y se eliminan al llegar al piso del canvas
		for (int i = 0; i < rocas->getCantidad(); i++) {
			rocas->getElemento(i)->dibujar(buffer->Graphics, bmpRoca);
		}

		// interfaz: vidas (corazones), llaves recogidas y tiempo sobrevivido
		dibujarHUD(buffer->Graphics);
		dibujarHUDLlaves(buffer->Graphics);

		if (juegoTerminado) {
			dibujarGameOver(buffer->Graphics);
		}
		else if (juegoGanado) {
			dibujarVictoria(buffer->Graphics);
		}

		buffer->Render(graficos);

		if (finalizado) {
			timer->Enabled = false;
			if (!puntajeGuardado) {
				puntajeGuardado = true;
				GuardarPuntajeYMostrarTabla();
			}
			return;
		}

		for (int i = 0; i < secundarios->getCantidad(); i++) {
			secundarios->getElemento(i)->mover(graficos);
		}

		Rectangle rectExplorador(principal->getX(), principal->getY(), principal->getAncho(), principal->getAlto());

		// colision explorador-llaves
		for (int i = 0; i < cantidadLlaves; i++) {
			if (!llaves[i]->estaRecogida()) {
				Rectangle rectLlave(llaves[i]->getX(), llaves[i]->getY(), llaves[i]->getAncho(), llaves[i]->getAlto());
				if (rectLlave.IntersectsWith(rectExplorador)) {
					llaves[i]->recoger();
					llavesRecogidas++;
					if (llavesRecogidas >= cantidadLlaves && !juegoGanado && !juegoTerminado) {
						confirmarVictoriaConPreguntas();
					}
				}
			}
		}

		for (int i = rocas->getCantidad() - 1; i >= 0; i--) {
			Roca* r = rocas->getElemento(i);
			r->mover();
			Rectangle rectRoca(r->getX(), r->getY(), r->getAncho(), r->getAlto());
			if (rectRoca.IntersectsWith(rectExplorador)) {
				vidas--;
				rocas->deleteElemento(i);
				if (vidas <= 0) {
					juegoTerminado = true;
				}
				continue;
			}
			if (r->getY() > canvas->Height) {
				rocas->deleteElemento(i);
			}
		}
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Escape) {
			this->Close();
			return;
		}
		if (juegoTerminado || juegoGanado) {
			return;
		}
		principal->mover(e->KeyCode, graficos);
		principal->cambiarColor(e->KeyCode);
		if (e->KeyData == Keys::E) {
			int cnt = secundarios->getCantidad();
			secundarios->deleteElemento(cnt - 1);
		}

	}
	private: System::Void canvas_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}

	private: System::Void canvas_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (secundarios->getCantidad() < maximoSecundarios) {
			Explorador* nuevoExplorador = new Explorador(e->X, e->Y, bmpExplorador->Width / 8, bmpExplorador->Height / 4, 1);
			nuevoExplorador->cambiarColor();
			secundarios->addElemento(nuevoExplorador);
		}
	}
	};
}