#pragma once
#include "Usuario.h"
#include "Arbol.h"
#include "Vector.h"
#include "Registros.h"

class ArbolUsuarios:public Base
{
private:
	Arbol<Usuario>* usuarios;
	Datos lectura;
	size_t cant_usuarios;
	int atUsuario;
	int numeracion_aux;
public:
	ArbolUsuarios()
	{
		usuarios = new Arbol<Usuario>([](Usuario a, Usuario b) {return a.getTelefono() >= b.getTelefono(); }, [](Usuario a) {cout << a.toString() << endl; });
		atUsuario = -1;
		cant_usuarios = lectura.cantidad_registros;
		leerUsuarios();
	}
	void elegirUsuario()
	{
		do
		{
			cout << "  -------- Menu de Opciones de Usuario ----------" << endl << endl;
			cout << "  1. Ingresar nuevo usuario					  " << endl;
			cout << "  2. Mostrar todos los usuarios				  " << endl;
			cout << "  3. Eliminar usuario por nombre				  " << endl;
			cout << "  4. Buscar usuario por nombre	y mostrar datos	  " << endl;
			cout << "  5. Ordenar por edad ascendentemente			  " << endl;
			cout << "  6. Ordenar por edad descendentemente		      " << endl;
			cout << "  7. Salir						                  " << endl;
			cout << "  -----------------------------------------------" << endl;
			verificarOpcion(7);
			/*if (*opcion == 1) insercion();*/
			if (*opcion == 2) listar();
			/*if (*opcion == 3) eliminar();
			if (*opcion == 4) buscar();
			if (*opcion == 5) ordenarEdadAscendentemente();
			if (*opcion == 6) ordenarEdadDescendentemente();*/
		} while (*opcion != 7);
	}
	/*void seleccionarUsuario()
	{
		do
		{
			listar();
			cout << cant_usuarios << ". Salir" << endl;
			cout << "---------------- Elija el Usuario ----------------" << endl << endl;
			verificarOpcion(cant_usuarios - 1);
			if (*opcion != cant_usuarios)
			{
				elegirUsuario(*opcion);
				cout << "--- Se elegio el usuario correctamente ---" << endl;
			}
		} while (*opcion != retornarCantidad());
	}*/
	void leerUsuarios()
	{
		Arbol<Usuario>*aux = new Arbol<Usuario>([](Usuario a, Usuario b) {return a.getTelefono() >= b.getTelefono(); }, [](Usuario a) {cout << a.toString() << endl; });
		size_t id = 0;
		string nombre = "";
		string alias = "";
		string pais = "";
		short edad = 0;
		int telefono = 0;
		string email = "";
		int puntuacion = 0;
		for (auto i : lectura.registros)
		{
			nombre = i.nombre;
			alias = i.alias;
			pais = i.pais;
			edad = i.n[0];
			telefono = i.n[1];
			email = i.email;
			puntuacion = i.n[2];
			aux->insert(Usuario(id, nombre, alias, pais, edad, telefono, email, puntuacion));
			id++;
		}
		numeracion_aux = id;
		usuarios = aux;
	}
	void listar() {
		cout << "----------------Lista de Usuarios-----------------" << endl;
		usuarios->print();
	}
};

