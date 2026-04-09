#include "Circunferencia.h"

#include <GL/glut.h>
#include <cmath>

Circunferencia::Circunferencia(float raio, Vetor2* pose, Cor* cor, float intervaloAngular, float tamanhoPonto, int tipo, bool preenchida, bool bordaContinua, bool bordaTracejada) : FormaGeometrica2D(pose, cor), raio(raio), intervaloAngular(intervaloAngular), tamanhoPonto(tamanhoPonto), tipo(tipo), preenchida(preenchida), bordaContinua(bordaContinua), bordaTracejada(bordaTracejada) {
}

Circunferencia::Circunferencia(float raio, Cor* cor, float intervaloAngular, float tamanhoPonto, int tipo, bool preenchida, bool bordaContinua, bool bordaTracejada) : Circunferencia(raio, nullptr, cor, intervaloAngular, tamanhoPonto, tipo, preenchida, bordaContinua, bordaTracejada) {
}

Circunferencia::~Circunferencia() {
}

float
Circunferencia::obterRaio(void) {
	return (raio);
}

void
Circunferencia::desenhar(void) {
	if (preenchida) {
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
	}

	if (bordaContinua) {
		glPointSize(tamanhoPonto * 2.0f);
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

	if (bordaTracejada) {
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, 0x00FF);
		glLineWidth(tamanhoPonto * 3.0f);
		glColor3f(obterCor().obterVermelho(), obterCor().obterVerde(), obterCor().obterAzul());
		glBegin(GL_LINE_LOOP);
		for (float anguloRaio = 0.0f; anguloRaio <= (2.0f * M_PI); anguloRaio += intervaloAngular) {
			float x = raio * sin(anguloRaio);
			float y = raio * cos(anguloRaio);
			glVertex3f(x, y, 0.0f);
		}
		glEnd();
		glDisable(GL_LINE_STIPPLE);
	}
}

bool
Circunferencia::colidiu(Circunferencia* circunferencia) {
	return (obterPose().calcularDistancia(circunferencia->obterPose()) <= (obterRaio() + circunferencia->obterRaio()));
}