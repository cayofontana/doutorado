#include "Mouse.h"
#include "../Cenario.h"

#include <GL/glut.h>
#include <cmath>
#include <algorithm>

Mouse::Mouse() : pressionado(false), xInicial(0), xAtual(0) {
}

void
Mouse::clicar(int botao, int estado, int x, int y, Cenario& cenario) {
	if (botao != GLUT_LEFT_BUTTON)
		return;

	if (estado == GLUT_DOWN) {
		pressionado = true;
		xInicial = x;
		xAtual = x;
	}
	else {
		pressionado = false;
		cenario.obterJogadores().at(1)->voltarPosicaoInicialDosBracos();
	}
}

void
Mouse::mover(int x, int y, Cenario& cenario) {
	if (!pressionado)
		return;

	xAtual = x;

	float dx = (float)(xAtual - xInicial);
	float metade = cenario.obterLargura() / 2.0f;
	float intensidade = std::min(std::fabs(dx), metade);

	if (dx > 0.0f)
		cenario.obterJogadores().at(1)->socarDireito(cenario, intensidade, x, y);
	else if (dx < 0.0f)
		cenario.obterJogadores().at(1)->socarEsquerdo(cenario, intensidade, x, y);
	else
		cenario.obterJogadores().at(1)->voltarPosicaoInicialDosBracos();
}