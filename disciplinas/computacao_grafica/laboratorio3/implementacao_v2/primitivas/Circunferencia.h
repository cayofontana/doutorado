#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H

#include "FormaGeometrica2D.h"
#include "Pixel.h"

class Circunferencia : public FormaGeometrica2D {
public:
	Circunferencia(float, Pixel*, float, int, float);
	virtual ~Circunferencia();

	float obterRaio(void);
	float obterDiametro(void);
	Pixel obterPixel(void);
	float obterIntervaloAngular(void);
	int obterTipo(void);
	float obterTamanhoPonto(void);
	void desenhar(float);
	bool colidiu(Circunferencia*);

	void mover(float, float) override;
	void desenhar(void) override;

private:
	float raio;
	float intervaloAngular;
	int tipo;
	float tamanhoPonto;
};

#endif