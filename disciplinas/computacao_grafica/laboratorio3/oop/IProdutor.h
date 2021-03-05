#ifndef IPRODUTOR_H
#define IPRODUTOR_H

#include "IConsumidor.h"

class IProdutor {
public:
	virtual void adicionar(IConsumidor*) = 0;
	virtual void remover(IConsumidor*) = 0;
	virtual void notificar(void) = 0;
};

#endif