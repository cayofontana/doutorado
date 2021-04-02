#ifndef RETANGULO_H
#define RETANGULO_H

#include "primitivas/Cor.h"
#include "primitivas/Vetor2.h"
#include "FormaGeometrica2D.h"

#include <vector>
using namespace std;

class Retangulo : public FormaGeometrica2D {
public:
	Retangulo(float, float, Cor*);
	Retangulo(float, float, Vetor2, Cor*);
	virtual ~Retangulo();

	float obterLargura(void);
	float obterAltura(void);

	void desenhar(void) override;
	
private:
	float largura;
	float altura;
	vector<Vetor2> vertices;
};

#endif