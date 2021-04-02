#ifndef VETOR2_H
#define VETOR2_H

#include "Cor.h"

class Vetor2 {
public:
	Vetor2(float, float);
	Vetor2(float, float, Cor*);

	float obterX(void);
	void definirX(float);
	float obterY(void);
	void definirY(float);
	Cor obterCor(void);
	void definirCor(Cor);
	void incrementar(float, float);
	float calcularDistancia(Vetor2);

private:
	float x;
	float y;
	Cor *cor;
};

#endif