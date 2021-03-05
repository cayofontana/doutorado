#include "Projetil.h"

Projetil::Projetil(float raio, Pixel* pixel, float intervaloAngular, int tipo, float tamanhoPonto) : Circunferencia(raio, pixel, intervaloAngular, tipo, tamanhoPonto) {
}

Projetil::~Projetil() {
}