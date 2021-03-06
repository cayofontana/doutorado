#ifndef ICONSUMIDOR_H
#define ICONSUMIDOR_H

class Projetil;

class IConsumidor {
public:
	virtual ~IConsumidor() {};
	virtual bool atualizou(Projetil*) = 0;
};

#endif