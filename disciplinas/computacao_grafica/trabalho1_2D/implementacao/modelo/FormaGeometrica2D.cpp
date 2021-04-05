#include "FormaGeometrica2D.h"

#include <cmath>

FormaGeometrica2D::FormaGeometrica2D(Vetor2* pose, float angulo, Cor* cor) : pose(pose), angulo(angulo), cor(cor) {
}

FormaGeometrica2D::FormaGeometrica2D(Vetor2* pose, Cor* cor) : FormaGeometrica2D(pose, 0.0f, cor) {
}

FormaGeometrica2D::FormaGeometrica2D(Cor* cor) : FormaGeometrica2D(nullptr, 0.0f, cor) {
}

FormaGeometrica2D::~FormaGeometrica2D() {
	delete pose;
	delete cor;
}

Vetor2&
FormaGeometrica2D::obterPose(void) {
	return (*pose);
}

float
FormaGeometrica2D::obterAngulo(void) {
	return (angulo);
}

float
FormaGeometrica2D::obterAngulo(Vetor2 pose) {
	return (atan2f(pose.obterY() - this->pose->obterY(), pose.obterX() - this->pose->obterX()) * 180.0f / M_PI - 90.0f);
}

Cor
FormaGeometrica2D::obterCor(void) {
	return (*cor);
}

void 
FormaGeometrica2D::transladar(float x, float y) {
	pose->incrementar(x, y);
}

void
FormaGeometrica2D::rotacionar(int angulo) {
	this->angulo += angulo;
}