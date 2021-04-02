#ifndef FORMAGEOMETRICA2D_H
#define FORMAGEOMETRICA2D_H

#include "primitivas/Cor.h"
#include "primitivas/Vetor2.h"

class FormaGeometrica2D {
public:
	~FormaGeometrica2D();

	Vetor2 obterPose(void);
	float obterAngulo(void);
	float obterAngulo(Vetor2);
	Cor obterCor(void);
	void transladar(float, float);
	void rotacionar(int);

	virtual void desenhar(void) = 0;

protected:
	Vetor2 pose;
	float angulo;
	Cor* cor;

	FormaGeometrica2D(Vetor2, Cor*);
	FormaGeometrica2D(Cor*);
};

#endif