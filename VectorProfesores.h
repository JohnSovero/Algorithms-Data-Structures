#pragma once
#include "Vector.h"
#include "Profesor.h"
class VectorProfesores:public Base
{
private:
	Vector<Profesor*> *profesores;
	ofstream archivo;
	Vector<string> *resultado;
	size_t cant_profesores;
	int numeracion_aux;
	int atProfesor;
public:
	VectorProfesores()
	{
		profesores = new Vector<Profesor*>(100);
		resultado = new Vector<string>(100);
		string linea;
		ifstream miarchivo("Profesores.txt");
		cant_profesores = 0;
		numeracion_aux = 0;
		if (!miarchivo.fail())
		{
			while (!miarchivo.eof())
			{
				getline(miarchivo, linea);
				resultado->pushBack(linea);
				cant_profesores++;
			}
			miarchivo.close();
		}
		leerProfesores();
	}
	void elegirProfesor()
	{
		do
		{
			cout << "  -------- Menu de Opciones de Profesor ---------" << endl << endl;
			cout << "  1. Ingresar nuevo profesor					  " << endl;
			cout << "  2. Mostrar todos los profesores				  " << endl;
			cout << "  3. Eliminar profesor por nombre				  " << endl;
			cout << "  4. Modificar profesor por nombre				  " << endl;
			cout << "  5. Salir						                  " << endl;
			cout << "  -----------------------------------------------" << endl;
			verificarOpcion(4);
			if (*opcion == 1) insertar();
			if (*opcion == 2) imprimirProfesores();
			if (*opcion == 3) eliminarNombre();
			if (*opcion == 4) modificarProfesor();
		} while (*opcion != 5);
		*opcion = 0;
	}
	void leerProfesores()
	{
		atProfesor = -1;
		size_t id = 0;
		string numeracion = "";
		string nivel = "";
		string nombre = "";
		string idioma = "";
		string aux2 = "";
		Vector<Profesor*>* aux = new Vector<Profesor*>();
		for (size_t i = 0; i < cant_profesores - 1; i++)
		{
			id = 0;
			numeracion = "";
			nivel = "";
			nombre = "";
			idioma = "";
			aux2 = "";
			size_t size = resultado->at(i).size();
			for (size_t j = 0; j < size + 1; j++)
			{
				if (resultado->at(i)[j] == '-')
				{
					if (id == 0)numeracion = aux2;
					else if (id == 1)nivel = aux2;
					else if (id == 2)nombre = aux2;
					else idioma = aux2;
					aux2 = "";
					id++;
				}
				else aux2 = aux2 + resultado->at(i)[j];
			}
			aux->pushBack(new Profesor(stoi(numeracion), stoi(nivel), nombre, idioma));
		}
		numeracion_aux = stoi(numeracion);
		profesores = aux;
	}
	void insertar()
	{
		int numeracion = numeracion_aux;
		int nivel;
		string nombre;
		string idioma;
		string aux_nivel;
		string opcion;
		ofstream archivo;
		char aux;
		archivo.open("Profesores.txt", ofstream::app);
		do
		{
			cout << "Nivel :" << endl;
			getline(cin, aux_nivel);
			cout << "Nombre :" << endl;
			getline(cin, nombre);
			cout << "Idioma :" << endl;
			getline(cin, idioma);
			nivel = stoi(aux_nivel);
			numeracion++;
			cant_profesores++;
			profesores->pushBack(new Profesor(numeracion,nivel, nombre, idioma));
			archivo << numeracion << "-" << nivel << "-" << nombre << "-" << idioma << "-" << endl;
			cout << "Desea continuar registrando un profesor (Si: S, No:N)";
			getline(cin, opcion);
			aux = toupper(opcion[0]);
		} while (aux != 'N');
		system("CLS");
		archivo.close();
	}
	void imprimirProfesores()
	{
		cout << "----------------Lista de Profesores-----------------" << endl;
		profesores->imprimirDatos([](Profesor* e) {cout << e->toString() << endl; });
	}
	void ordenarNivel()
	{
		profesores->ordenar([](Profesor* a, Profesor* b) {return a->getNivel() > b->getNivel(); });
	}
	void eliminarNombre()
	{
		string aux = " ";
		cout << "Ingrese el nombre del profesor a eliminar:" << endl;
		getline(cin, aux);
		profesores->eliminar([=](Profesor* e) {return e->getNombre() == aux; });
	}
	void modificarProfesor() 
	{ 
		string aux = " ";
		int nivel;
		string aux_nivel;
		cout << "Ingrese el nombre del profesor a modificar:" << endl;
		getline(cin, aux);
		cout << "Ingrese el nuevo nivel:" << endl;
		getline(cin, aux_nivel);
		nivel = stoi(aux_nivel);
		profesores->modificarEnPos([=](Profesor* e) { return e->getNombre() == aux; }, [=](Profesor* e) {e->setNivel(nivel); });
		imprimirProfesores();
	}
	void elegirProfesor(size_t posicion) { atProfesor = posicion - 1; }
	int retornarProfesorElegido() { return atProfesor; }
};

