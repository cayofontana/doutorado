#ifndef ANALISADORXML_H
#define ANALISADORXML_H

#include "../modelo/primitivas/Cor.h"
#include "../Cenario.h"

#include <vector>
#include <tinyxml2.h>

using namespace std;
using namespace tinyxml2;

#define CENARIO "rect"
#define JOGADOR "circle"

class AnalisadorXML {
public:
	AnalisadorXML(const char*);
	virtual ~AnalisadorXML() = default;

	void obterListaElementosFilhos(XMLNode*, const char*);
	void configurar(Cenario&);

private:
	XMLDocument documentoXML;
	vector<XMLElement*> elementos;
	
	Cor* obterCor(const char*);
};

#endif