#include "AnalistaXML.h"

#include <stdexcept>

AnalistaXML::AnalistaXML(const char* arquivoXML) {
	if (documentoXML.LoadFile(arquivoXML))
		throw invalid_argument("documento SVG inválido ou não encontrado");
	const char* tagRaiz = documentoXML.RootElement()->Name();
	obterListaElementosFilhos(documentoXML.FirstChildElement(tagRaiz), tagRaiz);	
}

void
AnalistaXML::obterListaElementosFilhos(XMLNode* noRaiz, const char* tagRaiz) {
	if (strcmp(((XMLElement*)noRaiz)->Name(), tagRaiz))
		elementos.push_back((XMLElement*)noRaiz);
	if (!noRaiz->NoChildren())
		obterListaElementosFilhos(noRaiz->FirstChild(), tagRaiz);
	if (noRaiz->NextSibling())
		obterListaElementosFilhos(noRaiz->NextSibling(), tagRaiz);
}

void
AnalistaXML::configurar(Cenario& cenario) {
	for (auto elemento : elementos)
		if (!strcmp(elemento->Name(), CENARIO))
			cenario.inicializar(atoi(elemento->Attribute("width")), atoi(elemento->Attribute("height")), obterCor(elemento->Attribute("fill")));
		else if (!strcmp(elemento->Name(), JOGADOR))
			cenario.inserir(new Jogador(atoi(elemento->Attribute("cx")), atoi(elemento->Attribute("cy")), atoi(elemento->Attribute("r")), obterCor(elemento->Attribute("fill"))));
}

Cor*
AnalistaXML::obterCor(const char* nomeCor) {
	if (!strcmp(nomeCor, "red"))
		return (new Cor(255.0f, 0.0f, 0.0f));
	else if (!strcmp(nomeCor, "green"))
		return (new Cor(0.0f, 255.0f, 0.0f));
	else if (!strcmp(nomeCor, "blue"))
		return (new Cor(0.0f, 0.0f, 255.0f));
	return (new Cor(0.0f, 0.0f, 0.0f));
}