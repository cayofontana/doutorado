#include "Vetor2.h"

#include <cmath>

Vetor2::Vetor2(float x, float y) : x(x), y(y) {
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

void
Vetor2::incrementar(float x, float y) {
	this->x += x;
	this->y += y;
}

float
Vetor2::calcularDistancia(Vetor2 Vetor2) {
	return (sqrt(pow(x - Vetor2.obterX(), 2) + pow(y - Vetor2.obterY(), 2)));
}