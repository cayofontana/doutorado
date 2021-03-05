#include "Alvo.h"
#include "primitivas/Cor.h"

Alvo::Alvo(int larguraJanela, int alturaJanela) : larguraJanela(larguraJanela), alturaJanela(alturaJanela) {
	corpo = new Circunferencia(20.0f, new Pixel(0.0f, alturaJanela / 2 * 0.8f, Cor(255.0f, 0.0f, 0.0f)));
}

Alvo::~Alvo() {
	delete corpo;
}

Circunferencia*
Alvo::obterCorpo(void) {
	return (corpo);
}