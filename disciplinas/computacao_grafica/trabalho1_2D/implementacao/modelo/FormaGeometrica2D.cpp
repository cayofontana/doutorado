#include "FormaGeometrica2D.h"

FormaGeometrica2D::FormaGeometrica2D(int deslocamentoHorizontal, int deslocamentoVertical) : deslocamentoHorizontal(deslocamentoHorizontal), deslocamentoVertical(deslocamentoVertical), angulo(0) {
}

FormaGeometrica2D::~FormaGeometrica2D() {
	for (auto& pixel : pixels)
		delete pixel;
}

std::vector<Pixel*>
FormaGeometrica2D::obterPixels(void) {
	return (pixels);
}

int
FormaGeometrica2D::obterDeslocamentoHorizontal(void) {
	return (deslocamentoHorizontal);
}

int
FormaGeometrica2D::obterDeslocamentoVertical(void) {
	return (deslocamentoVertical);
}

float
FormaGeometrica2D::obterAngulo(void) {
	return (angulo);
}