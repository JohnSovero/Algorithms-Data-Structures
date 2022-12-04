#pragma once
#include "ArbolRojoNegro.h"
#include "Pagos.h"
#include "Vector.h"

class ArbolPagos :public Base
{
private:
	ArbolRojoNegro<Pagos>* _ArbolPagos;
	Vector<string>* pagos;
	int tipopago;
	int cantPlanes;
	ofstream archivo;
public:
	ArbolPagos()
	{
		pagos = new Vector<string>(100);
		cantPlanes = 0;
		_ArbolPagos = new ArbolRojoNegro<Pagos>([](Pagos a, Pagos b) {return a.getId() >= b.getId(); }, [](Pagos p1) {cout << p1.toString(); });
		lecturaArchivos();
		lecturaDatos();
	}
	void MenuPagos()
	{
		do
		{
			cout << "  --------Menu de Planes Premium----------" << endl << endl;
			cout << "  1. Consultar los planes de pago disponibles					  " << endl;
			cout << "  2. Salir										  " << endl;
			cout << "  ---------------------------------------------------" << endl;
			verificarOpcion(2);
			if (*opcion == 1) ListaPagos();
		} while (*opcion != 2);
	}
	void lecturaArchivos()
	{
		string tmp;
		ifstream miarchivo("Pagos.txt");
		if (!miarchivo.fail())
		{
			while (!miarchivo.eof())
			{
				getline(miarchivo, tmp);
				pagos->pushBack(tmp);
				cantPlanes++;
			}
			miarchivo.close();
		}
	}
	void lecturaDatos()
	{
		int id = 1;
		for (int i = 0; i < cantPlanes - 1; i++)
		{
			int size = pagos->at(i).size();
			int tmp = 0;
			string nombrepago = "";
			string informacion = "";
			string importe = "";
			string aux2 = "";
			for (int j = 0; j < size; j++)
			{
				if (pagos->at(i)[j] != '/')
				{
					aux2 = aux2 + pagos->at(i)[j];
				}
				else
				{
					if (tmp == 0) nombrepago = aux2;
					if (tmp == 1) informacion = aux2;
					if (tmp == 2) importe = aux2;
					aux2 = "";
					tmp++;
				}
			}
			_ArbolPagos->insertar(Pagos(id, nombrepago, informacion, stoi(importe)));
			id++;
		}
	}
	void ListaPagos()
	{
		cout << "PLanes de Pago Disponibles: " << endl;
		_ArbolPagos->print();
	}
};