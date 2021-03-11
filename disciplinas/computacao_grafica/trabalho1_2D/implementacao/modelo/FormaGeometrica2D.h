#ifndef FORMAGEOMETRICA2D_H
#define FORMAGEOMETRICA2D_H

#include <vector>

#include "primitivas/Cor.h"
#include "primitivas/Pixel.h"

class FormaGeometrica2D {
public:
	~FormaGeometrica2D();

	std::vector<Pixel*> obterPixels(void);
	float obterAngulo(void);

	virtual void mover(float, float) = 0;
	virtual void desenhar(void) = 0;

protected:
	std::vector<Pixel*> pixels;
	int deslocamentoHorizontal;
	int deslocamentoVertical;
	float angulo;

	FormaGeometrica2D(int, int);
};

#endif