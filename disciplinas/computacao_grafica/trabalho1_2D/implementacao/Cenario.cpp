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

    // cenario.desenharPlacar();

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
Cenario::moverMouse(int x, int y) {
	cenario.mouse->mover(x, y, cenario);
}

void
Cenario::ociar(void) {
	if (!cenario.jogoEncerrado) {
		if (cenario.teclado->possuiTeclaPressionada())
			cenario.teclado->atualizar(&cenario);
		cenario.atualizarOponente();
		// cenario.atualizarPontuacao();
	}

	glutPostRedisplay();
}

Cenario::Cenario() : largura(0), altura(0), cor(nullptr), pontosJogador(0), pontosOponente(0), bloqueioJogadorDireita(false), bloqueioJogadorEsquerda(false), bloqueioOponenteDireita(false), bloqueioOponenteEsquerda(false), jogoEncerrado(false), contadorIA(0) {
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
    vertices.clear();
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

    reiniciarJogo();
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


bool
Cenario::jogadorDentroArena(Jogador* jogador) {
	float x = jogador->obterPose().obterX();
	float y = jogador->obterPose().obterY();
	float r = jogador->obterCabeca()->obterRaio();
	
	return (x - r >= -largura / 2.0f && x + r <=  largura / 2.0f && y - r >= -altura / 2.0f && y + r <=  altura / 2.0f);
}

bool
Cenario::colisaoJogadores(Jogador* jogador, Jogador* oponente) {
	float dx = jogador->obterPose().obterX() - oponente->obterPose().obterX();
	float dy = jogador->obterPose().obterY() - oponente->obterPose().obterY();
	float dist = sqrtf(dx * dx + dy * dy);

	return (dist < (jogador->obterRaioColisao() + oponente->obterCabeca()->obterRaio()));
}

void
Cenario::reiniciarJogo() {
	pontosJogador = 0;
	pontosOponente = 0;
	bloqueioJogadorDireita = false;
	bloqueioJogadorEsquerda = false;
	bloqueioOponenteDireita = false;
	bloqueioOponenteEsquerda = false;
	jogoEncerrado = false;
	contadorIA = 0;

	if (jogadores.size() >= 2) {
		jogadores.at(0)->voltarPosicaoInicialDosBracos();
		jogadores.at(1)->voltarPosicaoInicialDosBracos();
		jogadores.at(0)->encarar(*jogadores.at(1));
		jogadores.at(1)->encarar(*jogadores.at(0));
	}
}

void Cenario::atualizarOponente() {
	if (jogoEncerrado)
		return;
	
	Jogador* cpu = jogadores.at(0);
	Jogador* player = jogadores.at(1);

	cpu->encarar(*player);
	contadorIA++;

	float dx = player->obterPose().obterX() - cpu->obterPose().obterX();
	float dy = player->obterPose().obterY() - cpu->obterPose().obterY();
	float dist = sqrtf(dx * dx + dy * dy);

	if (dist > cpu->obterRaioColisao() + player->obterCabeca()->obterRaio() + 30.0f) {
		float mx = 2.0f * -sinf(cpu->obterAngulo() * M_PI / 180.0f);
		float my = 2.0f *  cosf(cpu->obterAngulo() * M_PI / 180.0f);
		cpu->transladar(mx, my);
		if (!jogadorDentroArena(cpu) || colisaoJogadores(cpu, player))
			cpu->transladar(-mx, -my);
		cpu->voltarPosicaoInicialDosBracos();
	}
	else {
		float intensidade = largura * 0.35f + (rand() % 40);
		int fase = (contadorIA / 18) % 4;
		if (fase == 0)
			cpu->socarDireito(*this, intensidade, 0, 0);
		else if (fase == 2)
			cpu->socarEsquerdo(*this, intensidade, 0, 0);
		else
			cpu->voltarPosicaoInicialDosBracos();
	}
}