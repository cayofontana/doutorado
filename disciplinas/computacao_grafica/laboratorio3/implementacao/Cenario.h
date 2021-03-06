#ifndef CENARIO_H
#define CENARIO_H

#include <GL/glut.h>
#include <vector>

#include "controle/Mouse.h"
#include "controle/Teclado.h"
#include "Robo.h"
#include "Alvo.h"
#include "IConsumidor.h"

class Robo;
class Alvo;

class Cenario : public IConsumidor {
public:
	~Cenario();

	void inicializar(const int, const int, const int, const int);
	void atualizar(void);
	Robo* obterRobo(void);
	Alvo* obterAlvo(void);

	bool atualizou(Projetil*) override;

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
	Alvo* alvo;
	std::vector<Pixel*> pixelsCenario;

	Cenario();
	bool objetoVisivel(FormaGeometrica2D* formaGeometrica2D);
};

#endif