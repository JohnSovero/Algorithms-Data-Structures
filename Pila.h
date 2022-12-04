#include <iostream>
#include <string>
#include <functional>
#include <fstream>
using namespace std;

template<class G>
class Nodo2 {
public:
	G dato;
	Nodo2<G>* siguiente;
	Nodo2(G v, Nodo2<G>* sig = nullptr) : dato(v), siguiente(sig) {}
};

template<class G>
class Pila {
private:
	Nodo2<G>* tope;
	int cantidad;
	int id;
public:
	Pila(int cant = 0) :cantidad(cant), tope(NULL),id(0) {}

	void push(G v) 
	{
		if (isEmpty()) {
			tope = new Nodo2<G>(v);
		}
		else {
			tope = new Nodo2<G>(v, tope);
		}
		++id;
	}
	void pop()
	{
		if (isEmpty()) {
			return NULL;
		}
		else {
			tope = (Nodo2<G>*) tope->siguiente;
			--id;
		}
	}
	G peekPop() 
	{
		if (isEmpty()) {
			return NULL;
		}
		else {
			G elemento = (G)(tope->dato);
			tope = (Nodo2<G>*) tope->siguiente;
			--id;
			return elemento;
		}
	}
	G peek()
	{
		if (isEmpty()) {
			return NULL;
		}
		else {
			G elemento = (G)(tope->dato);
			return elemento;
		}
	}
	void modifyPeek(function<void(G)> aux) {
		aux(tope->dato);
	}
	void ordenarLambdas(function<bool(G, G)> condicion)
	{
		Nodo2<G>* p = tope;
		while (p != nullptr)
		{
			Nodo2<G>* j = p->siguiente;
			while (j != nullptr)
			{
				if (condicion(p->dato, j->dato))
				{
					G aux = j->dato;
					j->dato = p->dato;
					p->dato = aux;
				}
				j = j->siguiente;
			}
			p = p->siguiente;
		}
	}
	bool isEmpty() 
	{
		return (tope == NULL);
	}
	bool isFull()
	{
		return (cantidad == id);
	}
	void imprimir(function<void(int, G)> imprime)
	{
		G elem;
		int i = 1;
		do {
			elem = peekPop();
			if (elem != NULL) imprime(i,elem);
			i++;
		} while (elem != NULL);
	}
	//recursivo
	void clear(int aux)
	{
		if (aux == 0) return;
		pop();
		clear(id);
	}
};