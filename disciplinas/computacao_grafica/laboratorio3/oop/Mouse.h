#ifndef MOUSE_H
#define MOUSE_H

#include <GL/glut.h>
#include <vector>

#include "primitivas/Pixel.h"

class Mouse {
public:
	Mouse();

	void clicar(int, int, int, int, const int, const int);
	void clicarMovendo(int, int, const int, const int, std::vector<Pixel*>);
	bool possuiBotaoEsquerdoPressionado(void);

private:
	bool botaoEsquerdoPressionado;
};

#endif