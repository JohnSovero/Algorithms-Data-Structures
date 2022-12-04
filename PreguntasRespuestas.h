#pragma once
#include <iostream>
#include "Vector.h"
#include <string>

using namespace std;

class PreguntaRespuestas
{
private:
	int id;
	int capacidad_respuestas;
	int cantidad_respuestas;
	string pregunta;
	Vector<string>* respuestas;
public:
	PreguntaRespuestas(int id = 0, string pregunta = " ", Vector<string>* respuesta = nullptr, int capacidad = 100) :id(id), pregunta(pregunta), respuestas(respuesta), capacidad_respuestas(capacidad)
	{
		respuesta = new Vector<string>(capacidad);
		cantidad_respuestas = 0;
	}
	string toStringRespuestas()
	{
		string respuestaString = "";
		for (int i = 0; i < respuestas->returnCantidad(); ++i)
		{
			respuestaString += "- " + respuestas->at(i) + ".\n";
		}
		return respuestaString;
	}
	void insertarRespuesta(string _respuesta)
	{
		respuestas->pushBack(_respuesta);
	}
	string toStringPreguntas()
	{
		return to_string(id) + ". ¿" + pregunta + "?\n";
	}

	string getPregunta() { return pregunta; }
	Vector<string>* getRespuestas() { return respuestas; }
};