#include "Teclado.h"
#include "../Cenario.h"
#include "../Jogador.h"

#include <algorithm>
#include <cmath>

Teclado::Teclado() : teclas(256), cor(0.0f, 1.0f, 0.0f), colisaoFrontal(false), colisaoTraseira(false) {
}

Teclado::~Teclado() {
}

void
Teclado::teclar(unsigned char tecla, int valor, Cenario* cenario, bool teclaPressionada) {
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
		case 'r':
		case 'R':
			if (valor)
				cenario->reiniciarJogo();
			break;
		case 'c':
		case 'C':
			if (teclaPressionada)
				for (auto jogador : cenario->obterJogadores())
					jogador->alterarCirculoColisao();
				// definirValor(tecla, valor);
				// definirValor(tecla & 0x5f, valor);
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
    Jogador* jogador = cenario->obterJogadores().at(1);
    Jogador* oponente = cenario->obterJogadores().at(0);

	if (teclas.at((int)'a') || teclas.at((int)'A'))
		jogador->rotacionar(2);
	if (teclas.at((int)'d') || teclas.at((int)'D'))
		jogador->rotacionar(-2);

	if (teclas.at((int)'w') || teclas.at((int)'W')) {
		float dx = 3.0f * -sinf(jogador->obterAngulo() * M_PI / 180.0f);
		float dy = 3.0f *  cosf(jogador->obterAngulo() * M_PI / 180.0f);
		jogador->transladar(dx, dy);
		if (!cenario->jogadorDentroArena(jogador) || cenario->colisaoJogadores(jogador, oponente))
			jogador->transladar(-dx, -dy);
	}

	if (teclas.at((int)'s') || teclas.at((int)'S')) {
		float dx = -3.0f * -sinf(jogador->obterAngulo() * M_PI / 180.0f);
		float dy = -3.0f *  cosf(jogador->obterAngulo() * M_PI / 180.0f);
		jogador->transladar(dx, dy);
		if (!cenario->jogadorDentroArena(jogador) || cenario->colisaoJogadores(jogador, oponente))
			jogador->transladar(-dx, -dy);
	}

	// if (teclas.at((int)'c') || teclas.at((int)'C'))
	// 	jogador->alterarCirculoColisao();
}

Cor
Teclado::obterCor(void) {
	return (cor);
}

bool
Teclado::possuiTeclaPressionada(void) {
	return (std::find(teclas.begin(), teclas.end(), (int)true) != teclas.end());
}