#pragma once
#define BLACK 1
#define RED 0
#include "Base.h"
#include<functional>

template<class T>
class ArbolRojoNegro {
private:
    //atributos
    template<class T>
    class Node {
    public:
        T valor;
        bool color;
        Node<T>* izquierdaArbol, * derechaArbol, * padre;
        //funciones
        Node() : color(RED), izquierdaArbol(nullptr), derechaArbol(nullptr), padre(nullptr) {}
        Node<T>* abuelo() {
            if (padre == nullptr) {
                return nullptr;
            }
            return padre->padre;
        }
        Node<T>* tio() {
            if (abuelo() == nullptr) {
                return nullptr;
            }
            if (padre == abuelo()->derechaArbol)
                return abuelo()->izquierdaArbol;
            else
                return abuelo()->derechaArbol;
        }
        Node<T>* hermano() {
            if (padre->izquierdaArbol == this)
                return padre->derechaArbol;
            else
                return padre->izquierdaArbol;
        }
    };
    Node<T>* root, * NIL;
    function<void(T)>fprint;
    function<bool(T, T)>compare;
    friend class ArbolPromociones;
    //funciones
    void rotarDerecha(Node<T>* p) 
    {
        Node<T>* gp = p->abuelo();
        Node<T>* fa = p->padre;
        Node<T>* y = p->derechaArbol;

        fa->izquierdaArbol = y;

        if (y != NIL)
            y->padre = fa;
        p->derechaArbol = fa;
        fa->padre = p;

        if (root == fa)
            root = p;
        p->padre = gp;

        if (gp != NULL) {
            if (gp->izquierdaArbol == fa)
                gp->izquierdaArbol = p;
            else
                gp->derechaArbol = p;
        }

    }
    void rotarIzquierda(Node<T>* p) 
    {
        if (p->padre == NULL) {
            root = p;
            return;
        }
        Node<T>* gp = p->abuelo();
        Node<T>* fa = p->padre;
        Node<T>* y = p->izquierdaArbol;

        fa->derechaArbol = y;

        if (y != NIL)
            y->padre = fa;
        p->izquierdaArbol = fa;
        fa->padre = p;

        if (root == fa)
            root = p;
        p->padre = gp;

        if (gp != NULL) {
            if (gp->izquierdaArbol == fa)
                gp->izquierdaArbol = p;
            else
                gp->derechaArbol = p;
        }
    }
    void enOrden(Node<T>* p) 
    {
        if (p == NIL)
            return;

        if (p->izquierdaArbol)
            enOrden(p->izquierdaArbol);

        cout << p->valor << " ";

        if (p->derechaArbol)
            enOrden(p->derechaArbol);
    }
    string outputColor(bool color) 
    {
        return color ? "BLACK" : "RED";
    }
    Node<T>* getMenorHijo(Node<T>* p) {
        if (p->izquierdaArbol == NIL)
            return p;
        return getMenorHijo(p->izquierdaArbol);
    }
    bool eliminarHijo(Node<T>* p, T data) 
    {
        if (p->valor > data) {
            if (p->izquierdaArbol == NIL) {
                return false;
            }
            return eliminarHijo(p->izquierdaArbol, data);
        }
        else if (p->valor < data) {
            if (p->derechaArbol == NIL) {
                return false;
            }
            return eliminarHijo(p->derechaArbol, data);
        }
        else if (p->valor == data) {
            if (p->derechaArbol == NIL) {
                EliminarUnHijo(p);
                return true;
            }
            Node<T>* smallest = getMenorHijo(p->derechaArbol);
            swap(p->valor, smallest->valor);
            EliminarUnHijo(smallest);

            return true;
        }
        else {
            return false;
        }
    }
    void EliminarUnHijo(Node<T>* p) 
    {
        Node<T>* child = p->izquierdaArbol == NIL ? p->derechaArbol : p->izquierdaArbol;
        if (p->padre == nullptr && p->izquierdaArbol == NIL && p->derechaArbol == NIL) {
            p = nullptr;
            root = p;
            return;
        }

        if (p->padre == nullptr) {
            delete  p;
            child->padre = nullptr;
            root = child;
            root->color = BLACK;
            return;
        }

        if (p->padre->izquierdaArbol == p) {
            p->padre->izquierdaArbol = child;
        }
        else {
            p->padre->derechaArbol = child;
        }
        child->padre = p->padre;

        if (p->color == BLACK) {
            if (child->color == RED) {
                child->color = BLACK;
            }
            else
                eliminarCaso(child);
        }

        delete p;
    }
    void eliminarCaso(Node<T>* p)
    {
        if (p->padre == nullptr) {
            p->color = BLACK;
            return;
        }
        if (p->hermano()->color == RED) {
            p->padre->color = RED;
            p->hermano()->color = BLACK;
            if (p == p->padre->izquierdaArbol)
                rotarIzquierda(p->hermano());
            else
                rotarDerecha(p->hermano());
        }
        if (p->padre->color == BLACK && p->hermano()->color == BLACK
            && p->hermano()->izquierdaArbol->color == BLACK && p->hermano()->derechaArbol->color == BLACK) {
            p->hermano()->color = RED;
            eliminarCaso(p->padre);
        }
        else if (p->padre->color == RED && p->hermano()->color == BLACK
            && p->hermano()->izquierdaArbol->color == BLACK && p->hermano()->derechaArbol->color == BLACK) {
            p->hermano()->color = RED;
            p->padre->color = BLACK;
        }
        else {
            if (p->hermano()->color == BLACK) {
                if (p == p->padre->izquierdaArbol && p->hermano()->izquierdaArbol->color == RED
                    && p->hermano()->derechaArbol->color == BLACK) {
                    p->hermano()->color = RED;
                    p->hermano()->izquierdaArbol->color = BLACK;
                    rotarDerecha(p->hermano()->izquierdaArbol);
                }
                else if (p == p->padre->derechaArbol && p->hermano()->izquierdaArbol->color == BLACK
                    && p->hermano()->derechaArbol->color == RED) {
                    p->hermano()->color = RED;
                    p->hermano()->derechaArbol->color = BLACK;
                    rotarIzquierda(p->hermano()->derechaArbol);
                }
            }
            p->hermano()->color = p->padre->color;
            p->padre->color = BLACK;
            if (p == p->padre->izquierdaArbol) {
                p->hermano()->derechaArbol->color = BLACK;
                rotarIzquierda(p->hermano());
            }
            else {
                p->hermano()->izquierdaArbol->color = BLACK;
                rotarDerecha(p->hermano());
            }
        }
    }
    void insertar(Node<T>* p, T data)
    {
        if (compare(p->valor,data)) {
            if (p->izquierdaArbol != NIL)
                insertar(p->izquierdaArbol, data);
            else {
                Node<T>* tmp = new Node<T>();
                tmp->valor = data;
                tmp->izquierdaArbol = tmp->derechaArbol = NIL;
                tmp->padre = p;
                p->izquierdaArbol = tmp;
                insertarCaso(tmp);
            }
        }
        else {
            if (p->derechaArbol != NIL)
                insertar(p->derechaArbol, data);
            else {
                Node<T>* tmp = new Node<T>();
                tmp->valor = data;
                tmp->izquierdaArbol = tmp->derechaArbol = NIL;
                tmp->padre = p;
                p->derechaArbol = tmp;
                insertarCaso(tmp);
            }
        }
    }
    void insertarCaso(Node<T>* p) 
    {
        if (p->padre == nullptr) {
            root = p;
            p->color = BLACK;
            return;
        }
        if (p->padre->color == RED) {
            if (p->tio()->color == RED) {
                p->padre->color = p->tio()->color = BLACK;
                p->abuelo()->color = RED;
                insertarCaso(p->abuelo());
            }
            else {
                if (p->padre->derechaArbol == p && p->abuelo()->izquierdaArbol == p->padre) {
                    rotarIzquierda(p);
                    rotarDerecha(p);
                    p->color = BLACK;
                    p->izquierdaArbol->color = p->derechaArbol->color = RED;
                }
                else if (p->padre->izquierdaArbol == p && p->abuelo()->derechaArbol == p->padre) {
                    rotarDerecha(p);
                    rotarIzquierda(p);
                    p->color = BLACK;
                    p->izquierdaArbol->color = p->derechaArbol->color = RED;
                }
                else if (p->padre->izquierdaArbol == p && p->abuelo()->izquierdaArbol == p->padre) {
                    p->padre->color = BLACK;
                    p->abuelo()->color = RED;
                    rotarDerecha(p->padre);
                }
                else if (p->padre->derechaArbol == p && p->abuelo()->derechaArbol == p->padre) {
                    p->padre->color = BLACK;
                    p->abuelo()->color = RED;
                    rotarIzquierda(p->padre);
                }
            }
        }
    }
    void EliminarArbol(Node<T>* p)
    {
        if (!p || p == NIL) {
            return;
        }
        EliminarArbol(p->izquierdaArbol);
        EliminarArbol(p->derechaArbol);
        delete p;
    }
    void print(Node<T>* tmp) // Recorrido en orden
    {
        if (tmp == nullptr)return;
        print(tmp->izquierdaArbol);// Recurisvamente a la izquierda
        fprint(tmp->valor);//imprime valor
        print(tmp->derechaArbol);// Recursivamente a la derecha

    }
public:
    ArbolRojoNegro(function<bool(T, T)>compare, function<void(T)>f) :compare(compare),fprint(f) 
    {
        NIL = new Node<T>();
        NIL->color = BLACK;
        root = nullptr;
    }
    ~ArbolRojoNegro()
    {
        if (root)
            EliminarArbol(root);
        delete NIL;
    }
    void enOrden() 
    {
        if (root == nullptr)
            return;
        enOrden(root);
        cout << endl;
    }
    void insertar(T x) 
    {
        if (root == nullptr) 
        {
            root = new Node<T>();
            root->color = BLACK;
            root->izquierdaArbol = root->derechaArbol = NIL;
            root->valor = x;
        }
        else {
            insertar(root, x);
        }
    }
    bool eliminarValor(int data) 
    {
        return eliminarHijo(root, data);
    }
    void print()
    {
        print(root);
    }
};