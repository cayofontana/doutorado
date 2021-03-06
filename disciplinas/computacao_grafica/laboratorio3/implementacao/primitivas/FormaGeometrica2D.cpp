#include "FormaGeometrica2D.h"

FormaGeometrica2D::FormaGeometrica2D() : angulo(0) {
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