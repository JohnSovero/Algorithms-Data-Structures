#pragma once
#include "ArbolRojoNegro.h"
#include "Vector.h"
#include "Promociones.h"
class ArbolPromociones:public Base
{
private:
	ArbolRojoNegro<Promociones>* arbolPromociones;
	ofstream archivo;
	Vector<string>* promociones;
	int cantidad_promociones;
	int numeracion_aux;
public:
	ArbolPromociones()
	{
		promociones = new Vector<string>(100);
		arbolPromociones = new ArbolRojoNegro<Promociones>([](Promociones a, Promociones b) {return a.getId() >= b.getId(); }, [](Promociones a) {cout << a.toString() << endl; });
		cantidad_promociones = 0;
		lecturaArchivos();
		lecturaDatos();
	}
	void menuPromocion()
	{
		do
		{
			cout << "  -------- Menu de Opciones de Promociones ----------" << endl << endl;
			cout << "  1. Ingresar nueva promocion					  " << endl;
			cout << "  2. Mostrar todas las promociones				  " << endl;
			cout << "  3. Salir										  " << endl;
			cout << "  ---------------------------------------------------" << endl;
			verificarOpcion(3);
			if (*opcion == 1) insertarPromocion();
			if (*opcion == 2) listar();

		} while (*opcion != 3);
	}
	void lecturaArchivos()
	{
		string tmp;
		ifstream miarchivo("Promociones.txt");
		if (!miarchivo.fail())
		{
			while (!miarchivo.eof())
			{
				getline(miarchivo, tmp);
				promociones->pushBack(tmp);
				cantidad_promociones++;
			}
			miarchivo.close();
		}
	}
	void lecturaDatos()
	{
		int id = 1;
		for (size_t i = 0; i < cantidad_promociones - 1; i++)
		{
			int size = promociones->at(i).size();
			int tmp = 0;
			string nombre = "";
			string detalle = "";
			string descuento = "";
			string aux2 = "";
			for (size_t j = 0; j < size; j++)
			{
				if (promociones->at(i)[j] != '/')
				{
					aux2 = aux2 + promociones->at(i)[j];
				}
				else
				{
					if (tmp == 0) nombre = aux2;
					if (tmp == 1) detalle = aux2;
					if (tmp == 2) descuento = aux2;
					aux2 = "";
					tmp++;
				}
			}
			arbolPromociones->insertar(Promociones(id, nombre, detalle,stoi(descuento)));
			id++;
		}
		numeracion_aux = id;
	}
	void listar() 
	{
		cout << "---------------- Arbol de Promociones -----------------" << endl;
		arbolPromociones->print();
	}
	void insertarPromocion()
	{
		cout << "----------------Ingresando una nueva Promocion -----------------" << endl;
		string nombre, detalle,descuento, opcion;
		archivo.open("Promociones.txt", ofstream::app);
		int numeracion = cantidad_promociones-1;
		char opt;
		do
		{
			cout << "Ingrese el nombre de la Promocion :" << endl;
			getline(cin, nombre);
			cout << "Ingrese el detalle de la Promocion :" << endl;
			getline(cin, detalle);
			cout << "Ingrese el descuento de la Promocion (en caso no tener colocar 0) :" << endl;
			getline(cin, descuento);
			++cantidad_promociones;
			++numeracion;
			arbolPromociones->insertar(Promociones(numeracion, nombre,detalle,stoi(descuento)));
			archivo << nombre << "/" << detalle << "/" << descuento << "/" << endl;
			cout << "Desea continuar registrando una Promocion (Si: S, No:N)";
			getline(cin, opcion);
			opt = toupper(opcion[0]);
		} while (opt != 'N');
		system("CLS");
	}
};