#include "Retangulo.h"

#include <iostream>
using namespace std;

Retangulo::Retangulo(Pixel pixel, float largura, float altura, Cor cor) : largura(largura), altura(altura), cor(cor) {
	pixels.push_back(new Pixel(pixel.obterX() - largura / 2, pixel.obterY() - altura / 2));
	pixels.push_back(new Pixel(pixel.obterX() - largura / 2, pixel.obterY() + altura / 2));
	pixels.push_back(new Pixel(pixel.obterX() + largura / 2, pixel.obterY() + altura / 2));
	pixels.push_back(new Pixel(pixel.obterX() + largura / 2, pixel.obterY() - altura / 2));
}

Retangulo::~Retangulo() {
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

void
Retangulo::inclinar(int valor) {
	this->angulo += valor;
}

void
Retangulo::mover(float x, float y) {
	for (auto& pixel : pixels)
		pixel->incrementar(x, y);
}