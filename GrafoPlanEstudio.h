#pragma once
#include "Grafos.h"
#include "PlanEstudio.h"
class GrafoPlanEstudio :public Base
{
private:
	CGrafo<PlanEstudio>* grafo;
	ofstream archivo;
	Vector<string> planes;
	int cantidad_planes;
	int numeracion_aux;
public:
	GrafoPlanEstudio() 
	{
		planes = Vector<string>(100);
		grafo = new CGrafo<PlanEstudio>();
		cantidad_planes = 0;
		lecturaArchivos();
		lecturaDatos();
	}
	void menuPlanEstudio()
	{
		do
		{
			cout << "  -------- Menu de Opciones de Plan de Estudios ----------" << endl << endl;
			cout << "  1. Ingresar nuevo plan de estudios					  " << endl;
			cout << "  2. Mostrar todas los planes de estudio				  " << endl;
			cout << "  3. Salir												  " << endl;
			cout << "  ---------------------------------------------------" << endl;
			verificarOpcion(3);
			if (*opcion == 1) insertarPlanEstudio();
			if (*opcion == 2) listar();

		} while (*opcion != 3);
	}
	void lecturaArchivos()
	{
		string tmp;
		int cont = 0;
		ifstream miarchivo("PlanEstudio.txt");
		if (!miarchivo.fail())
		{
			while (!miarchivo.eof())
			{
				getline(miarchivo, tmp);
				planes.pushBack(tmp);
				//grafo->adicionarVertice(tmp); //inserta la info en el vertice sin arco
				cantidad_planes++;
			}
			miarchivo.close();
		}
	}
	void lecturaDatos()
	{
		int id = 1;
		for (int i = 0; i < cantidad_planes - 1; i++)
		{
			int size = planes.at(i).size();
			int tmp = 0;
			string curso = "";
			string tema = "";
			string aux2 = "";
			Vector<string>* aux = new Vector<string>(50);
			for (int j = 0; j < size; j++)
			{
				if (planes.at(i)[j] != '/')
				{
					aux2 = aux2 + planes.at(i)[j];
				}
				else
				{
					if (tmp == 0) curso = aux2;
					else aux->pushBack(aux2);
					aux2 = "";
					tmp++;
				}
			}
			int a = grafo->adicionarVertice(PlanEstudio(curso, aux));
			id++;
		}
		numeracion_aux = id;
	}
	void insertarPlanEstudio()
	{
		archivo.open("PlanEstudio.txt", ofstream::app);
		string curso, tema, cantidad,opcion;
		Vector<string>* temas = new Vector<string>(50);
		int numeracion = numeracion_aux;
		char opt;
		archivo.open("PlanEstudio.txt", ofstream::app);
		do
		{
			cout << "Nombre del curso:" << endl;
			getline(cin, curso);
			archivo << curso << "/";
			cout << "Numero de modulos(temas):" << endl;
			getline(cin, cantidad);
			int cant = stoi(cantidad);
			for (size_t i = 0; i < cant; i++)
			{
				cout << "Nombre del tema :" << endl;
				getline(cin, tema);
				archivo << tema << "/";
				temas->pushBack(tema);
			}
			archivo << endl;
			cantidad_planes++;
			grafo->adicionarVertice(PlanEstudio(curso,temas));
			numeracion++;
			cout << "Desea continuar registrando un usuario (Si: S, No:N)";
			getline(cin, opcion);
			opt = toupper(opcion[0]);
		} while (opt != 'N');
		archivo.close();
		system("CLS");
	}
	void listar()
	{
		for (int i = 0; i < grafo->cantidadVertices(); i++)
		{
			cout << i << ". " << grafo->obtenerVertice(i).toString() << endl;
		}
	}
};