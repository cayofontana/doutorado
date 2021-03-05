#include "Projetil.h"

Projetil::Projetil(float raio, Pixel* pixel, float intervaloAngular, int tipo, float tamanhoPonto) : Circunferencia(raio, pixel, intervaloAngular, tipo, tamanhoPonto) {
}

Projetil::~Projetil() {
}

void
Projetil::desenhar(void) {
	mover(0.0f, 2.0f);
	Circunferencia::desenhar();
}