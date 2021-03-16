#ifndef FORMAGEOMETRICA2D_H
#define FORMAGEOMETRICA2D_H

#include <vector>

#include "primitivas/Cor.h"
#include "primitivas/Pixel.h"

class FormaGeometrica2D {
public:
	~FormaGeometrica2D();

	std::vector<Pixel*> obterPixels(void);
	int obterDeslocamentoHorizontal(void);
	int obterDeslocamentoVertical(void);
	float obterAngulo(void);

	virtual void desenhar(void) = 0;
	void transladar(float, float);
	void rotacionar(int);
	

protected:
	std::vector<Pixel*> pixels;
	int deslocamentoHorizontal;
	int deslocamentoVertical;
	float angulo;

	FormaGeometrica2D(int, int);
};

#endif