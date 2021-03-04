#include "Circunferencia.h"

Circunferencia::Circunferencia(float raio, Pixel* pixel) : raio(raio) {
	pixels.push_back(pixel);
}

Circunferencia::~Circunferencia() {
}

float
Circunferencia::obterRaio(void) {
	return (raio);
}

Pixel
Circunferencia::obterPixel(void) {
	return (*pixels.at(0));
}

float
Circunferencia::obterDiametro(void) {
	return (raio * 2);
}

void
Circunferencia::mover(float x, float y) {
	pixels.at(0)->incrementar(x, y);
	this->angulo += x;
}