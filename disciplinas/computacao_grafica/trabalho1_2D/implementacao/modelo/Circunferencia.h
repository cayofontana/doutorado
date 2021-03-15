#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H

#include "primitivas/Pixel.h"
#include "FormaGeometrica2D.h"

class Circunferencia : public FormaGeometrica2D {
public:
	Circunferencia(int, int, float, Cor*, float, float);
	virtual ~Circunferencia();
	
	float obterRaio(void);
	Pixel obterPixel(void);
	bool colidiu(Circunferencia*);
	
	void desenhar(void) override;

protected:
	void definirRaio(float);
	
private:
	float raio;
	float intervaloAngular;
	float tamanhoPonto;
};

#endif