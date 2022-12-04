#pragma once
#include "Base.h"
#include "Vector.h"
using namespace std;

class Promociones
{
private:
	string nombre;
	string detalle;
	int descuento;
	int id;
public:
	Promociones(int id = 0, string nombre = " ", string detalle = " ", int descuento = 0) :id(id), nombre(nombre), detalle(detalle), descuento(descuento){}
	int getId() { return id; }
	void setId(int nuevo) { id = nuevo; }
	string getNombre() { return nombre; }
	void setNombre(string nuevo) { nombre = nuevo; }
	string getDetalle() { return detalle; }
	void getDetalle(string nuevo) { detalle = nuevo; }
	int getDescuento() { return descuento; }
	void setDescuento(int nuevo) { descuento = nuevo; }
	string toString() 
	{ 
		string tmp = "";
		if (id == 0)return tmp;
		if (descuento==0)
		{
			tmp = to_string(id) + ". " + nombre + " = " + detalle;
		}
		else
		{
			tmp = to_string(id) + ". " + nombre + " = " + detalle + " -> Se le otorgara el descuento de " + to_string(descuento) + "%";
		}
		return tmp;
	}
};