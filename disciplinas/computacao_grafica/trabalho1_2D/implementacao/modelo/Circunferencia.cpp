#include "Circunferencia.h"

#include <GL/glut.h>
#include <cmath>

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
Circunferencia::desenhar(void) {
	glEnable(GL_POINT_SMOOTH);
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
		for (float anguloRaio = 0.0f; anguloRaio <= (2.0f * M_PI); anguloRaio += intervaloAngular * 0.1f) {
			float x = raio * sin(anguloRaio);
			float y = raio * cos(anguloRaio);
			glVertex3f(x, y, 0.0f);
		}
	}
	glEnd();
}

bool
Circunferencia::colidiu(Circunferencia* circunferencia) {
	return (Pixel(obterDeslocamentoHorizontal(), obterDeslocamentoVertical()).calcularDistancia(Pixel(circunferencia->obterDeslocamentoHorizontal(), circunferencia->obterDeslocamentoVertical())) <= obterRaio());
}

void
Circunferencia::definirRaio(float raio) {
	this->raio = raio;
}