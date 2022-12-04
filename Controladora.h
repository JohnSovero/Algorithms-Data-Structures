#pragma once
#include "HashTableUsuarios.h"
#include "ArbolPromociones.h"
#include "VectorProfesores.h"
#include "PilaPuntuaciones.h"
#include "ListaPreguntaRespuestas.h"
#include "Idioma.h"
#include "ArbolPagos.h"
#include "GrafoPlanEstudio.h"
using namespace System;

class Controladora : public Base
{
private:
	HashTableUsuarios* usuario_registro;
	VectorProfesores* profesor_registro;
	PilaPuntuaciones* ranking;
	Idioma* idioma_registro;
	ListaPreguntaRespuestas* preguntas_respuestas;
	ArbolPromociones* promociones_registro;
	ArbolPagos* pagos_registros;
	GrafoPlanEstudio* planEstudios_registro;
	string opc;
public:
	Controladora()
	{
		usuario_registro = new HashTableUsuarios();
		profesor_registro = new VectorProfesores();
		idioma_registro = new Idioma();
		preguntas_respuestas = new ListaPreguntaRespuestas(); 
		promociones_registro = new ArbolPromociones();
		ranking = new PilaPuntuaciones(usuario_registro->retornarUsuarios());
		pagos_registros = new ArbolPagos();
		planEstudios_registro = new GrafoPlanEstudio();
	}
	void mostrarMenu()
	{		
		do
		{
			cout << "  ----------------- Menu de Opciones ------------" << "\n\n";
			cout << "  1. Ingresar usuario							  " << "\n";
			cout << "  2. Ingresar profesor							  " << "\n";
			cout << "  3. Aprender idioma					          " << "\n"; 
			cout << "  4. Puntuaciones   					          " << "\n";
			cout << "  5. Preguntas y Respuestas			          " << "\n";
			cout << "  6. Promociones						          " << "\n";
			cout << "  7. Pagos								          " << "\n";
			cout << "  8. Planes de Estudio					          " << "\n";
			cout << "  9. Salir						                  " << "\n";
			cout << "  -----------------------------------------------" << "\n";
			verificarOpcion(9);
			if (*opcion == 1) usuario_registro->menuUsuarios();
			if (*opcion == 2) profesor_registro->elegirProfesor();
			if (*opcion == 3 && usuario_registro->retornarCantidad() > 0) idioma_registro->elegirIdioma(usuario_registro);
			if (*opcion == 3 && usuario_registro->retornarCantidad() == 0) { cout << "         Debe registrarse primero" << endl; }
			if (*opcion == 4) ranking->elegirPuntuaciones(); 
			if (*opcion == 5) preguntas_respuestas->MenuPreguntasRespuestas();
			if (*opcion == 6) promociones_registro->menuPromocion();
			if (*opcion == 7) pagos_registros->MenuPagos();
			if (*opcion == 8) planEstudios_registro->menuPlanEstudio();
		} while (*opcion != 9);
	}
	void run() 
	{
		mostrarMenu();
	}
};