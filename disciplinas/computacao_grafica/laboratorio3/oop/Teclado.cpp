#include "Teclado.h"

Teclado::Teclado() : teclas(256), cor(0.0f, 1.0f, 0.0f) {
}

void
Teclado::teclar(unsigned char tecla, int valor, Robo* robo) {
	if (valor)
		switch (tecla) {
			case 'a':
			case 'A':
				robo->mover(-0.01, 0);
				break;
			case 'd':
			case 'D':
				robo->mover(0.01, 0);
				break;
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