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
	Cenario::obterInstancia().teclado->teclar(tecla, 1, &Cenario::obterInstancia());
}

void
Cenario::liberarTecla(unsigned char tecla, int x, int y) {
	Cenario::obterInstancia().teclado->teclar(tecla, 0, &Cenario::obterInstancia());
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
	for (auto pixelCenario : pixelsCenario)
		delete pixelCenario;
}

void
Cenario::inicializar(const int larguraJanela, const int alturaJanela, const int larguraCenario, const int alturaCenario) {
	this->larguraJanela = larguraJanela;
	this->alturaJanela = alturaJanela;
	this->larguraCenario = larguraCenario;
	this->alturaCenario = alturaCenario;
	robo = new Robo(larguraCenario, alturaCenario);
	alvo = new Alvo(larguraCenario, alturaCenario);
	pixelsCenario.push_back(new Pixel(-(this->larguraCenario / 2), -(this->alturaCenario / 2)));
	pixelsCenario.push_back(new Pixel(-(this->larguraCenario / 2), (this->alturaCenario / 2)));
	pixelsCenario.push_back(new Pixel((this->larguraCenario / 2), (this->alturaCenario / 2)));
	pixelsCenario.push_back(new Pixel((this->larguraCenario / 2), -(this->alturaCenario / 2)));

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

Robo*
Cenario::obterRobo(void) {
	return (robo);
}

Alvo*
Cenario::obterAlvo(void) {
	return (alvo);
}

bool
Cenario::atualizou(Projetil* projetil) {
	if (projetil && !objetoVisivel(projetil)) {
		return (true);
	}
	return (false);
}

bool
Cenario::objetoVisivel(FormaGeometrica2D* formaGeometrica2D) {
	std::vector<Pixel*> pixelsObjeto = formaGeometrica2D->obterPixels();

	for (auto pixelObjeto : pixelsObjeto)
		for (auto pixelIncial = pixelsCenario.begin(), pixelAtual = std::next(pixelIncial); pixelAtual != pixelsCenario.end(); ++pixelAtual)
			if ((pixelObjeto->obterX() <= std::max((*pixelIncial)->obterX(), (*pixelAtual)->obterX())) && 
				(pixelObjeto->obterX() >= std::min((*pixelIncial)->obterX(), (*pixelAtual)->obterX())) &&
				(pixelObjeto->obterY() <= std::max((*pixelIncial)->obterY(), (*pixelAtual)->obterY())) &&
				(pixelObjeto->obterY() >= std::min((*pixelIncial)->obterY(), (*pixelAtual)->obterY())))
				return (true);
	return (false);
}