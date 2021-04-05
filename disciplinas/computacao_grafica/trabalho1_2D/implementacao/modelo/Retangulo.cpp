#include "Retangulo.h"

#include <GL/gl.h>

Retangulo::Retangulo(float largura, float altura, Vetor2* pose, float angulo, Cor* cor) : FormaGeometrica2D(pose, angulo, cor), largura(largura), altura(altura) {
	vertices.push_back(Vetor2(-largura / 2, -altura / 2));
	vertices.push_back(Vetor2(-largura / 2, altura / 2));
	vertices.push_back(Vetor2(largura / 2, altura / 2));
	vertices.push_back(Vetor2(largura / 2, -altura / 2));
}

Retangulo::Retangulo(float largura, float altura, Vetor2* pose, Cor* cor) : Retangulo(largura, altura, pose, 0.0f, cor) {
}

Retangulo::Retangulo(float largura, float altura, Cor* cor) : Retangulo(largura, altura, nullptr, cor) {
}

Retangulo::~Retangulo(){
}

float
Retangulo::obterLargura(void) {
	return (largura);
}

float
Retangulo::obterAltura(void) {
	return (altura);
}

void
Retangulo::desenhar(void) {
	glColor3f(obterCor().obterVermelho(), obterCor().obterVerde(), obterCor().obterAzul());
	glBegin(GL_POLYGON); {
		for (auto vertice : vertices)
			glVertex3f(vertice.obterX(), vertice.obterY(), 0.0f);
	}
	glEnd();
}