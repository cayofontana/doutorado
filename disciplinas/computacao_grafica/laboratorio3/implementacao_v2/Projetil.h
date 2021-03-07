#ifndef PROJETIL_H
#define PROJETIL_H

#include "primitivas/Circunferencia.h"
#include "IProdutor.h"
#include "IConsumidor.h"

#include <list>

class Projetil : public Circunferencia, public IProdutor {
public:
	Projetil(float, Pixel*, float, int, float);
	virtual ~Projetil();

	void desenhar(void) override;
	std::list<IConsumidor*> obterConsumidores(void);

	void adicionar(IConsumidor*) override;
	void remover(IConsumidor*) override;
	void notificar(void) override;

private:
	std::list<IConsumidor*> consumidores;
};

#endif