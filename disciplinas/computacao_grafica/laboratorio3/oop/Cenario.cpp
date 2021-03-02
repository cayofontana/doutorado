#include "Cenario.h"

#include <iostream>
using namespace std;

Cenario&
Cenario::obterInstancia(void) {
	static Cenario instance;
	return instance;
}

void
Cenario::exibir(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(Cenario::obterInstancia().robo->obterBase()->obterCor().obterVermelho(), Cenario::obterInstancia().robo->obterBase()->obterCor().obterVerde(), Cenario::obterInstancia().robo->obterBase()->obterCor().obterAzul());
	glBegin(GL_POLYGON);
	for (auto pixel : Cenario::obterInstancia().robo->obterBase()->obterPixels())
		glVertex3f(pixel->obterX(), pixel->obterY(), 0.0);
	glEnd();

	glutSwapBuffers();
}

void
Cenario::pressionarTecla(unsigned char tecla, int x, int y) {
	Cenario::obterInstancia().teclado->teclar(tecla, 1, Cenario::obterInstancia().robo);
}

void
Cenario::liberarTecla(unsigned char tecla, int x, int y) {
	Cenario::obterInstancia().teclado->teclar(tecla, 0, Cenario::obterInstancia().robo);
}

void
Cenario::ociar(void) {
	glutPostRedisplay();
}

Cenario::Cenario() {
}

Cenario::~Cenario() {
	delete robo;
}

void
Cenario::inicializar(const int larguraJanela, const int alturaJanela, const int larguraCenario, const int alturaCenario) {
	this->larguraJanela = larguraJanela;
	this->alturaJanela = alturaJanela;
	this->larguraCenario = larguraCenario;
	this->alturaCenario = alturaCenario;
	robo = new Robo(larguraJanela, alturaJanela);
	teclado = new Teclado();

	// selecionar cor de fundo (preto)
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// inicializar sistema de visualizacao 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	// // The color the windows will redraw. Its done to erase the previous frame.
	// glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).

	// glMatrixMode(GL_PROJECTION); // Select the projection matrix    
	// glOrtho(-(this->larguraCenario/2),     // X coordinate of left edge             
	// 	(this->larguraCenario/2),     // X coordinate of right edge            
	// 	-(this->alturaCenario/2),     // Y coordinate of bottom edge             
	// 	(this->alturaCenario/2),     // Y coordinate of top edge             
	// 	-1,     // Z coordinate of the “near” plane            
	// 	1);    // Z coordinate of the “far” plane
	// glMatrixMode(GL_MODELVIEW); // Select the projection matrix    
	// glLoadIdentity();
}