#include "Cor.h"

Cor::Cor(float vermelho, float verde, float azul) : vermelho(vermelho), verde(verde), azul(azul) {
}

float
Cor::obterVermelho(void) {
	return (vermelho);
}

void
Cor::definirVermelho(float vermelho) {
	this->vermelho = vermelho;
}

float
Cor::obterVerde(void) {
	return (verde);
}

void
Cor::definirVerde(float verde) {
	this->verde = verde;
}

float
Cor::obterAzul(void) {
	return (azul);
}

void
Cor::definirAzul(float azul) {
	this->azul = azul;
}

Cor
Cor::obterSombreada(void) {
	return (Cor(vermelho * 0.5f, verde * 0.5f, azul * 0.5f));	
}