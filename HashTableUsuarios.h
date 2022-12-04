#pragma once
#include "Usuario.h"
#include "HashTable.h"
#include "Registros.h"
class HashTableUsuarios : public Base
{
	HashTable<Usuario>* usuariosH;
	Datos* lectura;
	int cant_usuarios;
	int atUsuario;
	Usuario usuarioSeleccionado;
	int numeracion_aux;
	ofstream archivo;
public:
	HashTableUsuarios()
	{
		usuariosH = new HashTable<Usuario>([](Usuario u) {
			int aux = 0; 
			for (int i = 0; i < u.getNombre().size(); ++i) 
				aux += u.getNombre()[i];
			return aux % 1000; 
			});
		lectura = new Datos(usuariosH);
		lectura->~Datos();
		atUsuario = -1;
		cant_usuarios = lectura->cantidad_registros;
	}
	void menuUsuarios()
	{
		do
		{
			cout << "  -------- Menu de Opciones de Usuario ----------" << "\n\n";
			cout << "  1. Ingresar nuevo usuario					  " << "\n";
			cout << "  2. Mostrar todos los usuarios				  " << "\n";
			cout << "  3. Eliminar usuario por nombre				  " << "\n";
			cout << "  4. Buscar usuario por nombre	y mostrar datos	  " << "\n";
			cout << "  5. Mostrar usuarios ordenados por edad ascendentemente  " << "\n";
			cout << "  6. Mostrar usuarios Ordenados por edad descendentemente " << "\n";
			cout << "  7. Salir						                  " << "\n";
			cout << "  -----------------------------------------------" << "\n";
			verificarOpcion(7);
			if (*opcion == 1) insercion();
			if (*opcion == 2) listar();
			if (*opcion == 3) eliminar();
			if (*opcion == 4) buscar();
			if (*opcion == 5) ordenarEdadAscendentemente();
			if (*opcion == 6) ordenarEdadDescendentemente();
		} while (*opcion != 7);
		guardar();
	}
	bool seleccionarUsuario()
	{
		string nombre;
		cout << "---------------- Elija el Usuario por nombre----------------" << endl << endl;
		getline(cin, nombre);
		int aux = 0;
		for (int i = 0; i < nombre.size(); ++i) aux += nombre[i];
		bool flat = usuariosH->buscar2([=](Usuario e) {return e.getNombre() == nombre; }, aux % 10000);
		if (flat)
		{
			string aux_num;
			cout << "Elija al usuario " << endl;
			getline(cin, aux_num);
			int num = stoi(aux_num);
			usuarioSeleccionado = usuariosH->retornar_pos([=](Usuario e) {return e.getNombre() == nombre; }, num , aux % 10000);
			cout << "\nSe eligio a "<<usuarioSeleccionado.toString2() << "\n";
			return true;
		}
		else
		{
			cout << "Este usuario no existe" << endl;
			return false;
		}
	}
	void insercion()
	{
		string nombre, alias, pais, aux_edad, aux_telefono, email, opcion;
		short edad;
		int telefono;
		int numeracion = numeracion_aux;
		char opt;
		archivo.open("datos.csv", ofstream::app);
		do
		{
			cout << "Nombre :" << endl;
			getline(cin, nombre);
			cout << "Alias :" << endl;
			getline(cin, alias);
			cout << "Pais :" << endl;
			getline(cin, pais);
			cout << "Edad :" << endl;
			getline(cin, aux_edad);
			cout << "Telefono :" << endl;
			getline(cin, aux_telefono);
			cout << "Email :" << endl;
			getline(cin, email);
			edad = stoi(aux_edad);
			cant_usuarios++;
			telefono = stoi(aux_telefono);
			edad = stoi(aux_edad);
			usuariosH->add(Usuario(numeracion, nombre, alias, pais, edad, telefono, email, 0));
			numeracion++;
			cout << "Desea continuar registrando un usuario (Si: S, No:N)";
			getline(cin, opcion);
			opt = toupper(opcion[0]);
		} while (opt != 'N');
		archivo.close();
		system("CLS");
	}
	void listar()
	{
		cout << "----------------Lista de Usuarios-----------------" << endl;
		unsigned ti, tf;
		ti = clock();
		usuariosH->display();
		tf = clock();
		double tiempo = (double(tf - ti) / CLOCKS_PER_SEC);
		Console::ForegroundColor = ConsoleColor::Red;
		cout << "El tiempo de ejecucion para mostrar los datos en Hash Table es: " << tiempo << " segundos\n";
		Console::ForegroundColor = ConsoleColor::White;
	}
	void ordenarEdadAscendentemente()
	{
		unsigned ti, tf;
		ti = clock();
		usuariosH->ordenarMergeSort([](Usuario i, Usuario j) {return i.getEdad() < j.getEdad(); });
		tf = clock();
		double tiempo = (double(tf - ti) / CLOCKS_PER_SEC);
		Console::ForegroundColor = ConsoleColor::Red;
		cout << "El tiempo de ejecucion para ordenar los datos en Hash Table es: " << tiempo <<" segundos\n";
		Console::ForegroundColor = ConsoleColor::White;
	}
	void ordenarEdadDescendentemente()
	{
		unsigned ti, tf;
		ti = clock();
		usuariosH->ordenarMergeSort([](Usuario i, Usuario j) {return i.getEdad() > j.getEdad(); });
		tf = clock();
		double tiempo = (double(tf - ti) / CLOCKS_PER_SEC);
		Console::ForegroundColor = ConsoleColor::Red;
		cout << "El tiempo de ejecucion para ordenar los datos en Hash Table es: " << tiempo << " segundos\n";
		Console::ForegroundColor = ConsoleColor::White;
	}
	void eliminar()
	{
		unsigned ti, tf;
		string nombre;
		cout << "Ingrese el nombre a eliminar: " << endl;
		getline(cin, nombre);
		int aux = 0;
		ti = clock();
		for (int i = 0; i < nombre.size(); ++i) aux += nombre[i];
		bool flat = usuariosH->eliminar([=](Usuario e) {return e.getNombre() != nombre; }, aux % 10000, nombre);
		if (flat)
		{
			cout << "Eliminado correctamente todos los usuarios con nombre " << nombre << "\n";
			tf = clock();
			double tiempo = (double(tf - ti) / CLOCKS_PER_SEC);
			Console::ForegroundColor = ConsoleColor::Red;
			cout << "El tiempo de ejecucion para eliminar el dato en Hash Table es: " << tiempo << " segundos\n";
			Console::ForegroundColor = ConsoleColor::White;
		}
		if (!flat)cout << "No existe el usuario con nombre " << nombre << " registrado" << "\n";
	}
	void buscar()
	{
		unsigned ti, tf;
		string nombre;
		cout << "Ingrese el nombre a buscar : " << endl;
		getline(cin, nombre);
		int aux = 0;
		ti = clock();
		for (int i = 0; i < nombre.size(); ++i) aux += nombre[i];
		bool flat = usuariosH->buscar([=](Usuario e) {return e.getNombre() == nombre; }, aux % 10000);
		if (flat)
		{
			cout << nombre << "Se encontro correctamente el usuario con nombre " << nombre << "\n";
			tf = clock();
			double tiempo = (double(tf - ti) / CLOCKS_PER_SEC);
			Console::ForegroundColor = ConsoleColor::Red;
			cout << "El tiempo de ejecucion para buscar el dato en Hash Table es: " << tiempo << " segundos\n";
			Console::ForegroundColor = ConsoleColor::White;
		}
		if (!flat)cout << "No existe el usuario con nombre" << nombre << " registrado" << "\n";
	}
	void guardar()
	{
		unsigned ti, tf;
		ofstream miarchivo("datos.csv"); // BORRA EL CONTENIDO DEL ARCHIVO
		ti = clock();
		if (!miarchivo.fail())
		{
			for (int i = 0; i < cant_usuarios; i++)
			{
				for (auto it:usuariosH->getContainer()[i])
				{
					if(!usuariosH->getContainer().empty())
						miarchivo << it.getNombre() << "," << it.getAlias() << "," << it.getPais() << "," << it.getEdad() << "," << it.getTelefono() << "," << it.getEmail() << "," << it.getPuntuacion() << endl;
				}
			}

			miarchivo.flush();
			miarchivo.close();
		}
		tf = clock();
		double tiempo = (double(tf - ti) / CLOCKS_PER_SEC);
		Console::ForegroundColor = ConsoleColor::Red;
		cout << "El tiempo de ejecucion para guardar los datos en el archivo es: " << tiempo << " segundos\n";
		Console::ForegroundColor = ConsoleColor::White;
	}
	void elegirUsuario(int posicion) { atUsuario = posicion - 1; }
	int retornarUsuarioElegido() { return atUsuario; }
	int retornarCantidad() { return cant_usuarios; }
	HashTable<Usuario>* retornarUsuarios() { return usuariosH; }
};