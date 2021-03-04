#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H

#include "FormaGeometrica2D.h"
#include "Pixel.h"

class Circunferencia : public FormaGeometrica2D {
public:
	Circunferencia(float, Pixel*);
	virtual ~Circunferencia();

	float obterRaio(void);
	float obterDiametro(void);
	Pixel obterPixel(void);
	void mover(float, float) override;
	
private:
	float raio;
};

#endif