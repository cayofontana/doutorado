#include "Mouse.h"
#include "../Cenario.h"

#include <GL/glut.h>
#include <cmath>
#include <algorithm>

Mouse::Mouse() : pressionado(false), xInicial(0), yInicial(0), xAtual(0), yAtual(0), anguloReferencia(0.0f) {
}

void
Mouse::clicar(int botao, int estado, int x, int y, Cenario& cenario) {
	if (botao != GLUT_LEFT_BUTTON)
		return;

	if (estado == GLUT_DOWN) {
		pressionado = true;
		xInicial = x;
		yInicial = y;
		xAtual = x;
		yAtual = y;

		anguloReferencia = cenario.obterJogadores().at(1)->obterAngulo();
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
	yAtual = y;

	// deslocamento do mouse na tela
	float dxTela = (float)(xAtual - xInicial);
	float dyTela = (float)(yInicial - yAtual); // invertido para ficar compatível com eixo Y matemático

	float angRad = anguloReferencia * M_PI / 180.0f;

	// eixo "direita" do jogador
	float direitaX = cosf(angRad);
	float direitaY = sinf(angRad);

	// projeção do deslocamento do mouse no eixo lateral do jogador
	float dxLocal = dxTela * direitaX + dyTela * direitaY;

	float metade = cenario.obterLargura() / 2.0f;
	float intensidade = std::min(std::fabs(dxLocal), metade);

	Jogador* jogador = cenario.obterJogadores().at(1);

	if (dxLocal > 0.0f)
		jogador->socarDireito(cenario, intensidade, x, y);
	else if (dxLocal < 0.0f)
		jogador->socarEsquerdo(cenario, intensidade, x, y);
	else
		jogador->voltarPosicaoInicialDosBracos();
}