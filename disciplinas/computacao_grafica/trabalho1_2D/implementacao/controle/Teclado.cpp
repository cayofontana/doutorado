#include "Teclado.h"
#include "../Cenario.h"

#include <algorithm>
#include <cmath>

Teclado::Teclado() : teclas(256), cor(0.0f, 1.0f, 0.0f), colisaoFrontal(false), colisaoTraseira(false) {
}

Teclado::~Teclado() {
}

void
Teclado::teclar(unsigned char tecla, int valor, Cenario* cenario) {
	switch (tecla) {
		case 'a':
		case 'd':
		case 'w':
		case 's':
			definirValor(tecla, valor);
			definirValor(tecla & 0x5f, valor);
			break;
		case 'A':
		case 'D':
		case 'W':
		case 'S':
			definirValor(tecla, valor);
			definirValor(tecla ^ 0x20, valor);
			break;
		case 27:
			exit(1);
			break;
	}
}

void
Teclado::definirValor(unsigned char tecla, int valor) {
	teclas.at((int)tecla) = valor;
}

void
Teclado::atualizar(Cenario* cenario) {
	if (teclas.at((int)'a') || teclas.at((int)'A'))
		cenario->obterJogadores().at(1)->rotacionar(2);
	if (teclas.at((int)'d') || teclas.at((int)'D'))
		cenario->obterJogadores().at(1)->rotacionar(-2);
	if (teclas.at((int)'w') || teclas.at((int)'W'))
		if (!cenario->obterJogadores().at(1)->colidiu(cenario->obterJogadores().at(0)))
			cenario->obterJogadores().at(1)->transladar(3.0f * -sinf(cenario->obterJogadores().at(1)->obterAngulo() * M_PI / 180.0f), 3.0f * cosf(cenario->obterJogadores().at(1)->obterAngulo() * M_PI / 180.0f));
	if (teclas.at((int)'s') || teclas.at((int)'S'))
		if (!cenario->obterJogadores().at(1)->colidiu(cenario->obterJogadores().at(0)))
			cenario->obterJogadores().at(1)->transladar(-3.0f * -sinf(cenario->obterJogadores().at(1)->obterAngulo() * M_PI / 180.0f), -3.0f * cosf(cenario->obterJogadores().at(1)->obterAngulo() * M_PI / 180.0f));
}

Cor
Teclado::obterCor(void) {
	return (cor);
}

bool
Teclado::possuiTeclaPressionada(void) {
	return (std::find(teclas.begin(), teclas.end(), (int)true) != teclas.end());
}