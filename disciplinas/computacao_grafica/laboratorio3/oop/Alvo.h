#ifndef ALVO_H
#define ALVO_H

#include <list>

#include "primitivas/Circunferencia.h"
#include "IConsumidor.h"
#include "Projetil.h"

class Alvo : public IConsumidor {
public:
	Alvo(int, int);
	~Alvo();

	void desenhar(void);
	Circunferencia* obterCorpo(void);
	void reiniciar(void);

	bool atualizou(Projetil*) override;

private:
	int larguraJanela;
	int alturaJanela;
	Circunferencia* corpo;
};

#endif