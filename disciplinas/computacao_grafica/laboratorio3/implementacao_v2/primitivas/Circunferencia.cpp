#include "Circunferencia.h"

#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

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

float
Circunferencia::obterIntervaloAngular(void) {
	return (intervaloAngular);
}

int
Circunferencia::obterTipo(void) {
	return (tipo);
}

float
Circunferencia::obterTamanhoPonto(void) {
	return (tamanhoPonto);
}

void
Circunferencia::mover(float x, float y) {
	pixels.at(0)->incrementar(x, y);
}

void
Circunferencia::desenhar(void) {
	glColor3f(obterPixel().obterCor().obterVermelho(), obterPixel().obterCor().obterVerde(), obterPixel().obterCor().obterAzul());
	glLoadIdentity();
	glPushMatrix();
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
	glPopMatrix();
}

bool
Circunferencia::colidiu(Circunferencia* circunferencia) {
	// float x = ((obterPixel().obterY() - circunferencia->obterPixel().obterY()) - (circunferencia->obterAngulo() * obterPixel().obterX()) / -circunferencia->obterAngulo());


	// cout << "circunferencia->obterPixel().obterX() + circunferencia->obterRaio() * std::cos(circunferencia->obterAngulo())" << circunferencia->obterPixel().obterX() + circunferencia->obterRaio() * std::cos(circunferencia->obterAngulo()) << endl;
	// cout << "alvo: (" << obterPixel().obterX() << ", " << obterPixel().obterY() << ")" << endl;
	// cout << "projétil: (" << circunferencia->obterPixel().obterX() << ", " << circunferencia->obterPixel().obterY() << ")" << endl;
	// cout << "angulo projétil: " << circunferencia->obterAngulo() << endl;
	// cout << "x projétil: " << x << endl;

	// return (sqrt(pow(obterPixel().obterX() - x, 2) + pow(obterPixel().obterY() - circunferencia->obterPixel().obterY(), 2)) <= raio + circunferencia->obterRaio());
	return (obterPixel().calcularDistancia(circunferencia->obterPixel()) <= raio + circunferencia->obterRaio());
}