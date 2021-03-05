#ifndef ALVO_H
#define ALVO_H

#include "primitivas/Circunferencia.h"

class Alvo {
public:
	Alvo(int, int);
	~Alvo();

	Circunferencia* obterCorpo(void);

private:
	int larguraJanela;
	int alturaJanela;
	Circunferencia* corpo;
};

#endif