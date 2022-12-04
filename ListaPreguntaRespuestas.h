#pragma once
#include "PreguntasRespuestas.h"
#include "Lista.h"
#include "Registros.h"
class ListaPreguntaRespuestas :public Base
{
private:
	ofstream archivo;
	Vector<string>* preguntas;
	Vector<string>* respuestas;
	int cantidad_preguntas;
	int cantidad_respuestas;
	int numeracion_aux ;
	int atPregunta;
	Lista<PreguntaRespuestas> *preguntasRespuestas;
public:
	ListaPreguntaRespuestas()
	{
		preguntas= new Vector<string>(100);
		respuestas= new Vector<string>(100);
		cantidad_preguntas = 0;
		cantidad_respuestas = 0;
		atPregunta = -1;
		preguntasRespuestas = new Lista<PreguntaRespuestas>();
		lecturaArchivos();
		lecturaDatos();
	}
	void lecturaArchivos()
	{
		string linea2;
		ifstream miarchivo2("Respuestas.txt");
		if (!miarchivo2.fail())
		{
			while (!miarchivo2.eof())
			{
				getline(miarchivo2, linea2);
				respuestas->pushBack(linea2);
				cantidad_respuestas++;
			}
			miarchivo2.close();
		}
		string linea;
		ifstream miarchivo("Preguntas.txt");
		if (!miarchivo.fail())
		{
			while (!miarchivo.eof())
			{
				getline(miarchivo, linea);
				preguntas->pushBack(linea);
				cantidad_preguntas++;
			}
			miarchivo.close();
		}

	}
	void guardarArchivos()
	{
		//ofstream miarchivo("Preguntas.txt"); // BORRA EL CONTENIDO DEL ARCHIVO
		//if (!miarchivo.fail())
		//{
		//	for (int i = 0; i < cantidad_preguntas - 1; i++)
		//		miarchivo << preguntasRespuestas->at(i).getPregunta() << endl;
		//	miarchivo.flush();
		//	miarchivo.close();
		//}
		ofstream miarchivo2("Respuestas.txt"); // BORRA EL CONTENIDO DEL ARCHIVO
		Vector<string>* aux_respuestas=new Vector<string>(100);
		if (!miarchivo2.fail())
		{
			for (int i = 0; i < cantidad_respuestas - 1; i++)
			{
				aux_respuestas = preguntasRespuestas->at(i).getRespuestas();
				for (int j = 0; j < aux_respuestas->returnCantidad(); j++)
				{
					miarchivo2 << aux_respuestas->at(j) << "/";
				}
				miarchivo2 << endl;
			}
			miarchivo2.close();
		}
	}
	void lecturaDatos()
	{
		int id = 0;
		for (int i = 0; i < cantidad_preguntas-1; i++)
		{
			int size = respuestas->at(i).length();
			string pregunta = preguntas->at(i);
			string aux2 = "";
			Vector<string>*respuesta= new Vector<string>(50);
			for (int j = 0; j < size; j++)
			{
				if (i == 1)
				{
					j = j;
				}
				if (respuestas->at(i)[j] != '/')
				{
					aux2 = aux2 + respuestas->at(i)[j];
				}
				else
				{
					respuesta->pushBack(aux2);
					aux2 = "";
				}
			}
			preguntasRespuestas->pushBack(PreguntaRespuestas(id, pregunta, respuesta));
			id++;
		}
		numeracion_aux = id;
	}
	void MenuPreguntasRespuestas()
	{
		do
		{
			cout << "  -------- Menu de Opciones de Preguntas y Respuestas ----------" << endl << endl;
			cout << "  1. Ingresar una pregunta  									 " << endl;
			cout << "  2. Ingresar una respuesta  									 " << endl;
			cout << "  3. Mostrar las preguntas y respuestas						 " << endl;
			cout << "  4. Salir													     " << endl;
			cout << "  --------------------------------------------------------------" << endl;
			verificarOpcion(4);
			if (*opcion == 1) insertarPregunta();
			if (*opcion == 2) insertarRespuesta();
			if (*opcion == 3) imprimirPreguntasRespuestas();
		} while (*opcion != 4);
		guardarArchivos();
	}
	void insertarPregunta()
	{
		string pregunta,opcion;
		Vector<string>* vacio = new Vector<string>(50);
		archivo.open("Preguntas.txt", ofstream::app);
		ofstream archivo2;
		archivo2.open("Respuestas.txt", ofstream::app);
		int numeracion = cantidad_preguntas;
		char opt;
		do
		{
			cout << "Pregunta :" << endl;
			getline(cin, pregunta);
			cantidad_preguntas++;
			preguntasRespuestas->pushBack(PreguntaRespuestas(numeracion,pregunta,vacio));
			numeracion++;
			archivo << pregunta << endl;
			archivo2 << endl;
			cout << "Desea continuar registrando un usuario (Si: S, No:N)";
			getline(cin, opcion);
			opt = toupper(opcion[0]);
		} while (opt != 'N');
		archivo.close();
		archivo2.close();
		system("CLS");
	}
	void insertarRespuesta()
	{
		string respuesta, opcion;
		Vector<string>* aux = new Vector<string>(50);
		archivo.open("Respuestas.txt", ofstream::app);
		int numeracion = numeracion_aux;
		char opt;
		seleccionarPregunta();
		cout << "¿" << preguntasRespuestas->at(atPregunta).getPregunta() << "?" << endl;
		cout << "Responder :" << endl;
		getline(cin, respuesta);
		preguntasRespuestas->at(atPregunta).insertarRespuesta(respuesta);
		system("CLS");
		archivo.close();
		guardarArchivos();
	}
	void elegirPregunta(size_t posicion) {
		atPregunta = posicion;
	}
	void seleccionarPregunta()
	{
		do
		{
			imprimirPreguntasRespuestas();
			cout << cantidad_preguntas - 1 << ". Salir" << endl;
			cout << "---------------- Elija la Pregunta a Responder ----------------" << endl << endl;
			verificarOpcion(cantidad_preguntas - 1);
			if (*opcion != cantidad_preguntas-1)
			{
				elegirPregunta(*opcion);
				cout << "--- Se elegio la pregunta correctamente ---" << endl;
			}
		} while (*opcion != cantidad_preguntas-1);
	}
	void imprimirPreguntasRespuestas()
	{
		cout << "----------------Lista de Preguntas y Respuestas -----------------" << endl;
		preguntasRespuestas->imprimirDatos([](PreguntaRespuestas e) {Console::ForegroundColor = ConsoleColor::Cyan; cout << e.toStringPreguntas(); Console::ForegroundColor = ConsoleColor::Yellow; cout << e.toStringRespuestas(); }, preguntasRespuestas->retornarNodoInicio());
		Console::ForegroundColor = ConsoleColor::White;
	}
};

