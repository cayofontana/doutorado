#include "Teclado.h"

#include "../Cenario.h"
#include <algorithm>


Teclado::Teclado() : teclas(256), cor(0.0f, 1.0f, 0.0f) {
}

Teclado::~Teclado() {
}

void
Teclado::teclar(unsigned char tecla, int valor, Cenario* cenario) {
	if (valor)
		switch (tecla) {
			case 'a':
			case 'A':
				cenario->obterRobo()->mover(-5.0f, 0.0f);
				break;
			case 'd':
			case 'D':
				cenario->obterRobo()->mover(5.0f, 0.0f);
				break;
			case 'f':
			case 'F':
				cenario->obterRobo()->mover(Braco::BASE, -1);
				break;
			case 'r':
			case 'R':
				cenario->obterRobo()->mover(Braco::BASE, 1);
				break;
			case 'g':
			case 'G':
				cenario->obterRobo()->mover(Braco::MEDIO, -1);
				break;
			case 't':
			case 'T':
				cenario->obterRobo()->mover(Braco::MEDIO, 1);
				break;
			case 'h':
			case 'H':
				cenario->obterRobo()->mover(Braco::PONTA, -1);
				break;
			case 'y':
			case 'Y':
				cenario->obterRobo()->mover(Braco::PONTA, 1);
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