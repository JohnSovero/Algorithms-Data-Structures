#pragma once
#include "Base.h"
#include <functional>
#include <fstream>

template <class T>
class Arbol {
	template <class T>
	class Node {
	public:
		Node<T>* izquierda;
		Node<T>* derecha;
		T e;
		Node(T e) {
			derecha = izquierda = nullptr; this->e = e;
		}
	};
	typedef function<int(T, T)> Comp;
	Node<T>* root;
	function<void(T)>fprint;
	Comp comparar;
	function<bool(T, T)>compare;
	friend class ArbolUsuarios;
public:
	Arbol(function<bool(T, T)>compare, function<void(T)>f) :compare(compare), fprint(f) 
	{
		root = nullptr;
	}
	void add(T e, Node<T>*& tmp) 
	{
		if (tmp == nullptr) tmp = new Node<T>(e);
		else if (compare(e, root->e)) add(e, tmp->derecha);//inserta por la derecha
		else add(e, tmp->izquierda);//inserta por la izquierda
	}
	void insert(T e) 
	{
		add(e, root);
	}
	void print(Node<T>* tmp) // Recorrido en orden
	{
		if (tmp == nullptr)return;
		print(tmp->izquierda);// Recurisvamente a la izquierda
		fprint(tmp->e);//imprime valor
		print(tmp->derecha);// Recursivamente a la derecha
	}
	void print()
	{
		print(root);
	}
	void printPostOrden()
	{
		PostOrden(root);
	}
	void PostOrden(Node<T>* tmp)
	{
		if (tmp == nullptr)return;
		PostOrden(tmp->derecha);
		PostOrden(tmp->izquierda);
		fprint(tmp->e);
	}
};