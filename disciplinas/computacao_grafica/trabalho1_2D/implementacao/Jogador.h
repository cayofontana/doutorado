#ifndef JOGADOR_H
#define JOGADOR_H

#include "modelo/primitivas/Cor.h"
#include "modelo/Circunferencia.h"
#include "modelo/Retangulo.h"
#include "Cenario.h"

#include <map>
using namespace std;

enum Membro { BRACO = 1, ANTEBRACO };

class Jogador {
public:
	Jogador(Cenario&, int, int, int, Cor*);
	~Jogador();

	void desenhar(void);

private:
	Circunferencia* cabeca;
	Circunferencia* nariz;
	map<Membro, Retangulo*> membrosEsquerdo;
	map<Membro, Retangulo*> membrosDireito;
	Circunferencia* luvaEsquerda;
	Circunferencia* luvaDireita;
};

#endif