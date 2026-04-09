#ifndef JOGADOR_H
#define JOGADOR_H

#include "modelo/primitivas/Cor.h"
#include "modelo/Circunferencia.h"
#include "modelo/Retangulo.h"
#include "Cenario.h"

#include <map>
using namespace std;

enum Membro { BRACO = 1, ANTEBRACO };

class Jogador : public Circunferencia {
public:
	Jogador(Cenario&, int, int, int, Cor*);
	~Jogador();

	void definirOponente(Jogador*);
	void encarar(Jogador&);
	void socar(Cenario&, float, int, int);
	void voltarPosicaoInicialDosBracos(void);
	void alterarCirculoColisao(void);
	Circunferencia* obterCabeca(void);
	float obterRaioColisao(void);
	void socarDireito(Cenario&, float, int, int);
	void socarEsquerdo(Cenario&, float, int, int);

	void desenhar(void) override;

private:
	Circunferencia* cabeca;
	Circunferencia* nariz;
	map<Membro, Retangulo*> membrosEsquerdo;
	map<Membro, Retangulo*> membrosDireito;
	Circunferencia* luvaEsquerda;
	Circunferencia* luvaDireita;
	Circunferencia* circuloColisao;
	Jogador* oponente;
	bool exibeCirculoColisao;
};

#endif