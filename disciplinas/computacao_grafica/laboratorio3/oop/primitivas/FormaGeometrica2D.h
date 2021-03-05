#ifndef FORMAGEOMETRICA2D_H
#define FORMAGEOMETRICA2D_H

#include <vector>

#include "Cor.h"
#include "Pixel.h"

class FormaGeometrica2D {
public:
	~FormaGeometrica2D();

	std::vector<Pixel*> obterPixels(void);
	float obterAngulo(void);

	virtual void mover(float, float) = 0;
	virtual void desenhar(void) = 0;

protected:
	std::vector<Pixel*> pixels;
	float angulo;

	FormaGeometrica2D();
};

#endif