#ifndef TECLADO_H
#define TECLADO_H

#include <vector>

#include "../primitivas/Cor.h"
#include "../Robo.h"

#define INC_KEY 1
#define INC_KEYIDLE 0.01

class Teclado {
public:
	Teclado();

	void teclar(unsigned char, int, Robo*);
	void definirValor(unsigned char, int);
	Cor obterCor(void);
	bool possuiTeclaPressionada(void);

private:
	std::vector<int> teclas;
	Cor cor;
};

#endif