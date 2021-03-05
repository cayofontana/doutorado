#include "Alvo.h"
#include "primitivas/Cor.h"

#include <GL/gl.h>

Alvo::Alvo(int larguraJanela, int alturaJanela) : larguraJanela(larguraJanela), alturaJanela(alturaJanela) {
	corpo = new Circunferencia(20.0f, new Pixel(0.0f, alturaJanela / 2 * 0.8f, Cor(255.0f, 0.0f, 0.0f)), 0.1f, GL_TRIANGLE_FAN, 1.0f);
}

Alvo::~Alvo() {
	delete corpo;
}

void
Alvo::desenhar(void) {
	// corpo->mover(1.0f, 0.0f);
	corpo->desenhar();
}

Circunferencia*
Alvo::obterCorpo(void) {
	return (corpo);
}