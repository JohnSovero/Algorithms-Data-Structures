#pragma once
#include "Vector.h"
#include "HashTableUsuarios.h"
class Idioma:public Base
{
	private:
		unsigned short n;
		string alternativa;
		Vector<string> datos;
		HashTableUsuarios* usuarios;
		string nombre;
	public:
		Idioma(){}
		void leerArchivos(string _nombre)
		{
			datos = Vector<string>(1000);
			nombre = _nombre;
			string linea;
			ifstream miarchivo(nombre + ".txt");
			if (!miarchivo.fail())
			{
				while (!miarchivo.eof())
				{
					getline(miarchivo, linea);
					datos.pushBack(linea);
				}
				miarchivo.close();
			}
			leerPreguntas();
		}
		void leerPreguntas()
		{
			n = 10;
			niveles(n);
			/*usuarios->guardar();*/
		}
		void niveles(short n)
		{
			int at;
			if (n == 0)return;
			niveles(n - 1);
			do {
				cout << "Nivel " << n << endl;
				datos.imprimirIntervalo([](string e) {cout << e << endl; }, 5 * n - 4, 4);
				getline(cin, alternativa);
				for (int i = 0; i < 10000; ++i)
				{
					for (auto I : usuarios->retornarUsuarios()->getContainer()[i])
					{
						if (I.getNumeracion() == usuarios->retornarUsuarioElegido())
						{
							if (alternativa[0] == datos.at(5 * n)[0])I.addPuntuacion(60);
						}
					}
				}
				at = usuarios->retornarUsuarioElegido();
			} while (alternativa[0] != datos.at(5*n)[0]);
		}
		void elegirIdioma(HashTableUsuarios* registros)
		{
			usuarios = registros;
			if (usuarios->seleccionarUsuario()) {
				do
				{
					cout << "  -------- Menu de Opciones de  Idiomas ---------" << endl << endl;
					cout << "  1. Ingles          							  " << endl;
					cout << "  2. Frances                   				  " << endl;
					cout << "  3. Salir										  " << endl;
					cout << "  -----------------------------------------------" << endl;
					verificarOpcion(3);
					if (*opcion == 1) leerArchivos("Ingles");
					if (*opcion == 2) leerArchivos("Frances");
				} while (*opcion != 3);
			}
		}
};

