#ifndef COR_H
#define COR_H

class Cor {
public:
	Cor(float, float, float);

	float obterVermelho(void);
	void definirVermelho(float);
	float obterVerde(void);
	void definirVerde(float);
	float obterAzul(void);
	void definirAzul(float);

private:
	float vermelho;
	float verde;
	float azul;
};

#endif