#ifndef PROJETIL_H
#define PROJETIL_H

#include "primitivas/Circunferencia.h"

class Projetil : public Circunferencia {
public:
	Projetil(float, Pixel*);
	virtual ~Projetil();
private:
};

#endif