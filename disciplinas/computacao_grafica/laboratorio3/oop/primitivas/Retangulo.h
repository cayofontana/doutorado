#ifndef RETANGULO_H
#define RETANGULO_H

#include "FormaGeometrica2D.h"
#include "Cor.h"
#include "Pixel.h"

#include <vector>

class Retangulo : public FormaGeometrica2D {
public:
	Retangulo(Pixel, float, float, Cor);
	virtual ~Retangulo();

	float obterLargura(void);
	float obterAltura(void);
	Cor obterCor(void);
	void inclinar(int);
	void mover(float, float) override;
	void desenhar(void) override;

	static Pixel* obterPixelInferirEsquerdo(std::vector<Pixel*>);
	static Pixel* obterPixelInferirDireito(std::vector<Pixel*>);
	static Pixel* obterPixelSuperiorEsquerdo(std::vector<Pixel*>);
	static Pixel* obterPixelSuperiorDireito(std::vector<Pixel*>);
	static Pixel* obterPixelIntermediario(Pixel, Pixel);
	
private:
	float largura;
	float altura;
	Cor cor;
};

#endif