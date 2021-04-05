#include "Jogador.h"

#include <cmath>
#include <iostream>
using namespace std;

Jogador::Jogador(Cenario& cenario, int xAbsoluto, int yAbsoluto, int raioCabeca, Cor* cor) : Circunferencia(0, Vetor2(xAbsoluto - cenario.obterLargura() / 2, cenario.obterAltura() / 2 - yAbsoluto), nullptr, 0.0f, 0.0f, GL_POINTS) {
	cabeca = new Circunferencia(raioCabeca, cor, 0.1f, 1.0f, GL_TRIANGLE_FAN);

	nariz = new Circunferencia(raioCabeca * 0.2f, Vetor2(cabeca->obterRaio() + raioCabeca * 0.2f * 0.7f, cabeca->obterRaio() + raioCabeca * 0.2f * 0.7f), cor, 0.1f, 1.0f, GL_TRIANGLE_FAN);

	membrosDireito.insert(pair<Membro, Retangulo*>(Membro::BRACO, new Retangulo(100.0f, 20.0f, Vetor2(cabeca->obterRaio(), 0.0f), new Cor(0.6f, 0.6f, 0.0f))));
	membrosDireito.insert(pair<Membro, Retangulo*>(Membro::ANTEBRACO, new Retangulo(100.0f, 20.0f, Vetor2(membrosDireito[Membro::BRACO]->obterLargura() * 0.5f, 0.0f), new Cor(0.6f, 0.6f, 0.0f))));

	membrosEsquerdo.insert(pair<Membro, Retangulo*>(Membro::BRACO, new Retangulo(100.0f, 20.0f, Vetor2(cabeca->obterRaio(), 0.0f), new Cor(0.6f, 0.6f, 0.0f))));
	membrosEsquerdo.insert(pair<Membro, Retangulo*>(Membro::ANTEBRACO, new Retangulo(100.0f, 20.0f, Vetor2(membrosEsquerdo[Membro::BRACO]->obterLargura() * 0.5f, 0.0f), new Cor(0.6f, 0.6f, 0.0f))));

	luvaDireita = new Circunferencia(raioCabeca * 0.4f, Vetor2(-membrosDireito[Membro::ANTEBRACO]->obterLargura() * 0.5f, 0.0f), new Cor(cabeca->obterCor().obterVermelho() > 0.0f ? 0.0f : 1.0f, cabeca->obterCor().obterVerde() > 0.0f ? 0.0f : 1.0f, cabeca->obterCor().obterAzul() > 0.0f ? 0.0f : 1.0f), 0.1f, 1.0f, GL_TRIANGLE_FAN);
	luvaEsquerda = new Circunferencia(raioCabeca * 0.4f, Vetor2(membrosEsquerdo[Membro::ANTEBRACO]->obterLargura() * 0.5f, 0.0f), new Cor(cabeca->obterCor().obterVermelho() > 0.0f ? 0.0f : 1.0f, cabeca->obterCor().obterVerde() > 0.0f ? 0.0f : 1.0f, cabeca->obterCor().obterAzul() > 0.0f ? 0.0f : 1.0f), 0.1f, 1.0f, GL_TRIANGLE_FAN);
}

Jogador::~Jogador() {
	delete cabeca;
	delete nariz;
	for (auto par : membrosEsquerdo)
		delete par.second;
	for (auto par : membrosDireito)
		delete par.second;
	delete luvaEsquerda;
	delete luvaDireita;
}

void
Jogador::definirOponente(Jogador* oponente) {
	this->oponente = oponente;
}

void
Jogador::encarar(Jogador& jogador) {
	rotacionar(obterAngulo(jogador.obterPose()));
}

void
Jogador::socar(Cenario& cenario, bool socou, int x, int y) {
	Vetor2 poseSoco(x - cenario.obterLargura() / 2, (y - cenario.obterAltura() / 2) * -1);
	float anguloSoco = obterAngulo(poseSoco);

	// cout << "(" << poseSoco.obterX() << ", " << poseSoco.obterY() << ")" << endl;
	// cout << "anguloSoco: " << anguloSoco << endl;
	// cout << "obterAngulo(): " << obterAngulo() << endl;
	
	// if (socou) {
	// 	socouEsquerda = !socou;
	// 	socouDireita = !socou;
	// 	if (anguloSoco < obterAngulo()) {
	// 		socouDireita = socou;
	// 		cout << "Socou com a direita!" << endl;
	// 	}
	// 	else {
	// 		socouEsquerda = socou;
	// 		cout << "Socou com a esquerda!" << endl;
	// 	}
	// }
	// else {
	// 	socouEsquerda = socou;
	// 	socouDireita = socou;
	// }
}

void
Jogador::desenhar(void) {
	glLoadIdentity();
	glPushMatrix();
		glTranslatef(obterPose().obterX(), obterPose().obterY(), 0.0f);
		glRotatef(obterAngulo(), 0.0f, 0.0f, 1.0f);

		glPushMatrix();
			glTranslatef(0.0f, nariz->obterPose().obterY(), 0.0f);
			nariz->desenhar();
		glPopMatrix();

		glPushMatrix();
			Retangulo* bracoDireito = membrosDireito[Membro::BRACO];
			glTranslatef(bracoDireito->obterPose().obterX(), 0.0f, 0.0f);
			glRotatef(socouDireita ? 65.0f : -45.0f, 0.0f, 0.0f, 1.0f);
			glTranslatef(bracoDireito->obterPose().obterX() * 0.8f, 0.0f, 0.0f);
			bracoDireito->desenhar();			

			glPushMatrix();
				Retangulo* anteBracoDireito = membrosDireito[Membro::ANTEBRACO];
				glTranslatef(anteBracoDireito->obterPose().obterX(), 0.0f, 0.0f);
				glRotatef(socouDireita ? -125.0f : -45.0f, 0.0f, 0.0f, 1.0f);
				glTranslatef(-anteBracoDireito->obterPose().obterX(), -anteBracoDireito->obterAltura() * 0.4f, 0.0f);
				anteBracoDireito->desenhar();

				glPushMatrix();
					glTranslatef(luvaDireita->obterPose().obterX(), 0.0f, 0.0f);
					luvaDireita->desenhar();
				glPopMatrix();
				
			glPopMatrix();
			
		glPopMatrix();

		glPushMatrix();
			Retangulo* bracoEsquerdo = membrosEsquerdo[Membro::BRACO];
			glTranslatef(-bracoEsquerdo->obterPose().obterX(), 0.0f, 0.0f);
			glRotatef(socouEsquerda ? -65.0f : 45.0f, 0.0f, 0.0f, 1.0f);
			glTranslatef(-bracoEsquerdo->obterPose().obterX() * 0.8f, 0.0f, 0.0f);
			bracoEsquerdo->desenhar();

			glPushMatrix();
				Retangulo* anteBracoEsquerdo = membrosDireito[Membro::ANTEBRACO];
				glTranslatef(-anteBracoEsquerdo->obterPose().obterX(), 0.0f, 0.0f);
				glRotatef(socouEsquerda ? 125.0f : 45.0f, 0.0f, 0.0f, 1.0f);
				glTranslatef(anteBracoEsquerdo->obterPose().obterX(), -anteBracoEsquerdo->obterAltura() * 0.4f, 0.0f);
				anteBracoEsquerdo->desenhar();

				glPushMatrix();
					glTranslatef(luvaEsquerda->obterPose().obterX(), 0.0f, 0.0f);
					luvaEsquerda->desenhar();
				glPopMatrix();

			glPopMatrix();
			
		glPopMatrix();

		cabeca->desenhar();
	glPopMatrix();
}