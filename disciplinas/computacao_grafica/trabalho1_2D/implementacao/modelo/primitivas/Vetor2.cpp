#include "Vetor2.h"

#include <cmath>

Vetor2::Vetor2(float x, float y) : x(x), y(y), cor(new Cor(0.0f, 0.0f, 0.0f)) {
}

Vetor2::Vetor2(float x, float y, Cor* cor) : x(x), y(y), cor(cor) {
}

float
Vetor2::obterX(void) {
	return (x);
}

void
Vetor2::definirX(float x) {
	this->x = x;
}

float
Vetor2::obterY(void) {
	return (y);
}

void
Vetor2::definirY(float y) {
	this->y = y;
}

Cor
Vetor2::obterCor(void) {
	return (*cor);
}

void
Vetor2::definirCor(Cor cor) {
	this->cor->definirVermelho(cor.obterVermelho());
	this->cor->definirVerde(cor.obterVerde());
	this->cor->definirAzul(cor.obterAzul());
}

void
Vetor2::incrementar(float x, float y) {
	this->x += x;
	this->y += y;
}

float
Vetor2::calcularDistancia(Vetor2 Vetor2) {
	return (sqrt(pow(x - Vetor2.obterX(), 2) + pow(y - Vetor2.obterY(), 2)));
}