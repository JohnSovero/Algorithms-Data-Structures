#pragma once
#include "Vector.h"
#include <list>
#include <functional>
using namespace std;
template <class T>

class HashTable {
	Vector<list<T>> container;
	list<T> aux_delete;
	function<int(T)> funcionHash;
	int cantidad_elems;
public:
	HashTable(function<int(T)> funcionHash) :funcionHash(funcionHash)
	{
		int cap_ht = 1000;
		/*container = Vector<list<T>>(cap_ht+10);*/
		for (int i = 0; i < cap_ht; ++i)
		{
			container.pushBack(list<T>());
		}
		cantidad_elems = 0;
	}
	void add(T key)
	{
		container[funcionHash(key)].push_back(key);
		cantidad_elems++;
	}
	bool buscar(function<bool(T)> condicion_find, int pos)
	{
		Vector<T> aux_find = Vector<T>(cantidad_elems);
		if (!container[pos].empty())
		{
			for (T it : container[pos])
			{
				if (condicion_find(it)) aux_find.pushBack(it);
			}
			if (!aux_find.empty())
			{
				for (auto it : aux_find)
				{
					cout << it.toString() << "\n";
				}
				
				return true;
			}
			else
			{
				
				return false;
			}
		}
		else
		{
			
			return false;
		}
	}
	bool buscar2(function<bool(T)> condicion_find, int pos)
	{
		Vector<T> aux_find = Vector<T>(cantidad_elems);
		if (!container[pos].empty())
		{
			for (T it : container[pos])
			{
				if (condicion_find(it)) aux_find.pushBack(it);
			}
			if (!aux_find.empty())
			{
				int cont = 1;
				for (auto it : aux_find)
				{
					cout << cont << ". " << it.toString2() << "\n";
					++cont;
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	T retornar_pos(function<bool(T)> condicion_find, int num, int pos)
	{
		Vector<T> aux = Vector<T>(cantidad_elems);
		for (T it : container[pos])
		{
			if (condicion_find(it)) aux.pushBack(it);
		}
		int cont = 1;
		for (T it : aux)
		{
			if (cont == num)
			{
				return it;
			}
			else
			{
				++cont;
			}
		}
	}
	void ordenarMergeSort(function<bool(T, T)> criterio)
	{
		serializacion();
		Vector<T> aux_sort = Vector<T>(container.returnCantidad());
		aux_sort.mergeSort(aux_sort.retornar_elems(), aux_sort.returnCantidad(), criterio);
		/*for (auto it : aux_sort)
		{
			cout << it.toString() << "\n";
		}*/
	}
	bool eliminar(function<bool(T)> condicion_delete, int pos, string nombre)
	{
		if (!container[pos].empty())
		{
			for (auto it : container[pos])
			{
				if (it.getNombre() != nombre) aux_delete.push_back(it);
			}
			container[pos] = aux_delete;
			for (auto it : container[pos])
			{
				cout << it.toString() << "->" << "\n";
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	void serializacion()
	{
		Vector<T> aux_sort = Vector<T>(cantidad_elems);
		for (int i = 0; i < container.size(); ++i)
		{
			for (auto it : container[i])
			{
				aux_sort.pushBack(it);
			}
		}
	}
	void display()
	{
		int tamano = container.size();
		for (int i = 0; i < tamano; ++i)
		{
			cout << i << "->";
			for (auto it : container[i])
			{
				cout << it.toString() << "->" << "\n";
			}
			cout << "\n";
		}
	}
	Vector<list<T>> getContainer() { return container; }
	int returnCantidad() { return cantidad_elems; }
};