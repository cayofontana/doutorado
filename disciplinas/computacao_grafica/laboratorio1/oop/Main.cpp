#include "View.h"

int
main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(atoi(argv[1]), atoi(argv[2])); 
	glutInitWindowPosition(atoi(argv[3]), atoi(argv[4]));
	glutCreateWindow("Lab 1");
	View::getInstance().initialize();
	glutDisplayFunc(View::getInstance().display);
	glutKeyboardFunc(View::getInstance().keyPress);
    glutKeyboardUpFunc(View::getInstance().keyUp);
	glutIdleFunc(View::getInstance().idle);
	glutMainLoop();

	return (0);
}