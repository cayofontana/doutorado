#include "Robo.h"

#include <math.h>
#include <float.h>
#include <algorithm>

#include <iostream>
using namespace std;

Robo::Robo(int larguraJanela, int alturaJanela) : larguraJanela(larguraJanela), alturaJanela(alturaJanela) {
	Pixel pixelReferencia(0.0f, alturaJanela / 2.0f);

	construirBase(100.0f, 40.0f, &pixelReferencia);
	// bracos.push_back(construirBraco(10.0f, 80.0f, &pixelReferencia));
	// bracos.push_back(construirBraco(10.0f, 80.0f, &pixelReferencia));
	// bracos.push_back(construirBraco(10.0f, 80.0f, &pixelReferencia));
	construirhasteBase(10.0f, 80.0f, &pixelReferencia);
	construirhasteMedia(10.0f, 80.0f, &pixelReferencia);
	construirhastePonta(10.0f, 80.0f, &pixelReferencia);
	rodas.push_back(construirRoda(30.0f, obterEixoEsquerdo(Cor(255.0f, 255.0f, 255.0f))));
	rodas.push_back(construirRoda(30.0f, obterEixoDireito(Cor(255.0f, 255.0f, 255.0f))));
}

Robo::~Robo() {
	delete base;
	delete hasteBase;
	delete hasteMedia;
	delete hastePonta;
	for (auto& roda : rodas)
		delete roda;
}

void
Robo::mover(float x, float y) {
	// COLOCAR OS COMPONENTES EM UMA LLISTA
	base->mover(x, y);
	hasteBase->mover(x, y);
	hasteMedia->mover(x, y);
	hastePonta->mover(x, y);
	for (auto& roda : rodas)
		roda->mover(x, y);
}

Retangulo*
Robo::obterBase(void) {
	return (base);
}

Retangulo*
Robo::obterHasteBase(void) {
	return (hasteBase);
}

Retangulo*
Robo::obterHasteMedia(void) {
	return (hasteMedia);
}

Retangulo*
Robo::obterHastePonta(void) {
	return (hastePonta);
}

std::vector<Circunferencia*>
Robo::obterRodas(void) {
	return (rodas);
}

void
Robo::inclinarHasteBase(int valor) {
	hasteBase->inclinar(valor);
}

void
Robo::construirBase(float largura, float altura, Pixel* pixelReferencia) {
	Pixel pixelCentralBase(pixelReferencia->obterX(), (pixelReferencia->obterY() - pixelReferencia->obterY() * 0.3) * -1);
	base = new Retangulo(pixelCentralBase, largura, altura, Cor(255.0f, 0.0f, 0.0f));

	pixelReferencia->definirX(pixelCentralBase.obterX());
	pixelReferencia->definirY(pixelCentralBase.obterY());
}

void
Robo::construirhasteBase(float largura, float altura, Pixel* pixelReferencia) {
	Pixel pixelCentralHasteBase(pixelReferencia->obterX(), pixelReferencia->obterY() + altura / 2 + base->obterAltura() / 2);
	hasteBase = new Retangulo(pixelCentralHasteBase, largura, altura, Cor(0.0f, 0.0f, 255.0f));

	pixelReferencia->definirX(pixelCentralHasteBase.obterX());
	pixelReferencia->definirY(pixelCentralHasteBase.obterY());
}

void
Robo::construirhasteMedia(float largura, float altura, Pixel* pixelReferencia) {
	Pixel pixelCentralHasteMedia(pixelReferencia->obterX(), pixelReferencia->obterY() + altura / 2 + hasteBase->obterAltura() / 2);
	hasteMedia = new Retangulo(pixelCentralHasteMedia, largura, altura, Cor(255.0f, 255.0f, 0.0f));

	pixelReferencia->definirX(pixelCentralHasteMedia.obterX());
	pixelReferencia->definirY(pixelCentralHasteMedia.obterY());
}

void
Robo::construirhastePonta(float largura, float altura, Pixel* pixelReferencia) {
	Pixel pixelCentralHastePonta(pixelReferencia->obterX(), pixelReferencia->obterY() + altura / 2 + hasteMedia->obterAltura() / 2);
	hastePonta = new Retangulo(pixelCentralHastePonta, largura, altura, Cor(0.0f, 255.0f, 0.0f));

	pixelReferencia->definirX(pixelCentralHastePonta.obterX());
	pixelReferencia->definirY(pixelCentralHastePonta.obterY());
}

Circunferencia*
Robo::construirRoda(float raio, Pixel pixelReferencia) {
	// MELHORAR ESSE PONTO DO POLIMORFISMO
	return (new Circunferencia(raio, new Pixel(pixelReferencia.obterX(), pixelReferencia.obterY(), pixelReferencia.obterCor())));
}

Pixel
Robo::obterEixoEsquerdo(Cor cor) {
	float x, y, minX = FLT_MAX, minY = FLT_MAX;

	std::vector<Pixel*> pixels = base->obterPixels();
	for (auto pixelInicial = pixels.begin(), pixelAtual = std::next(pixelInicial); pixelAtual != pixels.end(); ++pixelAtual) {
		if (x > (minX = std::min((*pixelInicial)->obterX(), (*pixelAtual)->obterX())))
			x = minX;
		if (y > (minY = std::min((*pixelInicial)->obterY(), (*pixelAtual)->obterY())))
			y = minY;
	}

	return (Pixel(x, y, cor));
}

Pixel
Robo::obterEixoDireito(Cor cor) {
	float x, y, maxX = FLT_MIN, minY = FLT_MAX;

	std::vector<Pixel*> pixels = base->obterPixels();
	for (auto pixelInicial = pixels.begin(), pixelAtual = std::next(pixelInicial); pixelAtual != pixels.end(); ++pixelAtual) {
		if (x < (maxX = std::max((*pixelInicial)->obterX(), (*pixelAtual)->obterX())))
			x = maxX;
		if (y > (minY = std::min((*pixelInicial)->obterY(), (*pixelAtual)->obterY())))
			y = minY;
	}

	return (Pixel(x, y, cor));
}