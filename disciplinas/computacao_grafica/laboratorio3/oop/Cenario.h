#ifndef CENARIO_H
#define CENARIO_H

#include <GL/glut.h>
#include <vector>

#include "Mouse.h"
#include "Teclado.h"
#include "Robo.h"

class Cenario {
public:
	~Cenario();

	void inicializar(const int, const int, const int, const int);
	void atualizar(void);

	static Cenario& obterInstancia(void);
	static void exibir(void);
	static void pressionarTecla(unsigned char, int, int);
	static void liberarTecla(unsigned char, int, int);
	static void ociar(void);

private:
	int larguraJanela;
	int alturaJanela;
	int larguraCenario;
	int alturaCenario;
	Robo* robo;
	Teclado* teclado;

	Cenario();
};

#endif