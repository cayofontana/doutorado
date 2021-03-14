#ifndef TECLADO_H
#define TECLADO_H

#include <vector>

#include "../modelo/primitivas/Cor.h"

class Cenario;

class Teclado {
public:
	Teclado();
	~Teclado();

	void teclar(unsigned char, int, Cenario*);
	void definirValor(unsigned char, int);
	void atualizar(Cenario*);
	Cor obterCor(void);
	bool possuiTeclaPressionada(void);

private:
	std::vector<int> teclas;
	Cor cor;
};

#endif