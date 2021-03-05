#ifndef ICONSUMIDOR_H
#define ICONSUMIDOR_H

class Projetil;

class IConsumidor {
public:
	virtual ~IConsumidor() {};
	virtual void atualizar(Projetil*) = 0;
};

#endif