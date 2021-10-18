#include "Projetil.h"

#include <GL/gl.h>
#include <cmath>
#include <iostream>
using namespace std;

Projetil::Projetil(float raio, Pixel* pixel, float intervaloAngular, int tipo, float tamanhoPonto, std::vector<Retangulo*> bracos) : Circunferencia(raio, pixel, intervaloAngular, tipo, tamanhoPonto) {
	float deslocamentoHorizontal, deslocamentoVertical, angulo;
	deslocamentoHorizontal = deslocamentoVertical = angulo = 0.0f;

	for (auto const braco : bracos) {
		deslocamentoHorizontal = braco->obterDeslocamentoHorizontal();
		deslocamentoVertical = braco->obterAltura() + braco->obterDeslocamentoVertical();
		angulo += braco->obterAngulo();
	}
	cout << "deslocamentoHorizontal: " << deslocamentoHorizontal << endl;
	cout << "deslocamentoVertical: " << deslocamentoVertical << endl;
	mover(deslocamentoHorizontal, deslocamentoVertical);
	rotacionar(angulo);
}

Projetil::~Projetil() {
	for (auto consumidor : consumidores)
		delete consumidor;
}

void
Projetil::desenhar(void) {
	float anguloRadianos = obterAngulo() * M_PI / 180.0f;
	mover(5.0f * sinf(anguloRadianos), 5.0f * cosf(anguloRadianos));

	glColor3f(obterPixel().obterCor().obterVermelho(), obterPixel().obterCor().obterVerde(), obterPixel().obterCor().obterAzul());
	glLoadIdentity();	

		glPushMatrix(); {
			glTranslatef(obterPixel().obterX(), obterPixel().obterY(), 0.0f);
			glPointSize(obterTamanhoPonto());
			glBegin(obterTipo());
			for (float anguloRaio = 0.0f; anguloRaio <= (2.0f * M_PI); anguloRaio += obterIntervaloAngular()) {
				float x = obterRaio() * sin(anguloRaio);
				float y = obterRaio() * cos(anguloRaio);
				glVertex3f(x, y, 0.0f);
			}
			glEnd();
		}
		glPopMatrix();

	notificar();
}

std::list<IConsumidor*>
Projetil::obterConsumidores(void) {
	return (consumidores);
}

void
Projetil::adicionar(IConsumidor* consumidor) {
	consumidores.push_back(consumidor);
}

void
Projetil::remover(IConsumidor* consumidor) {
	consumidores.remove(consumidor);
}

void
Projetil::notificar(void) {
	for (auto consumidor = consumidores.begin(); consumidor != consumidores.end(); ++consumidor)
		if ((*consumidor)->atualizou(this)) {
			consumidores.clear();
			break;
		}
}