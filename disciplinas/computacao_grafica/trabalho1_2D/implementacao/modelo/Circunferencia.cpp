#include "Circunferencia.h"

#include <GL/glut.h>
#include <cmath>

Circunferencia::Circunferencia(float raio, Cor* cor, float intervaloAngular, float tamanhoPonto, int tipo) : FormaGeometrica2D(cor), raio(raio), intervaloAngular(intervaloAngular), tamanhoPonto(tamanhoPonto), tipo(tipo) {
}

Circunferencia::Circunferencia(float raio, Vetor2 pose, Cor* cor, float intervaloAngular, float tamanhoPonto, int tipo) : FormaGeometrica2D(pose, cor), raio(raio), intervaloAngular(intervaloAngular), tamanhoPonto(tamanhoPonto), tipo(tipo) {
}

Circunferencia::~Circunferencia() {
}

float
Circunferencia::obterRaio(void) {
	return (raio);
}

void
Circunferencia::desenhar(void) {
	glEnable(GL_POINT_SMOOTH);
	glPointSize(tamanhoPonto);
	Cor corSombreada = obterCor().obterSombreada();
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
	glColor3f(obterCor().obterVermelho(), obterCor().obterVerde(), obterCor().obterAzul());
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
	return true;// (Pixel(obterDeslocamentoHorizontal(), obterDeslocamentoVertical()).calcularDistancia(Pixel(circunferencia->obterDeslocamentoHorizontal(), circunferencia->obterDeslocamentoVertical())) <= obterRaio());
}