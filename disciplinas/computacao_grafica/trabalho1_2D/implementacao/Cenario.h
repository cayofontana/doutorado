#ifndef CENARIO_H
#define CENARIO_H

#include "modelo/primitivas/Vetor2.h"
#include "controle/Teclado.h"
#include "controle/Mouse.h"
#include "Jogador.h"

#include <GL/glut.h>
#include <vector>
#include <cmath>


using namespace std;

class Jogador;

class Cenario {
public:
	~Cenario();

	void configurar(const int largura, const int altura, Cor* cor);
	void inicializar(void);
	int obterLargura(void);
	int obterAltura(void);
	vector<Jogador*> obterJogadores(void);
	void inserir(Jogador*);
	bool jogadorVisivel(Jogador*);
	bool jogadorDentroArena(Jogador*);
	bool colisaoJogadores(Jogador*, Jogador*);
	void atualizarOponente(void);
	void reiniciarJogo(void);

	static Cenario& obterInstancia(void);
	static void exibir(void);
	static void pressionarTecla(unsigned char, int, int);
	static void liberarTecla(unsigned char, int, int);
	static void clicar(int, int, int, int);
	static void moverMouse(int, int);
	static void ociar(void);

private:
	int largura;
	int altura;
	Cor* cor;
	vector<Vetor2*> vertices;
	Teclado* teclado;
	Mouse* mouse;
	vector<Jogador*> jogadores;
	int pontosJogador;
	int pontosOponente;
	bool bloqueioJogadorDireita;
	bool bloqueioJogadorEsquerda;
	bool bloqueioOponenteDireita;
	bool bloqueioOponenteEsquerda;
	bool jogoEncerrado;
	int contadorIA;

	Cenario();
};

#endif