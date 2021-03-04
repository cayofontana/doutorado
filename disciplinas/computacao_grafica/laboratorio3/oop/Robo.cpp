#include "Robo.h"

#include <cmath>
#include <cfloat>

Robo::Robo(int larguraJanela, int alturaJanela) : larguraJanela(larguraJanela), alturaJanela(alturaJanela) {
	Pixel pixelReferencia(0.0f, alturaJanela / 2.0f);

	construirBase(100.0f, 40.0f, &pixelReferencia);
	bracos.insert(std::pair<Braco, Retangulo*>(Braco::BASE, construirBraco(10.0f, 80.0f, &pixelReferencia, new Cor(0.0f, 0.0f, 255.0f))));
	bracos.insert(std::pair<Braco, Retangulo*>(Braco::MEDIO, construirBraco(10.0f, 80.0f, &pixelReferencia, new Cor(255.0f, 255.0f, 0.0f))));
	bracos.insert(std::pair<Braco, Retangulo*>(Braco::PONTA, construirBraco(10.0f, 80.0f, &pixelReferencia, new Cor(0.0f, 255.0f, 0.0f))));
	rodas.push_back(construirRoda(30.0f, obterEixoEsquerdo(), new Cor(255.0f, 255.0f, 255.0f)));
	rodas.push_back(construirRoda(30.0f, obterEixoDireito(), new Cor(255.0f, 255.0f, 255.0f)));
}

Robo::~Robo() {
	delete base;
	for (auto& roda : rodas)
		delete roda;
	for (auto const& par : bracos) {
		auto braco = par.second;
		delete braco;
	}
}

void
Robo::mover(float x, float y) {
	base->mover(x, y);
	for (auto const& par : bracos) {
		auto braco = par.second;
		braco->mover(x, y);
	}
	for (auto& roda : rodas)
		roda->mover(x, y);
}

Retangulo*
Robo::obterBase(void) {
	return (base);
}

std::vector<Circunferencia*>
Robo::obterRodas(void) {
	return (rodas);
}

std::map<Braco, Retangulo*>
Robo::obterBracos(void) {
	return (bracos);
}

void
Robo::construirBase(float largura, float altura, Pixel* pixelReferencia) {
	Pixel pixelCentralBase(pixelReferencia->obterX(), (pixelReferencia->obterY() - pixelReferencia->obterY() * 0.3) * -1);
	base = new Retangulo(pixelCentralBase, largura, altura, Cor(255.0f, 0.0f, 0.0f));

	pixelReferencia->definirX(pixelCentralBase.obterX());
	pixelReferencia->definirY(pixelCentralBase.obterY());
}

Retangulo*
Robo::construirBraco(float largura, float altura, Pixel* pixelReferencia, Cor* cor) {
	Pixel pixelCentralBraco(pixelReferencia->obterX(), pixelReferencia->obterY() + altura / 2 + base->obterAltura() / 2);

	pixelReferencia->definirX(pixelCentralBraco.obterX());
	pixelReferencia->definirY(pixelCentralBraco.obterY());

	return (new Retangulo(pixelCentralBraco, largura, altura, *cor));
}

Circunferencia*
Robo::construirRoda(float raio, Pixel pixelReferencia, Cor* cor) {
	return (new Circunferencia(raio, new Pixel(pixelReferencia.obterX(), pixelReferencia.obterY(), *cor)));
}

Pixel
Robo::obterEixoEsquerdo(void) {
	float x, y, minX = FLT_MAX, minY = FLT_MAX;

	std::vector<Pixel*> pixels = base->obterPixels();
	for (auto pixelInicial = pixels.begin(), pixelAtual = std::next(pixelInicial); pixelAtual != pixels.end(); ++pixelAtual) {
		if (x > (minX = std::min((*pixelInicial)->obterX(), (*pixelAtual)->obterX())))
			x = minX;
		if (y > (minY = std::min((*pixelInicial)->obterY(), (*pixelAtual)->obterY())))
			y = minY;
	}

	return (Pixel(x, y));
}

Pixel
Robo::obterEixoDireito(void) {
	float x, y, maxX = FLT_MIN, minY = FLT_MAX;

	std::vector<Pixel*> pixels = base->obterPixels();
	for (auto pixelInicial = pixels.begin(), pixelAtual = std::next(pixelInicial); pixelAtual != pixels.end(); ++pixelAtual) {
		if (x < (maxX = std::max((*pixelInicial)->obterX(), (*pixelAtual)->obterX())))
			x = maxX;
		if (y > (minY = std::min((*pixelInicial)->obterY(), (*pixelAtual)->obterY())))
			y = minY;
	}

	return (Pixel(x, y));
}