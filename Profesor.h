#include <iostream>
#include <functional>
#include <string>
using namespace std;

class Profesor
{
private:
	int nivel;
	string idioma;
	string nombre;
	int numeracion;
public:
	Profesor(int numeracion=0, int nivel = 0, string nombre = " ", string idioma = " ") : numeracion(numeracion), nivel(nivel), nombre(nombre), idioma(idioma) { }
	~Profesor() {}
	short getNivel() { return nivel; }
	string getNombre() { return nombre; }
	string getIdioma() { return idioma; }
	void setNombre(string valor) { nombre = valor; };
	void setIdioma(string valor) { idioma= valor; }
	void setNivel(int valor) { nivel = valor; };
	int getNumeracion() { return numeracion; }
	void setNumeracion(int valor) { numeracion = valor; }
	string toString() { return to_string(numeracion) + ". " + nombre + " - " + idioma + " - " + to_string(nivel); }
};

