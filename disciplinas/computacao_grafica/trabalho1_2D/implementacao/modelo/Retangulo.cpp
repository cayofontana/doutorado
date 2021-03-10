#include "Retangulo.h"

Retangulo::Retangulo(Pixel pixel, float largura, float altura, Cor cor) : cor(cor) {
	// pixels.push_back(new Pixel(pixel.obterX() - largura / 2, pixel.obterY() - altura / 2));
	// pixels.push_back(new Pixel(pixel.obterX() - largura / 2, pixel.obterY() + altura / 2));
	// pixels.push_back(new Pixel(pixel.obterX() + largura / 2, pixel.obterY() + altura / 2));
	// pixels.push_back(new Pixel(pixel.obterX() + largura / 2, pixel.obterY() - altura / 2));
}

Retangulo::~Retangulo() {
}

Cor
Retangulo::obterCor(void) {
	return (cor);
}

void
Retangulo::mover(float x, float y) {
}

void
Retangulo::desenhar(void) {
}