#include "Robo.h"

#include <GL/gl.h>
#include <cmath>

Robo::Robo(int larguraJanela, int alturaJanela) : larguraJanela(larguraJanela), alturaJanela(alturaJanela), projetil(nullptr) {
	int deslocamentoVerticalRodas, deslocamentoVerticalRobo;

	deslocamentoVerticalRodas = deslocamentoVerticalRobo = (alturaJanela / 2) * 0.7f * -1;

	construirBase(100.0f, 40.0f, &deslocamentoVerticalRobo);
	bracos.insert(std::pair<Braco, Retangulo*>(Braco::BASE, construirBraco(10.0f, 80.0f, &deslocamentoVerticalRobo, new Cor(0.0f, 0.0f, 255.0f))));
	bracos.insert(std::pair<Braco, Retangulo*>(Braco::MEDIO, construirBraco(10.0f, 80.0f, &deslocamentoVerticalRobo, new Cor(255.0f, 255.0f, 0.0f))));
	bracos.insert(std::pair<Braco, Retangulo*>(Braco::PONTA, construirBraco(10.0f, 80.0f, &deslocamentoVerticalRobo, new Cor(0.0f, 255.0f, 0.0f))));
	rodas.push_back(construirRoda(30.0f, 0.35f, -base->obterLargura() / 2, deslocamentoVerticalRodas, new Cor(255.0f, 255.0f, 255.0f)));
	rodas.push_back(construirRoda(30.0f, 0.35f, base->obterLargura() / 2, deslocamentoVerticalRodas, new Cor(255.0f, 255.0f, 255.0f)));
}

Robo::~Robo() {
	delete base;
	for (auto roda : rodas)
		delete roda;
	for (auto const par : bracos) {
		auto braco = par.second;
		delete braco;
	}
	if (projetil)
		delete projetil;
}

void
Robo::desenhar(std::map<Braco, Retangulo*> bracos, Braco braco) {
	glLoadIdentity();
	glPushMatrix();
	for (auto const& par : bracos) {
		glColor3f(par.second->obterCor().obterVermelho(), par.second->obterCor().obterVerde(), par.second->obterCor().obterAzul());
		glTranslatef(par.second->obterDeslocamentoHorizontal(), par.second->obterDeslocamentoVertical(), 0.0f);
		glRotatef(-par.second->obterAngulo(), 0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		for (auto pixel : par.second->obterPixels())
			glVertex3f(pixel->obterX(), pixel->obterY(), 0.0f);
		glEnd();
		glTranslatef(-par.second->obterDeslocamentoHorizontal(), -par.second->obterDeslocamentoVertical(), 0.0f);
	}
	glPopMatrix();
}

void
Robo::desenhar(void) {
	base->desenhar();
	for (auto& roda : rodas)
		roda->desenhar();
	desenhar(bracos, Braco::BASE);
	if (projetil)
		projetil->desenhar();
}

void
Robo::mover(float x, float y) {
	base->mover(x, y);
	for (auto const& par : bracos) {
		auto braco = par.second;
		braco->mover(x, y);
	}
	for (auto& roda : rodas) {
		roda->mover(x, y);
		roda->rotacionar(x);
	}
}

void
Robo::mover(Braco braco, int angulo) {
	bracos[braco]->rotacionar(angulo);
}

Retangulo*
Robo::obterBase(void) {
	return (base);
}

std::vector<Circunferencia*>
Robo::obterRodas(void) {
	return (rodas);
}

std::map<Braco, Retangulo*>
Robo::obterBracos(void) {
	return (bracos);
}

void
Robo::disparar(Alvo* alvo, Cenario* cenario) {
	if (!projetil || (projetil && projetil->obterConsumidores().empty())) {
		delete projetil;

		std::vector<Retangulo*> _bracos;
		for (auto & braco : bracos)
			_bracos.push_back(braco.second);

		projetil = new Projetil(5.0f, new Pixel(0.0f, 0.0f, Cor(255.0f, 255.0f, 255.0f)), 0.1f, GL_TRIANGLE_FAN, 1.0f, _bracos);
		projetil->adicionar(alvo);
		projetil->adicionar(cenario);
	}
}

void
Robo::construirBase(float largura, float altura, int* deslocamentoVerticalRobo) {
	base = new Retangulo(Pixel(0.0f, 0.0f), largura, altura, Cor(255.0f, 0.0f, 0.0f));
	base->mover(0.0f, *deslocamentoVerticalRobo);
	*deslocamentoVerticalRobo = *deslocamentoVerticalRobo + altura;
}

Retangulo*
Robo::construirBraco(float largura, float altura, int* deslocamentoVerticalRobo, Cor* cor) {
	Retangulo* braco = new Retangulo(Pixel(0.0f, 0.0f), largura, altura, *cor);
	braco->mover(0.0f, *deslocamentoVerticalRobo);
	*deslocamentoVerticalRobo = *deslocamentoVerticalRobo + altura;

	return (braco);
}

Circunferencia*
Robo::construirRoda(float raio, float intervaloAngular, int deslocamentoHorizontal, int deslocamentoVertical, Cor* cor) {
	Circunferencia* roda = new Circunferencia(raio, new Pixel(0.0f, 0.0f, *cor), intervaloAngular, GL_POINTS, 3.0f);
	roda->mover(deslocamentoHorizontal, deslocamentoVertical);
	
	return (roda);
}