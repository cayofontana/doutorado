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

void
FormaGeometrica2D::definirAngulo(float angulo) {
	this->angulo = angulo;
}

void 
FormaGeometrica2D::transladar(float deslocamentoHorizontal, float deslocamentoVertical) {
	this->deslocamentoHorizontal += deslocamentoHorizontal;
	this->deslocamentoVertical += deslocamentoVertical;
}

void
FormaGeometrica2D::rotacionar(int angulo) {
	this->angulo += angulo;
}