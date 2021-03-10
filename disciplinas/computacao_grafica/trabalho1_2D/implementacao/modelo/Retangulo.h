#ifndef RETANGULO_H
#define RETANGULO_H

#include "primitivas/Cor.h"
#include "primitivas/Pixel.h"
#include "FormaGeometrica2D.h"

#include <vector>

class Retangulo : public FormaGeometrica2D {
public:
	Retangulo(Pixel, float, float, Cor);
	virtual ~Retangulo();

	Cor obterCor(void);

	void mover(float, float) override;
	void desenhar(void) override;
	
private:
	Cor cor;
};

#endif