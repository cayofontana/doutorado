#ifndef ROBO_H
#define	ROBO_H

#include <vector>
#include <map>

#include "primitivas/Circunferencia.h"
#include "primitivas/Retangulo.h"

enum Braco { BASE = 1, MEDIO, PONTA };

class Robo {
public:
	Robo(int, int);
	~Robo();

	void mover(float, float);
	Retangulo* obterBase(void);
	std::vector<Circunferencia*> obterRodas(void);
	std::map<Braco, Retangulo*> obterBracos(void);

private:
	int larguraJanela;
	int alturaJanela;
	std::vector<Circunferencia*> rodas;
	std::map<Braco, Retangulo*> bracos;
	Retangulo* base;

	void construirBase(float, float, Pixel*);
	Retangulo* construirBraco(float, float, Pixel*, Cor*);
	Circunferencia* construirRoda(float, Pixel, Cor*);

	Pixel obterEixoEsquerdo(void);
	Pixel obterEixoDireito(void);
};

#endif