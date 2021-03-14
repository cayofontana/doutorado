#include "Retangulo.h"

#include <GL/gl.h>

Retangulo::Retangulo(int deslocamentoHorizontal, int deslocamentoVertical, float base, float lateral, Cor* cor) : FormaGeometrica2D(deslocamentoHorizontal, deslocamentoVertical), base(base), lateral(lateral), cor(cor) {
	float medidabase = base, medidaLateral = lateral;
	pixels.push_back(new Pixel(-medidabase, -medidaLateral));
	pixels.push_back(new Pixel(-medidabase, medidaLateral));
	pixels.push_back(new Pixel(medidabase, medidaLateral));
	pixels.push_back(new Pixel(medidabase, -medidaLateral));
}

Retangulo::~Retangulo() {
	delete cor;
}

Cor
Retangulo::obterCor(void) {
	return (*cor);
}

void
Retangulo::desenhar(void) {
	glColor3f(obterCor().obterVermelho(), obterCor().obterVerde(), obterCor().obterAzul());
	glBegin(GL_POLYGON); {
		for (auto pixel : obterPixels())
			glVertex3f(pixel->obterX(), pixel->obterY(), 0.0f);
	}
	glEnd();
}