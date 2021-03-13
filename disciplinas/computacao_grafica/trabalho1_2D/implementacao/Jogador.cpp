#include "Jogador.h"
#include <iostream>
using namespace std;

Jogador::Jogador(Cenario& cenario, int xAbsoluto, int yAbsoluto, int raioCabeca, Cor* cor) {
	cabeca = new Circunferencia(xAbsoluto - cenario.obterLargura() / 2, cenario.obterAltura() / 2 - yAbsoluto, raioCabeca, cor, 0.1f, 1.0f);
	nariz =  new Circunferencia(raioCabeca * 0.8f, raioCabeca * 0.8f, raioCabeca * 0.2f, cor, 0.1f, 1.0f);
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
	glPushMatrix(); {
		glRotatef(cabeca->obterAngulo(), 0.0f, 0.0f, 1.0f);
		glTranslatef(cabeca->obterDeslocamentoHorizontal(), cabeca->obterDeslocamentoVertical(), 0.0f);
		glPushMatrix(); {
			glTranslatef(nariz->obterDeslocamentoHorizontal(), nariz->obterDeslocamentoVertical(), 0.0f);
			nariz->desenhar();
		}
		glPopMatrix();
		cabeca->desenhar();
	}
	glPopMatrix();
}