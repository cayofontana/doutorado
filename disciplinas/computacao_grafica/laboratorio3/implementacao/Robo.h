#ifndef ROBO_H
#define	ROBO_H

#include <vector>
#include <map>

#include "primitivas/Circunferencia.h"
#include "primitivas/Retangulo.h"
#include "Projetil.h"
#include "Alvo.h"
#include "Cenario.h"

enum Braco { BASE = 1, MEDIO, PONTA };

class Robo {
public:
	Robo(int, int);
	~Robo();

	void desenhar(void);
	void mover(float, float);
	void mover(Braco, int);
	Retangulo* obterBase(void);
	std::vector<Circunferencia*> obterRodas(void);
	std::map<Braco, Retangulo*> obterBracos(void);
	void disparar(Alvo*, Cenario*);

private:
	int larguraJanela;
	int alturaJanela;
	std::vector<Circunferencia*> rodas;
	std::map<Braco, Retangulo*> bracos;
	Retangulo* base;
	Projetil* projetil;

	void construirBase(float, float, Pixel*);
	Retangulo* construirBraco(float, float, Pixel*, Cor*);
	Circunferencia* construirRoda(float, float, Pixel*, Cor*);
};

#endif