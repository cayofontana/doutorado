#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H

#include "Pixel.h"

class Circunferencia {
public:
	Circunferencia(float, Pixel);

	float obterRaio(void);
	float obterDiametro(void);
	
private:
	float raio;
	Pixel pixel;
};

#endif