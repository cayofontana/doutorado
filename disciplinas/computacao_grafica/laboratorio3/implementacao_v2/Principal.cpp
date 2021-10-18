#include <iostream>

#include "Cenario.h"

int
main(int argc, char** argv) {
	if (argc != 7) {
		std::cout << "Erro!" << std::endl;
		std::cout << "Use: ./laboratorio3 <largura_janela> <altura_janela> <largura_cenário> <altura_cenário> <posição_janela_x> <posição_janela_y>" << std::endl;
		
		return (-1);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(atoi(argv[1]), atoi(argv[2])); 
	glutInitWindowPosition(atoi(argv[5]), atoi(argv[6]));
	glutCreateWindow(argv[0]);
	Cenario::obterInstancia().inicializar(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	glutDisplayFunc(Cenario::obterInstancia().exibir);
	glutKeyboardFunc(Cenario::obterInstancia().pressionarTecla);
	glutKeyboardUpFunc(Cenario::obterInstancia().liberarTecla);
	glutIdleFunc(Cenario::obterInstancia().ociar);
	glutMainLoop();

	return (0);
}