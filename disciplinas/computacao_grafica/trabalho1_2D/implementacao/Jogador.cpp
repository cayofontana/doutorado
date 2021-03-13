#include "Jogador.h"

Jogador::Jogador(Cenario& cenario, int xAbsoluto, int yAbsoluto, int raioCabeca, Cor* cor) {
	cabeca = new Circunferencia(xAbsoluto - cenario.obterLargura() / 2, cenario.obterAltura() / 2 - yAbsoluto, raioCabeca, cor, 0.1f, 1.0f);
	nariz =  new Circunferencia(cabeca->obterDeslocamentoHorizontal() + cabeca->obterRaio() - raioCabeca / 5, cabeca->obterDeslocamentoVertical() + cabeca->obterRaio() - raioCabeca / 5, raioCabeca / 5, cor, 0.1f, 1.0f);
}

Jogador::~Jogador() {
	delete cabeca;
	delete nariz;
	for (auto par : membrosEsquerdo)
		delete par.second;
	for (auto par : membrosDireito)
		delete par.second;
	delete luvaEsquerda;
	delete luvaDireita;
}

void
Jogador::desenhar(void) {
	glLoadIdentity();
	glPushMatrix();
	nariz->desenhar();
	cabeca->desenhar();
	glPopMatrix();
}