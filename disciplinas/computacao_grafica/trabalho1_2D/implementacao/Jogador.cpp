#include "Jogador.h"

#include <cmath>
using namespace std;

Jogador::Jogador(Cenario& cenario, int xAbsoluto, int yAbsoluto, int raioCabeca, Cor* cor) : Circunferencia(xAbsoluto - cenario.obterLargura() / 2, cenario.obterAltura() / 2 - yAbsoluto, 0, nullptr, 0.0f, 0.0f) {
	rotacionar(xAbsoluto < cenario.obterLargura() / 2 ? -45.0f : 135.0f);

	cabeca = new Circunferencia(0, 0, raioCabeca, cor, 0.1f, 1.0f);
	definirRaio(obterRaio() + raioCabeca);

	nariz = new Circunferencia(0, 0, raioCabeca * 0.2f, cor, 0.1f, 1.0f);
	definirRaio(obterRaio() + raioCabeca * 0.8f);

	membrosEsquerdo.insert(pair<Membro, Retangulo*>(Membro::BRACO, new Retangulo(raioCabeca, raioCabeca, 60.0f, 10.0f, new Cor(0.6f, 0.6f, 0.0f))));
	definirRaio(obterRaio() + membrosEsquerdo[Membro::BRACO]->obterBase() * sin(45));
	membrosEsquerdo.insert(pair<Membro, Retangulo*>(Membro::ANTEBRACO, new Retangulo(raioCabeca, raioCabeca, 60.0f, 10.0f, new Cor(0.6f, 0.6f, 0.0f))));
	definirRaio(obterRaio() + membrosEsquerdo[Membro::ANTEBRACO]->obterBase() * sin(45));
	
	membrosDireito.insert(pair<Membro, Retangulo*>(Membro::BRACO, new Retangulo(raioCabeca, raioCabeca, 60.0f, 10.0f, new Cor(0.6f, 0.6f, 0.0f))));
	membrosDireito.insert(pair<Membro, Retangulo*>(Membro::ANTEBRACO, new Retangulo(raioCabeca, raioCabeca, 60.0f, 10.0f, new Cor(0.6f, 0.6f, 0.0f))));

	luvaEsquerda = new Circunferencia(0, 0, raioCabeca * 0.4f, new Cor(cabeca->obterPixel().obterCor().obterVermelho() > 0.0f ? 0.0f : 1.0f, cabeca->obterPixel().obterCor().obterVerde() > 0.0f ? 0.0f : 1.0f, cabeca->obterPixel().obterCor().obterAzul() > 0.0f ? 0.0f : 1.0f), 0.1f, 1.0f);
	luvaDireita = new Circunferencia(0, 0, raioCabeca * 0.4f, new Cor(cabeca->obterPixel().obterCor().obterVermelho() > 0.0f ? 0.0f : 1.0f, cabeca->obterPixel().obterCor().obterVerde() > 0.0f ? 0.0f : 1.0f, cabeca->obterPixel().obterCor().obterAzul() > 0.0f ? 0.0f : 1.0f), 0.1f, 1.0f);
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
Jogador::socar(bool socou) {
	this->socou = socou;
}

void
Jogador::desenhar(void) {
	glLoadIdentity();
	glPushMatrix(); {
		glTranslatef(this->obterDeslocamentoHorizontal(), this->obterDeslocamentoVertical(), 0.0f);
		glRotatef(this->obterAngulo(), 0.0f, 0.0f, 1.0f);
		glPushMatrix(); {
			glTranslatef(cabeca->obterRaio() * 0.8f, cabeca->obterRaio() * 0.8f, 0.0f);
			nariz->desenhar();
		}
		glPopMatrix();
		glPushMatrix(); {
			Retangulo* bracoEsquerdo = membrosEsquerdo[Membro::BRACO];
			glRotatef(bracoEsquerdo->obterAngulo() - 45.0f, 0.0f, 0.0f, 1.0f);
			glTranslatef(-bracoEsquerdo->obterDeslocamentoHorizontal(), 0.0f, 0.0f);
			glPushMatrix(); {
				glRotatef(bracoEsquerdo->obterAngulo() + socou ? -45.0f : 45.0f, 0.0f, 0.0f, 1.0f);
				glTranslatef(-bracoEsquerdo->obterDeslocamentoHorizontal() * 0.8, 0.0f, 0.0f);
				bracoEsquerdo->desenhar();
				Retangulo* anteBracoEsquerdo = membrosEsquerdo[Membro::ANTEBRACO];
				glPushMatrix(); {
					glTranslatef(-anteBracoEsquerdo->obterDeslocamentoHorizontal(), 0.0f, 0.0f);
					glRotatef(anteBracoEsquerdo->obterAngulo() + socou ? 105.0f : 45.0f, 0.0f, 0.0f, 1.0f);
					glTranslatef(anteBracoEsquerdo->obterDeslocamentoHorizontal(), 0.0f, 0.0f);
					anteBracoEsquerdo->desenhar();
					glPushMatrix(); {
						glTranslatef(anteBracoEsquerdo->obterDeslocamentoHorizontal(), 0.0f, 0.0f);
						luvaEsquerda->desenhar();
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix(); {
			Retangulo* bracoDireito = membrosDireito[Membro::BRACO];
			glRotatef(bracoDireito->obterAngulo() - 45.0f, 0.0f, 0.0f, 1.0f);
			glTranslatef(bracoDireito->obterDeslocamentoHorizontal(), 0.0f, 0.0f);
			glPushMatrix(); {
				glRotatef(bracoDireito->obterAngulo() - 45.0f, 0.0f, 0.0f, 1.0f);
				glTranslatef(bracoDireito->obterDeslocamentoHorizontal() * 0.8, 0.0f, 0.0f);
				bracoDireito->desenhar();
				Retangulo* anteBracoDireito = membrosDireito[Membro::ANTEBRACO];
				glPushMatrix(); {
					glTranslatef(anteBracoDireito->obterDeslocamentoHorizontal(), 0.0f, 0.0f);
					glRotatef(anteBracoDireito->obterAngulo() - 45.0f, 0.0f, 0.0f, 1.0f);
					glTranslatef(-anteBracoDireito->obterDeslocamentoHorizontal(), 0.0f, 0.0f);
					anteBracoDireito->desenhar();
					glPushMatrix(); {
						glTranslatef(-anteBracoDireito->obterDeslocamentoHorizontal(), 0.0f, 0.0f);
						luvaDireita->desenhar();
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
		cabeca->desenhar();
	}
	glPopMatrix();
}