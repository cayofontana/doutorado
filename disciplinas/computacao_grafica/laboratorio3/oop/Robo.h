#ifndef ROBO_H
#define	ROBO_H

#include <vector>

#include "primitivas/Circunferencia.h"
#include "primitivas/Retangulo.h"

class Robo {
public:
	Robo(int, int);
	~Robo();

	void mover(float, float);
	Retangulo* obterBase(void);

private:
	int larguraJanela;
	int alturaJanela;
	std::vector<Circunferencia> rodas;
	Retangulo* base;
	Retangulo* hasteBase;
	Retangulo* hasteMedia;
	Retangulo* hastePonta;

	void construir(void);
};

#endif