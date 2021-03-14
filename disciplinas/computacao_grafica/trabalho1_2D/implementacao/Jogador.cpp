#include "Jogador.h"

Jogador::Jogador(Cenario& cenario, int xAbsoluto, int yAbsoluto, int raioCabeca, Cor* cor) {
	cabeca = new Circunferencia(xAbsoluto - cenario.obterLargura() / 2, cenario.obterAltura() / 2 - yAbsoluto, raioCabeca, cor, 0.1f, 1.0f);
	nariz =  new Circunferencia(raioCabeca * 0.8f, raioCabeca * 0.8f, raioCabeca * 0.2f, cor, 0.1f, 1.0f);
	membrosEsquerdo.insert(std::pair<Membro, Retangulo*>(Membro::BRACO, new Retangulo(raioCabeca, raioCabeca, 60.0f, 10.0f, new Cor(0.6f, 0.6f, 0.0f))));
	membrosEsquerdo.insert(std::pair<Membro, Retangulo*>(Membro::ANTEBRACO, new Retangulo(raioCabeca, raioCabeca, 60.0f, 10.0f, new Cor(0.6f, 0.6f, 0.0f))));
	membrosDireito.insert(std::pair<Membro, Retangulo*>(Membro::BRACO, new Retangulo(raioCabeca, raioCabeca, 60.0f, 10.0f, new Cor(0.6f, 0.6f, 0.0f))));
	membrosDireito.insert(std::pair<Membro, Retangulo*>(Membro::ANTEBRACO, new Retangulo(raioCabeca, raioCabeca, 60.0f, 10.0f, new Cor(0.6f, 0.6f, 0.0f))));
	luva =  new Circunferencia(0, 0, raioCabeca * 0.4f, new Cor(cabeca->obterPixel().obterCor().obterVermelho() > 0.0f ? 0.0f : 1.0f, cabeca->obterPixel().obterCor().obterVerde() > 0.0f ? 0.0f : 1.0f, cabeca->obterPixel().obterCor().obterAzul() > 0.0f ? 0.0f : 1.0f), 0.1f, 1.0f);
}

Jogador::~Jogador() {
	delete cabeca;
	delete nariz;
	for (auto par : membrosEsquerdo)
		delete par.second;
	for (auto par : membrosDireito)
		delete par.second;
	delete luva;
}

void
Jogador::desenhar(void) {
	glLoadIdentity();
	glPushMatrix(); {
		glTranslatef(cabeca->obterDeslocamentoHorizontal(), cabeca->obterDeslocamentoVertical(), 0.0f);
		glRotatef(cabeca->obterAngulo() - 45.0f, 0.0f, 0.0f, 1.0f);
		glPushMatrix(); {
			glTranslatef(nariz->obterDeslocamentoHorizontal(), nariz->obterDeslocamentoVertical(), 0.0f);
			nariz->desenhar();
		}
		glPopMatrix();
		glPushMatrix(); {
			Retangulo* bracoEsquerdo = membrosEsquerdo[Membro::BRACO];
			glRotatef(bracoEsquerdo->obterAngulo() - 45.0f, 0.0f, 0.0f, 1.0f);
			glTranslatef(-bracoEsquerdo->obterDeslocamentoHorizontal(), 0.0f, 0.0f);
			glPushMatrix(); {
				glRotatef(bracoEsquerdo->obterAngulo() + 45.0f, 0.0f, 0.0f, 1.0f);
				glTranslatef(-bracoEsquerdo->obterDeslocamentoHorizontal() * 0.8, 0.0f, 0.0f);
				bracoEsquerdo->desenhar();
				Retangulo* anteBracoEsquerdo = membrosEsquerdo[Membro::ANTEBRACO];
				glPushMatrix(); {
					glTranslatef(-anteBracoEsquerdo->obterDeslocamentoHorizontal(), 0.0f, 0.0f);
					glRotatef(anteBracoEsquerdo->obterAngulo() + 45.0f, 0.0f, 0.0f, 1.0f);
					glTranslatef(anteBracoEsquerdo->obterDeslocamentoHorizontal(), 0.0f, 0.0f);
					anteBracoEsquerdo->desenhar();
					glPushMatrix(); {
						glTranslatef(anteBracoEsquerdo->obterDeslocamentoHorizontal(), 0.0f, 0.0f);
						luva->desenhar();
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
						luva->desenhar();
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

void 
Jogador::transladar(float deslocamentoHorizontal, float deslocamentoVertical) {
	cabeca->transladar(deslocamentoHorizontal, deslocamentoVertical);
}

void
Jogador::rotacionar(int angulo) {
	cabeca->rotacionar(angulo);
}