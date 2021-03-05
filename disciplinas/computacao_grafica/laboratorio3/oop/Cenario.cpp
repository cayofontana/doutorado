#include "Cenario.h"

#include <cmath>

Cenario&
Cenario::obterInstancia(void) {
	static Cenario instance;
	return instance;
}

void
Cenario::exibir(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	Cenario::obterInstancia().robo->desenhar();
	Cenario::obterInstancia().alvo->desenhar();

	glutSwapBuffers();
}

void
Cenario::pressionarTecla(unsigned char tecla, int x, int y) {
	Cenario::obterInstancia().teclado->teclar(tecla, 1, Cenario::obterInstancia().robo, Cenario::obterInstancia().alvo);
}

void
Cenario::liberarTecla(unsigned char tecla, int x, int y) {
	Cenario::obterInstancia().teclado->teclar(tecla, 0, Cenario::obterInstancia().robo, Cenario::obterInstancia().alvo);
}

void
Cenario::ociar(void) {
	glutPostRedisplay();
}

Cenario::Cenario() {
	teclado = new Teclado();
}

Cenario::~Cenario() {
	delete teclado;
	delete robo;
	delete alvo;
}

void
Cenario::inicializar(const int larguraJanela, const int alturaJanela, const int larguraCenario, const int alturaCenario) {
	this->larguraJanela = larguraJanela;
	this->alturaJanela = alturaJanela;
	this->larguraCenario = larguraCenario;
	this->alturaCenario = alturaCenario;
	robo = new Robo(larguraCenario, alturaCenario);
	alvo = new Alvo(larguraCenario, alturaCenario);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-(this->larguraCenario / 2),
		(this->larguraCenario / 2),
		-(this->alturaCenario / 2),
		(this->alturaCenario / 2), 
		-100,
		100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}