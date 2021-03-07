#include "Retangulo.h"

#include <GL/glut.h>
#include <cmath>
#include <cfloat>

Retangulo::Retangulo(Pixel pixel, float largura, float altura, Cor cor) : largura(largura), altura(altura), cor(cor) {
	pixels.push_back(new Pixel(pixel.obterX() - largura / 2, pixel.obterY() - altura / 2));
	pixels.push_back(new Pixel(pixel.obterX() - largura / 2, pixel.obterY() + altura / 2));
	pixels.push_back(new Pixel(pixel.obterX() + largura / 2, pixel.obterY() + altura / 2));
	pixels.push_back(new Pixel(pixel.obterX() + largura / 2, pixel.obterY() - altura / 2));
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
Retangulo::inclinar(int angulo) {
	this->angulo += angulo;
}

void
Retangulo::mover(float x, float y) {
	// for (auto& pixel : pixels)
	// 	pixel->incrementar(x, y);
	FormaGeometrica2D::mover(x, y);
}

void
Retangulo::desenhar(void) {
	glColor3f(obterCor().obterVermelho(), obterCor().obterVerde(), obterCor().obterAzul());
	glPushMatrix();
	glRotatef(-obterAngulo(), 0.0f, 0.0f, 1.0f);
	glTranslatef(deslocamentoHorizontal, deslocamentoVertical, 0.0f);
	glBegin(GL_POLYGON);
	for (auto pixel : obterPixels())
		glVertex3f(pixel->obterX(), pixel->obterY(), 0.0f);
	glTranslatef(-deslocamentoHorizontal, -deslocamentoVertical, 0.0f);
	glRotatef(obterAngulo(), 0.0f, 0.0f, 1.0f);
	glEnd();
	glPopMatrix();
}

Pixel*
Retangulo::obterPixelInferirEsquerdo(std::vector<Pixel*> pixels) {
	float x = pixels.at(0)->obterX(), y = pixels.at(0)->obterY(), minX, minY;
	
	for (auto pixelInicial = pixels.begin(), pixelAtual = std::next(pixelInicial); pixelAtual != pixels.end(); ++pixelAtual) {
		if (x > (minX = std::min((*pixelInicial)->obterX(), (*pixelAtual)->obterX())))
			x = minX;
		if (y > (minY = std::min((*pixelInicial)->obterY(), (*pixelAtual)->obterY())))
			y = minY;
	}

	return (new Pixel(x, y));
}

Pixel*
Retangulo::obterPixelInferirDireito(std::vector<Pixel*> pixels) {
	float x = pixels.at(0)->obterX(), y = pixels.at(0)->obterY(), maxX, minY;

	for (auto pixelInicial = pixels.begin(), pixelAtual = std::next(pixelInicial); pixelAtual != pixels.end(); ++pixelAtual) {
		if (x < (maxX = std::max((*pixelInicial)->obterX(), (*pixelAtual)->obterX())))
			x = maxX;
		if (y > (minY = std::min((*pixelInicial)->obterY(), (*pixelAtual)->obterY())))
			y = minY;
	}

	return (new Pixel(x, y));
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

Pixel*
Retangulo::obterPixelIntermediario(Pixel pixelInicial, Pixel pixelFinal) {
	return (new Pixel((pixelInicial.obterX() + pixelFinal.obterX()) / 2.0f, (pixelInicial.obterY() + pixelFinal.obterY()) / 2.0f));
}