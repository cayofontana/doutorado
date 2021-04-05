#ifndef VETOR2_H
#define VETOR2_H

#include "Cor.h"

class Vetor2 {
public:
	Vetor2(float, float);

	float obterX(void);
	void definirX(float);
	float obterY(void);
	void definirY(float);
	void incrementar(float, float);
	float calcularDistancia(Vetor2);

private:
	float x;
	float y;
};

#endif