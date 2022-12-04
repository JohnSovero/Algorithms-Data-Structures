#pragma once
#include <iostream>
#include <functional>
#include <string>
using namespace std;

class Usuario 
{
private:
    string nombre;
    string alias;
    string pais;
    string email;
    short edad;
    int telefono;
    int *puntuacion;
    int puntos;
    int numeracion;
public:
    Usuario(int numeracion = 0, string nombre = " ", string alias = " ", string pais = " ", short edad = 0, int telefono = 0,string email=" ", int puntos = 0) :numeracion(numeracion), nombre(nombre), alias(alias),pais(pais), edad(edad), telefono(telefono),email(email), puntos(puntos) { puntuacion = new int; *puntuacion = puntos; }
    ~Usuario() {}
    int getNumeracion() { return numeracion; }
    void setNumeracion(int valor) { numeracion = valor; }
    string getNombre() { return nombre; }
    void setNombre(string nuevo) { nombre = nuevo; }
    string getAlias() { return alias; }
    void setAlias(string nuevo) { alias = nuevo; }
    string getPais() { return pais; }
    void setPais(string nuevo) { pais = nuevo; }
    short getEdad() { return edad; }
    void setEdad(short nuevo) { edad = nuevo; }
    int getTelefono() { return telefono; }
    void setTelefono(short nuevo) { telefono = nuevo; }
    int getPuntuacion() { return *puntuacion; }
    void setPuntuacion(int nuevo) { *puntuacion = nuevo; }
    void addPuntuacion(int valor) { *puntuacion = *puntuacion + valor; }
    string getEmail() { return email; }
    void setEmail(string nuevo) { email = nuevo; }
    string toString() { return to_string(numeracion) + ". Nombre: " + nombre + " - Alias: " + alias + " - Pais: " + pais + " - Edad: " + to_string(edad) + " - Telefono: " + to_string(telefono) + " - Email: " + email + " - Puntos: " + to_string(*puntuacion); }
    string toString2() { return "Nombre: " + nombre + " - Alias: " + alias + " - Pais: " + pais + " - Edad: " + to_string(edad) + " - Telefono: " + to_string(telefono) + " - Email: " + email + " - Puntos: " + to_string(*puntuacion); }
};

