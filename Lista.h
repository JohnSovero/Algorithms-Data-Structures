#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <fstream>
#include "Base.h"
using namespace std;

template<class G>
class Nodo {
public:
	G elemento;
	Nodo<G>* sig;
	Nodo<G>* ant;
	Nodo(G elemento, Nodo<G>* sig=nullptr, Nodo<G>* ant=nullptr):elemento(elemento),sig(sig),ant(ant){}
};

template<class G>
class Lista {
private:
	Nodo<G>* inicio;
	Nodo<G>* fin;
	int cantidad;
public:
	Lista() 
	{
		inicio = fin = nullptr;
		cantidad = 0;
	}
	void pushFront(G e) 
	{
		Nodo<G>* n = new Nodo<G>(e);
		if (cantidad == 0)
			inicio = fin = n;
		else {
			n->sig = inicio;
			inicio->ant = n;
			inicio = n;
		}
		++cantidad;
	}
	void pushBack(G elem)
	{
		Nodo<G>* nuevo = new Nodo<G>(elem);
		if (cantidad == 0)
			inicio =fin= nuevo;
		else
		{
			fin->sig = nuevo;
			nuevo->ant = fin;
			fin = nuevo;
		}
		++cantidad;
	}
	G at(short i)
	{
		Nodo<G>* aux = inicio;
		size_t cont = 0;
		while (cont != i && aux != nullptr)
		{
			aux = aux->sig;
			cont++;
		}
		return aux->elemento;
	}
	//void imprimir_con_lambdas(function<void(Generico)> imprime) {
	//	Nodo<Generico>* aux = inicio;
	//	while (aux != nullptr) {
	//		imprime(aux->elemento);
	//		aux = aux->sig;
	//	}
	//}
	/*void imprimir_recursivamente_lambdas(function<void(Generico)> imprime, Nodo<Generico>* aux) {
	//	if (aux == nullptr) return;
	//	imprime(aux->elemento);
	//	aux = aux->sig;
	//	imprimir_recursivamente_lambdas(imprime, aux);
	}*/
	//recursivo
	void imprimirRecursivaLambdasCondicion(function<void(G)> imprime, Nodo<G>* aux, function<bool(G)> condicion) 
	{
		if (aux == nullptr) return;
		if (condicion(aux->elemento)) {
			imprime(aux->elemento);
		}
		aux = aux->sig;
		imprimirRecursivaLambdasCondicion(imprime, aux, condicion);
	}
	void imprimirDatos(function<void(G)> imprime, Nodo<G>* aux)
	{
		while (aux != nullptr)
		{
			imprime(aux->elemento);
			aux = aux->sig;
		}
	}
	void eliminarLambdas(function<bool(G)> condicion) 
	{
		Nodo<G>* actual = inicio;
		Nodo<G>* antes = nullptr;
		while (actual != nullptr && condicion(actual->elemento))
		{
			antes = actual;
			actual = actual->sig;
		}
		if (actual == nullptr)
		{
			cout << "No existe el valor a eliminar" << endl;
		}
		else if (antes == nullptr)
		{
			inicio = inicio->sig;
			--cantidad;
			delete actual;
		}
		else if (actual->sig == nullptr)
		{
			antes->sig = nullptr;
			--cantidad;
			fin = antes;
			delete actual;
		}
		else
		{
			antes->sig = actual->sig;
			--cantidad;
			delete actual;
		}
	}
	void eliminartodo() {
		Nodo<Generico>* actual = inicio;
		Nodo<Generico>* antes = nullptr;
		do
		{
			antes = actual;
			actual = actual->sig;
			delete actual;
		} while (actual != nullptr);
	}
	void buscarLambdas(function<bool(G)> condicion)
	{
		Nodo<G>* actual = inicio;
		Nodo<G>* antes = nullptr;
		
		while (actual != nullptr && condicion(actual->elemento))
		{
			antes = actual;
			actual = actual->sig;
		}
		if (actual == nullptr)
		{
			cout << "No existe" << endl;
		}
		else if (antes == nullptr)
		{
			cout << "Se encontro" << endl;
		}
		else
		{
			cout << "Se encontro" << endl;
		}
	}
	void ordenarLambdas(function<bool(G, G)> condicion)
	{
		Nodo<G>* p = inicio;
		while (p != nullptr)
		{
			Nodo<G>* j = p->sig;
			while (j != nullptr)
			{
				if(condicion(p->elemento, j->elemento))
				{
					G aux = j->elemento;
					j->elemento = p->elemento;
					p->elemento = aux;
				}
				j = j->sig;
			}
			p = p->sig;
		}
	}
	Nodo<G>* retornarNodoInicio() { return inicio; }
	int retornarCantidad(){ return cantidad; }
};


