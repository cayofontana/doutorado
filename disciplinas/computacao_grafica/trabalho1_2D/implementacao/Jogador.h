#ifndef JOGADOR_H
#define JOGADOR_H

#include "modelo/primitivas/Cor.h"
#include "modelo/Circunferencia.h"
#include "modelo/Retangulo.h"

#include <map>
using namespace std;

enum Membro { BRACO = 1, ANTEBRACO };

class Jogador {
public:
	Jogador(int, int, int, Cor*);

private:
	Circunferencia* corpo;
	Circunferencia* cabeca;
	map<Membro, Retangulo*> membrosEsquerdo;
	map<Membro, Retangulo*> membrosDireito;
	Circunferencia* luvaEsquerda;
	Circunferencia* luvaDireita;
};

#endif