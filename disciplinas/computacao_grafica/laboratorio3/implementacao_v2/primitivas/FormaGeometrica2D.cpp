#include "FormaGeometrica2D.h"

FormaGeometrica2D::FormaGeometrica2D() : angulo(0), deslocamentoHorizontal(0), deslocamentoVertical(0) {
}

FormaGeometrica2D::~FormaGeometrica2D() {
	for (auto& pixel : pixels)
		delete pixel;
}

std::vector<Pixel*>
FormaGeometrica2D::obterPixels(void) {
	return (pixels);
}

float
FormaGeometrica2D::obterAngulo(void) {
	return (angulo);
}

float
FormaGeometrica2D::obterDeslocamentoHorizontal(void) {
	return (deslocamentoHorizontal);
}

float
FormaGeometrica2D::obterDeslocamentoVertical(void) {
	return (deslocamentoVertical);
}

void
FormaGeometrica2D::mover(float deslocamentoHorizontal, float deslocamentoVertical) {
	this->deslocamentoHorizontal += deslocamentoHorizontal;
	this->deslocamentoVertical += deslocamentoVertical;
}