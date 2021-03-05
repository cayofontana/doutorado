#ifndef PROJETIL_H
#define PROJETIL_H

#include "primitivas/Circunferencia.h"

class Projetil : public Circunferencia {
public:
	Projetil(float, Pixel*, float, int, float);
	virtual ~Projetil();
private:
};

#endif