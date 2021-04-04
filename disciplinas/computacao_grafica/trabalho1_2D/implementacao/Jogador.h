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
	void socar(Cenario&, bool, int, int);

	void desenhar(void) override;

private:
	Circunferencia* cabeca;
	Circunferencia* nariz;
	map<Membro, Retangulo*> membrosEsquerdo;
	map<Membro, Retangulo*> membrosDireito;
	Circunferencia* luvaEsquerda;
	Circunferencia* luvaDireita;
	Jogador* oponente;
	bool socouEsquerda;
	bool socouDireita;
};

#endif