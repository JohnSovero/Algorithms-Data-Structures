#pragma once
#include "Base.h"
#include "Vector.h"
class PlanEstudio
{
private:
	string curso;
	Vector<string>* tema;
public:
	PlanEstudio(string curso = "",  Vector<string>*tema = nullptr) : curso(curso), tema(tema) 
	{
		tema = new Vector<string>(10);
	}
	void insertarTema(string nuevo) 
	{
		tema->pushBack(nuevo);
	}
	string toString() {
		string aux = "";
		aux = curso;
		for (int i = 0; i < tema->size(); i++)
			aux = aux + "-->" + tema->at(i);
		return aux;
	}
};