#include "Retangulo.h"

#include <GL/glut.h>
#include <cmath>
#include <cfloat>

Retangulo::Retangulo(Pixel pixel, float largura, float altura, Cor cor) : largura(largura), altura(altura), cor(cor) {
	pixels.push_back(new Pixel(pixel.obterX() - largura / 2, pixel.obterY()));
	pixels.push_back(new Pixel(pixel.obterX() - largura / 2, pixel.obterY() + altura));
	pixels.push_back(new Pixel(pixel.obterX() + largura / 2, pixel.obterY() + altura));
	pixels.push_back(new Pixel(pixel.obterX() + largura / 2, pixel.obterY()));
}

Retangulo::~Retangulo() {
}

float
Retangulo::obterLargura(void) {
	return (largura);
}

float
Retangulo::obterAltura(void) {
	return (altura);
}

Cor
Retangulo::obterCor(void) {
	return (cor);
}

void
Retangulo::mover(float x, float y) {
	FormaGeometrica2D::mover(x, y);
}

void
Retangulo::desenhar(void) {
	glColor3f(obterCor().obterVermelho(), obterCor().obterVerde(), obterCor().obterAzul());
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(deslocamentoHorizontal, deslocamentoVertical, 0.0f);
	glRotatef(-obterAngulo(), 0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	for (auto pixel : obterPixels())
		glVertex3f(pixel->obterX(), pixel->obterY(), 0.0f);
	glEnd();
	glRotatef(obterAngulo(), 0.0f, 0.0f, 1.0f);
	glTranslatef(-deslocamentoHorizontal, -deslocamentoVertical, 0.0f);
	glPopMatrix();
}

Pixel*
Retangulo::obterPixelSuperiorEsquerdo(std::vector<Pixel*> pixels) {
	float x = pixels.at(0)->obterX(), y = pixels.at(0)->obterY(), maxY, minX;

	for (auto pixelInicial = pixels.begin(), pixelAtual = std::next(pixelInicial); pixelAtual != pixels.end(); ++pixelAtual) {
		if (x > (minX = std::min((*pixelInicial)->obterX(), (*pixelAtual)->obterX())))
			x = minX;
		if (y < (maxY = std::max((*pixelInicial)->obterY(), (*pixelAtual)->obterY())))
			y = maxY;
	}

	return (new Pixel(x, y));
}

Pixel*
Retangulo::obterPixelSuperiorDireito(std::vector<Pixel*> pixels) {
	float x = pixels.at(0)->obterX(), y = pixels.at(0)->obterY(), maxX, maxY;

	for (auto pixelInicial = pixels.begin(), pixelAtual = std::next(pixelInicial); pixelAtual != pixels.end(); ++pixelAtual) {
		if (x < (maxX = std::max((*pixelInicial)->obterX(), (*pixelAtual)->obterX())))
			x = maxX;
		if (y < (maxY = std::max((*pixelInicial)->obterY(), (*pixelAtual)->obterY())))
			y = maxY;
	}

	return (new Pixel(x, y));
}