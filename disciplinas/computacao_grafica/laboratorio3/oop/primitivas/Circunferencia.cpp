#include "Circunferencia.h"

Circunferencia::Circunferencia(float raio, Pixel pixel) : raio(raio), pixel(pixel) {
}

float
Circunferencia::obterRaio(void) {
	return (raio);
}

float
Circunferencia::obterDiametro(void) {
	return (raio * 2);
}