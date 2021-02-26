#include <iostream>

#include "View.h"

int
main(int argc, char** argv) {
	if (argc != 5) {
		std::cout << "Erro!" << std::endl;
		std::cout << "Usage: ./lab1 <window_width> <window_height> <window_position_x> <window_position_y>" << std::endl;
		
		return (-1);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(atoi(argv[1]), atoi(argv[2])); 
	glutInitWindowPosition(atoi(argv[3]), atoi(argv[4]));
	glutCreateWindow(argv[0]);
	View::getInstance().initialize(atoi(argv[1]), atoi(argv[2]));
	glutKeyboardFunc(View::getInstance().keyPress);
	glutKeyboardUpFunc(View::getInstance().keyUp);	
	glutMouseFunc(View::getInstance().mouseClick);
	glutMotionFunc(View::getInstance().mouseClickMotion);
	glutDisplayFunc(View::getInstance().display);
	glutIdleFunc(View::getInstance().idle);
	glutMainLoop();

	return (0);
}