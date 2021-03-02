#include "Retangulo.h"

#include <iostream>
using namespace std;

Retangulo::Retangulo(Pixel* pixel, float largura, float altura, Cor cor) : largura(largura), altura(altura), cor(cor), angulo(0) {
	pixels.push_back(new Pixel(pixel->obterX() - largura / 2, pixel->obterY() - altura / 2));
	pixels.push_back(new Pixel(pixel->obterX() - largura / 2, pixel->obterY() + altura / 2));
	pixels.push_back(new Pixel(pixel->obterX() + largura / 2, pixel->obterY() + altura / 2));
	pixels.push_back(new Pixel(pixel->obterX() + largura / 2, pixel->obterY() - altura / 2));
}

Retangulo::~Retangulo() {
	for (auto& pixel : pixels)
		delete pixel;
}

std::vector<Pixel*>
Retangulo::obterPixels(void) {
	return (pixels);
}

float
Retangulo::obterLargura(void) {
	return (largura);
}

float
Retangulo::obterAltura(void) {
	return (altura);
}

Cor
Retangulo::obterCor(void) {
	return (cor);
}

float
Retangulo::obterAngulo(void) {
	return (angulo);
}

void
Retangulo::definirAngulo(float angulo) {
	this->angulo = angulo;
}