#include "Teclado.h"
#include "../Cenario.h"

#include <algorithm>


Teclado::Teclado() : teclas(256), cor(0.0f, 1.0f, 0.0f) {
}

Teclado::~Teclado() {
}

void
Teclado::teclar(unsigned char tecla, int valor, Cenario* cenario) {
	switch (tecla) {
		case 27:
			exit(0);
			break;
	}
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