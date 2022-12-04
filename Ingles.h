#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <fstream>

using namespace std;

class Ingles
{
private:
	unsigned short n;
	string alternativa;
	vector<string>datos; //estructura
public:
	Ingles()
	{
		n = 1;
		string linea;
		ifstream miarchivo("Ingles.txt");
		if (!miarchivo.fail())
		{
			while (!miarchivo.eof())
			{
				getline(miarchivo, linea);
				datos.push_back(linea);
			}
			miarchivo.close();
		}
	}
	//void Recalibracion(){}
	void Niveles(short n)
{
	cout << "Nivel " << n << endl;
	cout << datos.at(n) << endl;
	getline(cin, alternativa);
	if (alternativa[0] == datos.at(n + 1)[0])
	{
		/*usuario->maspuntuacion();*/
		system("CLS");
		Niveles(++n);
	}
}

};

