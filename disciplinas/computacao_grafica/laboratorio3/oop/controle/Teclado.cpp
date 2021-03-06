#include "Teclado.h"

#include "../Cenario.h"
#include <algorithm>


Teclado::Teclado() : teclas(256), cor(0.0f, 1.0f, 0.0f) {
}

void
Teclado::teclar(unsigned char tecla, int valor, Cenario* cenario) {
	if (valor)
		switch (tecla) {
			case 'a':
			case 'A':
				cenario->obterRobo()->mover(-5, 0);
				break;
			case 'd':
			case 'D':
				cenario->obterRobo()->mover(5, 0);
				break;
			case 'f':
			case 'F':
				break;
			case 'r':
			case 'R':
				break;
			case 'g':
			case 'G':
				break;
			case 't':
			case 'T':
				break;
			case 'h':
			case 'H':
				break;
			case 'y':
			case 'Y':
				break;
			case ' ':
				cenario->obterRobo()->disparar(cenario->obterAlvo(), cenario);
				break;
			case 27 :
				exit(0);
		}
	definirValor(tecla, valor);
}

void
Teclado::definirValor(unsigned char tecla, int valor) {
	teclas.at((int)tecla) = valor;
}

Cor
Teclado::obterCor(void) {
	return (cor);
}

bool
Teclado::possuiTeclaPressionada(void) {
	return (std::find(teclas.begin(), teclas.end(), (int)true) != teclas.end());
}