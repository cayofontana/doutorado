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
	Retangulo* obterHasteBase(void);
	Retangulo* obterHasteMedia(void);
	Retangulo* obterHastePonta(void);
	std::vector<Circunferencia*> obterRodas(void);
	void inclinarHasteBase(int);

private:
	int larguraJanela;
	int alturaJanela;
	std::vector<Circunferencia*> rodas;
	Retangulo* base;
	Retangulo* hasteBase;
	Retangulo* hasteMedia;
	Retangulo* hastePonta;

	void construirBase(float, float, Pixel*);
	void construirhasteBase(float, float, Pixel*);
	void construirhasteMedia(float, float, Pixel*);
	void construirhastePonta(float, float, Pixel*);
	Circunferencia* construirRoda(float, Pixel);

	Pixel obterEixoEsquerdo(Cor);
	Pixel obterEixoDireito(Cor);
};

#endif