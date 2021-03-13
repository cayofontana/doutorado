#include "Jogador.h"
#include <iostream>
using namespace std;

Jogador::Jogador(Cenario& cenario, int xAbsoluto, int yAbsoluto, int raioCabeca, Cor* cor) {
	cabeca = new Circunferencia(xAbsoluto - cenario.obterLargura() / 2, cenario.obterAltura() / 2 - yAbsoluto, raioCabeca, cor, 0.1f, 1.0f);
	nariz =  new Circunferencia(cabeca->obterDeslocamentoHorizontal() + (raioCabeca - raioCabeca * 0.2f), cabeca->obterDeslocamentoVertical() + (raioCabeca - raioCabeca * 0.2f), raioCabeca * 0.2f, cor, 0.1f, 1.0f);
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
	glPushMatrix();
	cabeca->desenhar();
	glPopMatrix();
	glPopMatrix();
}