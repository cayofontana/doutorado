#ifndef PIXEL_H
#define PIXEL_H

#include "Cor.h"

class Pixel {
public:
	Pixel(float, float);
	Pixel(float, float, Cor);

	float obterX(void);
	void definirX(float);
	float obterY(void);
	void definirY(float);
	Cor obterCor(void);
	void incrementar(float, float);
	void definirCoordenadasGL(int, int, int, int);

private:
	float x;
	float y;
	Cor cor;
};

#endif