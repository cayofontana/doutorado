#include "Alvo.h"
#include "primitivas/Cor.h"

#include <GL/gl.h>
#include <iostream>
using namespace std;

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
	delete corpo;
	corpo = new Circunferencia(20.0f, new Pixel(0.0f, alturaJanela / 2 * 0.8f, Cor(255.0f, 0.0f, 0.0f)), 0.1f, GL_TRIANGLE_FAN, 1.0f);
}

void
Alvo::atualizar(Projetil* projetil) {
	// VERIFICAR SE O PROJÉTIL COLIDIU COM O ALVO. SE SIM, LIBERAR A MEMÓRIA DO OBJETO
	// E REINICIAR A POSIÇÃO DO ALVO, RANDOMICAMENTE NO EIXO X.
	// if (projetil && Circunferencia::houveColisao(corpo, projetil)) {
	// 	delete projetil;
	// 	reiniciar();
	// }
}