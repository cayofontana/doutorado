#include "Robo.h"

#include <math.h>
#include <iostream>
using namespace std;

Robo::Robo(int larguraJanela, int alturaJanela) : larguraJanela(larguraJanela), alturaJanela(alturaJanela) {
	construir();
}

Robo::~Robo() {
	delete base;
	delete hasteBase;
	delete hasteMedia;
	delete hastePonta;
}

void
Robo::construir(void) {
	Pixel pixelCentral(0.5f, 0.5f);

	Pixel pixelCentralBase(0.5f, pixelCentral.obterX() - 0.3f);
	float largura = 100.0f / (float) larguraJanela, altura = 40.0f / (float) alturaJanela;

	base = new Retangulo(&pixelCentralBase, largura, altura, Cor(255.0f, 0.0f, 0.0f));
}

void
Robo::mover(float x, float y) {
	for (auto& pixel : base->obterPixels())
		pixel->incrementar(x, y);
}

Retangulo*
Robo::obterBase(void) {
	return (base);
}