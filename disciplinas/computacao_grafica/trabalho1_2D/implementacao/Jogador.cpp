#include "Jogador.h"

#include <cmath>


Jogador::Jogador(Cenario& cenario, int xAbsoluto, int yAbsoluto, int raioCabeca, Cor* cor) : Circunferencia(0, new Vetor2(xAbsoluto - cenario.obterLargura() / 2, cenario.obterAltura() / 2 - yAbsoluto), nullptr, 0.0f, 0.0f, GL_POINTS, true, true, false) {
	cabeca = new Circunferencia(raioCabeca, new Vetor2(obterPose().obterX(), obterPose().obterY()), cor, 0.1f, 1.0f, GL_TRIANGLE_FAN, true, true, false);

	nariz = new Circunferencia(raioCabeca * 0.2f, new Vetor2(0.0f, cabeca->obterRaio() * 1.15f), cor, 0.1f, 1.0f, GL_TRIANGLE_FAN, true, true, false);

	membrosDireito.insert(pair<Membro, Retangulo*>(Membro::BRACO, new Retangulo(raioCabeca * 2.0f, raioCabeca * .4f, new Vetor2(cabeca->obterRaio(), 0.0f), -45.0f, new Cor(0.6f, 0.6f, 0.0f))));
	membrosDireito.insert(pair<Membro, Retangulo*>(Membro::ANTEBRACO, new Retangulo(raioCabeca * 2.0f, raioCabeca * .4f, new Vetor2(membrosDireito[Membro::BRACO]->obterLargura() * 0.5f, 0.0f), -45.0f, new Cor(0.6f, 0.6f, 0.0f))));

	membrosEsquerdo.insert(pair<Membro, Retangulo*>(Membro::BRACO, new Retangulo(raioCabeca * 2.0f, raioCabeca * .4f, new Vetor2(-cabeca->obterRaio(), 0.0f), 45.0f, new Cor(0.6f, 0.6f, 0.0f))));
	membrosEsquerdo.insert(pair<Membro, Retangulo*>(Membro::ANTEBRACO, new Retangulo(raioCabeca * 2.0f, raioCabeca * .4f, new Vetor2(-membrosEsquerdo[Membro::BRACO]->obterLargura() * 0.5f, 0.0f), 45.0f, new Cor(0.6f, 0.6f, 0.0f))));

	luvaDireita = new Circunferencia(raioCabeca * 0.4f, new Vetor2(-membrosDireito[Membro::ANTEBRACO]->obterLargura() * 0.5f, 0.0f), new Cor(cabeca->obterCor().obterVermelho() > 0.0f ? 0.0f : 1.0f, cabeca->obterCor().obterVerde() > 0.0f ? 0.0f : 1.0f, cabeca->obterCor().obterAzul() > 0.0f ? 0.0f : 1.0f), 0.1f, 1.0f, GL_TRIANGLE_FAN, true, true, false);
	luvaEsquerda = new Circunferencia(raioCabeca * 0.4f, new Vetor2(membrosEsquerdo[Membro::ANTEBRACO]->obterLargura() * 0.5f, 0.0f), new Cor(cabeca->obterCor().obterVermelho() > 0.0f ? 0.0f : 1.0f, cabeca->obterCor().obterVerde() > 0.0f ? 0.0f : 1.0f, cabeca->obterCor().obterAzul() > 0.0f ? 0.0f : 1.0f), 0.1f, 1.0f, GL_TRIANGLE_FAN, true, true, false);

	circuloColisao = new Circunferencia(raioCabeca * 2.8f, new Vetor2(obterPose().obterX(), obterPose().obterY()), cor, 0.1f, 1.0f, GL_TRIANGLE_FAN, false, false, true);
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
	delete circuloColisao;
}

Circunferencia*
Jogador::obterCabeca(void) {
	return (cabeca);
}

float
Jogador::obterRaioColisao(void) {
	return (cabeca->obterRaio() * 2.2f);
}

void
Jogador::definirOponente(Jogador* oponente) {
	this->oponente = oponente;
}

void
Jogador::alterarCirculoColisao(void) {
	this->exibeCirculoColisao = !exibeCirculoColisao;
}

void
Jogador::encarar(Jogador& jogador) {
	rotacionar((int)(obterAngulo(jogador.obterPose()) - obterAngulo()));
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
Jogador::voltarPosicaoInicialDosBracos(void) {
	membrosDireito[Membro::BRACO]->rotacionar(-45 - (int)membrosDireito[Membro::BRACO]->obterAngulo());
	membrosDireito[Membro::ANTEBRACO]->rotacionar(-45 - (int)membrosDireito[Membro::ANTEBRACO]->obterAngulo());
	membrosEsquerdo[Membro::BRACO]->rotacionar(45 - (int)membrosEsquerdo[Membro::BRACO]->obterAngulo());
	membrosEsquerdo[Membro::ANTEBRACO]->rotacionar(45 - (int)membrosEsquerdo[Membro::ANTEBRACO]->obterAngulo());
}

void Jogador::socarDireito(Cenario& cenario, float intensidade, int x, int y) {
	float metadeJanela = cenario.obterLargura() / 2.0f;
	float t = std::min(intensidade / metadeJanela, 1.0f);
	int alvoBraco = (int)lround(-45.0f + 100.0f * t);
	int alvoAnte = (int)lround(-45.0f - 65.0f * t);

	membrosEsquerdo[Membro::BRACO]->rotacionar(45 - (int)membrosEsquerdo[Membro::BRACO]->obterAngulo());
	membrosEsquerdo[Membro::ANTEBRACO]->rotacionar(45 - (int)membrosEsquerdo[Membro::ANTEBRACO]->obterAngulo());
	membrosDireito[Membro::BRACO]->rotacionar(alvoBraco - (int)membrosDireito[Membro::BRACO]->obterAngulo());
	membrosDireito[Membro::ANTEBRACO]->rotacionar(alvoAnte - (int)membrosDireito[Membro::ANTEBRACO]->obterAngulo());
}

void Jogador::socarEsquerdo(Cenario& cenario, float intensidade, int x, int y) {
	float metadeJanela = cenario.obterLargura() / 2.0f;
	float t = std::min(intensidade / metadeJanela, 1.0f);
	int alvoBraco = (int)lround(45.0f - 100.0f * t);
	int alvoAnte = (int)lround(45.0f + 65.0f * t);

	membrosDireito[Membro::BRACO]->rotacionar(-45 - (int)membrosDireito[Membro::BRACO]->obterAngulo());
	membrosDireito[Membro::ANTEBRACO]->rotacionar(-45 - (int)membrosDireito[Membro::ANTEBRACO]->obterAngulo());
	membrosEsquerdo[Membro::BRACO]->rotacionar(alvoBraco - (int)membrosEsquerdo[Membro::BRACO]->obterAngulo());
	membrosEsquerdo[Membro::ANTEBRACO]->rotacionar(alvoAnte - (int)membrosEsquerdo[Membro::ANTEBRACO]->obterAngulo());
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

		if (exibeCirculoColisao)
			circuloColisao->desenhar();

	glPopMatrix();
}