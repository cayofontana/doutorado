#include "infraestrutura/AnalisadorXML.h"
#include "Cenario.h"

#include <iostream>

using namespace std;

int
main(int argc, char** argv) {
	if (argc != 4) {
		cerr << "Erro: " << endl;
		cerr << "Use ./trabalhocg <endereco_arquivo_xml> <posição_janela_x> <posição_janela_y>" << endl;
		return (-1);
	}

	Cenario& cenario = Cenario::obterInstancia();	
	try {
		AnalisadorXML analisadorXML(argv[1]);
		analisadorXML.configurar(cenario);
	}
	catch (const invalid_argument& excecao) {
		cerr << "Erro: " << excecao.what() << endl;
		return (-5);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(atoi(argv[2]), atoi(argv[3]));
	glutInitWindowSize(cenario.obterLargura(), cenario.obterAltura()); 
	glutCreateWindow(argv[0]);
	cenario.inicializar();
	glutDisplayFunc(cenario.exibir);
	glutKeyboardFunc(cenario.pressionarTecla);
	glutKeyboardUpFunc(cenario.liberarTecla);
	glutMouseFunc(cenario.clicar);
	glutIdleFunc(cenario.ociar);
	glutMainLoop();
	return (0);
}