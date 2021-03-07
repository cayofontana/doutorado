#include "Circunferencia.h"

#include <GL/glut.h>
#include <cmath>

Circunferencia::Circunferencia(float raio, Pixel* pixel, float intervaloAngular, int tipo, float tamanhoPonto) : raio(raio), intervaloAngular(intervaloAngular), tipo(tipo), tamanhoPonto(tamanhoPonto) {
	pixels.push_back(pixel);
}

Circunferencia::~Circunferencia() {
}

float
Circunferencia::obterRaio(void) {
	return (raio);
}

Pixel
Circunferencia::obterPixel(void) {
	return (*pixels.at(0));
}

float
Circunferencia::obterDiametro(void) {
	return (raio * 2);
}

void
Circunferencia::mover(float x, float y) {
	pixels.at(0)->incrementar(x, y);
	this->angulo += x;
}

void
Circunferencia::desenhar(void) {
	glColor3f(obterPixel().obterCor().obterVermelho(), obterPixel().obterCor().obterVerde(), obterPixel().obterCor().obterAzul());
	glTranslatef(obterPixel().obterX(), obterPixel().obterY(), 0.0f);
	glRotatef(-obterAngulo(), 0.0f, 0.0f, 1.0f);
	glPointSize(tamanhoPonto);
	glBegin(tipo);
	for (float anguloRaio = 0.0f; anguloRaio <= (2.0f * M_PI); anguloRaio += intervaloAngular) {
		float x = obterRaio() * sin(anguloRaio);
		float y = obterRaio() * cos(anguloRaio);
		glVertex3f(x, y, 0.0f);
	}
	glEnd();
	glRotatef(obterAngulo(), 0.0f, 0.0f, 1.0f);
	glTranslatef(-obterPixel().obterX(), -obterPixel().obterY(), 0.0f);
	glEnd();
}

bool
Circunferencia::colidiu(Circunferencia* circunferencia) {
	return (obterPixel().calcularDistancia(circunferencia->obterPixel()) <= raio + circunferencia->obterRaio());
}