#include "infraestrutura/AnalistaXML.h"
#include "Cenario.h"

#include <iostream>

using namespace std;

int
main(int argc, char** argv) {
	if (argc != 4) {
		cerr << "Erro: " << endl;
		cerr << "Use ./trabalho2D <endereco_arquivo_xml> <posição_janela_x> <posição_janela_y>" << endl;
		return (-1);
	}

	try {
		AnalistaXML analistaXML(argv[1]);
		analistaXML.configurar(Cenario::obterInstancia());
	}
	catch (const invalid_argument& excecao) {
		cerr << "Erro: " << excecao.what() << endl;
		return (-5);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(Cenario::obterInstancia().obterLargura(), Cenario::obterInstancia().obterAltura()); 
	glutInitWindowPosition(atoi(argv[2]), atoi(argv[3]));
	glutCreateWindow(argv[0]);
	glutDisplayFunc(Cenario::obterInstancia().exibir);
	glutKeyboardFunc(Cenario::obterInstancia().pressionarTecla);
	glutKeyboardUpFunc(Cenario::obterInstancia().liberarTecla);
	glutIdleFunc(Cenario::obterInstancia().ociar);
	glutMainLoop();
	return (0);
}