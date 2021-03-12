#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H

#include "primitivas/Pixel.h"
#include "FormaGeometrica2D.h"

class Circunferencia : public FormaGeometrica2D {
public:
	Circunferencia(int, int, float, Cor*, float, int, float);
	virtual ~Circunferencia();
	
	Pixel obterPixel(void);
	void mover(float, float) override;
	void desenhar(void) override;

private:
	float raio;
	float intervaloAngular;
	int tipo;
	float tamanhoPonto;
};

#endif