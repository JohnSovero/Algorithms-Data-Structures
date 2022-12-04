#pragma once
#include "HashTableUsuarios.h"

class TopLeaders
{
private:
	string nombre;
	int puntos;
public:
	TopLeaders(string nombre= "", int puntos = 0) :nombre(nombre),puntos(puntos) {}
	string return_nombre() { return nombre; };
	int return_puntos() { return puntos; }
	void setNombre(string valor) { nombre = valor; };
	void setPuntos(int valor) { puntos = valor; }
	string toString() { return nombre + " - " + to_string(puntos); }
};