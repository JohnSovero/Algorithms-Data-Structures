#pragma once
#include "Pila.h"
#include "TopLeaders.h"
#include "HashTableUsuarios.h"
class PilaPuntuaciones:public Base
{
	private:
		Pila<TopLeaders*>* tabla_top;
		Pila<TopLeaders*>* tabla_total;
		Vector<TopLeaders*>* ranking_total;
		int cant_top;
	public:
		PilaPuntuaciones(HashTable<Usuario>* hashTableUsuarios)
		{
			ranking_total = new Vector<TopLeaders*>(hashTableUsuarios->returnCantidad());
			cant_top = 5;
			tabla_top = new Pila<TopLeaders*>(cant_top);
			tabla_total = new Pila<TopLeaders*>(ranking_total->returnCantidad());
			Vector<list<Usuario>> aux = hashTableUsuarios->getContainer();
			for (int i = 0; i < aux.size(); ++i)
			{
				for (auto I : aux[i])
				{
					ranking_total->pushBack(new TopLeaders(I.getNombre(), I.getPuntuacion()));
				}	
			}
		}
		void imprimirRankingTotal()
		{
			generarTablaTotal();
			tabla_total->imprimir([](int i, TopLeaders* e) {cout << i << ". " << e->toString() << endl; });
		}
		void imprimirRankingTop(int n)
		{
			if (n == 1) ordenarRankingShellsort();
			if (n == 2) ordenarRankingCombsort();
			if (n == 3) ordenarRankingGnomeSort();
			generarTablaTop();
			tabla_top->imprimir([](int i, TopLeaders* e) {cout << i << ". " << e->toString() << endl; });
		}
		void generarTablaTotal()
		{
			for (int i = 0; i < ranking_total->returnCantidad(); ++i)
			{
				tabla_total->push(new TopLeaders(ranking_total->at(i)->return_nombre(), ranking_total->at(i)->return_puntos()));
			}
		}
		void generarTablaTop()
		{
			for (int i = cant_top-1; i >= 0; i--)
			{
				tabla_top->push(new TopLeaders(ranking_total->at(i)->return_nombre(), ranking_total->at(i)->return_puntos()));
			}
		}
		void ordenarRankingShellsort() 
		{
			unsigned ti, tf;
			ti = clock();
			ranking_total->shellSort([](TopLeaders* i, TopLeaders* j) {return i->return_puntos() >= j->return_puntos(); });
			tf = clock();
			double tiempo = (double(tf - ti) / CLOCKS_PER_SEC);
			Console::ForegroundColor = ConsoleColor::Red;
			cout << "El tiempo de ejecucion para ordenar el ranking con ShellSort es: " << tiempo << " segundos\n";
			Console::ForegroundColor = ConsoleColor::White;
		}
		void ordenarRankingCombsort() 
		{
			unsigned ti, tf;
			ti = clock();
			ranking_total->combSort([](TopLeaders* i, TopLeaders* j) {return i->return_puntos() < j->return_puntos(); });
			tf = clock();
			double tiempo = (double(tf - ti) / CLOCKS_PER_SEC);
			Console::ForegroundColor = ConsoleColor::Red;
			cout << "El tiempo de ejecucion para ordenar el ranking con CombSort es: " << tiempo << " segundos\n";
			Console::ForegroundColor = ConsoleColor::White;
		}
		void ordenarRankingGnomeSort() 
		{
			unsigned ti, tf;
			ti = clock();
			ranking_total->gnomeSort([](TopLeaders* i, TopLeaders* j) {return i->return_puntos() <= j->return_puntos(); });
			tf = clock();
			double tiempo = (double(tf - ti) / CLOCKS_PER_SEC);
			Console::ForegroundColor = ConsoleColor::Red;
			cout << "El tiempo de ejecucion para ordenar el ranking con gnomeSort es: " << tiempo << " segundos\n";
			Console::ForegroundColor = ConsoleColor::White;
			
		}
		void ordenarRankingDescendentemente() 
		{
			unsigned ti, tf;
			ti = clock();
			ranking_total->shellSort([](TopLeaders* i, TopLeaders* j) {return i->return_puntos() <= j->return_puntos(); });
			tf = clock();
			double tiempo = (double(tf - ti) / CLOCKS_PER_SEC);
			Console::ForegroundColor = ConsoleColor::Red;
			cout << "El tiempo de ejecucion para ordenar el ranking con ShellSort es: " << tiempo << " segundos\n";
			Console::ForegroundColor = ConsoleColor::White;
		}
		void modificarUltimaPuntuacion() 
		{
			generarTablaTop();
			int puntos;
			string aux_puntos;
			cout << "Ingrese los nuevos puntos:" << endl;
			getline(cin, aux_puntos);
			puntos = stoi(aux_puntos);
			unsigned ti, tf;
			ti = clock();
			tabla_top->modifyPeek([=](TopLeaders* i) { i->setPuntos(puntos); });
			tf = clock();
			double tiempo = (double(tf - ti) / CLOCKS_PER_SEC);
			Console::ForegroundColor = ConsoleColor::Red;
			cout << "El tiempo de ejecucion para modificar en la ultima posicin es: " << tiempo << " segundos\n";
			Console::ForegroundColor = ConsoleColor::White;
			imprimirRankingTop(1);
		}
		void elegirPuntuaciones()
		{
			do
			{
				cout << "  -------- Menu de Opciones de Puntuaciones de Usuario ---------" << endl << endl;
				cout << "  1. Ranking Mundial			        						 " << endl;
				cout << "  2. Ranking Top ordenado con Shellsort      					 " << endl;
				cout << "  3. Ranking Top ordenado con Combsort      					 " << endl;
				cout << "  4. Ranking Top ordenado con GnomeSort      					 " << endl;
				cout << "  5. Modificar Puntuacion del ultimo usuario					 " << endl;
				cout << "  6. Salir														 " << endl;
				cout << "  --------------------------------------------------------------" << endl;
				verificarOpcion(6);
				if (*opcion == 1) imprimirRankingTotal();
				if (*opcion == 2) imprimirRankingTop(1);
				if (*opcion == 3) imprimirRankingTop(2);
				if (*opcion == 4) imprimirRankingTop(3);
				if (*opcion == 5) modificarUltimaPuntuacion();
			} while (*opcion != 6);
			opcion = 0;
		}
};

