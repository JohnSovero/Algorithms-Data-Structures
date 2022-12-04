#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
using namespace System;
class Base
{
protected:
	int *opcion;
public:
	Base() { opcion = new int;  *opcion = -1; }
	~Base(){}
	void verificarOpcion(short limite)
	{
		string opc = "";
		do
		{
			getline(cin, opc);
			*opcion = stoi(opc);
			system("CLS");
		} while (*opcion < 0 && *opcion > limite);	
	}
};