#pragma once
#include <iostream>
#include <string>
#include "Vector.h"
using namespace std;

class Pagos
{
private:
	int id;
	int importe;
	string nombrepago;
	string informacion;
public:
	Pagos(int opcion = 0, string nombrepago = "", string informacion = "", int importe = 0) : id(opcion),nombrepago(nombrepago),informacion(informacion), importe(importe){}
	int getImporte() { return importe; }
	void setImporte(int aux) { importe = aux; }
	int getId() { return id; }
	void setId(int aux) { id = aux; }
	string NombrePago() { return nombrepago; }
	void setNombrePago(string aux) { nombrepago = aux; }
	string toString() 
	{
		string tmp = "";
		if (id == 0)return tmp;
		else tmp = nombrepago + " --> S/." + to_string(importe) + "\n- Detalle: " + informacion+"\n";
		return tmp;
	}
};