#include "Pixel.h"

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
Pixel::incrementar(float x, float y) {
	this->x += x;
	this->y += y;
}

void
Pixel::definirCoordenadasGL(int x, int y, int larguraJanela, int alturaJanela) {
	this->x = (float)x / (float)larguraJanela;
	this->y = 1 - (float)y / (float)alturaJanela;
}