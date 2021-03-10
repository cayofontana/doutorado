#include "Pixel.h"

#include <cmath>

Pixel::Pixel(float x, float y) : x(x), y(y), cor(0.0f, 0.0f, 0.0f) {
}

Pixel::Pixel(float x, float y, Cor cor) : x(x), y(y), cor(cor) {
}

float
Pixel::obterX(void) {
	return (x);
}

void
Pixel::definirX(float x) {
	this->x = x;
}

float
Pixel::obterY(void) {
	return (y);
}

void
Pixel::definirY(float y) {
	this->y = y;
}

Cor
Pixel::obterCor(void) {
	return (cor);
}

void
Pixel::definirCor(Cor cor) {
	this->cor.definirVermelho(cor.obterVermelho());
	this->cor.definirVerde(cor.obterVerde());
	this->cor.definirAzul(cor.obterAzul());
}

void
Pixel::incrementar(float x, float y) {
	this->x += x;
	this->y += y;
}

float
Pixel::calcularDistancia(Pixel pixel) {
	return (sqrt(pow(x - pixel.obterX(), 2) + pow(y - pixel.obterY(), 2)));
}