#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H

#include "Pixel.h"

class Circunferencia {
public:
	Circunferencia(float, Pixel);

	float obterRaio(void);
	Pixel obterPixel(void);
	float obterDiametro(void);
	float obterAngulo(void);
	void definirAngulo(float);
	void mover(float, float);
	
private:
	float raio;
	Pixel pixel;
	float angulo;
};

#endif