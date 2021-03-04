#ifndef RETANGULO_H
#define RETANGULO_H

#include <vector>

#include "Cor.h"
#include "Pixel.h"

class Retangulo {
public:
	Retangulo(Pixel, float, float, Cor);
	~Retangulo();

	std::vector<Pixel*> obterPixels(void);
	float obterLargura(void);
	float obterAltura(void);
	Cor obterCor(void);
	float obterAngulo	(void);
	void definirAngulo(float);
	void inclinar(int);
	void mover(float, float);
	
private:
	std::vector<Pixel*> pixels;
	float largura;
	float altura;
	Cor cor;
	float angulo;
};

#endif