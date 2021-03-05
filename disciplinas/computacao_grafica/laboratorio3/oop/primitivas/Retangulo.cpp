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
Retangulo::inclinar(int valor) {
	this->angulo += valor;
}

void
Retangulo::mover(float x, float y) {
	for (auto& pixel : pixels)
		pixel->incrementar(x, y);
}

void
Retangulo::desenhar(void) {
	glColor3f(obterCor().obterVermelho(), obterCor().obterVerde(), obterCor().obterAzul());
	glBegin(GL_POLYGON);
	for (auto pixel : obterPixels())
		glVertex3f(pixel->obterX(), pixel->obterY(), 0.0f);
	glEnd();
}

Pixel*
Retangulo::obterPixelInferirEsquerdo(std::vector<Pixel*> pixels) {
	float x, y, minX = FLT_MAX, minY = FLT_MAX;
	
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
	float x, y, maxX = FLT_MIN, minY = FLT_MAX;

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
	float x, y, minX = FLT_MAX, maxY = FLT_MIN;

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
	float x, y, maxX = FLT_MIN, maxY = FLT_MIN;

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