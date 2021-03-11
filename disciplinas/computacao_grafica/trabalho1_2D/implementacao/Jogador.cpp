#include "Jogador.h"

Jogador::Jogador(Cenario& cenario, int xAbsoluto, int yAbsoluto, int raioCabeca, Cor* cor) {
	cabeca = new Circunferencia(xAbsoluto - cenario.obterLargura() / 2, yAbsoluto - cenario.obterAltura() / 2, raioCabeca, cor, 0.01f, GL_TRIANGLE_FAN, 1.0f);
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