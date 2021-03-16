#include "Cenario.h"

static Cenario& cenario = Cenario::obterInstancia();

Cenario&
Cenario::obterInstancia(void) {
	static Cenario instance;
	return instance;
}

void
Cenario::exibir(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(cenario.cor->obterVermelho(), cenario.cor->obterVerde(), cenario.cor->obterAzul(), 1.0f);

	for (auto& jogador : cenario.jogadores)
		jogador->desenhar();

	glutSwapBuffers();
}

void
Cenario::pressionarTecla(unsigned char tecla, int x, int y) {
	cenario.teclado->teclar(tecla, 1, &cenario);
}

void
Cenario::liberarTecla(unsigned char tecla, int x, int y) {
	cenario.teclado->teclar(tecla, 0, &cenario);
}

void
Cenario::clicar(int botao, int estado, int x, int y) {
	cenario.mouse->clicar(botao, estado, x, y, &cenario);
}

void
Cenario::ociar(void) {
	if (cenario.teclado->possuiTeclaPressionada())
		cenario.teclado->atualizar(&cenario);

	glutPostRedisplay();
}

Cenario::Cenario() {
	teclado = new Teclado();
	mouse = new Mouse();
}

Cenario::~Cenario() {
	delete cor;
	delete teclado;
	delete mouse;
	for (auto pixel : pixels)
		delete pixel;
}

void
Cenario::configurar(const int largura, const int altura, Cor* cor) {
	this->largura = largura;
	this->altura = altura;
	this->cor = cor;
	pixels.push_back(new Pixel(-(this->largura / 2), -(this->altura / 2)));
	pixels.push_back(new Pixel(-(this->largura / 2), (this->altura / 2)));
	pixels.push_back(new Pixel((this->largura / 2), (this->altura / 2)));
	pixels.push_back(new Pixel((this->largura / 2), -(this->altura / 2)));
}

void
Cenario::inicializar(void) {
	glMatrixMode(GL_PROJECTION);
	glOrtho(-(this->largura / 2),
		(this->largura / 2),
		-(this->altura / 2),
		(this->altura / 2), 
		-100,
		100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int
Cenario::obterLargura(void) {
	return (largura);
}

int
Cenario::obterAltura(void) {
	return (altura);
}

vector<Jogador*>
Cenario::obterJogadores(void) {
	return (jogadores);
}

void
Cenario::inserir(Jogador* jogador) {
	jogadores.push_back(jogador);
}