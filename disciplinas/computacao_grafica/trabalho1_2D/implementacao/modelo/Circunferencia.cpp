#include "Circunferencia.h"

#include <GL/glut.h>
#include <cmath>

Circunferencia::Circunferencia(int deslocamentoHorizontal, int deslocamentoVertical, float raio, Cor* cor, float intervaloAngular, int tipo, float tamanhoPonto) : FormaGeometrica2D(deslocamentoHorizontal, deslocamentoVertical), raio(raio), intervaloAngular(intervaloAngular), tipo(tipo), tamanhoPonto(tamanhoPonto) {
	pixels.push_back(new Pixel(0.0f, 0.0f, cor));
}

Circunferencia::~Circunferencia() {
}

Pixel
Circunferencia::obterPixel(void) {
	return (*pixels.at(0));
}

void
Circunferencia::mover(float x, float y) {
}

void
Circunferencia::desenhar(void) {
	glColor3f(obterPixel().obterCor().obterVermelho(), obterPixel().obterCor().obterVerde(), obterPixel().obterCor().obterAzul());
	glLoadIdentity();
	glPushMatrix(); {
		glRotatef(obterAngulo(), 0.0f, 0.0f, 1.0f);
		glTranslatef(deslocamentoHorizontal, deslocamentoVertical, 0.0f);
		glPointSize(tamanhoPonto);
		glBegin(tipo); {
			for (float anguloRaio = 0.0f; anguloRaio <= (2.0f * M_PI); anguloRaio += intervaloAngular) {
				float x = raio * sin(anguloRaio);
				float y = raio * cos(anguloRaio);
				glVertex3f(x, y, 0.0f);
			}
		}
		glEnd();
		glTranslatef(-deslocamentoHorizontal, -deslocamentoVertical, 0.0f);
		glRotatef(-obterAngulo(), 0.0f, 0.0f, 1.0f);
	}
	glPopMatrix();
}