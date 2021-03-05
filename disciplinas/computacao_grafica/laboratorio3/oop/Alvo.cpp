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
Alvo::atualizar(Projetil* projetil) {
	cout << "Projetil passou pelo Alvo" << endl;
}