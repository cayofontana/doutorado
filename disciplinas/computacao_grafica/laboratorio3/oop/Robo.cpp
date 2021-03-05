#include "Robo.h"

#include <GL/gl.h>
#include <iostream>
using namespace std;

Robo::Robo(int larguraJanela, int alturaJanela) : larguraJanela(larguraJanela), alturaJanela(alturaJanela), projetil(nullptr) {
	Pixel pixelReferencia(0.0f, alturaJanela / 2.0f);

	construirBase(100.0f, 40.0f, &pixelReferencia);
	bracos.insert(std::pair<Braco, Retangulo*>(Braco::BASE, construirBraco(10.0f, 80.0f, &pixelReferencia, new Cor(0.0f, 0.0f, 255.0f))));
	bracos.insert(std::pair<Braco, Retangulo*>(Braco::MEDIO, construirBraco(10.0f, 80.0f, &pixelReferencia, new Cor(255.0f, 255.0f, 0.0f))));
	bracos.insert(std::pair<Braco, Retangulo*>(Braco::PONTA, construirBraco(10.0f, 80.0f, &pixelReferencia, new Cor(0.0f, 255.0f, 0.0f))));
	rodas.push_back(construirRoda(30.0f, 0.35f, Retangulo::obterPixelInferirEsquerdo(base->obterPixels()), new Cor(255.0f, 255.0f, 255.0f)));
	rodas.push_back(construirRoda(30.0f, 0.35f, Retangulo::obterPixelInferirDireito(base->obterPixels()), new Cor(255.0f, 255.0f, 255.0f)));
}

Robo::~Robo() {
	delete base;
	for (auto& roda : rodas)
		delete roda;
	for (auto const& par : bracos) {
		auto braco = par.second;
		delete braco;
	}
	delete projetil;
}

void
Robo::desenhar(void) {
	base->desenhar();
	for (auto& roda : rodas)
		roda->desenhar();
	for (auto const& par : bracos) {
		auto braco = par.second;
		braco->desenhar();
	}
	if (projetil)
		projetil->desenhar();
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
Robo::disparar(Alvo* alvo) {
	Pixel* pixelProjetil = Retangulo::obterPixelIntermediario(*Retangulo::obterPixelSuperiorEsquerdo(bracos[Braco::PONTA]->obterPixels()), *Retangulo::obterPixelSuperiorDireito(bracos[Braco::PONTA]->obterPixels()));
	
	projetil = new Projetil(5.0f, new Pixel(pixelProjetil->obterX(), pixelProjetil->obterY(), Cor(255.0f, 255.0f, 255.0f)), 0.1f, GL_TRIANGLE_FAN, 1.0f);
	projetil->adicionar(this);
	projetil->adicionar(alvo);
}

void
Robo::atualizar(Projetil* projetil) {	
	// VERIFICAR SE O PROJÉTIL ESTÁ FORA DA CENA. SE ESTIVER, LIBERAR A MEMÓRIA DO OBJETO.
	// if (projetil && Cenario::estahNoCenario(projetil))
	// 	delete projetil;
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
Robo::construirRoda(float raio, float intervaloAngular, Pixel* pixelReferencia, Cor* cor) {
	pixelReferencia->definirCor(*cor);
	return (new Circunferencia(raio, pixelReferencia, intervaloAngular, GL_POINTS, 3.0f));
}