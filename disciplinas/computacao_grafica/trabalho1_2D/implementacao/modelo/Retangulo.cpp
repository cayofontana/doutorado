#include "Retangulo.h"

Retangulo::Retangulo(int deslocamentoHorizontal, int deslocamentoVertical, Cor* cor) : FormaGeometrica2D(deslocamentoHorizontal, deslocamentoVertical), cor(cor) {
	pixels.push_back(new Pixel(-deslocamentoHorizontal / 2, -deslocamentoVertical / 2));
	pixels.push_back(new Pixel(-deslocamentoHorizontal / 2, deslocamentoVertical / 2));
	pixels.push_back(new Pixel(deslocamentoHorizontal / 2, deslocamentoVertical / 2));
	pixels.push_back(new Pixel(deslocamentoHorizontal / 2, -deslocamentoVertical / 2));
}

Retangulo::~Retangulo() {
	delete cor;
}

Cor
Retangulo::obterCor(void) {
	return (*cor);
}

void
Retangulo::mover(float x, float y) {
}

void
Retangulo::desenhar(void) {
}