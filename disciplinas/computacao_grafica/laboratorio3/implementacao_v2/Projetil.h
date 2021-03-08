#ifndef PROJETIL_H
#define PROJETIL_H

#include "primitivas/Circunferencia.h"
#include "primitivas/Retangulo.h"
#include "IProdutor.h"
#include "IConsumidor.h"

#include <list>
#include <vector>

class Projetil : public Circunferencia, public IProdutor {
public:
	Projetil(float, Pixel*, float, int, float, std::vector<Retangulo*>);
	virtual ~Projetil();

	std::list<IConsumidor*> obterConsumidores(void);

	void desenhar(void) override;
	
	void adicionar(IConsumidor*) override;
	void remover(IConsumidor*) override;
	void notificar(void) override;

private:
	std::list<IConsumidor*> consumidores;
};

#endif