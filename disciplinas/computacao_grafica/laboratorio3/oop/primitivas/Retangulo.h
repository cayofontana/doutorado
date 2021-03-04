#ifndef RETANGULO_H
#define RETANGULO_H

#include "FormaGeometrica2D.h"
#include "Cor.h"
#include "Pixel.h"

class Retangulo : public FormaGeometrica2D {
public:
	Retangulo(Pixel, float, float, Cor);
	virtual ~Retangulo();

	float obterLargura(void);
	float obterAltura(void);
	Cor obterCor(void);
	void inclinar(int);
	void mover(float, float) override;
	
private:
	float largura;
	float altura;
	Cor cor;
};

#endif