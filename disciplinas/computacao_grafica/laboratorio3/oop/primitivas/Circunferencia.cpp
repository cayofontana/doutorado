#include "Circunferencia.h"

Circunferencia::Circunferencia(float raio, Pixel pixel) : raio(raio), pixel(pixel), angulo(0) {
}

float
Circunferencia::obterRaio(void) {
	return (raio);
}

Pixel
Circunferencia::obterPixel(void) {
	return (pixel);
}

float
Circunferencia::obterDiametro(void) {
	return (raio * 2);
}

float
Circunferencia::obterAngulo(void) {
	return (angulo);
}

void
Circunferencia::definirAngulo(float angulo) {
	this->angulo = angulo;
}

void
Circunferencia::mover(float x, float y) {
	pixel.incrementar(x, y);
	this->angulo += x;
}