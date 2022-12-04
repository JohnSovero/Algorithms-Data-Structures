#pragma once
#include "Controladora.h"
int main() {
	setlocale(LC_CTYPE, "spanish");
	Controladora* c = new Controladora();
	c->run();
	return 0;
}