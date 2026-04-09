#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H

#include "primitivas/Vetor2.h"
#include "FormaGeometrica2D.h"

class Circunferencia : public FormaGeometrica2D {
public:
	Circunferencia(float, Vetor2*, Cor*, float, float, int, bool, bool, bool);
	Circunferencia(float, Cor*, float, float, int, bool, bool, bool);
	virtual ~Circunferencia();

	float obterRaio(void);
	bool colidiu(Circunferencia*);
	
	void desenhar(void) override;

protected:
	void definirRaio(float);
	
private:
	float raio;
	float intervaloAngular;
	float tamanhoPonto;
	int tipo;
	bool preenchida;
	bool bordaContinua;
	bool bordaTracejada;
};

#endif