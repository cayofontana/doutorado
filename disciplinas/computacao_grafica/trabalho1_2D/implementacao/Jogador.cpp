#include "Jogador.h"

#include <cmath>

Jogador::Jogador(Cenario& cenario, int xAbsoluto, int yAbsoluto, int raioCabeca, Cor* cor) : Circunferencia(0, new Vetor2(xAbsoluto - cenario.obterLargura() / 2, cenario.obterAltura() / 2 - yAbsoluto), nullptr, 0.0f, 0.0f, GL_POINTS) {
	cabeca = new Circunferencia(raioCabeca, new Vetor2(obterPose().obterX(), obterPose().obterY()), cor, 0.1f, 1.0f, GL_TRIANGLE_FAN);

	nariz = new Circunferencia(raioCabeca * 0.2f, new Vetor2(0.0f, cabeca->obterRaio() * 1.15f), cor, 0.1f, 1.0f, GL_TRIANGLE_FAN);

	membrosDireito.insert(pair<Membro, Retangulo*>(Membro::BRACO, new Retangulo(100.0f, 20.0f, new Vetor2(cabeca->obterRaio(), 0.0f), -45.0f, new Cor(0.6f, 0.6f, 0.0f))));
	membrosDireito.insert(pair<Membro, Retangulo*>(Membro::ANTEBRACO, new Retangulo(100.0f, 20.0f, new Vetor2(membrosDireito[Membro::BRACO]->obterLargura() * 0.5f, 0.0f), -45.0f, new Cor(0.6f, 0.6f, 0.0f))));

	membrosEsquerdo.insert(pair<Membro, Retangulo*>(Membro::BRACO, new Retangulo(100.0f, 20.0f, new Vetor2(-cabeca->obterRaio(), 0.0f), 45.0f, new Cor(0.6f, 0.6f, 0.0f))));
	membrosEsquerdo.insert(pair<Membro, Retangulo*>(Membro::ANTEBRACO, new Retangulo(100.0f, 20.0f, new Vetor2(-membrosEsquerdo[Membro::BRACO]->obterLargura() * 0.5f, 0.0f), 45.0f, new Cor(0.6f, 0.6f, 0.0f))));

	luvaDireita = new Circunferencia(raioCabeca * 0.4f, new Vetor2(-membrosDireito[Membro::ANTEBRACO]->obterLargura() * 0.5f, 0.0f), new Cor(cabeca->obterCor().obterVermelho() > 0.0f ? 0.0f : 1.0f, cabeca->obterCor().obterVerde() > 0.0f ? 0.0f : 1.0f, cabeca->obterCor().obterAzul() > 0.0f ? 0.0f : 1.0f), 0.1f, 1.0f, GL_TRIANGLE_FAN);
	luvaEsquerda = new Circunferencia(raioCabeca * 0.4f, new Vetor2(membrosEsquerdo[Membro::ANTEBRACO]->obterLargura() * 0.5f, 0.0f), new Cor(cabeca->obterCor().obterVermelho() > 0.0f ? 0.0f : 1.0f, cabeca->obterCor().obterVerde() > 0.0f ? 0.0f : 1.0f, cabeca->obterCor().obterAzul() > 0.0f ? 0.0f : 1.0f), 0.1f, 1.0f, GL_TRIANGLE_FAN);
}

Jogador::~Jogador() {
	delete cabeca;
	delete nariz;
	for (auto par : membrosDireito)
		delete par.second;
	for (auto par : membrosEsquerdo)
		delete par.second;
	delete luvaDireita;
	delete luvaEsquerda;
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
Jogador::socar(Cenario& cenario, float angulo, int x, int y) {
	Vetor2 poseSoco(x - cenario.obterLargura() / 2, (y - cenario.obterAltura() / 2) * -1);
	float anguloSoco = obterAngulo(poseSoco);
	
	if (anguloSoco > obterAngulo()) {
		membrosDireito[Membro::BRACO]->rotacionar(angulo);
		membrosDireito[Membro::ANTEBRACO]->rotacionar(-angulo * 0.65f);
	}
	else {
		membrosEsquerdo[Membro::BRACO]->rotacionar(-angulo);
		membrosEsquerdo[Membro::ANTEBRACO]->rotacionar(angulo * 0.65f);
	}
}

void
Jogador::desenhar(void) {
	glLoadIdentity();
	
	glPushMatrix();
		glTranslatef(obterPose().obterX(), obterPose().obterY(), 0.0f);
		glRotatef(obterAngulo(), 0.0f, 0.0f, 1.0f);

		glPushMatrix();
			glTranslatef(nariz->obterPose().obterX(), nariz->obterPose().obterY(), 0.0f);
			nariz->desenhar();
		glPopMatrix();

		glPushMatrix();
			Retangulo* bracoDireito = membrosDireito[Membro::BRACO];
			glTranslatef(bracoDireito->obterPose().obterX(), bracoDireito->obterPose().obterY(), 0.0f);
			glRotatef(bracoDireito->obterAngulo(), 0.0f, 0.0f, 1.0f);
			glTranslatef(bracoDireito->obterPose().obterX() - bracoDireito->obterAltura(), bracoDireito->obterPose().obterY(), 0.0f);
			bracoDireito->desenhar();			

			glPushMatrix();
				Retangulo* anteBracoDireito = membrosDireito[Membro::ANTEBRACO];
				glTranslatef(anteBracoDireito->obterPose().obterX(), anteBracoDireito->obterPose().obterY(), 0.0f);
				glRotatef(anteBracoDireito->obterAngulo(), 0.0f, 0.0f, 1.0f);
				glTranslatef(-anteBracoDireito->obterPose().obterX(), -anteBracoDireito->obterAltura() * 0.4f, 0.0f);
				anteBracoDireito->desenhar();

				glPushMatrix();
					glTranslatef(luvaDireita->obterPose().obterX(), luvaDireita->obterPose().obterY(), 0.0f);
					luvaDireita->desenhar();
				glPopMatrix();
				
			glPopMatrix();
			
		glPopMatrix();

		glPushMatrix();
			Retangulo* bracoEsquerdo = membrosEsquerdo[Membro::BRACO];
			glTranslatef(bracoEsquerdo->obterPose().obterX(), 0.0f, 0.0f);
			glRotatef(bracoEsquerdo->obterAngulo(), 0.0f, 0.0f, 1.0f);
			glTranslatef(bracoEsquerdo->obterPose().obterX() + bracoEsquerdo->obterAltura(), bracoEsquerdo->obterPose().obterY(), 0.0f);
			bracoEsquerdo->desenhar();

			glPushMatrix();
				Retangulo* anteBracoEsquerdo = membrosEsquerdo[Membro::ANTEBRACO];
				glTranslatef(anteBracoEsquerdo->obterPose().obterX(), anteBracoEsquerdo->obterPose().obterY(), 0.0f);
				glRotatef(anteBracoEsquerdo->obterAngulo(), 0.0f, 0.0f, 1.0f);
				glTranslatef(-anteBracoEsquerdo->obterPose().obterX(), -anteBracoEsquerdo->obterAltura() * 0.4f, 0.0f);
				anteBracoEsquerdo->desenhar();

				glPushMatrix();
					glTranslatef(luvaEsquerda->obterPose().obterX(), luvaDireita->obterPose().obterY(), 0.0f);
					luvaEsquerda->desenhar();
				glPopMatrix();

			glPopMatrix();
			
		glPopMatrix();

		cabeca->desenhar();
	glPopMatrix();
}