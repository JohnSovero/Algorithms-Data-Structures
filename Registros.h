#pragma once
#include <string>
#include "Vector.h"
using namespace std;
using namespace System;
class Registro
{
private:
    string nombre, alias, pais, email;
    int n[3];
    friend class Datos;
    friend class HashTableUsuarios;
    friend class ArbolUsuarios;
public:
    Registro(){}
};

class Datos
{
    char nombre[20], alias[20], pais[20], email[50];
    int cantidad_registros;
    friend class HashTableUsuarios;
    friend class ArbolPromociones;
    friend class ArbolUsuarios;
public:
    Datos(HashTable<Usuario>* aux) { 
        cantidad_registros = 0; 
        Registro t;
        int ti, tf;
        ti = clock();
        FILE* archivo = fopen("datos.csv", "r");
        while (fscanf(archivo, "%[^,],%[^,],%[^,],%d,%d,%[^,],%d",nombre, alias, pais, &t.n[0], &t.n[1], email, &t.n[2]) != EOF) 
        {
            fflush(stdin);
            t.nombre = nombre;
            if (t.nombre.compare("\n"))
            {
                if (cantidad_registros != 0) {
                    short cont = 1;
                    size_t tam = t.nombre.length();
                    t.nombre = "";
                    while (cont != tam) {
                        string aux = string(1, nombre[cont]);
                        t.nombre.append(aux);
                        cont++;
                    }
                    t.alias = alias;
                    t.pais = pais;
                    t.email = email;
                }
                else {
                    t.nombre = nombre;
                    t.alias = alias;
                    t.pais = pais;
                    t.email = email;
                }
                aux->add(Usuario(cantidad_registros,t.nombre,t.alias,t.pais,t.n[0], t.n[1],t.email,t.n[2]));
                cantidad_registros++;
            }    
        }
        fclose(archivo);
        tf = clock();
        float tiempo = (float(tf - ti) / CLOCKS_PER_SEC);
        Console::ForegroundColor = ConsoleColor::Red;
        cout << "El tiempo de ejecucion para leer los datos del archivo es: " << tiempo << " segundos\n";
        Console::ForegroundColor = ConsoleColor::White;
    }
    ~Datos(){}
    
};