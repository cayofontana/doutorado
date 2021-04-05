#include "Mouse.h"
#include "../Cenario.h"

#include <GL/glut.h>
#include <iostream>

Mouse::Mouse() {
}

void
Mouse::clicar(int botao, int estado, int x, int y, Cenario& cenario) {
	if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
		cenario.obterJogadores().at(1)->socar(cenario, 100.0f, x, y);
	else
		cenario.obterJogadores().at(1)->socar(cenario, -100.0f, x, y);
}