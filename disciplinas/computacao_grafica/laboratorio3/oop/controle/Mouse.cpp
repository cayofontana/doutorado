#include "Mouse.h"

Mouse::Mouse() {
}

void
Mouse::clicar(int botao, int estado, int x, int y, const int larguraJanela, const int alturaJanela) {
}

void
Mouse::clicarMovendo(int x, int y, const int larguraJanela, const int alturaJanela, std::vector<Pixel*> pixels) {
}

bool
Mouse::possuiBotaoEsquerdoPressionado(void) {
	return (botaoEsquerdoPressionado);
}