#pragma once
#include <functional>
#include "Base.h"
using namespace std;
using namespace System;
template <class T>
class Vector {
	T* elems;
	int cap;
	long long n;
	int pos;
public:
	class iterator {
		int i;
		T* elems;
	public:
		iterator(int i = 0, T* elems = nullptr)
			: i(i), elems(elems) {}
		void operator ++ () {
			i++;
		}
		T operator * () {
			return elems[i];
		}
		bool operator != (iterator b) {
			return this->i != b.i;
		}
	};

	iterator begin() {return iterator(0, elems);}
	iterator end() {return iterator(n, nullptr);}
	Vector(int cap = 1200000):cap(cap),	n(0) 
	{
		elems = new T[cap];
		pos = 0;
	}
	/*~Vector();*/
	/*~Vector() {delete[]elems; }*/
	T operator[] (int i) const {return elems[i];}
	T& operator[] (int i) {return elems[i];}
	long size() { return n; }
	void pushBack(T e) { elems[n++] = e; }
	void Merge(T* A1, T* A2, T* A, int n, function<bool(T, T)> orden) 
	{
		int i = 0, j = 0, k = 0;
		int mitad = n / 2;
		while (i < mitad && j < n - mitad) {
			if (orden(A1[i], A2[j])) {
				A[k] = A1[i];
				i++; k++;
			}
			else {
				A[k] = A2[j];
				j++; k++;
			}
		}
		while (i < mitad) {
			A[k] = A1[i];
			i++; k++;
		}
		while (j < n - mitad) {
			A[k] = A2[j];
			j++; k++;
		}
	}
	void mergeSort(T* e, int n, function<bool(T, T)> orden) 
	{
		if (n > 1) {
			int mitad = n / 2;
			T* A1 = new T[mitad];
			T* A2 = new T[n - mitad];

			for (int i = 0; i < mitad; i++) {
				A1[i] = e[i];
			}
			for (int i = mitad; i < n; i++) {
				A2[i - mitad] = e[i];
			}
			mergeSort(A1, mitad, orden);
			mergeSort(A2, n - mitad, orden);
			Merge(A1, A2, e, n, orden);
		}
	}
	void shellSort(function<bool(T, T)> cmp)
	{
		int i, j, k;
		int intervalo = n / 2;
		T temp;
		while (intervalo > 0)
		{
			for (i = intervalo; i < n; i++)
			{
				j = i - intervalo;
				while (j >= 0)
				{
					k = j + intervalo; //queda k=i;
					if (cmp(elems[j], elems[k])) j = -1; /*termina el bucle, par ordenado */
					else {
						temp = elems[j];
						elems[j] = elems[k];
						elems[k] = temp;
						j -= intervalo;
					}
				}
			}
			intervalo = intervalo / 2;
		}
	}
	void gnomeSort(function<bool(T, T)> cmp)
	{
		int auxi = 0;
		do
		{
			if (auxi == 0)
			{
				auxi++;
			}
			if (cmp(elems[auxi], elems[auxi - 1]))
			{
				auxi++;
			}
			else
			{
				swap(elems[auxi], elems[auxi - 1]);
				auxi = auxi - 1;
			}
		} while (auxi < n);
	}
	int getNextGap(int gap)
	{
		gap = (gap * 10) / 13;

		if (gap < 1)
			return 1;
		return gap;
	}
	void combSort(function<bool(T, T)> cmp)
	{
		int gap = n;
		bool swapped = true;
		while (gap != 1 || swapped == true)
		{
			gap = getNextGap(gap);
			swapped = false;
			for (int i = 0; i < n - gap; i++)
			{
				if (cmp(elems[i], elems[i + gap]))
				{
					swap(elems[i], elems[i + gap]);
					swapped = true;
				}
			}
		}

	}
	void ordenar(function<bool(T, T)> condicion)
	{
		for (size_t i = 0; i < n - 1; i++)
		{
			for (size_t j = i; j < n; j++)
			{
				if (condicion(elems[i], elems[j]))
				{
					T aux = elems[i];
					elems[i] = elems[j];
					elems[j] = aux;
				}
			}
		}
	}
	void eliminar(function<bool(T)> condicion)
	{
		int j = 0;
		int cont = 0;
		for (int i = 0; i < n; i++)
		{
			if (!condicion(elems[i]))++cont;
		}
		T* aux = new T[n - cont];
		for (int i = 0; i < n; ++i)
		{
			if (condicion(elems[i]))
			{
				aux[j] = elems[i];
				j++;
			}
		}
		n -= cont;
		elems = aux;
	}
	void modificarEnPos(function<bool(T)> condicion, function<void(T)> modifica)
	{
		for (int i = 0; i < n; i++)
		{
			if (condicion(elems[i]))
			{
				modifica(elems[i]);
			}
		}
	}
	T at(int pos)
	{
		if (elems != nullptr)	return elems[pos];
		else cout << "\nEl arreglo esta vacio";
	}
	void imprimirIntervalo(function<void(T)> imprime, short pos, short intervalo)
	{
		if (intervalo == 0)return;
		imprime(elems[pos]);
		imprimirIntervalo(imprime, pos + 1, intervalo - 1);
	}
	void imprimirDatos(function<void(T)> imprime)
	{
		pos = 0;
		while (pos != n)
		{
			if (pos == (n - 25)) {
				cout << "FELO";
			}
			imprime(elems[pos]);
			++pos;

		}
	}
	int returnCantidad() { return n; }
	T* retornar_elems() { return elems; }
	bool empty() { return n == 0; }
};
//template<class T>
//Vector<T>::~Vector() { delete[] elems; }