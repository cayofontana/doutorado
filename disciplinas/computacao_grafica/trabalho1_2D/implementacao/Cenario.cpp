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
	cenario.mouse->clicar(botao, estado, x, y, cenario);
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
	for (auto vertice : vertices)
		delete vertice;
	for (auto jogador : jogadores)
		delete jogador;
}

void
Cenario::configurar(const int largura, const int altura, Cor* cor) {
	this->largura = largura;
	this->altura = altura;
	this->cor = cor;
	vertices.push_back(new Vetor2(-(this->largura / 2), -(this->altura / 2)));
	vertices.push_back(new Vetor2(-(this->largura / 2), (this->altura / 2)));
	vertices.push_back(new Vetor2((this->largura / 2), (this->altura / 2)));
	vertices.push_back(new Vetor2((this->largura / 2), -(this->altura / 2)));
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

	jogadores.at(0)->definirOponente(jogadores.at(1));
	jogadores.at(1)->definirOponente(jogadores.at(0));

	jogadores.at(0)->encarar(*jogadores.at(1));
	jogadores.at(1)->encarar(*jogadores.at(0));	
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

bool
Cenario::jogadorVisivel(Jogador* jogador) {
	auto verticeObjeto = jogador->obterPose();
	for (auto verticeInicial = vertices.begin(), verticeAtual = next(verticeInicial); verticeAtual != vertices.end(); ++verticeAtual)
		if ((verticeObjeto.obterX() <= max((*verticeInicial)->obterX(), (*verticeAtual)->obterX())) && 
			(verticeObjeto.obterX() >= min((*verticeInicial)->obterX(), (*verticeAtual)->obterX())) &&
			(verticeObjeto.obterY() <= max((*verticeInicial)->obterY(), (*verticeAtual)->obterY())) &&
			(verticeObjeto.obterY() >= min((*verticeInicial)->obterY(), (*verticeAtual)->obterY())))
			return (true);
	return (false);
}