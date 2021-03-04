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

	glColor3f(Cenario::obterInstancia().robo->obterBase()->obterCor().obterVermelho(), Cenario::obterInstancia().robo->obterBase()->obterCor().obterVerde(), Cenario::obterInstancia().robo->obterBase()->obterCor().obterAzul());
	glBegin(GL_POLYGON);
	for (auto pixel : Cenario::obterInstancia().robo->obterBase()->obterPixels())
		glVertex3f(pixel->obterX(), pixel->obterY(), 0.0);
	glEnd();

	for (auto const& par : Cenario::obterInstancia().robo->obterBracos()) {
		auto braco = par.second;
		glColor3f(braco->obterCor().obterVermelho(), braco->obterCor().obterVerde(), braco->obterCor().obterAzul());
		glBegin(GL_POLYGON);
		for (auto pixel : braco->obterPixels())
			glVertex3f(pixel->obterX(), pixel->obterY(), 0.0);
		glEnd();
	}

	for (auto& roda : Cenario::obterInstancia().robo->obterRodas()) {
		glColor3f(roda->obterPixel().obterCor().obterVermelho(), roda->obterPixel().obterCor().obterVerde(), roda->obterPixel().obterCor().obterAzul());
		glTranslatef(roda->obterPixel().obterX(), roda->obterPixel().obterY(), 0.0f);
		glRotatef(-roda->obterAngulo(), 0.0f, 0.0f, 1.0f);
		glPointSize(3.0f);
		glBegin(GL_POINTS);
		for (float anguloRaio = 0.0f; anguloRaio <= (2.0f * M_PI); anguloRaio += 0.35) {
			float x = roda->obterRaio() * sin(anguloRaio);
			float y = roda->obterRaio() * cos(anguloRaio);
			glVertex3f(x, y, 0.0f);
		}
		glEnd();
		glRotatef(roda->obterAngulo(), 0.0f, 0.0f, 1.0f);
		glTranslatef(-roda->obterPixel().obterX(), -roda->obterPixel().obterY(), 0.0f);
	}

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
	teclado = new Teclado();
}

Cenario::~Cenario() {
	delete robo;
	delete teclado;
}

void
Cenario::inicializar(const int larguraJanela, const int alturaJanela, const int larguraCenario, const int alturaCenario) {
	this->larguraJanela = larguraJanela;
	this->alturaJanela = alturaJanela;
	this->larguraCenario = larguraCenario;
	this->alturaCenario = alturaCenario;
	robo = new Robo(larguraCenario, alturaCenario);

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