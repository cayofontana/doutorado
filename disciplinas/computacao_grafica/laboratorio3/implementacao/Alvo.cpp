#include "Alvo.h"
#include "primitivas/Cor.h"

#include <GL/gl.h>
#include <iostream>

Alvo::Alvo(int larguraJanela, int alturaJanela) : larguraJanela(larguraJanela), alturaJanela(alturaJanela) {
	corpo = new Circunferencia(20.0f, new Pixel(0.0f, alturaJanela / 2 * 0.8f, Cor(255.0f, 0.0f, 0.0f)), 0.1f, GL_TRIANGLE_FAN, 1.0f);
}

Alvo::~Alvo() {
	delete corpo;
}

void
Alvo::desenhar(void) {
	corpo->desenhar();
}

Circunferencia*
Alvo::obterCorpo(void) {
	return (corpo);
}

void
Alvo::reiniciar(void) {
	Cor cor(corpo->obterPixel().obterCor().obterVermelho() > 0.0f || corpo->obterPixel().obterCor().obterVerde() > 0.0f ? 0.0f : 255.0f, corpo->obterPixel().obterCor().obterVerde() > 0.0f || corpo->obterPixel().obterCor().obterAzul() > 0.0f ? 0.0f : 255.0f, corpo->obterPixel().obterCor().obterAzul() > 0.0f || corpo->obterPixel().obterCor().obterVermelho() > 0.0f ? 0.0f : 255.0f);
	delete corpo; 
	corpo = new Circunferencia(20.0f, new Pixel(rand() % larguraJanela + (larguraJanela / 2 * -1), alturaJanela / 2 * 0.8f, cor), 0.1f, GL_TRIANGLE_FAN, 1.0f);
}

bool
Alvo::atualizou(Projetil* projetil) {
	if (projetil && corpo->colidiu(projetil)) {
		reiniciar();
		return (true);
	}
	return (false);
}