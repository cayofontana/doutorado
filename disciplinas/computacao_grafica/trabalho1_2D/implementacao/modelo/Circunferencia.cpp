#include "Circunferencia.h"

#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

Circunferencia::Circunferencia(int deslocamentoHorizontal, int deslocamentoVertical, float raio, Cor* cor, float intervaloAngular, float tamanhoPonto) : FormaGeometrica2D(deslocamentoHorizontal, deslocamentoVertical), raio(raio), intervaloAngular(intervaloAngular), tamanhoPonto(tamanhoPonto) {
	pixels.push_back(new Pixel(0.0f, 0.0f, cor));
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

void
Circunferencia::mover(float x, float y) {
}

void
Circunferencia::desenhar(void) {
	glLoadIdentity();
	glPushMatrix(); {
		glEnable(GL_POINT_SMOOTH);
		glRotatef(obterAngulo(), 0.0f, 0.0f, 1.0f);
		glTranslatef(deslocamentoHorizontal, deslocamentoVertical, 0.0f);
		glPointSize(tamanhoPonto);
		Cor corSombreada = obterPixel().obterCorSombreada();
		glColor3f(corSombreada.obterVermelho(), corSombreada.obterVerde(), corSombreada.obterAzul());
		glBegin(GL_TRIANGLE_FAN); {
			for (float anguloRaio = 0.0f; anguloRaio <= (2.0f * M_PI); anguloRaio += intervaloAngular) {
				float x = raio * sin(anguloRaio);
				float y = raio * cos(anguloRaio);
				glVertex3f(x, y, 0.0f);
			}
		}
		glEnd();
		glPointSize(tamanhoPonto * 3);		
		glColor3f(obterPixel().obterCor().obterVermelho(), obterPixel().obterCor().obterVerde(), obterPixel().obterCor().obterAzul());
		glBegin(GL_POINTS); {
			for (float anguloRaio = 0.0f; anguloRaio <= (2.0f * M_PI); anguloRaio += 0.0001f) {
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